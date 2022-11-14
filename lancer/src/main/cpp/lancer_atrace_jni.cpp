//
// Created by YoungTr on 2022/9/27.
//
#include <jni.h>
#include <unistd.h>
#include "atrace.h"
#include "trace_provider.h"

#define LANCER_JNI_VERSION    JNI_VERSION_1_6
#define LANCER_JNI_CLASS_NAME "com/bomber/lancer/Lancer"

using namespace swan::lancer;

static bool SetATraceLocation(JNIEnv *env, jobject thiz, jstring traceDir) {
    if (nullptr == traceDir) {
        return false;
    }

    const char *trace_dir;
    trace_dir = env->GetStringUTFChars(traceDir, nullptr);
    TraceProvider::Get().SetTraceFolder(trace_dir);
    env->ReleaseStringUTFChars(traceDir, trace_dir);
    return true;
}

static int32_t JNI_startTrace(JNIEnv *env, jobject thiz, jstring traceDir, jlong bufferSize) {
    return ATrace::Get().StarTrace();
}

static int32_t JNI_stopTrace(JNIEnv *env, jobject thiz) {
    return ATrace::Get().StopTrace();
}

static void JNI_nativeInit(JNIEnv *env, jobject thiz, jstring trace_dir,
                                         jlong buffer_size, jboolean main_thread_only) {

    SetATraceLocation(env, thiz, trace_dir);
    TraceProvider::Get().SetBufferSize(buffer_size);
    TraceProvider::Get().SetMainThreadId(gettid());
    TraceProvider::Get().SetIsMainThreadOnly(main_thread_only);

}


static const JNINativeMethod methods[] = {
        {"startTrace", "()I",  (void *) JNI_startTrace},
        {"stopTrace",  "()I",                     (void *) JNI_stopTrace},
        {"nativeInit", "(Ljava/lang/String;JZ)V", (void *) JNI_nativeInit}
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jclass cls;
    (void) reserved;

    if (nullptr == vm) return -1;

    // register JNI methods
    if (JNI_OK != vm->GetEnv(reinterpret_cast<void **>(&env), LANCER_JNI_VERSION)) return -1;
    if (nullptr == env) return -1;
    if (nullptr == (cls = env->FindClass(LANCER_JNI_CLASS_NAME))) return -1;
    if ((env)->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]))) return -1;
    return LANCER_JNI_VERSION;
}