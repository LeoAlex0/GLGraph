package org.zleoalex.glgraph.gl.renderer

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * 一个专用于渲染迷宫的[GLSurfaceView.Renderer]
 * @param vtxShader 顶点着色器的源代码
 * @param fragShader 片元着色器的源代码
 * @author zLeoAlex
 */
class MazeRenderer(private val vtxShader: String = "", private val fragShader: String = "") : IRenderLib , GLSurfaceView.Renderer {

    /**
     * 每一帧绘制时调用
     */
    override fun onDrawFrame(unuse : GL10?) = step()

    /**
     * 当画面重新构造拉伸时调用
     */
    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) = resize(width, height)

    /**
     * 当绘制初始化时调用
     * @throws Exception 初始化错误
     */
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        if (!init(vtxShader, fragShader)) throw Exception("OpenGL Init Fail")
    }

    /**
     *  交给JNI下放C++代码的部分
     */
    external override fun init(vtxSrc: String, fragSrc: String): Boolean
    external override fun resize(width: Int, height: Int)
    external override fun step()

    external fun refresh()

    init {
        System.loadLibrary("mazeLib")
    }
}

