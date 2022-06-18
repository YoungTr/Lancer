//
// Created by YoungTr on 2022/6/18.
//

#ifndef STRACE_ST_TRACE_H
#define STRACE_ST_TRACE_H

#ifdef __cplusplus
extern "C" {
#endif

#define STRACE_LIB_CUTILS                       "/system/lib64/libcutils.so"
#define STRACE_LIB_CUTILS_ENABLETAGS            "atrace_enabled_tags"
#define STRACE_LIB_CUTILS_ATRACE_MAKER_FD       "atrace_marker_fd"






void enable_trace_tag();


#ifdef __cplusplus
}
#endif

#endif //STRACE_ST_TRACE_H
