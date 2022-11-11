package com.bomber.lancer.core;


import com.bomber.lancer.Lancer;
import com.bomber.lancer.utils.ProcessUtil;

public class SysTracer {

    public static boolean sIsMainProcess = false;
    public static boolean sStart = false;

    //todo 字符计算直接在插桩是完成

    public static void i(String className, String methodName) {
        if (!sStart) {
            return;
        }

        if (!sIsMainProcess) {
            return;
        }
        if (Lancer.getInstance().getConfiguration().getOnlyMainThread()) {
            if (ProcessUtil.isMainThread()) {
                String stringBuilder = "B|" + className + ":" + methodName;
                Lancer.getInstance().trace(stringBuilder);
            }
        } else {
            String stringBuilder = "B|" + className + ":" + methodName;
            Lancer.getInstance().trace(stringBuilder);
        }
    }

    public static void o(String className, String methodName) {
        if (!sStart) {
            return;
        }

        if (!sIsMainProcess) {
            return;
        }
        if (Lancer.getInstance().getConfiguration().getOnlyMainThread()) {
            if (ProcessUtil.isMainThread()) {
                String stringBuilder = "E|" + className + ":" + methodName;
                Lancer.getInstance().trace(stringBuilder);
            }
        } else {

            String stringBuilder = "E|" + className + ":" + methodName;
            Lancer.getInstance().trace(stringBuilder);
        }
    }

    public static void catchIn(String className, String methodName) {
        if (!sStart) {
            return;
        }

        if (!sIsMainProcess) {
            return;
        }
        if (Lancer.getInstance().getConfiguration().getOnlyMainThread()) {
            if (ProcessUtil.isMainThread()) {
                String stringBuilder = "T|" + className + ":" + methodName;
                Lancer.getInstance().trace(stringBuilder);
            }
        } else {
            String stringBuilder = "T|" + className + ":" + methodName;
            Lancer.getInstance().trace(stringBuilder);
        }

    }
}
