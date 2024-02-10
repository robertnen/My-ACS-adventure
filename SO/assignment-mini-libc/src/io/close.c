// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd) {
	int ret = syscall(__NR_close, fd);

    if (ret == -1) errno = EINVAL;

    return ret;
}
