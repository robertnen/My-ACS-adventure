/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

typedef long long time_t;

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

unsigned int sleep(unsigned int seconds);
unsigned int nanosleep(const struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif
