package com.bomber.strace

import com.android.tools.r8.internal.mv
import org.objectweb.asm.ClassVisitor
import org.objectweb.asm.MethodVisitor
import org.objectweb.asm.Opcodes

class TraceClassVisitor(nextVisitor: ClassVisitor, private val className: String) : ClassVisitor(
    Opcodes.ASM5, nextVisitor
) {

    private var superName: String? = null

    override fun visit(
        version: Int,
        access: Int,
        name: String?,
        signature: String?,
        superName: String?,
        interfaces: Array<out String>?
    ) {
        this.superName = superName

        super.visit(version, access, name, signature, superName, interfaces)
    }

    override fun visitMethod(
        access: Int,
        name: String?,
        descriptor: String?,
        signature: String?,
        exceptions: Array<out String>?
    ): MethodVisitor {
        val methodVisitor = super.visitMethod(access, name, descriptor, signature, exceptions)
        val newMethodVisitor =
            object : TraceMethodVisitor(
                className,
                Opcodes.ASM5,
                methodVisitor,
                access,
                name,
                descriptor
            ) {
                override fun onMethodStart() {
//                    println("onMethodEnter ---->className=$className methodName=$name")
                    if (isApplication() && name == "attachBaseContext") {
                        // TODO: 字节码插装
                        return
                    }
                    mv.visitLdcInsn(className)
                    mv.visitLdcInsn(name)
                    mv.visitMethodInsn(
                        INVOKESTATIC, SYS_TRACE_CLASS, "i",
                        SYS_TRACE_METHOD_DESC, false
                    )

                }

                override fun onMethodEnd(opcode: Int) {
//                    println("onMethodExit ---->className=$className methodName=$name")
                    mv.visitLdcInsn(className)
                    mv.visitLdcInsn(name)
                    mv.visitMethodInsn(
                        INVOKESTATIC, SYS_TRACE_CLASS, "o",
                        SYS_TRACE_METHOD_DESC, false
                    )
                }

                override fun onCatchIn() {
//                    println("catchIn ---->className=$className methodName=$name")
                    mv.visitLdcInsn(className)
                    mv.visitLdcInsn(name)
                    mv.visitMethodInsn(
                        INVOKESTATIC, SYS_TRACE_CLASS, "catchIn",
                        SYS_TRACE_METHOD_DESC, false
                    )
                }
            }
        return newMethodVisitor
    }


    private fun isApplication(): Boolean {
        return (SUPER_APPLICATION_CLASS == superName || SUPER_MULTI_APPLICATION_CLASS == superName)
    }


    companion object {
        private const val SYS_TRACE_CLASS = "com/bomber/lancer/core/SysTracer"
        private const val SYS_TRACE_METHOD_DESC = "(Ljava/lang/String;Ljava/lang/String;)V"

        private const val APPLICATION_LIKE_CLASS = "com/bomber/lancer/TraceApplicationLike"
        private const val APPLICATION_LIKE_ATTACHBASECONTEXT = "(Landroid/content/Context;)V"

        private const val SUPER_APPLICATION_CLASS = "android/app/Application"
        private const val SUPER_MULTI_APPLICATION_CLASS = "androidx/multidex/MultiDexApplication"
        private const val APPLICATION_ATTACHCONTEXT_NAME = "attachBaseContext"
    }

}