package com.bomber.lancer

import android.util.Printer

/**
 * @author youngtr
 * @data 2022/11/12
 */
class LooperPrinter : Printer {

    override fun println(x: String) {
        if (x[0] == '>') {
            // in
            LanTracer.i("B|${x.substring(21)}")
        } else {
            LanTracer.i("E|${x.substring(18)}")
        }
    }
}