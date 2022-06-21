package com.bomber.strace

import org.objectweb.asm.ClassVisitor
import org.objectweb.asm.Label
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
        println("visitMethod ---->className=$className methodName=$name descriptor=$descriptor signature=$signature")
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


                /**
                 * 往 catch 块中插入埋点
                 */
                var handler: Label? = null
                var state = State.NONE
                override fun visitTryCatchBlock(
                    start: Label?,
                    end: Label?,
                    handler: Label?,
                    type: String?
                ) {
                    super.visitTryCatchBlock(start, end, handler, type)
                    if (isNeedVisiMethod(name, className)) {
                        this.handler = handler
                    }
                }

                override fun visitLabel(label: Label?) {
                    super.visitLabel(label)
                    state = if (label != null && handler == label) {
                        State.LABEL
                    } else {
                        State.NONE
                    }
                }

                override fun visitFrame(
                    type: Int,
                    numLocal: Int,
                    local: Array<out Any>?,
                    numStack: Int,
                    stack: Array<out Any>?
                ) {
                    super.visitFrame(type, numLocal, local, numStack, stack)
                    if (state == State.LABEL) {
                        state = State.FRAME
                    }
                }

                override fun visitVarInsn(opcode: Int, `var`: Int) {
                    super.visitVarInsn(opcode, `var`)
                    if (state == State.FRAME && opcode == ASTORE) {
                        println("catchIn ---->className=$className methodName=$name")
                        mv.visitLdcInsn(className)
                        mv.visitLdcInsn(name)
                        mv.visitMethodInsn(
                            INVOKESTATIC, "com/bomber/strace/core/SysTracer", "catchIn",
                            "(Ljava/lang/String;Ljava/lang/String;)V", false
                        );
                    }
                }
            }
        return newMethodVisitor
    }

    private fun isNeedVisiMethod(name: String?, className: String?): Boolean {
        // todo SysTracer 和 构造不做插桩
        return className != "com.bomber.strace.core.SysTracer" && name != "<clinit>" && name != "<init>"
    }


    enum class State {
        NONE,
        LABEL,
        FRAME
    }
}