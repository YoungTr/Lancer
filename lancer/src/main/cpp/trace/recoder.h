//
// Created by YoungTr on 2022/10/2.
//

#ifndef LANCER_RECODER_H
#define LANCER_RECODER_H

#include "logger/Logger.h"

namespace swan {
namespace lancer {
using Logger =  facebook::profilo::Logger;
using StandardEntry = facebook::profilo::entries::StandardEntry;
using EntryType = facebook::profilo::entries::EntryType;

namespace {
    constexpr int64_t kRheaAtraceID = 18316;
    constexpr size_t kRingBufferSize = 100000;
}

bool PostCreateTrace(size_t ring_buffer_size = kRingBufferSize, int64_t thread_id = kRheaAtraceID);

void PostFinishTrace(int64_t trace_id = kRheaAtraceID);

}
}

#endif //LANCER_RECODER_H
