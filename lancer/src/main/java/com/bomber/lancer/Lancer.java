package com.bomber.lancer;

import static com.bomber.lancer.Errno.OK;

import android.os.Trace;
import android.util.Log;

import com.bomber.lancer.core.SysTracer;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * @author youngtr
 * @data 2022/6/18
 */
public class Lancer {

    private static final String TAG = "Lancer.NativeHandler";

    private Configuration configuration;

    static {
        try {
            System.loadLibrary("lancer");
        } catch (Throwable e) {
            Log.e(TAG, "Lancer System.loadLibrary failed", e);
        }
    }


    public void init(Configuration configuration) {
        this.configuration = configuration;
        SysTracer.sIsMainProcess = true;
        start(configuration.getTraceDir());
    }

    public Configuration getConfiguration() {
        return configuration;
    }


    public void start(String traceDir) {
        int r = startTrace(traceDir, configuration.getAtraceBufferSize());
        if (r == OK) {
            SysTracer.sStart = true;
        }
    }

    public void stop() {
        stopTrace();
        SysTracer.sStart = false;
    }

    public void trace(String section) {
        traceSection(section);
    }

//    private native int nativeInit(int appLevel, String traceFile, int debug);

    private native int startTrace(String traceDir, long bufferSize);

    private native int stopTrace();

    private native void traceSection(String section);


    public static Lancer getInstance() {
        return Holder.INSTANCE;
    }

    private static class Holder {
        private static final Lancer INSTANCE = new Lancer();
    }

}
