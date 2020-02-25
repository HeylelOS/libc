#ifndef DYLD_ELF64_DYLD_ELF64_H
#define DYLD_ELF64_DYLD_ELF64_H

#include <os/definitions/auxv_t.h>

typedef enum {
	DYLD_ELF64_ERROR_NONE,
	DYLD_ELF64_ERROR_INIT_NOTELF,
	DYLD_ELF64_ERROR_INIT_MISSING_AUXILIARY_VECTOR,
	DYLD_ELF64_ERROR_FILE_INVALID_EXECFD,
	DYLD_ELF64_ERROR_FILE_INVALID_IDENT,
	DYLD_ELF64_ERROR_FILE_INVALID_MACHINE,
	DYLD_ELF64_ERROR_FILE_INVALID_VERSION,

	DYLD_ELF64_ERROR_UNIMPLEMENTED,
} dyld_elf64_error_t;

typedef int (*dyld_elf64_entry_t)(int, char*[], char*[]);

dyld_elf64_error_t
dyld_elf64(dyld_elf64_entry_t *entry,
	long argc, char *argv[],
	char *environ[], auxv_t auxv[]);

/* DYLD_ELF64_DYLD_ELF64_H */
#endif
