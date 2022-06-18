//
// Created by YoungTr on 2022/6/18.
//

#ifndef STRACE_ST_TRACE_H
#define STRACE_ST_TRACE_H

#ifdef __cplusplus
extern "C" {
#endif

#define COMMON_OPEN_NEW_FILE_FLAGS (O_CREAT | O_WRONLY | O_CLOEXEC | O_TRUNC | O_APPEND)
#define COMMON_OPEN_NEW_FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) //644

#define STRACE_LIB_CUTILS                       "/system/lib64/libcutils.so"
#define STRACE_LIB_CUTILS_ENABLETAGS            "atrace_enabled_tags"
#define STRACE_LIB_CUTILS_ATRACE_MAKER_FD       "atrace_marker_fd"


void enable_trace_tag();

void disable_trace_tag();


#ifdef __cplusplus
}
#endif

#endif //STRACE_ST_TRACE_H
