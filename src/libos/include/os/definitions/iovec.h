#ifndef OS_DEFINITIONS_IOVEC_H
#define OS_DEFINITIONS_IOVEC_H

#include <os/definitions/size_t.h>

struct iovec {
	void  *iov_base; /* Base address of a memory region for input or output. */
	size_t iov_len;  /* The size of the memory pointed to by iov_base. */
};

/* OS_DEFINITIONS_IOVEC_H */
#endif
