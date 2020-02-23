#ifndef OS_DEFINITIONS_TMS_H
#define OS_DEFINITIONS_TMS_H

#include <os/definitions/clock_t.h>

struct tms {
	clock_t tms_utime;  /* User CPU time. */
	clock_t tms_stime;  /* System CPU time. */
	clock_t tms_cutime; /* User CPU time of terminated child processes. */
	clock_t tms_cstime; /* System CPU time of terminated child processes. */
};

/* OS_DEFINITIONS_TMS_H */
#endif
