#ifndef OS_DEFINITIONS_TIMESPEC_H
#define OS_DEFINITIONS_TIMESPEC_H

#include <os/definitions/time_t.h>

struct timespec {
	time_t tv_sec;  /* Seconds. */
	long   tv_nsec; /* Nanoseconds. */
};

/* OS_DEFINITIONS_TIMESPEC_H */
#endif
