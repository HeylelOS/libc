#ifndef OS_DEFINITIONS_TIMEVAL_H
#define OS_DEFINITIONS_TIMEVAL_H

#include <os/definitions/time_t.h>
#include <os/definitions/suseconds_t.h>

struct timeval {
	time_t      tv_sec;  /* Seconds. */
	suseconds_t tv_usec; /* Microseconds. */
};

/* OS_DEFINITIONS_TIMEVAL_H */
#endif
