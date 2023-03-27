#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define GL_GLES_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
// #include <GLES3/gl3platform.h>

#define EGL_EGL_PROTOTYPES 1
#define EGL_EGLEXT_PROTOTYPES 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
// #include <EGL/eglplatform.h>

// #include <webgl/webgl2.h>  //  much better performance without

// #include <emscripten/html5_webgl.h>
