package com.bomber.strace

import android.app.Application
import android.content.Context
import android.os.Build
import android.util.Log
import com.bomber.lancer.Lancer
import com.bomber.lancer.TraceApplicationLike
import com.bomber.lancer.core.SysTracer
import java.io.File
import java.lang.Thread.sleep

/**
 * @author youngtr
 * @data 2022/6/18
 */
class LancerApp : Application() {

    override fun attachBaseContext(base: Context) {
        // TODO: 字节码自动插入
        TraceApplicationLike.attachBaseContext(base)
        SysTracer.i("com.smart.app.SmartApplication", "attachBaseContext")
        super.attachBaseContext(base)
    }

    override fun onCreate() {
        super.onCreate()
        sleep(300)
    }
}