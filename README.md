# C Library

C library intended for use in HeylelOS, shall also be used as a dynamic linker if possible. Intends to follow POSIX-2018 standard as close as possible.

## Why?

The C library is the main interface between userspace and kernel space. In theory it abstracts the kernel so that userspace binaries wouldn't mind
underlying modifications. However, C libraries in current OSes are bound to their kernel. HeylelOS intends to provide a fully opaque interface to the kernel,
so that changing the C library would allow changing the kernel without any userspace binary noticing.

## How?

By providing opaque and POSIX-compliant developments headers to the userspace, and handling syscalls-backends within the libc itself.
MUSL libc also had the wonderful idea to make the libc be the dynamic linker, so let's try that to.

## Supported formats

- [ ] elf64

## Syscalls backends

- [ ] x86\_64-linux

## Headers

- [x] aio.h
- [x] arpa/inet.h
- [x] assert.h
- [x] complex.h
- [x] cpio.h
- [ ] ctype.h
- [ ] dirent.h
- [ ] dlfcn.h
- [ ] errno.h
- [ ] fcntl.h
- [ ] fenv.h
- [ ] float.h
- [ ] fmtmsg.h
- [ ] fnmatch.h
- [ ] ftw.h
- [ ] glob.h
- [ ] grp.h
- [ ] iconv.h
- [ ] inttypes.h
- [ ] iso646.h
- [ ] langinfo.h
- [ ] libgen.h
- [ ] limits.h
- [ ] locale.h
- [ ] math.h
- [ ] monetary.h
- [ ] mqueue.h
- [ ] ndbm.h
- [ ] net/if.h
- [ ] netdb.h
- [ ] netinet/in.h
- [ ] netinet/tcp.h
- [ ] nl\_types.h
- [ ] poll.h
- [ ] pthread.h
- [ ] pwd.h
- [ ] regex.h
- [ ] sched.h
- [ ] search.h
- [ ] semaphore.h
- [ ] setjmp.h
- [ ] signal.h
- [ ] spawn.h
- [ ] stdarg.h
- [ ] stdbool.h
- [ ] stddef.h
- [ ] stdint.h
- [ ] stdio.h
- [ ] stdlib.h
- [ ] string.h
- [ ] strings.h
- [ ] stropts.h
- [ ] sys/ipc.h
- [ ] sys/mman.h
- [ ] sys/msg.h
- [ ] sys/resource.h
- [ ] sys/select.h
- [ ] sys/sem.h
- [ ] sys/shm.h
- [ ] sys/socket.h
- [ ] sys/stat.h
- [ ] sys/statvfs.h
- [ ] sys/time.h
- [ ] sys/times.h
- [ ] sys/types.h
- [ ] sys/uio.h
- [ ] sys/un.h
- [ ] sys/utsname.h
- [ ] sys/wait.h
- [ ] syslog.h
- [ ] tar.h
- [ ] termios.h
- [ ] tgmath.h
- [ ] time.h
- [ ] trace.h
- [ ] ulimit.h
- [ ] unistd.h
- [ ] utime.h
- [ ] utmpx.h
- [ ] wchar.h
- [ ] wctype.h
- [ ] wordexp.h

