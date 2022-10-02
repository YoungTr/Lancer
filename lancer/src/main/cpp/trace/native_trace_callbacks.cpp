//
// Created by YoungTr on 2022/10/2.
//

#include "native_trace_callbacks.h"
#include "../log.h"

namespace swan {
namespace lancer {

void NativeTraceCallbacks::OnTraceStart(int64_t trace_id, int32_t flags, std::string trace_file) {
    LOGD("OnTraceStart: trace_id=%ld, flags=%d, trace_file=%s",
          trace_id, flags, (char*)trace_file.c_str());
}

void NativeTraceCallbacks::OnTraceEnd(int64_t trace_id) {
    LOGD("OnTraceEnd: trace_id=%ld", trace_id);
}

void NativeTraceCallbacks::OnTraceAbort(int64_t trace_id, AbortReason reason) {
    LOGD("OnTraceAbort: trace_id=%ld, abort reason=%d", trace_id, reason);
}

}
}