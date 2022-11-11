package com.bomber.lancer

data class Configuration(
    val traceDir: String,
    val atraceBufferSize: Long = 100000,
    val onlyMainThread: Boolean = true
)
