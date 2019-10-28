#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* The following is the log2 of the medium threshold - log2 of small threshold + 1 */
#define MALLOC_MEDIUMPOOL_SIZE 13
#define MALLOC_OVERHEAD sizeof(size_t)

#define MALLOC_SMALL_THRESHOLD 0x80
#define MALLOC_SMALLPOOL_EXTEND_BASE 0x1000

#define MALLOC_MEDIUM_FIRST_EXPONENT 8
#define MALLOC_MEDIUM_THRESHOLD 0x100000
#define MALLOC_MEDIUMPOOL_EXTEND_BASE MALLOC_MEDIUM_THRESHOLD

struct malloc_arena {
	void *smallpool;
	void *mediumpool[MALLOC_MEDIUMPOOL_SIZE];

	size_t smallexponent;
	size_t mediumexponent;
};

static inline void *
malloc_allocation_mark(size_t *ptr, size_t size) {
	*ptr = size;

	return ptr + 1;
}

static inline size_t
malloc_allocation(size_t * restrict ptr, void ** restrict allocation) {
	if(ptr == NULL) {
		return 0;
	}

	*allocation = --ptr;

	return *ptr;
}

static size_t 
malloc_smallpool_extend(struct malloc_arena *arena) {
	const size_t size = MALLOC_SMALLPOOL_EXTEND_BASE << arena->smallexponent;
	void * const mmaped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if(mmaped != MAP_FAILED) {
		void **iterator = mmaped, *allocationend = (uint8_t *)mmaped + size;

		while((*iterator = (uint8_t *)iterator + MALLOC_SMALL_THRESHOLD) < allocationend) {
			iterator = *iterator;
		}

		*iterator = NULL;

		arena->smallpool = mmaped;
		arena->smallexponent++;

		return size;
	} else {
		return 0;
	}
}

static void *
malloc_small(struct malloc_arena *arena, size_t size) {
	void **allocation;

	if(arena->smallpool == NULL
		&& malloc_smallpool_extend(arena) == 0) {
		return NULL;
	}

	allocation = arena->smallpool;
	arena->smallpool = *allocation;

	return malloc_allocation_mark((size_t *)allocation, size);
}

static void
free_small(struct malloc_arena *arena, void **allocation) {

	*allocation = arena->smallpool;
	arena->smallpool = allocation;
}

static inline size_t
malloc_medium_powerof2(size_t value) {
	size_t power = 0;
	value--;

	do {
		power++;
	} while((value >>= 1) != 0);

	return power;
}

static size_t 
malloc_mediumpool_extend(struct malloc_arena *arena) {
	const size_t size = MALLOC_MEDIUMPOOL_EXTEND_BASE << arena->mediumexponent;
	void * const mmaped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if(mmaped != MAP_FAILED) {
		void **iterator = mmaped, *allocationend = (uint8_t *)mmaped + size;

		while((*iterator = (uint8_t *)iterator + MALLOC_MEDIUM_THRESHOLD) < allocationend) {
			iterator = *iterator;
		}

		*iterator = NULL;

		arena->mediumpool[MALLOC_MEDIUMPOOL_SIZE - 1] = mmaped;
		arena->mediumexponent++;

		return size;
	} else {
		return 0;
	}
}

static void *
malloc_medium(struct malloc_arena *arena, size_t size) {
	const size_t power = malloc_medium_powerof2(size) - MALLOC_MEDIUM_FIRST_EXPONENT;
	size_t index = power;
	void **allocation;

	while(index < MALLOC_MEDIUMPOOL_SIZE
		&& arena->mediumpool[index] == NULL) {
		index++;
	}

	if(index == MALLOC_MEDIUMPOOL_SIZE
		&& (--index, malloc_mediumpool_extend(arena) == 0)) {
		return NULL;
	}

	while(index > power) {
		void **first = arena->mediumpool[index];
		void **buddy = (void **)((uint8_t *)first + (1 << (index - 1 + MALLOC_MEDIUM_FIRST_EXPONENT)));

		arena->mediumpool[index] = *first;
		index--;

		*buddy = arena->mediumpool[index];
		*first = buddy;
		arena->mediumpool[index] = first;
	}

	allocation = arena->mediumpool[index];
	arena->mediumpool[index] = *allocation;

	return malloc_allocation_mark((size_t *)allocation, size);
}

static void
free_medium(struct malloc_arena *arena, void *allocation, size_t size) {
	size_t index = malloc_medium_powerof2(size) - MALLOC_MEDIUM_FIRST_EXPONENT;
	void **ptr = allocation;
	void **iterator;

	do {
		void **buddy = (void **)((uintptr_t)ptr ^ (1 << index));

		iterator = &arena->mediumpool[index];

		while(iterator != NULL && *iterator != buddy) {
			iterator = *iterator;
		}

		if(iterator != NULL) {
			*iterator = *buddy;
			ptr = (void **)((uintptr_t)ptr & ~(1 << index));
			index++;
		}
	} while(iterator != NULL && index < MALLOC_MEDIUMPOOL_SIZE);

	*ptr = arena->mediumpool[index];
	arena->mediumpool[index] = ptr;
}

static void *
malloc_huge(size_t size) {
	void * const mmaped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if(mmaped != MAP_FAILED) {
		return malloc_allocation_mark(mmaped, size);
	} else {
		return NULL;
	}
}

static void
free_huge(void *allocation, size_t size) {
	munmap(allocation, size);
	/* TODO: Error check ? */
}

_Thread_local struct malloc_arena arena;

void *
malloc(size_t size) {
	size += MALLOC_OVERHEAD;

	/* TODO: Add pthread_cleanup_push to cleanse thread's arena */

	if(size > MALLOC_MEDIUM_THRESHOLD) {
		return malloc_huge(size);
	} else if(size > MALLOC_SMALL_THRESHOLD) {
		return malloc_medium(&arena, size);
	} else if(size > MALLOC_OVERHEAD) {
		return malloc_small(&arena, size);
	}

	return NULL;
}

void *
realloc(void *ptr, size_t size) {

	/* TODO: Not se foutre de la gueule du monde */

	if(size != 0) {
		if(ptr != NULL) {
			void *oldallocation;
			const size_t oldsize = malloc_allocation(ptr, &oldallocation);
			void *newallocation = malloc(size);

			if(newallocation != NULL) {
				memcpy(newallocation, ptr, oldsize);
				return newallocation;
			}
		} else {
			return malloc(size);
		}
	} else {
		free(ptr);
	}

	return NULL;
}

void
free(void *ptr) {
	if(ptr != NULL) {
		void *allocation;
		const size_t size = malloc_allocation(ptr, &allocation);

		if(size > MALLOC_MEDIUM_THRESHOLD) {
			free_huge(allocation, size);
		} else if(size > MALLOC_SMALL_THRESHOLD) {
			free_medium(&arena, allocation, size);
		} else if(size > MALLOC_OVERHEAD) {
			free_small(&arena, allocation);
		} /* else error, should we check? */
	}
}

