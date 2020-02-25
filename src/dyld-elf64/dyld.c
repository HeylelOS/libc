#include "dyld_elf64.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

extern char **environ;

int
main(int argc, char **argv) {

	while(getopt(argc, argv, "") != -1);

	if(argc - optind > 0) {
		const char * const program = argv[optind];
		auxv_t auxvs[] = {
			{ .a_type = AT_EXECFD, .a_un = { .a_val = open(program, O_RDONLY) } },
			{ .a_type = AT_NULL }
		};
		dyld_elf64_entry_t entry;

		if(auxvs->a_un.a_val < 0) {
			err(-1, "unable to open %s", program);
		}

		if(dyld_elf64(&entry, argc, argv, environ, auxvs) != DYLD_ELF64_ERROR_NONE) {
			errx(-1, "dynamic linker error, unable to load %s", program);
		}

		close(auxvs->a_un.a_val);

		return entry(argc, argv, environ);
	} else {
		fprintf(stderr, "usage: %s program [arguments...]\n", *argv);
		return -1;
	}
}

