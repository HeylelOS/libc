#ifndef _DLFCN_H
#define _DLFCN_H

/* dlfcn.h - dynamic linking */

#define RTLD_LAZY
#define RTLD_NOW
#define RTLD_GLOBAL
#define RTLD_LOCAL

int   dlclose(void *);
char *dlerror(void);
void *dlopen(const char *, int);
void *dlsym(void *restrict, const char *restrict);

/* _DLFCN_H */
#endif
