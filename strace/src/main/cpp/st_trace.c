//
// Created by YoungTr on 2022/6/18.
//

#include <dlfcn.h>
#include <unistd.h>
#include "st_trace.h"
#include "log.h"
#include "xhook.h"

static uint64_t original_tags = -1;
static uint64_t *atrace_enable_tags = NULL;

static int *atrace_maker_fd = NULL;

static int need_write_systrace(int fd, size_t count) {
    return (fd == *atrace_maker_fd && count > 0) ? 0 : 1;
}

ssize_t (*original_write)(int fd, const void *const __pass_object_size0 buf, size_t count);

ssize_t my_write(int fd, const void *const buf, size_t count) {
    if (0 == need_write_systrace(fd, count)) {
        const char *msg = buf;
        LOGD("%s", msg);
    }
    return original_write(fd, buf, count);
}

void hookLibc() {
    xhook_register(".*libc\\.so$", "write", (void *) my_write, (void **) (&original_write));
    xhook_refresh(1);
}

void enable_trace_tag() {
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
