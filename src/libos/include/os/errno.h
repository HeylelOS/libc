#ifndef OS_ERRNO_H
#define OS_ERRNO_H

#define __E2BIG           1
#define __EACCES          2
#define __EADDRINUSE      3
#define __EADDRNOTAVAIL   4
#define __EAFNOSUPPORT    5
#define __EAGAIN          6
#define __EALREADY        7
#define __EBADF           8
#define __EBADMSG         9
#define __EBUSY           10
#define __ECANCELED       11
#define __ECHILD          12
#define __ECONNABORTED    13
#define __ECONNREFUSED    14
#define __ECONNRESET      15
#define __EDEADLK         16
#define __EDESTADDRREQ    17
#define __EDOM            18
#define __EDQUOT          19
#define __EEXIST          20
#define __EFAULT          21
#define __EFBIG           22
#define __EHOSTUNREACH    23
#define __EIDRM           24
#define __EILSEQ          25
#define __EINPROGRESS     26
#define __EINTR           27
#define __EINVAL          28
#define __EIO             29
#define __EISCONN         30
#define __EISDIR          31
#define __ELOOP           32
#define __EMFILE          33
#define __EMLINK          34
#define __EMSGSIZE        35
#define __EMULTIHOP       36
#define __ENAMETOOLONG    37
#define __ENETDOWN        38
#define __ENETRESET       39
#define __ENETUNREACH     40
#define __ENFILE          41
#define __ENOBUFS         42
#define __ENODATA         43
#define __ENODEV          44
#define __ENOENT          45
#define __ENOEXEC         46
#define __ENOLCK          47
#define __ENOLINK         48
#define __ENOMEM          49
#define __ENOMSG          50
#define __ENOPROTOOPT     51
#define __ENOSPC          52
#define __ENOSR           53
#define __ENOSTR          54
#define __ENOSYS          55
#define __ENOTCONN        56
#define __ENOTDIR         57
#define __ENOTEMPTY       58
#define __ENOTRECOVERABLE 59
#define __ENOTSOCK        60
#define __ENOTSUP         61
#define __ENOTTY          62
#define __ENXIO           63
#define __EOPNOTSUPP      64
#define __EOVERFLOW       65
#define __EOWNERDEAD      66
#define __EPERM           67
#define __EPIPE           68
#define __EPROTO          69
#define __EPROTONOSUPPORT 70
#define __EPROTOTYPE      71
#define __ERANGE          72
#define __EROFS           73
#define __ESPIPE          74
#define __ESRCH           75
#define __ESTALE          76
#define __ETIME           77
#define __ETIMEDOUT       78
#define __ETXTBSY         79
#define __EWOULDBLOCK     80
#define __EXDEV           81

int *__errnop(void);

/* OS_ERRNO_H */
#endif
