//
// Created by YoungTr on 2022/9/27.
//

#include <xhook.h>
#include "hook_bridge.h"
#include "trace.h"
#include "atrace.h"

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

    void hook_libc() {
        xhook_register(".*libc\\.so$", "write", (void *) my_write, (void **) (&original_write));
        xhook_register(".*libc\\.so$", "__write_chk", (void *) my_write_chk,
                       (void **) (&original_write_chk));
        xhook_refresh(1);
    }

    void HookBridge::HookForAtrace() {
        hook_libc();
    }

    HookBridge &HookBridge::Get() {
        static HookBridge kInstance;
        return kInstance;
    }

    bool HookBridge::HookLoadedLibs() {
        if (IsHook()) {
            return true;
        }
//        ATRACE_BEGIN(__FUNCTION__);
        HookForAtrace();
        hook_ok_ = true;
//        ATRACE_END();
        return true;
    }

    bool HookBridge::UnHookLoadedLibs() {
        // todo
        xhook_clear();
        return true;
    }
}
}