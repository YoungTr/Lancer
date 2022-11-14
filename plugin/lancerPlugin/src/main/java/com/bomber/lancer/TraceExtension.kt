package com.bomber.lancer

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