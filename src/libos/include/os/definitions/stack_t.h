#ifndef OS_DEFINITIONS_STACK_T_H
#define OS_DEFINITIONS_STACK_T_H

#include <os/definitions/size_t.h>

typedef struct {
	void   *ss_sp;    /* Stack base or pointer. */
	size_t  ss_size;  /* Stack size. */
	int     ss_flags; /* Flags. */
} stack_t;

/* OS_DEFINITIONS_STACK_T_H */
#endif
