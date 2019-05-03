package org.zleoalex.glgraph.gl

import android.content.Context
import android.opengl.GLSurfaceView
import android.opengl.GLES20
import android.util.AttributeSet

/**
 * 简单重载[GLSurfaceView]，并启用[GLES20]特性
 * @author zLeoAlex
 */
class GL2SurfaceView(context: Context,attributeSet: AttributeSet) : GLSurfaceView(context,attributeSet) {
    init {
        setEGLContextClientVersion(2)
    }
}