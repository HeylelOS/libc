#include "dyld_elf64.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

int
main(int argc, char *argv[]) {
	struct dyld_elf64_image image;

	while(getopt(argc, argv, "") != -1);

	if(argc - optind > 0) {
		// Command line version, ignore auxiliary vectors
		const char * const path = argv[optind];
		int execfd = open(path, O_RDONLY);
		dyld_elf64_error_t error;

		if(execfd < 0) {
			err(-1, "unable to open %s", path);
		}

		error = dyld_elf64_image_init_fd(&image, getpagesize(), execfd);
		if(error != DYLD_ELF64_ERROR_NONE) {
			errx(-1, "dynamic linker error, unable to load %s", path);
		}

		error = dyld_elf64_image_objects_resolve(&image);
		if(error != DYLD_ELF64_ERROR_NONE) {
			errx(-1, "dynamic linker error, unable to resolve %s", path);
		}

		error = dyld_elf64_image_objects_relocate(&image);
		if(error != DYLD_ELF64_ERROR_NONE) {
			errx(-1, "dynamic linker error, unable to relocate %s", path);
		}

		close(execfd);

		dyld_elf64_image_control_transfer(&image);

		errx(-1, "dynamic linker error, unable to transfer control to %s", path);
	} else {
		fprintf(stderr, "usage: %s program [arguments...]\n", *argv);
		return -1;
	}
}

