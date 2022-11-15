//
// Created by YoungTr on 2022/9/26.
//

#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include "atrace.h"
#include "timers.h"
#include "hook_bridge.h"
#include "trace_provider.h"
#include "trace.h"
#include "../lan_utils.h"
#include "recoder.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
#pragma ide diagnostic ignored "ConstantFunctionResult"
namespace swan {
namespace lancer {

ATrace &ATrace::Get() {
    static ATrace kInstance;
    return kInstance;
}

int32_t ATrace::StarTrace() {
    int64_t start = elapsedRealtimeMicros();

    if (atrace_started_) {
        return OK;
    }

    if (!PostCreateTrace(TraceProvider::Get().GetBufferSize())) {
        return START_WRITE_TRACE_FAILED;
    }

    int32_t result = InstallProbe();
    if (result != OK) {
        LOGD("failed to install atrace, error: %d", result);
        return result;
    }

    auto prev = atrace_enable_tags_->exchange(DEFAULT_ATRACE_TAG);
    if (prev != UINT64_MAX) {
        original_tags_ = prev;
    }

    atrace_started_ = true;
    int64_t cost_us = elapsedRealtimeMicros() - start;
    LOGD("start trace cost us: %lld", cost_us);
    return OK;
}

int32_t ATrace::StopTrace() {
    int64_t start = elapsedRealtimeMicros();
    if (!atrace_started_) {
        LOGE("please start trace firstly");
        return OK;
    }
    uint64_t tags = original_tags_;
    if (tags != UINT64_MAX) {
        atrace_enable_tags_->store(tags);
    }

    PostFinishTrace();
    atrace_started_ = false;

    log_trace_cost_us_ = 0;
    int64_t cost_us = elapsedRealtimeMicros() - start;
    LOGD("stop trace cost us: %lld", cost_us);

    return OK;
}

bool ATrace::IsATrace(int fd, size_t count) {
   return (atrace_maker_fd_ != nullptr && fd == *atrace_maker_fd_ && count > 0);
}

void ATrace::LogTrace(const void *buf, size_t count) {
    const char *msg = (const char *) buf;
    switch (msg[0]) {
        case 'B':
        case 'E':
            break;
        default:
            return;
    }

    char tmp_buf[kAtraceMessageLen] = {0};
    int len;
    double sec = CurrentTime();
    // sec [pid]: trace
    if (TraceProvider::Get().IsMainThreadOnly()) {
        len = snprintf(tmp_buf, sizeof(tmp_buf), "%.6f: %s\n", sec, msg);
    } else {
        len = snprintf(tmp_buf, sizeof(tmp_buf), "%.6f %d: %s\n", sec, gettid(), msg);
    }

//    LOGD("tmp_buf content: %s", tmp_buf);
    Logger::get().writeBytes(
            EntryType::STRING_NAME,
            0,
            (const uint8_t *) tmp_buf,
            len);

}


// private functions
int32_t ATrace::InstallProbe() {
    if (atrace_probe_installed_) {
        return OK;
    }
    if (!HookBridge::Get().HookLoadedLibs()) {
        return HOOK_FAILED;
    }

    int32_t r = InstallAtraceProbe();
    if (r != OK) {
        return r;
    }
    
    atrace_probe_installed_ = true;
    return OK;

}

int32_t ATrace::InstallAtraceProbe() {

    void *handle;
    if (nullptr == (handle = dlopen(nullptr, RTLD_GLOBAL))) return INSTALL_ATRACE_FAILED;
    if (nullptr == (atrace_enable_tags_ = reinterpret_cast<std::atomic<uint64_t> *>(dlsym(handle,"atrace_enabled_tags")))) goto err;
    if (nullptr == (atrace_maker_fd_ =reinterpret_cast<int *>( dlsym(handle, "atrace_marker_fd")))) goto err;

    return OK;

   err:
    dlclose(handle);
    return INSTALL_ATRACE_FAILED;
}

ATrace::ATrace() = default;
ATrace::~ATrace() = default;


}
}



#pragma clang diagnostic pop