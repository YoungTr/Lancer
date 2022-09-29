//
// Created by YoungTr on 2022/9/27.
//

#ifndef LANCER_HOOK_BRIDGE_H
#define LANCER_HOOK_BRIDGE_H

#include "macros.h"

namespace swan{
namespace lancer {

class HookBridge {
public:
    static HookBridge &Get();

    bool IsHook() const { return hook_ok_; }

    bool HookLoadedLibs();

    bool UnHookLoadedLibs();

private:
    HookBridge() = default;
    ~HookBridge() = default;

    bool hook_ok_{false};

    DISALLOW_COPY_AND_ASSIGN(HookBridge);

    void HookForAtrace();
};
}
}

#endif //LANCER_HOOK_BRIDGE_H
