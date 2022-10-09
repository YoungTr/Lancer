package com.bomber.lancer

import android.content.Context
import com.bomber.lancer.utils.isMainProcess
import java.io.File

object TraceApplicationLike {

    @JvmStatic
    fun attachBaseContext(context: Context) {
        if (context.isMainProcess()) {
            val traceDir = (context.externalCacheDir?.absolutePath
                ?: context.filesDir.absolutePath) + File.separator + "lancer-atrace"
            Lancer.getInstance().start(traceDir)
        }
    }
}