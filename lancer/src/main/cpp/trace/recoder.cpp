//
// Created by YoungTr on 2022/10/2.
//

#include <thread>
#include <trace_provider.h>
#include <timers.h>
#include "recoder.h"
#include "../log.h"
#include "native_trace_writer.h"
#include "threads.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
namespace swan {
namespace lancer {

namespace {
    constexpr int32_t kTimeout = std::numeric_limits<int>::max();
    constexpr int32_t kFlags = 1 << 1;
    constexpr char kDefaultTraceFile[] = "lancer-atrace";

    std::unique_ptr<NativeTraceWriter> sTraceWriter = nullptr;
}

static bool WriteTraceStart(NativeTraceWriter* writer, int64_t trace_id = 1) {
    if (writer == nullptr) {
        LOGE("WriteTraceStart:native trace writer is null");
        return false;
    }

    TraceBuffer::Cursor cursor = RingBuffer::get().currentTail();
    int id = Logger::get().writeAndGetCursor(
            StandardEntry{
                    .id = 0,
                    .type = EntryType::TRACE_START,
                    .timestamp = systemTime(SYSTEM_TIME_BOOTTIME),
                    .tid = gettid(),
                    .callid = kTimeout,
                    .matchid = kFlags,
                    .extra = trace_id,
            },
            cursor);
    writer->submit(cursor, trace_id);
    return true;
}

static void WriteTraceEnd(NativeTraceWriter *writer, int64_t trace_id = 1) {
    if (writer == nullptr) {
        LOGD("WriteTraceEnd: native trace writer is null.");
    }
    TraceBuffer::Cursor cursor = RingBuffer::get().currentTail();
    int id = Logger::get().writeAndGetCursor(
            StandardEntry{
                    .id = 0,
                    .type = EntryType::TRACE_END,
                    .timestamp = systemTime(SYSTEM_TIME_BOOTTIME),
                    .tid = gettid(),
                    .callid = kTimeout,
                    .matchid = kFlags,
                    .extra = trace_id,
            },
            cursor);
    writer->submit(cursor, TraceWriter::kStopLoopTraceID);

}

static void StartWorkerThreadIfNecessary(size_t ring_buffer_size) {
    sTraceWriter = std::make_unique<NativeTraceWriter>(TraceProvider::Get().GetTraceFolder(),
                                                       std::string(kDefaultTraceFile),
                                                       ring_buffer_size);
    std::thread([=]() {
        SetThreadName("async-write");
        LOGD("start async atrace writer thread");
        sTraceWriter->loop();
        LOGD("stop async atrace writer thread");
    }).detach();
}

bool PostCreateTrace(size_t ring_buffer_size, int64_t trace_id) {
    LOGE("buffer size %zu", ring_buffer_size);
    StartWorkerThreadIfNecessary(ring_buffer_size);
    return WriteTraceStart(sTraceWriter.get(), trace_id);
}

void PostFinishTrace(int64_t trace_id) {
    WriteTraceEnd(sTraceWriter.get(), trace_id);
}
}
}


#pragma clang diagnostic pop