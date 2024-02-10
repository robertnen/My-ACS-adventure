#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <internal/syscall.h>

unsigned int sleep(unsigned int seconds) {
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    nanosleep(0, 0);

    int ret = syscall(__NR_nanosleep, &req, &rem);

    if (ret >= 0) return 0;

    if (errno == EINTR) { // interrupted system call
        return rem.tv_sec;
    } else {
        errno = -ret; // error
        return 0;
    }

    return 0;
}
