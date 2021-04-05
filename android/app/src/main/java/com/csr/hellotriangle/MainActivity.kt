package com.csr.hellotriangle

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.View

class MainActivity : AppCompatActivity(), SurfaceHolder.Callback {

    private var surfaceHolder: SurfaceHolder? = null
    private var surfaceView : SurfaceView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        findViewById<TextView>(R.id.sample_text).text = stringFromJNI()

        //CSR Manipulating SurfaceView and SurfaceHolder
        surfaceView = findViewById(R.id.surfaceView)
        setupSurfaceHolder()
    }

    private fun setViewVisibility(id: Int, visibility: Int) {
        val view = findViewById<View>(id)
        view!!.visibility = visibility
    }

    private fun setupSurfaceHolder(){
        setViewVisibility(R.id.surfaceView, View.VISIBLE)
        surfaceHolder = surfaceView!!.holder
        surfaceHolder!!.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        print("Surface Created!")
        surfaceHolder?.surface?.let { passSurfaceViewJNI(it) }
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        //TODO("Not yet implemented")
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        //TODO("Not yet implemented")
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun passSurfaceViewJNI(mySurface: Surface)

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}