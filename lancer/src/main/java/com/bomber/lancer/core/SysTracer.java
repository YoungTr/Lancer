package com.bomber.lancer.core;

import android.os.Trace;

public class SysTracer {

    public static void i(String className, String methodName) {
        String sectionName = className + "." + methodName;
        Trace.beginSection(sectionName);
    }

    public static void o(String className, String methodName) {
        Trace.endSection();
    }

    public static void catchIn(String className, String methodName) {
        String sectionName = className + "." + methodName;
        Trace.endSection();
    }
}
