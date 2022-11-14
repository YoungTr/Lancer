package com.bomber.lancer

import org.objectweb.asm.Label
import org.objectweb.asm.MethodVisitor
import org.objectweb.asm.commons.AdviceAdapter

abstract class TraceMethodVisitor(
    private val className: String,
    api: Int,
    methodVisitor: MethodVisitor,
    access: Int,
    name: String?,
    descriptor: String?
) : AdviceAdapter(api, methodVisitor, access, name, descriptor) {


    override fun onMethodEnter() {
        if (isNeedVisiMethod(name, className)) {
            onMethodStart()
        }
        super.onMethodEnter()
    }

    override fun onMethodExit(opcode: Int) {
        if (isNeedVisiMethod(name, className)) {
            onMethodEnd(opcode)
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
            onCatchIn()
        }
    }


    abstract fun onCatchIn()
    abstract fun onMethodStart()
    abstract fun onMethodEnd(opcode: Int)


    protected fun isNeedVisiMethod(name: String?, className: String?): Boolean {
        // todo 构造不做插桩
        return  name != "<clinit>" && name != "<init>"
    }


    enum class State {
        NONE,
        LABEL,
        FRAME
    }
}