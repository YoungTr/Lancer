//
// Created by YoungTr on 2022/9/29.
//
#include "trace_provider.h"
#include "../log.h"

namespace swan {
namespace lancer {

TraceProvider &TraceProvider::Get() {
    static TraceProvider kInstance;
    return kInstance;
}

void TraceProvider::SetBufferSize(size_t buffer_size) {
    buffer_size_ = buffer_size;
}

size_t TraceProvider::GetBufferSize() const {
    return buffer_size_;
}

void TraceProvider::SetTraceFolder(const std::string &trace_folder) {
    trace_folder_ = trace_folder;
}

bool TraceProvider::IsMainThreadOnly() const {
    return is_main_thread_only_;
}

void TraceProvider::SetIsMainThreadOnly(bool only) {
    is_main_thread_only_ = only;
}

void TraceProvider::SetMainThreadId(pid_t tid) {
   main_thread_id_ = tid;
}

pid_t TraceProvider::GetMainThreadId() const {
        return main_thread_id_;
}

const std::string &TraceProvider::GetTraceFolder() {
    return trace_folder_;
}
}
}