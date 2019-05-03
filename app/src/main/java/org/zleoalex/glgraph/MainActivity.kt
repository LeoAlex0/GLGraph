package org.zleoalex.glgraph

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import org.zleoalex.glgraph.gl.GL2SurfaceView
import org.zleoalex.glgraph.gl.renderer.MazeRenderer

class MainActivity : AppCompatActivity() {

    /**
     * 应用启动时调用，构造一个[MazeRenderer]绑定到[GL2SurfaceView]作为整个应用的根视图
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)
    }

    /**
     * 构造完成时启动，配置[GL2SurfaceView]
     */
    override fun onStart() {
        super.onStart()

        val renderer = MazeRenderer(
            resources.openRawResource(R.raw.demo_vertex).reader().readText(),
            resources.openRawResource(R.raw.demo_fragment).reader().readText()
        )

        surface.setRenderer(renderer)
        refreshButton.setOnClickListener { renderer.refresh() }
    }
}
