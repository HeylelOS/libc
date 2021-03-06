#ifndef _AIO_H
#define _AIO_H

/* aio.h - asynchronous input and output */

/* As in <sys/types.h> */
#include <os/definitions/off_t.h>
#include <os/definitions/pthread_attr_t.h>
#include <os/definitions/size_t.h>
#include <os/definitions/ssize_t.h>

/* As in <time.h> */
#include <os/definitions/timespec.h>

/* As in <signal.h> */
#include <os/definitions/sigevent.h>
#include <os/definitions/sigval.h>

struct aiocb {
	int             aio_fildes;     /* File descriptor. */
	off_t           aio_offset;     /* File offset. */
	volatile void  *aio_buf;        /* Location of buffer. */
	size_t          aio_nbytes;     /* Length of transfer. */
	int             aio_reqprio;    /* Request priority offset. */
	struct sigevent aio_sigevent;   /* Signal number and value. */
	int             aio_lio_opcode; /* Operation to be performed. */
};

#define AIO_ALLDONE     0
#define AIO_CANCELED    1
#define AIO_NOTCANCELED 2

#define LIO_NOP    0
#define LIO_NOWAIT 1
#define LIO_READ   2
#define LIO_WAIT   3
#define LIO_WRITE  4

int     aio_cancel(int, struct aiocb *);
int     aio_error(const struct aiocb *);
int     aio_read(struct aiocb *);
ssize_t aio_return(struct aiocb *);
int     aio_suspend(const struct aiocb *const [], int, const struct timespec *);
int     aio_write(struct aiocb *);
int     lio_listio(int, struct aiocb *restrict const [restrict], int, struct sigevent *restrict);

#if defined(_POSIX_EXTENSION_FSC) && defined(_POSIX_EXTENSION_SIO)
int aio_fsync(int, struct aiocb *);
#endif

/* _AIO_H */
#endif
