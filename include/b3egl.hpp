#pragma once

#include <cstdint>

#include <popcntintrin.h>
// #include <mmintrin.h> //  MMX
#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
#include <pmmintrin.h> // SSE3
#include <tmmintrin.h> // SSSE3
#include <nmmintrin.h>  //  SSE 4.2 lib
#include <avxintrin.h>  // AVX

#include <avxvnniint8intrin.h>  // AVX
#include <wasm_simd128.h>

#include <unistd.h>
// #include <webgl/webgl2.h>

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#define EGL_EGLEXT_PROTOTYPES 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>


#include <emscripten/html5.h>
// #include <emscripten/html5_webgl.h>
