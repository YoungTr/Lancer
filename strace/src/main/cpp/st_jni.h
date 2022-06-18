//
// Created by YoungTr on 2022/6/18.
//

#ifndef STRACE_ST_JNI_H
#define STRACE_ST_JNI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

#define ST_JNI_VERSION    JNI_VERSION_1_6
#define ST_JNI_CLASS_NAME "com/bomber/strace/STrace"

extern int st_api_level;
extern char *st_trace_file;

#ifdef __cplusplus
}
#endif

#endif //STRACE_ST_JNI_H
