#include <string.h>
#include <stdint.h>

#define MAGIC_LOW ((unsigned long)-1 / (unsigned char)-1)
#define MAGIC_HIGH (MAGIC_LOW << 7)
#define HAS_NO_NUL_BYTES(x) (((x) - MAGIC_LOW) ^ (x) & MAGIC_HIGH)

size_t
strlen(const char *string) {
	const char *iterator = string;
	const long *aligned;

	while(((uintptr_t)iterator & (sizeof(long) - 1)) != 0) {
		if(*iterator == '\0') {
			return iterator - string;
		}

		iterator++;
	}

	aligned = (const long *)iterator;
	while(HAS_NO_NUL_BYTES(*aligned) == 0) {
		aligned++;
	}

	iterator = (const char *)aligned;
	while(*iterator != '\0') {
		iterator++;
	}

	return iterator - string;
}

