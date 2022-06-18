//
// Created by YoungTr on 2022/6/18.
//

#include <string.h>
#include "lan_jni.h"
#include "log.h"
#include "lan_trace.h"

int st_api_level = 0;
char *st_trace_file = NULL;

static jint st_jni_init(JNIEnv *env, jobject this, jint app_level, jstring trace_file) {
    st_api_level = app_level;
    st_trace_file = strdup((*env)->GetStringUTFChars(env, trace_file, 0));

    LOGD("app_level: %d, trace_file: %s", st_api_level, st_trace_file);

    enable_trace_tag();

    return 0;
}

static const JNINativeMethod TRACE_METHODS[] = {
        {"nativeInit", "(ILjava/lang/String;)I", (void *) st_jni_init}
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jclass cls;
    (void) reserved;

    if (NULL == vm) return -1;

    // register JNI methods
    if (JNI_OK != (*vm)->GetEnv(vm, (void **) &env, ST_JNI_VERSION)) return -1;
    if (NULL == env || NULL == *env) return -1;
    if (NULL == (cls = (*env)->FindClass(env, ST_JNI_CLASS_NAME))) return -1;
    if ((*env)->RegisterNatives(env, cls, TRACE_METHODS,sizeof(TRACE_METHODS) / sizeof(TRACE_METHODS[0]))) return -1;

    return ST_JNI_VERSION;

}