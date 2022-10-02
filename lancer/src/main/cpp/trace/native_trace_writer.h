//
// Created by YoungTr on 2022/10/2.
//

#ifndef LANCER_NATIVE_TRACE_WRITER_H
#define LANCER_NATIVE_TRACE_WRITER_H

#include <writer/TraceWriter.h>

namespace swan {
namespace lancer {

using RingBuffer = facebook::profilo::RingBuffer;
using TraceBuffer = facebook::profilo::TraceBuffer;
using TraceWriter = facebook::profilo::writer::TraceWriter;

class NativeTraceWriter {
public:
    NativeTraceWriter(const std::string trace_folder,
                      const std::string trace_file,
                      const size_t ring_buffer_size
                      );

    void loop();

    void submit(TraceBuffer::Cursor cursor, int64_t trace_id);

private:
    TraceWriter writer_;
};

}
}

#endif //LANCER_NATIVE_TRACE_WRITER_H
