package com.bomber.lancer

import com.android.build.api.instrumentation.AsmClassVisitorFactory
import com.android.build.api.instrumentation.ClassContext
import com.android.build.api.instrumentation.ClassData
import com.android.build.api.instrumentation.InstrumentationParameters
import org.objectweb.asm.ClassVisitor
import java.util.regex.Pattern


abstract class TraceTransform : AsmClassVisitorFactory<TraceParams> {
    override fun createClassVisitor(
        classContext: ClassContext,
        nextClassVisitor: ClassVisitor
    ): ClassVisitor {
        return TraceClassVisitor(nextClassVisitor, classContext.currentClassData.className)
    }

    override fun isInstrumentable(classData: ClassData): Boolean {
        val ignoreClass = parameters.get().ignoreClass.get().toMutableList()
        // 类库本身不做插桩操作
        ignoreClass.add("com.bomber.lancer.*")
        ignoreClass.add("io.reactivex.*")
        ignoreClass.add("com.facebook.*")
        ignoreClass.add("com.google.*")
        ignoreClass.add("android.*")
        ignoreClass.add("androidx.*")
        ignoreClass.add("kotlin.*")
        ignoreClass.add("kotlinx.*")
        ignoreClass.add("okhttp.*")
        ignoreClass.add("dagger.*")
        ignoreClass.add("okio.*")
        ignoreClass.add("org.*")
        ignoreClass.add("com.*.R")
        ignoreClass.add("com.*.R\\\$.*")
        ignoreClass.add("com.*.BuildConfig")
        ignoreClass.add("com.*.Manifest")

        val ignore = ignoreClass.filter { regex ->
            Pattern.matches(regex, classData.className)
        }.toList()

        // 未匹配到 ignore class，并且该 class 的前缀为需要插桩的模块
        val isInstrumentable = ignore.isEmpty()
        println("ignore: $ignore")

        if (isInstrumentable) {
            println("trace class=${classData.className}")
        }
        return isInstrumentable
    }
}
