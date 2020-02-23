#ifndef _DIRENT_H
#define _DIRENT_H

/* dirent.h - format of directory entries */

#ifdef _POSIX_EXTENSION_XSI
#include <_definitions/ino_t.h>
#endif

typedef struct _DIR DIR;

struct dirent {
#ifdef _POSIX_EXTENSION_XSI
	ino_t d_ino;   /* File serial number. */
#endif
	char d_name[]; /* Filename string of entry. */
};

int            alphasort(const struct dirent **, const struct dirent **);
int            closedir(DIR *);
int            dirfd(DIR *);
DIR           *fdopendir(int);
DIR           *opendir(const char *);
struct dirent *readdir(DIR *);
int            readdir_r(DIR *restrict, struct dirent *restrict, struct dirent **restrict);
void           rewinddir(DIR *);
int            scandir(const char *, struct dirent ***, int (*)(const struct dirent *), int (*)(const struct dirent **, const struct dirent **));

#ifdef _POSIX_EXTENSION_XSI
void seekdir(DIR *, long);
long telldir(DIR *);
#endif

/* _DIRENT_H */
#endif
