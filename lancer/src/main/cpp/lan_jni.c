//
// Created by YoungTr on 2022/6/18.
//

#include <string.h>
#include "log.h"
#include "lan_jni.h"
#include "lan_trace.h"

static jint lan_jni_init(JNIEnv *env, jobject this, jint app_level, jstring trace_file) {
    int r;
    lan_api_level = app_level;
    const char *trace_dir = (*env)->GetStringUTFChars(env, trace_file, 0);
    r = lan_trace_init(app_level, trace_dir);
    return r;
}

static void lan_jni_enable_trace(JNIEnv *env, jobject this) {
    LOGD("lan_jni_enable_trace");
    lan_trace_enable();
}

static void lan_jni_disable_trace(JNIEnv *env, jobject this) {
    lan_trace_disable();
}


static const JNINativeMethod TRACE_METHODS[] = {
        {"nativeInit",    "(ILjava/lang/String;)I", (void *) lan_jni_init},
        {"enableLancer",  "()V",                    (void *) lan_jni_enable_trace},
        {"disableLancer", "()V",                    (void *) lan_jni_disable_trace}
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jclass cls;
    (void) reserved;

    if (NULL == vm) return -1;

    // register JNI methods
    if (JNI_OK != (*vm)->GetEnv(vm, (void **) &env, LANCER_JNI_VERSION)) return -1;
    if (NULL == env || NULL == *env) return -1;
    if (NULL == (cls = (*env)->FindClass(env, LANCER_JNI_CLASS_NAME))) return -1;
    if ((*env)->RegisterNatives(env, cls, TRACE_METHODS,
                                sizeof(TRACE_METHODS) / sizeof(TRACE_METHODS[0])))
        return -1;

    return LANCER_JNI_VERSION;

}