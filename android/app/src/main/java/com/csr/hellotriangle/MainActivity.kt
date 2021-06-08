package com.csr.hellotriangle

import android.graphics.SurfaceTexture
import android.os.Bundle
import android.view.Surface
import android.view.TextureView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {


    private var textureView : TextureView? = null
    private var surfaceListener: KotlinInnerSurfaceListener? = null
    private var surfaceTexture: SurfaceTexture? = null
    private var surface: Surface? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //setContentView(R.layout.activity_main)

        // Example of a call to a native method
        //findViewById<TextView>(R.id.sample_text).text = stringFromJNI()

        //Getting TextureView from xml layout
        //textureView = findViewById(R.id.textureView)
        //surfaceListener = KotlinInnerSurfaceListener()
        //textureView?.setSurfaceTextureListener(surfaceListener)

        surfaceListener = KotlinInnerSurfaceListener()
        textureView = TextureView(this)
        textureView?.setSurfaceTextureListener(surfaceListener)
        setContentView(textureView)
    }

    inner class KotlinInnerSurfaceListener: TextureView.SurfaceTextureListener{

        override fun onSurfaceTextureAvailable( pSurfaceTexture: SurfaceTexture, width: Int, height: Int
        ) {
            surface = Surface(pSurfaceTexture)
            passSurfaceJNI(surface!!)

            initVolk()
        }

        override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {
            TODO("Not yet implemented")
        }

        override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {
            TODO("Not yet implemented")
        }

        override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
            TODO("Not yet implemented")
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun passSurfaceJNI(mySurface: Surface)
    external fun initVolk()

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("vulkan_sample")
        }
    }
}