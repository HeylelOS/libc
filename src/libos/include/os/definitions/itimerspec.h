#ifndef OS_DEFINITIONS_ITIMERSPEC_H
#define OS_DEFINITIONS_ITIMERSPEC_H

#include <os/definitions/timespec.h>

struct itimerspec {
	struct timespec it_interval; /* Timer period. */
	struct timespec it_value;    /* Timer expiration. */
};

/* OS_DEFINITIONS_ITIMERSPEC_H */
#endif
