package com.bomber.strace

import android.app.Application
import android.content.Context
import android.os.Build
import android.util.Log
import com.bomber.lancer.Lancer
import java.io.File

/**
 * @author youngtr
 * @data 2022/6/18
 */
class LancerApp : Application() {

    override fun attachBaseContext(base: Context?) {
        super.attachBaseContext(base)
        installLancer()

    }


    private fun installLancer() {
        val traceDir = externalCacheDir?.absolutePath + File.separator + "trace"
        val r = Lancer.getInstance().initialize(
            Build.VERSION.SDK_INT,
            traceDir,
            BuildConfig.DEBUG
        )
        Log.d("TraceApp", "r = $r")
        Lancer.getInstance().start()
    }
}