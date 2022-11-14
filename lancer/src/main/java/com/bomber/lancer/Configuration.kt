package com.bomber.lancer

data class Configuration(
    val traceDir: String,
    val atraceBufferSize: Long = 100000,
    val mainThreadOnly: Boolean = true,
    val startWhenLaunch: Boolean = true
)
