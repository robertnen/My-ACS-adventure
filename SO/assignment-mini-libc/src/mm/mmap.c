// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
	if (fd > -1) { // invalid fd
		errno = EBADF;
		return MAP_FAILED;
	}

    // for some reason (flags & MAP_ANONYMOUS) doesn't work
    // and I have to write this instead
    if (flags == MAP_ANONYMOUS) {
        errno = EINVAL;
        return MAP_FAILED;
    }

	if (flags & ~(MAP_SHARED | MAP_PRIVATE | MAP_ANONYMOUS)) { // invalid flags
        errno = EINVAL;
        return MAP_FAILED;
    }

    void *mem = (void *) syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if (mem == MAP_FAILED) return MAP_FAILED;

    return mem;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags) {
    void *new = (void *) syscall(__NR_mremap, old_address, old_size, new_size, flags);

    if (new == MAP_FAILED) return MAP_FAILED;

    return new;
}

int munmap(void *addr, size_t length) {
    int ret = syscall(__NR_munmap, addr, length);

    if (ret < 0) { // it didn't work
        errno = -ret;
        return -1;
    }

    return 0; // done
}
