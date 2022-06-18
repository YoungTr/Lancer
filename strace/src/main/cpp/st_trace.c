//
// Created by YoungTr on 2022/6/18.
//

#include <sn_dl.h>
#include "st_trace.h"
#include "log.h"

void enable_trace_tag() {
    void *handle;

    uint64_t *atrace_enable_tags = NULL;
    int *atrace_maker_fd = NULL;

    if (NULL == (handle = sn_dl_create(STRACE_LIB_CUTILS))) return;
    if (NULL == (atrace_enable_tags = sn_dl_sym(handle, STRACE_LIB_CUTILS_ENABLETAGS))) {
        LOGE("dl sym error: %s", STRACE_LIB_CUTILS_ENABLETAGS);
        goto err;
    }
    if (NULL == (atrace_maker_fd = sn_dl_sym(handle, STRACE_LIB_CUTILS_ATRACE_MAKER_FD))) {
        LOGE("dl sym error: %s", STRACE_LIB_CUTILS_ATRACE_MAKER_FD);
        goto err;
    }

    LOGD("fd: %d", *atrace_maker_fd);

    return;


 err:
    sn_dl_destroy(handle);
    handle = NULL;


}