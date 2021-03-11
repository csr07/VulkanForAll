# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("hellotriangle")

#CSR stuff on the CMakeLists.txt this project dont have
#set(CMAKE_SYSTEM_NAME "Android")
#set(CMAKE_SYSTEM_VERSION "7")
#add_definitions(-DVK_USE_PLATFORM_ANDROID_KHR)

#set(SAMPLES_DATA_DIR ${SAMPLES_DATA_DIR} "${CMAKE_SOURCE_DIR}/data")
#set(SHADER_FILES ${SHADER_FILES} "")


# Build Util Lib
set(UTILS_NAME  vsamputils)
get_filename_component(PROJECT_SOURCE_DIR
                       "${CMAKE_SOURCE_DIR}/../../.."
                       ABSOLUTE)
get_filename_component(GLMINC_PREFIX
                       "${CMAKE_SOURCE_DIR}/utils"
                       ABSOLUTE)
add_subdirectory(${CMAKE_SOURCE_DIR}/utils ${CMAKE_BINARY_DIR}/utils)





# Build application's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -Werror -D VK_USE_PLATFORM_ANDROID_KHR")

# Force export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")




# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             vulkan_sample

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             15-draw_cube.cpp
             ${CMAKE_SOURCE_DIR}/../android/vulkan_wrapper/vulkan_wrapper.cpp
            )

#CSR added from template
target_include_directories(vulkan_sample PRIVATE
                           ${CMAKE_SOURCE_DIR}/data
                           ${GLMINC_PREFIX}
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../externals
                           ${CMAKE_SOURCE_DIR}/../../ShaderHeadersAndroid
                           ${CMAKE_SOURCE_DIR}/../android/vulkan_wrapper)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       vulkan_sample

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ${UTILS_NAME} )