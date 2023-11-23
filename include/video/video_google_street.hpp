#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define _XOPEN_SOURCE 700
#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD -1

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
// #include <GLES3/gl31.h>
// #include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#define EGL_EGL_PROTOTYPES 1
#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>
// #include <EGL/eglplatform.h>

void avgFrm(int,int,float *,float *);

extern "C"{

void b3();

void nano(short int,int,float *,float *);

}

void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

char32_t * read_file(const GLchar *);

void renderFrame();

EM_BOOL mouse_call_click(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL mouse_call_move(int,const EmscriptenMouseEvent *,void *);

void clrclr(GLfloat,GLfloat,GLfloat);

extern "C"{

void clr(GLfloat,GLfloat,GLfloat);

void str();

}
