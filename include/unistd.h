#ifndef _UNISTD_H
#define _UNISTD_H

#include <_extensions.h>

#include <sys/types.h>

/* Definition of NULL as a zero pointer */
#define NULL ((void *)0)

void	_exit(int) _NORETURN;
ssize_t	write(int, const void *, size_t);

/* _UNISTD_H */
#endif
