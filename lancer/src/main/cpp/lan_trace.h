//
// Created by YoungTr on 2022/6/18.
//

#ifndef LANCER_LAN_TRACE_H
#define LANCER_LAN_TRACE_H

#ifdef __cplusplus
extern "C" {
#endif

#define COMMON_OPEN_NEW_FILE_FLAGS (O_CREAT | O_WRONLY | O_CLOEXEC | O_TRUNC | O_APPEND)
#define COMMON_OPEN_NEW_FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) //644

#define LANCER_LIB_CUTILS                       "/system/lib64/libcutils.so"
#define LANCER_LIB_CUTILS_ENABLETAGS            "atrace_enabled_tags"
#define LANCER_LIB_CUTILS_ATRACE_MAKER_FD       "atrace_marker_fd"

extern int lan_api_level;
extern char *lan_trace_dir;

int lan_trace_init(const int app_level, const char *trace_dir);

void lan_trace_enable();

void lan_trace_disable();


#ifdef __cplusplus
}
#endif

#endif //LANCER_LAN_TRACE_H
