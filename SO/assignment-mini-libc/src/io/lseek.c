// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence) {
	if (fd == -1) { // invalid fd
		errno = EBADF;
		return -1;
	}

	if (whence < 0 || whence > 2) { // invalid whence
		errno = EINVAL;
		return -1;
	}

	if (offset < 0) { // invalid offset
		errno = EINVAL;
		return -1;
	}

	off_t result = syscall(__NR_lseek, fd, offset, whence);

    if (result == -1) errno = -EBADF;

	return result;
}
