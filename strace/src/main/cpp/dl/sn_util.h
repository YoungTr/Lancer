//
// Created by YoungTr on 2022/4/14.
//

#ifndef SWAN_SN_UTIL_H
#define SWAN_SN_UTIL_H

#include <stdint.h>
#include <sys/types.h>
#include <inttypes.h>
#include <signal.h>
#include <sys/syscall.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SWAN_UTIL_TEMP_FAILURE_RETRY(exp) ({         \
            __typeof__(exp) _rc;                    \
            do {                                    \
                errno = 0;                          \
                _rc = (exp);                        \
            } while (_rc == -1 && errno == EINTR);  \
            _rc; })

char *util_trim(char *start);

#ifdef __cplusplus
}
#endif

#endif //SWAN_SN_UTIL_H
