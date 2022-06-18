//
// Created by YoungTr on 2022/6/18.
//

#include <dlfcn.h>
#include "st_trace.h"
#include "log.h"

static uint64_t original_atrace_enalble_tags = -1;
static uint64_t *atrace_enable_tags = NULL;

static int *atrace_maker_fd = NULL;

void enable_trace_tag() {
    void *handle;

    if (NULL == (handle = dlopen(NULL, RTLD_GLOBAL))) return;
    if (NULL == (atrace_enable_tags = dlsym(handle, STRACE_LIB_CUTILS_ENABLETAGS))) {
        LOGE("dl sym error: %s", STRACE_LIB_CUTILS_ENABLETAGS);
        goto err;
    }

    original_atrace_enalble_tags = *atrace_enable_tags;

    *atrace_enable_tags = UINT64_MAX;
    if (NULL == (atrace_maker_fd = dlsym(handle, STRACE_LIB_CUTILS_ATRACE_MAKER_FD))) {
        LOGE("dl sym error: %s", STRACE_LIB_CUTILS_ATRACE_MAKER_FD);
        goto err;
    }

    LOGD("fd: %d", *atrace_maker_fd);

    return;


  err:
    dlclose(handle);
    handle = NULL;

}

void disable_trace_tag() {
    if (NULL != atrace_enable_tags) {
        *atrace_enable_tags = original_atrace_enalble_tags;
    }
}
