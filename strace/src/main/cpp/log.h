//
// Created by YoungTr on 2022/4/13.
//

#ifndef STRACE_LOG_H
#define STRACE_LOG_H

#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TAG "STrace.Native"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //STRACE_LOG_H
