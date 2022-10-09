package com.bomber.strace

import com.android.build.api.instrumentation.FramesComputationMode
import com.android.build.api.instrumentation.InstrumentationParameters
import com.android.build.api.instrumentation.InstrumentationScope
import com.android.build.api.variant.AndroidComponentsExtension
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.provider.Property
import org.gradle.api.tasks.Input

class TracePlugin : Plugin<Project> {
    companion object {
        const val EXTENSION_NAME = "lancerTrace"
    }


    override fun apply(project: Project) {

        project.extensions.create(EXTENSION_NAME, TraceExtension::class.java)

        val androidComponents =
            project.extensions.getByType(AndroidComponentsExtension::class.java)

        androidComponents.onVariants { variant ->
            val extension = project.extensions.findByName(EXTENSION_NAME) as TraceExtension

            println("extension=$extension")
            variant.instrumentation.transformClassesWith(
                TraceTransform::class.java,
                InstrumentationScope.ALL
            ) {
                it.ignoreClass.set(extension.ignoreClass)
            }
            variant.instrumentation.setAsmFramesComputationMode(
                FramesComputationMode.COMPUTE_FRAMES_FOR_INSTRUMENTED_METHODS
            )
        }

    }
}