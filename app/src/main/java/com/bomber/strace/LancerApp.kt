package com.bomber.strace

import android.app.Application
import android.content.Context
import java.lang.Thread.sleep

/**
 * @author youngtr
 * @data 2022/6/18
 */
class LancerApp : Application() {

    override fun attachBaseContext(base: Context) {
        super.attachBaseContext(base)
    }

    override fun onCreate() {
        super.onCreate()
        sleep(300)
    }
}