#ifndef _DIRENT_H
#define _DIRENT_H

/* dirent.h - format of directory entries */

/* Definitions */
#include <_definitions/DIR.h>
#include <_definitions/dirent.h>

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
#include <_definitions/ino_t.h>

void seekdir(DIR *, long);
long telldir(DIR *);
#endif

/* _DIRENT_H */
#endif
