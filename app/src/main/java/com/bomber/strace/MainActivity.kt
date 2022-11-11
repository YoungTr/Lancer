package com.bomber.strace

import android.Manifest
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.annotation.RequiresApi
import com.bomber.lancer.Lancer
import com.bomber.strace.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    @RequiresApi(Build.VERSION_CODES.M)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        requestPermissions(
            arrayOf(
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE
            ), 1
        )


        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        funA()
        textError()

        binding.sampleText.setOnClickListener {
            Lancer.getInstance().stop()
        }

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()


    }

    fun textTrace(view: View) {
        funA()
    }

    fun funA() {
        funB()
        funC()
        funD()
        funE()
        funF()
        recursion(10)
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

    fun recursion(x: Int): Int {
        val result = if (x <= 1) 1 else recursion(x - 1) + x
        return result
    }

    fun textError() {


        try {
            funB()
        } catch (e: Exception) {

        }

        funC()
    }

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