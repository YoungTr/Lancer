//
// Created by YoungTr on 2022/9/27.
//

#include <xhook.h>
#include <unistd.h>
#include "hook_bridge.h"
#include "trace.h"
#include "atrace.h"
#include "trace_provider.h"

namespace swan {
namespace lancer {

    ssize_t (*original_write)(int fd, const void *const __pass_object_size0 buf, size_t count);

    ssize_t my_write(int fd, const void *const buf, size_t count) {
        if (ATrace::Get().IsATrace(fd, count)) {
            ATrace::Get().LogTrace(buf, count);
            return (ssize_t) count;
        }
        return original_write(fd, buf, count);
    }

    ssize_t (*original_write_chk)(int fd, const void *const __pass_object_size0 buf, size_t count,
                                  size_t buf_size);

    ssize_t my_write_chk(int fd, const void *const buf, size_t count, size_t buf_size) {
        if (ATrace::Get().IsATrace(fd, count)) {
            ATrace::Get().LogTrace(buf, count);
            return (ssize_t) count;
        }
        return original_write(fd, buf, count);
    }

    void (*original_trace_begin)(const char *name);

    void proxy_atrace_begin_body(const char *name) {
        if (gettid() == TraceProvider::Get().GetMainThreadId()) {
            original_trace_begin(name);
        }
    }

    void (*original_atrace_end)();

    void proxy_atrace_end_body() {

        if (gettid() == TraceProvider::Get().GetMainThreadId()) {
            original_atrace_end();
        }
    }

    void HookLibc() {
        xhook_register(".*libc\\.so$", "write", (void *) my_write, (void **) (&original_write));
        xhook_register(".*libc\\.so$", "__write_chk", (void *) my_write_chk,
                       (void **) (&original_write_chk));

        if (TraceProvider::Get().IsMainThreadOnly()) {
            xhook_register(".*libc\\.so$", "atrace_begin_body", (void *) proxy_atrace_begin_body, (void **) (&original_trace_begin));
            xhook_register(".*libc\\.so$", "atrace_end_body", (void *) proxy_atrace_end_body,
                           (void **) (&original_atrace_end));
        }
        xhook_refresh(0);
    }

    void HookBridge::HookForAtrace() {
        HookLibc();
    }

    HookBridge &HookBridge::Get() {
        static HookBridge kInstance;
        return kInstance;
    }

    bool HookBridge::HookLoadedLibs() {
        if (IsHook()) {
            return true;
        }
        HookForAtrace();
        hook_ok_ = true;
        return true;
    }

    bool HookBridge::UnHookLoadedLibs() {
        // todo
        xhook_clear();
        return true;
    }
}
}