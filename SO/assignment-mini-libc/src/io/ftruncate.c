// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length) {
    if (fd < 0) { // invalid fd
        errno = EBADF;
        return -1;
    }

    if (length < 0) { // invalid length
        errno = EINVAL;
        return -1;
    }

    int ret = syscall(__NR_ftruncate, fd, length);

    if (ret < 0) { // it didn't work
        errno = -ret;
        return -1;
    }

    return ret;
}
