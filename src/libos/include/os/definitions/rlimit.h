#ifndef OS_DEFINITIONS_RLIMIT_H
#define OS_DEFINITIONS_RLIMIT_H

#include <os/definitions/rlim_t.h>

struct rlimit {
	rlim_t rlim_cur; /* The current (soft) limit.  */
	rlim_t rlim_max; /* The hard limit. */
};

/* OS_DEFINITIONS_RLIMIT_H */
#endif
