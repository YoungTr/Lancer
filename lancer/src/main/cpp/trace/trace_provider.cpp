//
// Created by YoungTr on 2022/9/29.
//
#include "trace_provider.h"

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

const std::string &TraceProvider::GetTraceFolder() {
    return trace_folder_;
}


}
}