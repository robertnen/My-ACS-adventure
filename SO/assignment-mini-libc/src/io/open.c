// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...) {
	va_list args;
	va_start(args, flags);

	mode_t mode = 0; // default choice is 0
	int fd;

	// create file if it doesn't exists and get the permissions
	if (flags & O_CREAT) mode = va_arg(args, mode_t);

	va_end(args);

	fd = syscall(__NR_open, filename, flags, mode);

	switch(fd) {
		case -ENOENT: // no file or dir
			errno = ENOENT;
			return -1;

		case -EACCES: // no acces
			errno = EACCES;
			return -1;

		case -ENOTDIR: // not dir
			errno = ENOTDIR;
			return -1;

		case -EFBIG: // the file is too big
			errno = EFBIG;
			return -1;

		case -EISDIR: // dir
			errno = EISDIR;
			return -1;

		case -EEXIST: // the file exists
			errno = EEXIST;
			return -1;

		default: // no errors, incredible
			return fd;
	}
}
