package com.bomber.strace

import com.android.build.api.instrumentation.InstrumentationParameters
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input


interface TraceParams : InstrumentationParameters {

    @get:Input
    val ignoreClass: Property<Array<String>>
}
