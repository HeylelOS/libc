#include "dyld_elf64.h"
#include "elf64.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <strings.h>

struct dyld_elf64_object {
	Elf64_Addr  file; /* Address of the file mapping, or zero if unknown. */
	struct {
		struct Elf64_Phdr *begin; /* Address of the program header table. */
		Elf64_Word         count; /* Number of entries in the program header table. */
		Elf64_Word         size;  /* Size of a program header entry. */
	} program_header_table;
	Elf64_Addr base;  /* Base address, zero if unknown */
	Elf64_Addr entry; /* Program entry, zero if unknown */
	Elf64_Word flags; /* Header flags */
};

/****************************
 * struct dyld_elf64_object *
 ****************************/

static const unsigned char elf64_expected_ident[] = {
	ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3, ELFCLASS64, ELFDATA2LSB, EV_CURRENT
};

static dyld_elf64_error_t
dyld_elf64_object_init(struct dyld_elf64_object *object, int execfd) {
	const struct Elf64_Ehdr *elfheader;
	struct stat st;

	if(fstat(execfd, &st) != 0
		|| (elfheader = mmap(0, st.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, execfd, 0)) == MAP_FAILED) {
		return DYLD_ELF64_ERROR_OBJECT_INVALID_EXECFD;
	}

	if(bcmp(elfheader->e_ident, elf64_expected_ident, sizeof(elf64_expected_ident)) != 0) {
		return DYLD_ELF64_ERROR_OBJECT_INVALID_IDENT;
	}

	/* TODO: Check supported e_target */

	if(elfheader->e_machine != EM_X86_64) {
		return DYLD_ELF64_ERROR_OBJECT_INVALID_MACHINE;
	}

	if(elfheader->e_version != EV_CURRENT) {
		return DYLD_ELF64_ERROR_OBJECT_INVALID_VERSION;
	}

	/* TODO: Add check for program header entry size? (fixed, greater or equals?) */

	object->file                       = (Elf64_Addr)elfheader;
	object->entry                      = elfheader->e_entry;
	object->program_header_table.begin = (struct Elf64_Phdr *)((Elf64_Addr)elfheader + elfheader->e_phoff);
	object->flags                      = elfheader->e_flags;
	object->program_header_table.size  = elfheader->e_phentsize;
	object->program_header_table.count = elfheader->e_phnum > PN_XNUM ? PN_XNUM : elfheader->e_phnum;
	object->base                       = 0;

	return DYLD_ELF64_ERROR_NONE;
}

static dyld_elf64_error_t
dyld_elf64_object_program_preview(struct dyld_elf64_object *object) {
	const struct Elf64_Phdr *current = object->program_header_table.begin,
		* const end = object->program_header_table.begin + object->program_header_table.count;
	unsigned int loadable = 0, dynamic = 0, interp = 0, phdr = 0, ignored = 0;

	while(current < end) {
		switch(current->p_type) {
		case PT_LOAD:
			loadable++;
			break;
		case PT_DYNAMIC:
			if(++dynamic > 1) {
				return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_DYNAMIC;
			}
			break;
		case PT_INTERP:
			/* should be before any loadable segment, see SysV ABI */
			if(loadable > 0 | ++interp > 1) {
				return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_INTERP;
			}
			break;
		case PT_SHLIB:
			return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_SHLIB;
		case PT_PHDR:
			if(object->file == 0) {
				const struct Elf64_Ehdr * const elfheader = (const struct Elf64_Ehdr *)
					((Elf64_Addr)object->program_header_table.begin - current->p_offset);

				object->file  = (Elf64_Addr)elfheader;
				object->entry = elfheader->e_entry;
				object->flags = elfheader->e_flags;
			}
			if(++phdr > 1) {
				return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_PHDR;
			}
			break;
		default:
			ignored++;
			break;
		}

		const Elf64_Xword alignmask = current->p_align - 1;
		if((current->p_align & alignmask) != 0) {
			return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_INVALID_ALIGN;
		}

		if((current->p_offset & alignmask) != (current->p_vaddr & alignmask)) {
			return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_INVALID_ALIGNMENT_REQUIREMENT;
		}

		current = (const struct Elf64_Phdr *)((Elf64_Addr)current + object->program_header_table.size);
	}

	if(object->file == 0) {
		return DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_EXPECTED_PHDR;
	}

	return DYLD_ELF64_ERROR_NONE;
}

/***************************
 * struct dyld_elf64_image *
 ***************************/

dyld_elf64_error_t
dyld_elf64_image_init_fd(struct dyld_elf64_image *image, size_t pagesize, int execfd) {
	image->objects.base  = mmap(0, pagesize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	image->objects.count = 1;
	image->objects.size  = pagesize;

	image->pagesize = pagesize;

	return dyld_elf64_object_init(image->objects.base, execfd);
}

dyld_elf64_error_t
dyld_elf64_image_objects_resolve(struct dyld_elf64_image *image) {
	dyld_elf64_error_t error;

	/* The indexed for-loop is important, because image->objects will change if objects are added */
	for(size_t i = 0; i < image->objects.count; i++) {
		struct dyld_elf64_object *object = image->objects.base + i;
		error = dyld_elf64_object_program_preview(object);

		if(error == DYLD_ELF64_ERROR_NONE) {
			const struct Elf64_Phdr *current = object->program_header_table.begin,
				* const end = object->program_header_table.begin + object->program_header_table.count;

			//printf("File mapping: %.16lX\n", object->file);

			while(current < end) {
				switch(current->p_type) {
				case PT_LOAD:
					//printf("PT_LOAD:\n\tp_flags:\t0x%.8X\n\tp_offset:\t0x%.16llX\n\tp_vaddr:\t0x%.16lX\n\tp_paddr:\t0x%.16lX\n\tp_filesz:\t0x%.16llX\n\tp_memsz:\t0x%.16llX\n\tp_align:\t0x%.16llX\n",
					//	current->p_flags, current->p_offset, current->p_vaddr, current->p_paddr, current->p_filesz, current->p_memsz, current->p_align);
					break;
				case PT_DYNAMIC:
					//puts("PT_DYNAMIC");
					break;
				}
	
				current = (const struct Elf64_Phdr *)((Elf64_Addr)current + object->program_header_table.size);
			}
		} else {
			break;
		}
	}

	return error;
}

dyld_elf64_error_t
dyld_elf64_image_objects_relocate(struct dyld_elf64_image *image) {
	return DYLD_ELF64_ERROR_NONE;
}

void
dyld_elf64_image_control_transfer(struct dyld_elf64_image *image) {
}

