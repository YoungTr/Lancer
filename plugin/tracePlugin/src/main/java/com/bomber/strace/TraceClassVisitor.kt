package com.bomber.strace

import org.objectweb.asm.ClassVisitor
import org.objectweb.asm.MethodVisitor
import org.objectweb.asm.Opcodes

class TraceClassVisitor(nextVisitor: ClassVisitor, private val className: String) : ClassVisitor(
    Opcodes.ASM5, nextVisitor
) {
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
                    mv.visitLdcInsn(className)
                    mv.visitLdcInsn(name)
                    mv.visitMethodInsn(
                        INVOKESTATIC, "com/bomber/strace/core/SysTracer", "i",
                        "(Ljava/lang/String;Ljava/lang/String;)V", false
                    )
                }

                override fun onMethodEnd(opcode: Int) {
//                    println("onMethodExit ---->className=$className methodName=$name")
                    mv.visitLdcInsn(className)
                    mv.visitLdcInsn(name)
                    mv.visitMethodInsn(
                        INVOKESTATIC, "com/bomber/strace/core/SysTracer", "o",
                        "(Ljava/lang/String;Ljava/lang/String;)V", false
                    )
                }

                override fun onCatchIn() {
//                    println("catchIn ---->className=$className methodName=$name")
                    mv.visitLdcInsn(className)
                    mv.visitLdcInsn(name)
                    mv.visitMethodInsn(
                        INVOKESTATIC, "com/bomber/strace/core/SysTracer", "catchIn",
                        "(Ljava/lang/String;Ljava/lang/String;)V", false
                    )
                }
            }
        return newMethodVisitor
    }

}