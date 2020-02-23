#ifndef OS_DEFINITIONS_POLLFD_H
#define OS_DEFINITIONS_POLLFD_H

struct pollfd {
	int fd;        /* The following descriptor being polled. */
	short events;  /* The input event flags (see below). */
	short revents; /* The output event flags (see below). */
};

/* OS_DEFINITIONS_POLLFD_H */
#endif
