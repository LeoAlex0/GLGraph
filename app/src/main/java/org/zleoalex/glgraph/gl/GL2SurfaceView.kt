package org.zleoalex.glgraph.gl

import android.content.Context
import android.opengl.GLSurfaceView

class GL2SurfaceView(context: Context) : GLSurfaceView(context) {
    constructor(context: Context,renderer: Renderer) : this(context) {
        setEGLContextClientVersion(2)
        setRenderer(renderer)
    }
}