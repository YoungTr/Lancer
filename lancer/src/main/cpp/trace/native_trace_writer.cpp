//
// Created by YoungTr on 2022/10/2.
//

#include <writer/trace_headers.h>
#include <writer/trace_backwards.h>
#include "native_trace_writer.h"
#include "native_trace_callbacks.h"
#include "../log.h"

namespace swan {
namespace lancer {

NativeTraceWriter::NativeTraceWriter(const std::string trace_folder, const std::string trace_file,
                                     const size_t ring_buffer_size): writer_(std::move(trace_folder),
                                                                             std::move(trace_file),
                                                                             facebook::profilo::RingBuffer::init(ring_buffer_size),
                                                                             std::make_shared<NativeTraceCallbacks>(),
                                                                             facebook::profilo::writer::calculateHeaders(),
                                                                             facebook::profilo::writer::traceBackwards) {

}

void NativeTraceWriter::loop() {
    try {
        writer_.loop();
    } catch (...) {
        LOGE("maybe you should request permissions for writing external storage.");
    }
}

void NativeTraceWriter::submit(TraceBuffer::Cursor cursor, int64_t trace_id) {
    writer_.submit(cursor, trace_id);
}

}
}
