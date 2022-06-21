package com.bomber.strace.sample;


public class CatchSample {
    public void test() {
        try {
            System.out.println("try");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
/*
    methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "test2", "()V", null, null);
    methodVisitor.visitCode();
    Label label0 = new Label();
    Label label1 = new Label();
    Label label2 = new Label();
    methodVisitor.visitTryCatchBlock(label0, label1, label2, "java/lang/Exception");// todo 操作点
    Label label3 = new Label();
    methodVisitor.visitLabel(label3);
    methodVisitor.visitLineNumber(16, label3);
    methodVisitor.visitFieldInsn(GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
    methodVisitor.visitLdcInsn("test2");
    methodVisitor.visitMethodInsn(INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V", false);
    methodVisitor.visitLabel(label0);
    methodVisitor.visitLineNumber(18, label0);
    methodVisitor.visitFieldInsn(GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
    methodVisitor.visitLdcInsn("try");
    methodVisitor.visitMethodInsn(INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V", false);
    methodVisitor.visitLabel(label1);
    methodVisitor.visitLineNumber(22, label1);
    Label label4 = new Label();
    methodVisitor.visitJumpInsn(GOTO, label4);
    methodVisitor.visitLabel(label2);// todo 操作点
    methodVisitor.visitLineNumber(19, label2);
    methodVisitor.visitFrame(Opcodes.F_SAME1, 0, null, 1, new Object[]{"java/lang/Exception"});// todo 操作点
    methodVisitor.visitVarInsn(ASTORE, 1); //todo 在该处之后插入代码逻辑
    //todo 需要插入的代码 ----- start -----
    Label label5 = new Label();
    methodVisitor.visitLabel(label5);
    methodVisitor.visitLineNumber(20, label5);
    methodVisitor.visitMethodInsn(INVOKESTATIC, "com/bomber/strace/core/SysTracer", "catchIn", "()V", false);
    //todo 需要插入的代码 ----- end -----

    todo 插入 catch 块代码逻辑为：
    1、 visitTryCatchBlock 中保存 label2
    2、 visitLabel 中判断 label 是否是 visitTryCatchBlock 中的 label2，是的话则标记当前已到 visitLabel
    3、 visitFrame 中继续判断，是否有标记 visitLabel 状态，是的话，则标记已到 visitFrame
    4、 visitVarInsn 方法中判断，当前是否已走 visitLabel 和 visitFrame，是的话，开始插入字节码

*/
    public void test2() {
        System.out.println("test2");
        try {
            System.out.println("try");
        } catch (Exception e) {
            // todo 待插入
            e.printStackTrace();
        }
    }
}
