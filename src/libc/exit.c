#include <unistd.h>

void _NORETURN
exit(int status) {

	_exit(status);
}

