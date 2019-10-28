#ifndef _AIO_H
#define _AIO_H

/* aio.h - asynchronous input and output */

/* As in <sys/types.h> */
#include <_definitions/off_t.h>
#include <_definitions/pthread_attr_t.h>
#include <_definitions/size_t.h>
#include <_definitions/ssize_t.h>

/* As in <time.h> */
#include <_definitions/timespec.h>

/* As in <signal.h> */
#include <_definitions/sigevent.h>
#include <_definitions/sigval.h>

/* Definitions */
#include <_definitions/aiocb.h>

#define AIO_ALLDONE
#define AIO_CANCELED
#define AIO_NOTCANCELED

#define LIO_NOP
#define LIO_NOWAIT
#define LIO_READ
#define LIO_WAIT
#define LIO_WRITE

int     aio_cancel(int, struct aiocb *);
int     aio_error(const struct aiocb *);
int     aio_read(struct aiocb *);
ssize_t aio_return(struct aiocb *);
int     aio_suspend(const struct aiocb *const [], int, const struct timespec *);
int     aio_write(struct aiocb *);
int     lio_listio(int, struct aiocb *restrict const [restrict], int, struct sigevent *restrict);

#if defined(_POSIX_EXTENSION_FSC) || defined(_POSIX_EXTENSION_SIO)
int aio_fsync(int, struct aiocb *);
#endif

/* _AIO_H */
#endif
