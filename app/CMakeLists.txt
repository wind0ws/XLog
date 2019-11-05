# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

if (CMAKE_CURRENT_BINARY_DIR MATCHES "debug")
    message(STATUS "Debug build detected")
    add_compile_options("-DANDROID_DEBUG") # <-- change this to have an effect on the build
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fsanitize=address -fno-omit-frame-pointer")
#    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fsanitize=address -fno-omit-frame-pointer")
#    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
#    SET(CMAKE_ANDROID_ARM_MODE ARM)
else()
    message(STATUS "Release build detected")
endif()


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

# Android 5.0 以上需要在此处设置 PIE
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIE -pie")

# The version number
#set(XFAR_VERSION_CODE "${XFAR_VERSION_CODE}")
#set(XFAR_BUILD_TIME "\"${XFAR_BUILD_TIME}\"")
#set(XFAR_BUILD_TYPE \"${XFAR_BUILD_TYPE}\")

# configure a header file to pass some of the CMake settings to
# source code(demo11Config.h.in), the file demoConfig.h does't exists
#configure_file(
#        "${CMAKE_SOURCE_DIR}/src/main/cpp/headers/version.h.in"
#        "${CMAKE_SOURCE_DIR}/src/main/cpp/headers/version.h"
#)

# Specifies a path to native header files.
#include_directories(src/main/cpp/include/)
include_directories(
        ${CMAKE_SOURCE_DIR}/src/main/cpp/xlog/)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


add_executable( # Sets the name of the library.
        xlog_test

        # Provides a relative path to your source file(s).
        ${CMAKE_SOURCE_DIR}/src/main/cpp/xlog/xlog.c
        ${CMAKE_SOURCE_DIR}/src/main/cpp/main.c
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        xlog_test

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
