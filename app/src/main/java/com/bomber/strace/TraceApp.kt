package com.bomber.strace

import android.app.Application
import android.os.Build
import android.util.Log
import com.bomber.lancer.Lancer
import java.io.File

/**
 * @author youngtr
 * @data 2022/6/18
 */
class TraceApp : Application() {
    override fun onCreate() {
        super.onCreate()

        val r = Lancer.getInstance().initialize(
            Build.VERSION.SDK_INT,
            filesDir.absolutePath + File.separator + "trace" + File.separator + "my_trace.txt"
        )

        Log.d("TraceApp", "r = $r")
    }
}