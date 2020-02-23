#ifndef OS_DEFINITIONS_UTSNAME_H
#define OS_DEFINITIONS_UTSNAME_H

struct utsname {
	char  sysname[9];  /* Name of this implementation of the operating system. */
	char  nodename[9]; /* Name of this node within the communications
	                      network to which this node is attached, if any. */
	char  release[9];  /* Current release level of this implementation. */
	char  version[9];  /* Current version level of this release. */
	char  machine[9];  /* Name of the hardware type on which the system is running. */
};

/* OS_DEFINITIONS_UTSNAME_H */
#endif
