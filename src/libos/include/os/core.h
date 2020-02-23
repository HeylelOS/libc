#ifndef OS_CORE_H
#define OS_CORE_H

#include <os/definitions/clock_t.h>
#include <os/definitions/clockid_t.h>
#include <os/definitions/timespec.h>
#include <os/definitions/mode_t.h>
#include <os/definitions/uid_t.h>
#include <os/definitions/gid_t.h>
#include <os/definitions/pid_t.h>
#include <os/definitions/stat.h>
#include <os/definitions/size_t.h>
#include <os/definitions/ssize_t.h>
#include <os/definitions/rlimit.h>
#include <os/definitions/rusage.h>
#include <os/definitions/pollfd.h>
#include <os/definitions/nfds_t.h>
#include <os/definitions/fd_set.h>
#include <os/definitions/sigset_t.h>
#include <os/definitions/iovec.h>
#include <os/definitions/sigaction.h>
#include <os/definitions/siginfo_t.h>
#include <os/definitions/stack_t.h>
#include <os/definitions/sigevent.h>
#include <os/definitions/timer_t.h>
#include <os/definitions/itimerspec.h>
#include <os/definitions/tms.h>
#include <os/definitions/utsname.h>
#include <os/definitions/idtype_t.h>

/**********************************************************************
 * This header defines wrappers for core system calls implementations *
 **********************************************************************/

int     __clock_getres(clockid_t, struct timespec *);
int     __clock_gettime(clockid_t, struct timespec *);
int     __clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);
int     __clock_settime(clockid_t, const struct timespec *);
int     __close(int);
int     __dup2(int, int);
int     __dup(int);
int     __execve(const char *, char * const [], char * const []);
void    __exit(int) __attribute__((noreturn));
int     __faccessat(int, const char *, int, int);
int     __fchdir(int);
int     __fchdirat(int, const char *, int);
int     __fchmod(int, mode_t);
int     __fchmodat(int, const char *, mode_t, int);
int     __fchown(int, uid_t, gid_t);
int     __fchownat(int, const char *, uid_t, gid_t, int);
int     __fchroot(int);
int     __fchrootat(int, const char *, int);
int     __fcntl(int, int, ...);
pid_t   __fork(void);
int     __fstat(int, struct stat *);
int     __fstatat(int, const char * restrict, struct stat * restrict, int);
int     __fsync(int);
int     __ftruncate(int, off_t);
int     __ftruncateat(int, const char *, off_t, int);
int     __futimens(int, const struct timespec [2]);
int     __getpagesize(void);
int     __getpriority(int, id_t);
char   *__getcwd(char *, size_t);
gid_t   __getegid(void);
uid_t   __geteuid(void);
gid_t   __getgid(void);
pid_t   __getpgid(pid_t);
pid_t   __getpgrp(void);
pid_t   __getpid(void);
pid_t   __getppid(void);
int     __getrlimit(int, struct rlimit *);
int     __getrusage(int, struct rusage *);
pid_t   __getsid(void);
uid_t   __getuid(void);
int     __kill(pid_t, int);
int     __linkat(int, const char *, int, const char *, int);
off_t   __lseek(int, off_t, int);
int     __mkdirat(int, const char *, mode_t);
int     __mkfifoat(int, const char *, mode_t);
int     __mknodat(int, const char *, mode_t, dev_t);
void   *__mmap(void *, size_t, int, int, int, off_t);
int     __mprotect(void *, size_t, int);
int     __msync(void *, size_t, int);
int     __munmap(void *, size_t);
int     __nice(int);
int     __openat(int, const char *, int, mode_t);
int     __pipe(int [2]);
int     __poll(struct pollfd [], nfds_t, int);
ssize_t __pread(int, void *, size_t, off_t);
int     __pselect(int, fd_set * restrict, fd_set * restrict, fd_set * restrict, const struct timespec * restrict, const sigset_t * restrict);
ssize_t __pwrite(int, const void *, size_t, off_t);
ssize_t __read(int, void *, size_t);
ssize_t __readlinkat(int, const char * restrict, char * restrict, size_t);
ssize_t __readv(int, const struct iovec *, int);
int     __renameat(int, const char *, int, const char *);
int     __setegid(gid_t);
int     __seteuid(uid_t);
int     __setgid(gid_t);
int     __setpgid(pid_t, pid_t);
pid_t   __setpgrp(void);
int     __setpriority(int, id_t, int);
int     __setregid(gid_t, gid_t);
int     __setreuid(uid_t, uid_t);
int     __setrlimit(int, const struct rlimit *);
pid_t   __setsid(void);
int     __setuid(uid_t);
int     __sigaction(int, const struct sigaction * restrict, struct sigaction * restrict);
int     __sigaddset(sigset_t *, int);
int     __sigaltstack(const stack_t * restrict, stack_t * restrict);
int     __sigdelset(sigset_t *, int);
int     __sigemptyset(sigset_t *);
int     __sigfillset(sigset_t *);
int     __sigismember(const sigset_t *, int);
int     __sigpending(sigset_t *);
int     __sigprocmask(int, const sigset_t * restrict, sigset_t * restrict);
int     __sigqueue(pid_t, int, union sigval);
int     __sigsuspend(const sigset_t *);
int     __sigtimedwait(const sigset_t * restrict, siginfo_t * restrict, const struct timespec * restrict);
int     __sigwait(const sigset_t * restrict, int * restrict);
int     __sigwaitinfo(const sigset_t * restrict, siginfo_t * restrict);
int     __symlinkat(const char *, int, const char *);
int     __sync(void);
long    __sysconf(int);
int     __timer_create(clockid_t, struct sigevent * restrict, timer_t * restrict);
int     __timer_delete(timer_t);
int     __timer_getoverrun(timer_t);
int     __timer_gettime(timer_t, struct itimerspec *);
int     __timer_settime(timer_t, int, const struct itimerspec * restrict, struct itimerspec * restrict);
clock_t __times(struct tms *);
mode_t  __umask(mode_t);
int     __uname(struct utsname *);
int     __utimensat(int, const char *, const struct timespec [2], int);
pid_t   __wait(int *);
int     __waitid(idtype_t, id_t, siginfo_t *, int);
pid_t   __waitpid(pid_t, int *, int);
ssize_t __write(int, const void *, size_t);
ssize_t __writev(int, const struct iovec *, int);

/* OS_CORE_H */
#endif
