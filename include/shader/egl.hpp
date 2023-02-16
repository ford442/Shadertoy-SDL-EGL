#pragma once
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#undef STDC FP_CONTRACT
#pragma STDC FP_CONTRACT OFF

#include <wasm_simd128.h>
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>
#include <unistd.h>

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#define EGL_EGLEXT_PROTOTYPES 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <webgl/webgl2.h>
// #include <emscripten/html5_webgl.h>
