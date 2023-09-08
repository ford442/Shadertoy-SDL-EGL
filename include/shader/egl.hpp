#pragma once

// #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <webgl/webgl2.h>  //  much better performance without
#include <webgl/webgl2_ext.h>  //  much better performance without

#define GL_CONTEXT_PROFILE_MASK 0x9126
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001

// #define GLFW_INCLUDE_GLEXT 1
// #define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>

#define GL_GLES_PROTOTYPES 1
#define EGL_EGL_PROTOTYPES 1
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLES3/gl3.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

// #include <GLES3/gl3platform.h>
#include <GLES3/gl31.h>
// #include <GLES3/gl32.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
// #include <EGL/eglplatform.h>
// #include <KHR/khrplatform.h>

// #include <emscripten/html5_webgl.h>


