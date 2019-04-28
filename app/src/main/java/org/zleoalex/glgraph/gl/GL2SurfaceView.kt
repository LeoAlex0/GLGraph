package org.zleoalex.glgraph.gl

import android.content.Context
import android.opengl.GLSurfaceView
import android.opengl.GLES20

/**
 * 简单重载[GLSurfaceView]，并启用[GLES20]特性
 * @author zLeoAlex
 */
class GL2SurfaceView(context: Context) : GLSurfaceView(context) {
    constructor(context: Context,renderer: Renderer) : this(context) {
        setEGLContextClientVersion(2)
        setRenderer(renderer)
    }
}