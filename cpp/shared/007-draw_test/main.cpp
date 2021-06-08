#include <iostream>

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <string>

#define VOLK_IMPLEMENTATION
#include <volk.h>

#include <VkBootstrap.h>

static ANativeWindow* natWin = {0};
static jobject globalSurfaceView = nullptr;

static int32_t width = {640};
static int32_t height = {480};

VkSurfaceKHR surface;

void AndroidGetWindowSize(){
    width = ANativeWindow_getWidth(natWin);
    height = ANativeWindow_getHeight(natWin);
}

bool init_vulkan () {
    vkb::InstanceBuilder builder;
    auto inst_ret = builder.set_app_name ("Example Vulkan Application")
            .request_validation_layers ()
            .use_default_debug_messenger ()
            .build ();
    if (!inst_ret) {
        std::cerr << "Failed to create Vulkan instance. Error: " << inst_ret.error().message() << "\n";
        return false;
    }
    vkb::Instance vkb_inst = inst_ret.value ();

    volkLoadInstance(vkb_inst.instance);

    VkAndroidSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.window = natWin;

    VkResult res = vkCreateAndroidSurfaceKHR (vkb_inst.instance, &createInfo, nullptr, &surface);
    if(res != VK_SUCCESS){
        std::cerr<<"Failed to create Android Surface"<<"\n";
    }


    vkb::PhysicalDeviceSelector selector{ vkb_inst };
    auto phys_ret = selector.set_surface (surface)
            .set_minimum_version (1, 1) // require a vulkan 1.1 capable device
            .require_dedicated_transfer_queue ()
            .select ();
    if (!phys_ret) {
        std::cerr << "Failed to select Vulkan Physical Device. Error: " << phys_ret.error().message() << "\n";
        return false;
    }

    vkb::DeviceBuilder device_builder{ phys_ret.value () };
    // automatically propagate needed data from instance & physical device
    auto dev_ret = device_builder.build ();
    if (!dev_ret) {
        std::cerr << "Failed to create Vulkan device. Error: " << dev_ret.error().message() << "\n";
        return false;
    }
    vkb::Device vkb_device = dev_ret.value ();

    // Get the VkDevice handle used in the rest of a vulkan application
    VkDevice device = vkb_device.device;

    // Get the graphics queue with a helper function
    auto graphics_queue_ret = vkb_device.get_queue (vkb::QueueType::graphics);
    if (!graphics_queue_ret) {
        std::cerr << "Failed to get graphics queue. Error: " << graphics_queue_ret.error().message() << "\n";
        return false;
    }
    VkQueue graphics_queue = graphics_queue_ret.value ();

    // Turned 400-500 lines of boilerplate into less than fifty.
    return true;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_csr_hellotriangle_MainActivity_stringFromJNI( JNIEnv* env, jobject /* this */) {
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
    //ANativeWindow_release(natWin);
    return;
}

extern "C" JNIEXPORT void JNICALL
Java_com_csr_hellotriangle_MainActivity_initVolk(JNIEnv* env, jobject){

    VkResult res = volkInitialize();
    if(!res){
        std::printf("Vulkan loader not installed on the system");
    }

    init_vulkan();

}


int main(int i, char** args){

    return 0;
}