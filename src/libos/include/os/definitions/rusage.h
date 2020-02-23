#ifndef OS_DEFINITIONS_RUSAGE_H
#define OS_DEFINITIONS_RUSAGE_H

#include <os/definitions/timeval.h>

struct rusage {
	struct timeval ru_utime; /* User time used. */
	struct timeval ru_stime; /* System time used. */
};

/* OS_DEFINITIONS_RUSAGE_H */
#endif
