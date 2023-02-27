#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#pragma STDC CX_LIMITED_RANGE ON

#include <wasm_simd128.h>
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>
#include <unistd.h>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cfloat>
#include <climits>

#include <unistd.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1
#define GL4_PROTOTYPES 1 //maybe??

#include <webgl/webgl2.h>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>

#define GL_GLES_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#define EGL_EGL_PROTOTYPES 1
#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

void avgFrm(short int Fnum,int leng,float *ptr,float *aptr);

extern "C"{
  
void b3();

void nano(short int Fnum,int leng,float *ptr,float *aptr);

}
