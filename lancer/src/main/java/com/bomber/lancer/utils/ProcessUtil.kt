@file:JvmName("ProcessUtil")

package com.bomber.lancer.utils

import android.annotation.SuppressLint
import android.app.ActivityManager
import android.app.Application
import android.content.Context
import android.os.Build
import android.os.Build.VERSION_CODES.JELLY_BEAN_MR2
import android.os.Looper
import android.os.Process
import android.util.Log
import androidx.annotation.DoNotInline
import androidx.annotation.RequiresApi

/**
 * @author youngtr
 * @data 2022/4/9
 */

private lateinit var _processName: String

fun Context.isMainProcess(): Boolean {
    return getProcessName(this).equals(this.packageName)
}

fun Context.versionName(): String {
    return try {
        this.packageManager.getPackageInfo(this.packageName, 0).versionName
    } catch (e: Throwable) {
        "NA"
    }
}

@SuppressLint("PrivateApi", "ObsoleteSdkInt", "DiscouragedPrivateApi")
fun getProcessName(context: Context): String? {
    if (::_processName.isInitialized) return _processName
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) return Api28Impl.processName
    try {

        val activityThread = Class.forName(
            "android.app.ActivityThread",
            false,
            Application::class.java.classLoader
        )
        val processName = if (Build.VERSION.SDK_INT >= JELLY_BEAN_MR2) {
            val currentProcessName = activityThread.getDeclaredMethod("currentProcessName")
            currentProcessName.isAccessible = true
            currentProcessName.invoke(null)!!
        } else {
            val getActivityThread = activityThread.getDeclaredMethod("currentActivityThread")
            getActivityThread.isAccessible = true
            val getProcessName = activityThread.getDeclaredMethod("getProcessName")
            getProcessName.isAccessible = true
            getProcessName.invoke(getActivityThread.invoke(null))!!
        }
        if (processName is String) return processName
    } catch (exception: Throwable) {
        Log.d("TAG", "ERROR: ${exception.message}")
    }
    // Fallback to the most expensive way
    val pid = Process.myPid()
    val am = context.getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
    return am.runningAppProcesses?.find { process -> process.pid == pid }?.processName

}


@RequiresApi(Build.VERSION_CODES.P)
private object Api28Impl {
    @get:DoNotInline
    val processName: String
        get() = Application.getProcessName()
}

fun isMainThread() = Looper.getMainLooper() == Looper.myLooper()
