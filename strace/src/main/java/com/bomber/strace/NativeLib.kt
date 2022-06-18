package com.bomber.strace

class NativeLib {

    /**
     * A native method that is implemented by the 'strace' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'strace' library on application startup.
        init {
            System.loadLibrary("strace")
        }
    }
}