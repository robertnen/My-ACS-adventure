// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length) {
    int ret = syscall(__NR_truncate, path, length);

	if (length < 0) { // length is invalid
		errno = EINVAL;
		return -1;
	}

    if (ret < 0) { // it didn't work
		errno = -ret;
		return -1;
	}

    return ret;
}
