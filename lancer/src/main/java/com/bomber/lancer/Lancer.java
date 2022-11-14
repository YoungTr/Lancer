package com.bomber.lancer;

import static com.bomber.lancer.Errno.OK;

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

    private Configuration configuration;


    private static final String TAG = "Lancer.NativeHandler";

    static {
        try {
            System.loadLibrary("lancer");
        } catch (Throwable e) {
            Log.e(TAG, "Lancer System.loadLibrary failed", e);
        }
    }

    public void init(Configuration configuration) {
        LanTracer.sIsMainProcess = true;
        LanTracer.sIsMainThreadOnly = configuration.getMainThreadOnly();
        nativeInit(configuration.getTraceDir(), configuration.getAtraceBufferSize(), configuration.getMainThreadOnly());
        if (configuration.getStartWhenLaunch()) {
            start();
        }
    }


    public void start() {
        LanTracer.sStart = true;
        int r = startTrace();
        if (r == OK) {
            SystraceReflector.updateSystraceTags();
        }
    }

    public void stop() {
        LanTracer.sStart = false;
        stopTrace();
    }

    private native void nativeInit(String traceDir, long bufferSize, boolean mainThreadOnly);

    private native int startTrace();

    private native int stopTrace();


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
