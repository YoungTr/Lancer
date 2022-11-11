//
// Created by YoungTr on 2022/9/26.
//

#ifndef LANCER_ATRACE_H
#define LANCER_ATRACE_H

#include <stdint.h>
#include <stdlib.h>
#include <atomic>
#include <map>
#include <timers.h>
#include "macros.h"
#include "../log.h"

typedef std::map<int, std::string> THREAD_MAP;

namespace swan {
namespace lancer {

namespace {
constexpr ssize_t kAtraceMessageLen = 1024;
}

class ATrace {
public:
    static ATrace &Get();

    int32_t StarTrace();

    int32_t StopTrace();

    void LogTrace(const void *buf, size_t count);

    bool IsATraceStarted() const { return atrace_started_; }

private:

    static double CurrentTime() {
        return systemTime(SYSTEM_TIME_BOOTTIME) / 1000000000.0;
    }

    ATrace();
    ~ATrace();


    void revolveTrace(const char *, bool);

    int *atrace_maker_fd_{nullptr};

    bool atrace_started_{false};
    bool atrace_probe_installed_{false};
    bool first_start_trace_{true};

    uint64_t log_trace_cost_us_{0};



    DISALLOW_COPY_AND_ASSIGN(ATrace);

};

}
}

#endif //LANCER_ATRACE_H
