package com.bomber.strace

import org.gradle.api.Plugin
import org.gradle.api.Project

class TracePlugin : Plugin<Project> {
    override fun apply(project: Project) {
        println("------->begin TracePlugin")
    }
}