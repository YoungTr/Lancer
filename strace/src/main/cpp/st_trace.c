//
// Created by YoungTr on 2022/6/18.
//

#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/stat.h>
#include "st_utils.h"
#include "st_trace.h"
#include "log.h"
#include "xhook.h"
#include "st_jni.h"

static uint64_t original_tags = -1;
static uint64_t *atrace_enable_tags = NULL;

static int *atrace_maker_fd = NULL;

static int trace_fd = -1;
static struct timeval tv;

static int need_write_systrace(int fd, size_t count) {
    return (fd == *atrace_maker_fd && count > 0) ? 0 : 1;
}

void write_trace(const void *buf, size_t count) {
    const char *trace = buf;
    gettimeofday(&tv, NULL);
    double f = tv.tv_sec;
    char content[1024];
    char thread[256];
    int len;
    util_get_thread_name(gettid(), thread, sizeof(thread));
    switch (trace[0]) {
        case 'B':
            len = snprintf(content, sizeof(content),
                           "%s-%d [000] ...1 %.6f: tracing_mark_write: %s\n", thread, gettid(), f,
                           trace);
            write(trace_fd, content, len);
            break;
        case 'E':
            len = snprintf(content, sizeof(content),"%s-%d [000] ...1 %.6f: tracing_mark_write: E\n", thread, gettid(), f);
            write(trace_fd, content, len);
            break;
        default:
            return;
    }

}

ssize_t (*original_write)(int fd, const void *const __pass_object_size0 buf, size_t count);

ssize_t my_write(int fd, const void *const buf, size_t count) {
    if (0 == need_write_systrace(fd, count)) {
        write_trace(buf, count);
    }
    return original_write(fd, buf, count);
}

void hookLibc() {
    xhook_register(".*libc\\.so$", "write", (void *) my_write, (void **) (&original_write));
    xhook_refresh(1);
}

void enable_trace_tag() {

    // todo
    mkdir("/data/user/0/com.bomber.strace/files/trace", S_IRWXU);

    trace_fd = open(st_trace_file, COMMON_OPEN_NEW_FILE_FLAGS, COMMON_OPEN_NEW_FILE_MODE);

    LOGD("trace_fd: %d, %s", trace_fd, st_trace_file);

    void *handle;

    if (NULL == (handle = dlopen(NULL, RTLD_GLOBAL))) return;
    if (NULL == (atrace_enable_tags = dlsym(handle, STRACE_LIB_CUTILS_ENABLETAGS))) {
        LOGE("dl sym error: %s", STRACE_LIB_CUTILS_ENABLETAGS);
        goto err;
    }

    original_tags = *atrace_enable_tags;

    *atrace_enable_tags = UINT64_MAX;
    if (NULL == (atrace_maker_fd = dlsym(handle, STRACE_LIB_CUTILS_ATRACE_MAKER_FD))) {
        LOGE("dl sym error: %s", STRACE_LIB_CUTILS_ATRACE_MAKER_FD);
        goto err;
    }

    // todo pthread_create
    hookLibc();

    return;


  err:
    dlclose(handle);
    handle = NULL;

}

void disable_trace_tag() {
    if (NULL != atrace_enable_tags) {
        *atrace_enable_tags = original_tags;
    }
}
