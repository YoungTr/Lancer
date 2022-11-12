package com.bomber.strace

open class TraceExtension {
    /**
     * 设置需要插桩匹配的类
     */
    var pkg: String = ""

    /**
     * 设置需要忽略的类(支持正则匹配)
     */
    var ignoreClass = arrayOf<String>()


    override fun toString(): String {
        return "TraceExtension(pkg='$pkg', ignoreClass=${ignoreClass.contentToString()})"
    }
}

object Default {
    val defaultIgnore: MutableList<String> = mutableListOf<String>().also {
        // 类库本身不做插桩操作
        it.add("com.bomber.lancer.*")
        it.add("io.reactivex.*")
        it.add("com.facebook.*")
        it.add("com.google.*")
        it.add("android.*")
        it.add("androidx.*")
        it.add("kotlin.*")
        it.add("kotlinx.*")
        it.add("okhttp.*")
        it.add("dagger.*")
        it.add("okio.*")
        it.add("org.*")
        it.add("com.*.R")
        it.add("com.*.R\\\$.*")
        it.add("com.*.BuildConfig")
        it.add("com.*.Manifest")
    }
}