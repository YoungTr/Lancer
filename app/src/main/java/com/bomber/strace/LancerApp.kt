package com.bomber.strace

import android.app.Application
import android.content.Context

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
        funA()
    }


    fun funA() {
        funB()
        funC()
        funD()
        funE()
        funF()
    }

    fun funB() {
        Thread.sleep(500)
    }

    fun funC() {
        Thread.sleep(3000)
    }

    fun funD() {
        Thread.sleep(800)
    }

    fun funE() {
        Thread.sleep(2000)
    }

    fun funF() {
        Thread.sleep(50)
    }
}