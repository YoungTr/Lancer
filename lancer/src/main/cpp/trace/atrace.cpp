//
// Created by YoungTr on 2022/9/26.
//

#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include "atrace.h"
#include "timers.h"
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
    if (atrace_started_) {
        return OK;
    }

    if (!PostCreateTrace(TraceProvider::Get().GetBufferSize())) {
        return START_WRITE_TRACE_FAILED;
    }

    atrace_started_ = true;
    return OK;
}

int32_t ATrace::StopTrace() {
    if (!atrace_started_) {
        LOGE("please start trace firstly");
        return OK;
    }

    PostFinishTrace();
    atrace_started_ = false;

    return OK;
}

void ATrace::LogTrace(const void *buf, size_t count) {
    double sec = CurrentTime();
    char tmp_buf[kAtraceMessageLen] = {0};
    int len;

    len = snprintf(tmp_buf, sizeof(tmp_buf),"%.6f: %s\n",
                   sec, (char *)buf);
    LOGD("tmp_buf content: %s", tmp_buf);
    Logger::get().writeBytes(
            EntryType::STRING_NAME,
            0,
            (const uint8_t *) tmp_buf,
            len);
}

ATrace::ATrace() = default;
ATrace::~ATrace() = default;

}
}



#pragma clang diagnostic pop