#ifndef _FCNTL_H
#define _FCNTL_H

/* fcntl.h - file control options */

/* As in <stdio.h> */
#include <_definitions/SEEK_SET.h>
#include <_definitions/SEEK_CUR.h>
#include <_definitions/SEEK_END.h>

/* As in <sys/stat.h> */
#include <_definitions/S_IRWXA.h> /* Symbolic constants for file modes */

/* As in <sys/types.h> */
#include <_definitions/mode_t.h>
#include <_definitions/off_t.h>
#include <_definitions/pid_t.h>

#define F_DUPFD
#define F_DUPFD_CLOEXEC
#define F_GETFD
#define F_SETFD
#define F_GETFL
#define F_SETFL
#define F_GETLK
#define F_SETLK
#define F_SETLKW
#define F_GETOWN
#define F_SETOWN

#define FD_CLOEXEC

#define F_RDLCK
#define F_WRLCK
#define F_WRLCK

#define O_CLOEXEC
#define O_CREAT
#define O_DIRECTORY
#define O_EXCL
#define O_NOCTTY
#define O_NOFOLLOW
#define O_TRUNC
#define O_TTY_INIT

#define O_APPEND
#define O_DSYNC
#define O_NONBLOCK
#define O_RSYNC
#define O_SYNC

#define O_ACCMODE

#define O_EXEC
#define O_RDONLY
#define O_RDWR
#define O_SEARCH
#define O_WRONLY

#define AT_FDCWD

#define AT_EACCESS

#define AT_SYMLINK_NOFOLLOW

#define AT_SYMLINK_FOLLOW

#define AT_REMOVEDIR

#ifdef _POSIX_EXTENSION_ADV
#define POSIX_FADV_DONTNEED
#define POSIX_FADV_NOREUSE
#define POSIX_FADV_NORMAL
#define POSIX_FADV_RANDOM
#define POSIX_FADV_SEQUENTIAL
#define POSIX_FADV_WILLNEED
#endif

struct flock {
	short l_type;   /* Type of the lock; F_RDLCK, F_WRLCK, F_UNLCK. */
	short l_whence; /* Flag for starting offset. */
	off_t l_start;  /* Relative offset in bytes. */
	off_t l_len;    /* Size; if 0 then until EOF. */
	pid_t l_pid;    /* Process ID of the process holding the lock; returned with F_GETLK. */
};

int creat(const char *, mode_t);
int fcntl(int, int, ...);
int open(const char *, int, ...);
int openat(int, const char *, int, ...);
#ifdef _POSIX_EXTENSION_ADV
int posix_fadvise(int, off_t, off_t, int);
int posix_fallocate(int, off_t, off_t);
#endif

/* _FCNTL_H */
#endif
