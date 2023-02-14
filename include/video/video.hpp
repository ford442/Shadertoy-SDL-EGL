#pragma once

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

#define GL_GLEXT_PROTOTYPES 1
#define EGL_EGLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1
#define GL4_PROTOTYPES 1 //maybe??

#include <GL/gl.h>
#include <GL/glext.h>

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
// #include <GLES3/gl3platform.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
// #include <EGL/eglplatform.h>

#include <webgl/webgl2.h>

void avgFrm(short int Fnum,int leng,float *ptr,float *aptr);

void egl();

extern "C"{

void b3();

void nano(short int Fnum,int leng,float *ptr,float *aptr);

}
