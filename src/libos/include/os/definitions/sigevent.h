#ifndef OS_DEFINITIONS_SIGEVENT_H
#define OS_DEFINITIONS_SIGEVENT_H

#include <os/definitions/sigval.h>
#include <os/definitions/pthread_attr_t.h>

struct sigevent {
	int              sigev_notify;                         /* Notification type. */
	int              sigev_signo;                          /* Signal number. */
	union sigval     sigev_value;                          /* Signal value. */
	void           (*sigev_notify_function)(union sigval); /* Notification function. */
	pthread_attr_t  *sigev_notify_attributes;              /* Notification attributes. */
};

/* OS_DEFINITIONS_SIGEVENT_H */
#endif
