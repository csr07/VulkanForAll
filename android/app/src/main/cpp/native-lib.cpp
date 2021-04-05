#include <jni.h>
//#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <string>
#include <android/log.h>

static ANativeWindow* natWin = {0};
static jobject globalSurfaceView = nullptr;

static int32_t width = {640};
static int32_t height = {480};

void AndroidGetWindowSize(){
    width = ANativeWindow_getWidth(natWin);
    height = ANativeWindow_getHeight(natWin);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_csr_hellotriangle_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "CSR: Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_csr_hellotriangle_MainActivity_passSurfaceViewJNI( JNIEnv* env,
                                    jobject obj,
                                    jobject surfaceView ){

    globalSurfaceView = env->NewGlobalRef(surfaceView);
    natWin = ANativeWindow_fromSurface(env, globalSurfaceView);
    AndroidGetWindowSize();
    ANativeWindow_release(natWin);
    return;
}
