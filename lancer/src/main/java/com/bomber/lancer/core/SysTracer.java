package com.bomber.lancer.core;

import android.os.Trace;
import android.util.Log;

import java.util.Stack;

public class SysTracer {
    /**
     * 方法调用栈深度
     */
    private static final int maxSize = 6;

    private static final ThreadLocal<Stack<String>> threadLocal = new ThreadLocal<>();

    public static void i(String className, String methodName) {
        Stack<String> methodStack = threadLocal.get();
        if (methodStack == null) {
            methodStack = new Stack<>();
            threadLocal.set(methodStack);
        }

        String sectionName = className + "." + methodName;
        if (methodStack.size() <= maxSize) {
            methodStack.push(sectionName);
            Trace.beginSection(sectionName);
        }
    }

    public static void o(String className, String methodName) {
        Stack<String> methodStack = threadLocal.get();

        String sectionName = className + "." + methodName;

        if (methodStack != null && methodStack.size() > 0) {
            methodStack.pop();
            Trace.endSection();
        }
    }

    public static void catchIn(String className, String methodName) {
        String sectionName = className + "." + methodName;
        Trace.endSection();
    }
}
