#ifndef OS_DEFINITIONS_SIGACTION_H
#define OS_DEFINITIONS_SIGACTION_H

#include <os/definitions/siginfo_t.h>
#include <os/definitions/sigset_t.h>

struct sigaction {
	union {
		void (*sa_handler)(int);                        /* Pointer to a signal-catching function 
		                                                   or one of the SIG_IGN or SIG_DFL. */
		void (*sa_sigaction)(int, siginfo_t *, void *); /* Pointer to a signal-catching function. */
	};                       
	sigset_t sa_mask;                                   /* Set of signals to be blocked during execution 
	                                                       of the signal handling function. */
	int sa_flags;                                       /* Special flags. */
};

/* OS_DEFINITIONS_SIGACTION_H */
#endif
