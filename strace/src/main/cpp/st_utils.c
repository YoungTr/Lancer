//
// Created by YoungTr on 2022/6/18.
//

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "st_utils.h"

int util_read_file_line(const char *path, char *buf, size_t len) {
    int fd;
    int r = 0;

    if (0 > (fd = TEMP_FAILURE_RETRY(open(path, O_RDONLY | O_CLOEXEC)))) {
        r = ERRNO_SYS;
        goto end;
    }

    if (NULL == util_gets(buf, len, fd)) {
        r = ERRNO_SYS;
        goto end;
    }

    end:
    if (fd >= 0) close(fd);
    return r;
}

int util_get_process_thread_name(const char *path, char *buf, size_t len) {
    char tmp[256], *data;
    size_t data_len, cpy_len;
    int r;

    if (0 != (r = util_read_file_line(path, tmp, sizeof(tmp)))) return r;

    data = util_trim(tmp);
    if (0 == (data_len = strlen(data))) return ERRNO_SYS;
    cpy_len = UTIL_MIN(len - 1, data_len);
    memcpy(buf, data, cpy_len);
    buf[cpy_len] = '\0';
    return 0;
}

void util_get_thread_name(pid_t tid, char *buf, size_t len) {
    char path[128];
    snprintf(path, sizeof(path), "/proc/%d/comm", tid);

    if (0 != util_get_process_thread_name(path, buf, len)) {
        strncpy(buf, "unknown", len);
    }
}

char *util_gets(char *s, size_t size, int fd) {
    ssize_t i, nread;
    char c, *p;

    if (fd < 0 || NULL == s || size < 2) return NULL;

    s[0] = '\0';
    p = s;
    for (i = 0; i < size - 1; ++i) {
        if (1 == (nread = read(fd, &c, 1))) {
            *p++ = c;
            if ('\n' == c) break;
        } else if (0 == nread) break;
        else {
            if (errno != EINTR) return NULL;
        }
    }
    *p = '\0';
    return ('\0' == s[0] ? NULL : s);
}

char *util_trim(char *start) {
    char *end;

    if (NULL == start) return NULL;

    end = start + strlen(start);
    if (start == end) return start;

    while (start < end && isspace((int) (*start))) start++;
    if (start == end) return start;

    while (start < end && isspace((int) (*(end - 1)))) end--;
    *end = '\0';
    return start;
}

uint64_t get_system_nanosecond() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t) ts.tv_sec * 1000 * 1000 * 1000 + (uint64_t) ts.tv_nsec;
}



