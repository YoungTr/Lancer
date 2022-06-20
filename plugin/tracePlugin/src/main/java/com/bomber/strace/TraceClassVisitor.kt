package com.bomber.strace

import org.objectweb.asm.ClassVisitor
import org.objectweb.asm.MethodVisitor
import org.objectweb.asm.Opcodes
import org.objectweb.asm.commons.AdviceAdapter

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
            object : AdviceAdapter(Opcodes.ASM5, methodVisitor, access, name, descriptor) {

                @Override
                override fun onMethodEnter() {
                    if (isNeedVisiMethod(name, className)) {
                        println("onMethodEnter ---->className=$className methodName=$name")
                        mv.visitLdcInsn(className)
                        mv.visitLdcInsn(name)
                        mv.visitMethodInsn(
                            INVOKESTATIC, "com/bomber/strace/core/SysTracer", "i",
                            "(Ljava/lang/String;Ljava/lang/String;)V", false
                        );
                    }
                    super.onMethodEnter()
                }

                @Override
                override fun onMethodExit(opcode: Int) {
                    if (isNeedVisiMethod(name, className)) {
                        println("onMethodExit ---->className=$className methodName=$name")
                        mv.visitLdcInsn(className)
                        mv.visitLdcInsn(name)
                        mv.visitMethodInsn(
                            INVOKESTATIC, "com/bomber/strace/core/SysTracer", "o",
                            "(Ljava/lang/String;Ljava/lang/String;)V", false
                        );
                    }
                    super.onMethodExit(opcode)
                }
            }
        return newMethodVisitor
    }

    private fun isNeedVisiMethod(name: String?, className: String?): Boolean {
        // todo SysTracer 和 构造不做插桩
        return className != "com.bomber.strace.core.SysTracer" && name != "<clinit>" && name != "<init>"
    }
}