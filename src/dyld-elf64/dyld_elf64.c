#include "dyld_elf64.h"
#include "elf64.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <strings.h>

struct dyld_elf64_context {
	unsigned long pagesize;
	uid_t         uid;
	uid_t         euid;
	gid_t         gid;
	gid_t         egid;
};

struct dyld_elf64_dso {
	struct {
		struct Elf64_Phdr *table;
		Elf64_Word         count;
		Elf64_Word         size;
	} header;
	Elf64_Addr         base;
	Elf64_Addr         entry;
	Elf64_Word         flags;
};

#define PN_CLAMP(n) ((n)>PN_XNUM?PN_XNUM:(n))

static const unsigned char elf64_expected_ident[] = {
	ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3, ELFCLASS64, ELFDATA2LSB, EV_CURRENT
};

static dyld_elf64_error_t
dyld_elf64_dso_init(struct dyld_elf64_dso *program, int fd) {
	const struct Elf64_Ehdr *elfheader;
	struct stat st;

	if(fstat(fd, &st) != 0
		|| (elfheader = mmap(0, st.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		return DYLD_ELF64_ERROR_FILE_INVALID_EXECFD;
	}

	if(bcmp(elfheader->e_ident, elf64_expected_ident, sizeof(elf64_expected_ident)) != 0) {
		return DYLD_ELF64_ERROR_FILE_INVALID_IDENT;
	}

	/* TODO: Check supported e_target */

	if(elfheader->e_machine != EM_X86_64) {
		return DYLD_ELF64_ERROR_FILE_INVALID_MACHINE;
	}

	if(elfheader->e_version != EV_CURRENT) {
		return DYLD_ELF64_ERROR_FILE_INVALID_VERSION;
	}

	program->entry        = elfheader->e_entry;
	program->header.table = (struct Elf64_Phdr *)((Elf64_Addr)elfheader + elfheader->e_phoff);
	program->flags        = elfheader->e_flags;
	program->header.size  = elfheader->e_phentsize;
	program->header.count = PN_CLAMP(elfheader->e_phnum);
	program->base         = 0;

	return DYLD_ELF64_ERROR_NONE;
}

static dyld_elf64_error_t
dyld_elf64_dso_link(const struct dyld_elf64_dso *program,
	const struct dyld_elf64_context *context) {

	/* TODO */

	return DYLD_ELF64_ERROR_UNIMPLEMENTED;
}

#define AUXV_MAPED_PRESET (1 << AT_PHDR | 1 << AT_PHENT \
	| 1 << AT_PHNUM | 1 << AT_PHDR | 1 << AT_FLAGS)

static dyld_elf64_error_t
dyld_elf64_init(struct dyld_elf64_dso *program,
	struct dyld_elf64_context *context,
	auxv_t const *auxv) {
	int initialized = 0;
	int execfd;

	bzero(program, sizeof(*program));
	bzero(context, sizeof(*context));

	while(auxv->a_type != AT_NULL) {
		switch(auxv->a_type) {
		case AT_EXECFD:
			execfd = auxv->a_un.a_val;
			break;
		case AT_PHDR:
			program->header.table = auxv->a_un.a_ptr;
			break;
		case AT_PHENT:
			program->header.size = auxv->a_un.a_val;
			break;
		case AT_PHNUM:
			program->header.count = PN_CLAMP(auxv->a_un.a_val);
			break;
		case AT_PAGESZ:
			context->pagesize = auxv->a_un.a_val;
			break;
		case AT_BASE:
			program->base = (Elf64_Addr)auxv->a_un.a_ptr;
			break;
		case AT_FLAGS:
			program->flags = auxv->a_un.a_val;
			break;
		case AT_ENTRY:
			program->entry = (Elf64_Addr)auxv->a_un.a_ptr;
			break;
		case AT_NOTELF:
			if(auxv->a_un.a_val != 0) {
				return DYLD_ELF64_ERROR_INIT_NOTELF;
			}
			break;
		case AT_UID:
			context->uid = auxv->a_un.a_val;
			break;
		case AT_EUID:
			context->euid = auxv->a_un.a_val;
			break;
		case AT_GID:
			context->gid = auxv->a_un.a_val;
			break;
		case AT_EGID:
			context->egid = auxv->a_un.a_val;
			break;
		}

		initialized |= 1 << auxv->a_type;
		auxv++;
	}

	if((initialized & 1 << AT_PAGESZ) == 0) {
		context->pagesize = getpagesize();
	}

	if((initialized & 1 << AT_UID) == 0) {
		context->uid = getuid();
	}

	if((initialized & 1 << AT_EUID) == 0) {
		context->euid = geteuid();
	}

	if((initialized & 1 << AT_GID) == 0) {
		context->gid = getgid();
	}

	if((initialized & 1 << AT_EGID) == 0) {
		context->egid = getegid();
	}

	if((initialized & 1 << AT_EXECFD) != 0) {
		return dyld_elf64_dso_init(program, execfd);
	} else if((initialized & AUXV_MAPED_PRESET) != AUXV_MAPED_PRESET) {
		return DYLD_ELF64_ERROR_INIT_MISSING_AUXILIARY_VECTOR;
	} else {
		return DYLD_ELF64_ERROR_NONE;
	}
}

dyld_elf64_error_t
dyld_elf64(dyld_elf64_entry_t *entry,
	long argc, char *argv[],
	char *environ[], auxv_t auxv[]) {
	struct dyld_elf64_context context;
	struct dyld_elf64_dso program;
	dyld_elf64_error_t error;

	if((error = dyld_elf64_init(&program, &context, auxv)) == DYLD_ELF64_ERROR_NONE
		&& (error = dyld_elf64_dso_link(&program, &context)) == DYLD_ELF64_ERROR_NONE) {
		*entry = (dyld_elf64_entry_t)program.entry;
	}

	return error;
}

