package org.zleoalex.glgraph.gl.renderer

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MazeRenderer(private val vtxShader: String = "", private val fragShader: String = "") : IRenderLib , GLSurfaceView.Renderer {
    override fun onDrawFrame(gl: GL10?) {
        step()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        resize(width, height)
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        init(vtxShader,fragShader)
    }

    external override fun init(vtxSrc: String, fragSrc: String): Boolean

    external override fun resize(width: Int, height: Int)

    external override fun step()

    init {
        System.loadLibrary("mazeLib")
    }
}