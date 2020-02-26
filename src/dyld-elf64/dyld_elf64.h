#ifndef DYLD_ELF64_DYLD_ELF64_H
#define DYLD_ELF64_DYLD_ELF64_H

#include <sys/types.h>

typedef enum {
	DYLD_ELF64_ERROR_NONE,

	DYLD_ELF64_ERROR_OBJECT_INVALID_EXECFD,
	DYLD_ELF64_ERROR_OBJECT_INVALID_IDENT,
	DYLD_ELF64_ERROR_OBJECT_INVALID_MACHINE,
	DYLD_ELF64_ERROR_OBJECT_INVALID_VERSION,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_DYNAMIC,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_INTERP,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_SHLIB,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_UNEXPECTED_PHDR,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_INVALID_ALIGN,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_INVALID_ALIGNMENT_REQUIREMENT,
	DYLD_ELF64_ERROR_OBJECT_INVALID_PHDR_EXPECTED_PHDR,

} dyld_elf64_error_t;

struct dyld_elf64_image {
	struct {
		struct dyld_elf64_object *base;  /* table of dynamic shared objects */
		size_t                    count; /* number of entries in base */
		size_t                    size;  /* capacity of base in bytes */
	} objects;
	size_t pagesize;
};

dyld_elf64_error_t
dyld_elf64_image_init_fd(struct dyld_elf64_image *image, size_t pagesize, int execfd);

dyld_elf64_error_t
dyld_elf64_image_objects_resolve(struct dyld_elf64_image *image);

dyld_elf64_error_t
dyld_elf64_image_objects_relocate(struct dyld_elf64_image *image);

void
dyld_elf64_image_control_transfer(struct dyld_elf64_image *image);

/* DYLD_ELF64_DYLD_ELF64_H */
#endif
