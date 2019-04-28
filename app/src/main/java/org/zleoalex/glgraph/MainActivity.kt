package org.zleoalex.glgraph

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import org.zleoalex.glgraph.gl.GL2SurfaceView
import org.zleoalex.glgraph.gl.renderer.MazeRenderer

class MainActivity : AppCompatActivity() {

    /**
     * 应用启动时调用，构造一个[MazeRenderer]绑定到[GL2SurfaceView]作为整个应用的根视图
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(GL2SurfaceView(applicationContext,MazeRenderer(
            resources.openRawResource(R.raw.demo_vertex).reader().readText(),
            resources.openRawResource(R.raw.demo_fragment).reader().readText()
        )))
    }
}
