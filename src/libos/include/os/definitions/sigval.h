#ifndef OS_DEFINITIONS_SIGVAL_H
#define OS_DEFINITIONS_SIGVAL_H

union sigval {
	int   sival_int; /* Integer signal value. */
	void *sival_ptr; /* Pointer signal value. */
};

/* OS_DEFINITIONS_SIGVAL_H */
#endif
