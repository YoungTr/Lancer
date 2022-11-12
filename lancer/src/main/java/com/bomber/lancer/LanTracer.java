package com.bomber.lancer;

import com.bomber.lancer.utils.ProcessUtil;

public class LanTracer {

    static boolean sIsMainProcess = false;
    static boolean sIsMainThreadOnly = false;
    static boolean sStart = false;

    public static void i(String section) {
        if (!sStart) {
            return;
        }
        if (!sIsMainProcess) {
            return;
        }
        if (sIsMainThreadOnly) {
            if (ProcessUtil.isMainThread()) {
                Lancer.getInstance().trace(section);
            }
        } else {
            Lancer.getInstance().trace(section);
        }
    }
}
