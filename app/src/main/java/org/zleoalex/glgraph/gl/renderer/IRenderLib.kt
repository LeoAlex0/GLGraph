package org.zleoalex.glgraph.gl.renderer

import android.opengl.GLSurfaceView.Renderer

/**
 * 使用JNI交给C++部分实现的代码的接口
 * @author zLeoAlex
 */
interface IRenderLib {
    /**
     * 初始化(着色器的编译与链接)，对应[Renderer.onSurfaceCreated]
     * @param vtxSrc 顶点着色器代码
     * @param fragSrc 片元着色器代码
     */
    fun init(vtxSrc : String, fragSrc : String) : Boolean


    /**
     * 重新定义宽高，对应[Renderer.onSurfaceChanged]
     * @param width 新的宽度
     * @param height 新的高度
     */
    fun resize(width: Int, height: Int)

    /**
     * 帧的绘制,对应[Renderer.onDrawFrame]
     */
    fun step()
}