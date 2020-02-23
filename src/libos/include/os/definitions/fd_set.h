#ifndef OS_DEFINITIONS_FD_SET_H
#define OS_DEFINITIONS_FD_SET_H

typedef struct {
	unsigned char fds_bits[512];
} fd_set;

/* OS_DEFINITIONS_FD_SET_H */
#endif
