//
// Created by YoungTr on 2022/6/18.
//

#ifndef LANCER_LAN_UTILS_H
#define LANCER_LAN_UTILS_H

#include <stddef.h>
#include <sys/types.h>
#include <ctype.h>
#include <inttypes.h>
#include <time.h>
#include "string.h"


#ifdef __cplusplus
extern "C" {
#endif

#define UTIL_MIN(a,b) ({         \
            __typeof__ (a) _a = (a); \
            __typeof__ (b) _b = (b); \
            _a < _b ? _a : _b; })

int util_read_file_line(const char *path, char *buf, size_t len);


int util_get_process_thread_name(const char *path, char *buf, size_t len);


char *util_gets(char *s, size_t size, int fd);

/**
 * 去除 [start] 前后的空格字符
 */
char *util_trim(char *start);

void util_get_thread_name(pid_t tid, char *buf, size_t len);

uint64_t get_system_nanosecond();

int util_mkdirs(const char *dir);

#ifdef __cplusplus
}
#endif

#endif //LANCER_LAN_UTILS_H
