package com.bomber.lancer;

import android.os.Trace;

import com.bomber.lancer.utils.ProcessUtil;

public class LanTracer {

    static boolean sIsMainProcess = false;
    static boolean sIsMainThreadOnly = false;
    static volatile boolean sStart = false;

    public static void i(String section) {
        if (!sStart) {
            return;
        }
        if (!sIsMainProcess) {
            return;
        }

        if (section.length() > 127) {
            section = section.substring(0, 127);
        }

        if (sIsMainThreadOnly) {
            if (ProcessUtil.isMainThread()) {
                Trace.beginSection(section);
            }
        } else {
            Trace.beginSection(section);
        }
    }
}