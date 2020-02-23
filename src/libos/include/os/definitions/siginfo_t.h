#ifndef OS_DEFINITIONS_SIGINFO_T_H
#define OS_DEFINITIONS_SIGINFO_T_H

#include <os/definitions/pid_t.h>
#include <os/definitions/uid_t.h>
#include <os/definitions/sigval.h>

typedef struct {
	int          si_signo;  /* Signal number. */
	int          si_code;   /* Signal code. */
	int          si_errno;  /* If non-zero, an errno value associated with
	                           this signal, as described in <errno.h>. */
	pid_t        si_pid;    /* Sending process ID. */
	uid_t        si_uid;    /* Real user ID of sending process. */
	void        *si_addr;   /* Address of faulting instruction. */
	int          si_status; /* Exit value or signal. */
	long         si_band;   /* Band event for SIGPOLL. */
	union sigval si_value;  /* Signal value. */
} siginfo_t;

/* OS_DEFINITIONS_SIGINFO_T_H */
#endif
