#pragma once
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#pragma STDC CX_LIMITED_RANGE ON

// #include <webgl/webgl2.h>

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <avxintrin.h>  // AVX

#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2
#include <unistd.h>

#define GL_GLES_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#define EGL_EGL_PROTOTYPES 1
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

// #include <emscripten/html5_webgl.h>
