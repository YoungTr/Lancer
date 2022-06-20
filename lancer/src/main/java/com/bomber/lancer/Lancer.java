package com.bomber.lancer;

import android.os.Trace;
import android.util.Log;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * @author youngtr
 * @data 2022/6/18
 */
public class Lancer {

    private static final String TAG = "Lancer.NativeHandler";


    public int initialize(int appLevel, String traceDir, boolean debug) {
        try {
            System.loadLibrary("lancer");
        } catch (Throwable e) {
            Log.e(TAG, "Lancer System.loadLibrary failed", e);
            return Errno.LOAD_LIBRARY_FAILED;
        }

        try {
            int r = nativeInit(appLevel, traceDir, debug ? 1 : 0);
            if (r != 0) {
                Log.e(TAG, "Lancer init failed");
                return Errno.INIT_LIBRARY_FAILED;
            }
            Log.i(TAG, "Lancer init: " + r);
            return r;
        } catch (Throwable e) {
            Log.e(TAG, "Lancer init failed", e);
            return Errno.INIT_LIBRARY_FAILED;
        }
    }

    public void start() {
        enableLancer();
        SystraceReflector.updateSystraceTags();
    }

    public void stop() {
        disableLancer();
    }

    private native int nativeInit(int appLevel, String traceFile, int debug);

    private native void enableLancer();

    private native void disableLancer();


    public static Lancer getInstance() {
        return Holder.INSTANCE;
    }

    private static class Holder {
        private static final Lancer INSTANCE = new Lancer();
    }

    private static final class SystraceReflector {

        public static void updateSystraceTags() {
            if (sTrace_sEnabledTags != null && sTrace_nativeGetEnabledTags != null) {
                try {
                    sTrace_sEnabledTags.set(null, sTrace_nativeGetEnabledTags.invoke(null));
                } catch (IllegalAccessException e) {
                } catch (InvocationTargetException e) {

                }
            }
        }

        private static final Method sTrace_nativeGetEnabledTags;
        private static final Field sTrace_sEnabledTags;

        static {
            Method m;
            try {
                m = Trace.class.getDeclaredMethod("nativeGetEnabledTags");
                m.setAccessible(true);
            } catch (NoSuchMethodException e) {
                m = null;
            }
            sTrace_nativeGetEnabledTags = m;

            Field f;
            try {
                f = Trace.class.getDeclaredField("sEnabledTags");
                f.setAccessible(true);
            } catch (NoSuchFieldException e) {
                f = null;
            }
            sTrace_sEnabledTags = f;
        }
    }
}
