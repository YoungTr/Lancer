//
// Created by YoungTr on 2022/10/2.
//

#ifndef LANCER_NATIVE_TRACE_CALLBACKS_H
#define LANCER_NATIVE_TRACE_CALLBACKS_H

#include <writer/TraceCallbacks.h>
#include <cstdint>
#include <string>

namespace swan {
namespace lancer {
using TraceCallbacks = facebook::profilo::writer::TraceCallbacks;
using AbortReason = facebook::profilo::writer::AbortReason;

struct NativeTraceCallbacks : public TraceCallbacks {
    void OnTraceStart(int64_t trace_id, int32_t flags, std::string trace_file);

    void OnTraceEnd(int64_t trace_id);

    void OnTraceAbort(int64_t trace_id, AbortReason reason);
};

}
}

#endif //LANCER_NATIVE_TRACE_CALLBACKS_H
