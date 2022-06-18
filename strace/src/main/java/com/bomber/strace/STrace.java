package com.bomber.strace;

import android.util.Log;

/**
 * @author youngtr
 * @data 2022/6/18
 */
public class STrace {

    private static final String TAG = "STrace.Native";


    public int initialize(int appLevel, String traceFile) {
        try {
            System.loadLibrary("bomber-strace");
        } catch (Throwable e) {
            Log.e(TAG, "NativeHandler System.loadLibrary failed", e);
            return Errno.LOAD_LIBRARY_FAILED;
        }

        try {
            int r = nativeInit(appLevel, traceFile);
            if (r != 0) {
                Log.e(TAG, "STrace init failed");
                return Errno.INIT_LIBRARY_FAILED;
            }
            return r;
        } catch (Throwable e) {
            Log.e(TAG, "STrace init failed", e);
            return Errno.INIT_LIBRARY_FAILED;
        }
    }

    private native int nativeInit(int appLevel, String traceFile);


    public static STrace getInstance() {
        return Holder.INSTANCE;
    }

    private static class Holder {
        private static final STrace INSTANCE = new STrace();
    }

}
