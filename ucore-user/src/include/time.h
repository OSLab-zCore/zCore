#ifndef __LIBS_TIME_H__
#define __LIBS_TIME_H__

#include <defs.h>

struct timespec {
    // seconds
    uint64_t tv_sec;
    // nano seconds
    uint64_t tv_nsec;
};

#endif /* !__LIBS_TIME_H__ */