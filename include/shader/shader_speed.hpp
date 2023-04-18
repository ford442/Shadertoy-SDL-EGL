#include <emscripten.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

extern "C"{
  
void str();
  
}

#pragma STDC FP_CONTRACT OFF
// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD -1

#pragma STDC CX_LIMITED_RANGE ON

#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1


#include <float.h>
#include <math.h>

double_t wi,hi;
const float_t F=1.0f,Fm1=-1.0f;
const double_t Dm1=-1.0,D=1.0;
const double_t D0=0.0;
const float_t F0=0.0f;

#include "../../include/shader/intrins.hpp"
#include <algorithm>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <locale> // utf-16
#include <uchar.h> // utf-16

// #include <stdfloat>  //  c++23

#include <time.h>
#include <chrono>

using namespace std::chrono_literals;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;
std::chrono::steady_clock::time_point t3;
struct timespec rem;
struct timespec req={0,14200000};

#include "../../include/shader/gl.hpp"

float_t Tdlt;
float_t Ttime;
fast32_t iFrame;
double_t mouseY,mouseX;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
fast32_t fram;
fast32_t Size;
GLfloat mX,mY,mm,nn;
GLfloat delt,Tm,iFps;
GLfloat gF=1.0f,gF0=0.0f,gFm1=-1.0f;
GLclampf x,y,y1y=F;
GLdouble gD=1.0,gD0=0.0,gDm1=-1.0;
GLfloat g1g=1.0f;
double_t S;
GLsizei s4=4,i;
GLuint EBO,VBO,smp_chn[4],smp_chn_res,VCO,ECO,uni_mse,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps;
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vrt[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

const GLchar * src[4];

const GLchar cm_hdr_src[]=
"#version 300 es\n"
"#pragma STDGL(fastmath on)\n"
"#pragma optionNV(fastmath on)\n"
"#pragma STDGL(fastprecision on)\n"
"#pragma optionNV(fastprecision on)\n"
"#pragma STDGL(unroll none)\n"
"#pragma optionNV(unroll none)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma optionNV(ifcvt none)\n"
"#pragma STDGL(inline none)\n"
"#pragma optionNV(inline none)\n"
"#pragma STDGL(strict on)\n"
"#pragma optionNV(strict on)\n"
"#pragma optionNV(invariant none)\n"
"#pragma STDGL(invariant none)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
"precision mediump float;\n";

const GLchar vrt_bdy_src[]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

const GLchar frg_hdr_src[]=
"precision lowp sampler3D;precision mediump sampler2D;"
"precision lowp samplerCube;precision lowp sampler2DArray;precision lowp sampler2DShadow;"
"precision lowp isampler2D;precision lowp isampler3D;precision lowp isamplerCube;"
"precision lowp isampler2DArray;precision lowp usampler2D;precision lowp usampler3D;"
"precision lowp usamplerCube;precision lowp usampler2DArray;precision lowp samplerCubeShadow;"
"precision lowp sampler2DArrayShadow;"
"uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out vec4 fragColor;\n";

const GLchar frg_ftr_src[]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";

const GLchar * cm_hdr=cm_hdr_src;
const GLchar * vrt_bdy=vrt_bdy_src;
const GLchar * frg_hdr=frg_hdr_src;
const GLchar * frg_ftr=frg_ftr_src;

static inline void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint cmpl_shd(GLenum,GLsizei,const GLchar **);

GLchar * rd_fl(const char *);

#include "../../include/shader/egl.hpp"

EGLDisplay display;
EGLSurface surface;
EGLContext ctxegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;

EGLint att_lst2[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
EGL_NONE
};
const EGLint ctx_att[]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)7,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE
};
const EGLint att_lst[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
// EGL_CONFIG_CAVEAT,EGL_NONE,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_RED_SIZE,(EGLint)8,
EGL_GREEN_SIZE,(EGLint)8,
EGL_BLUE_SIZE,(EGLint)8,
EGL_ALPHA_SIZE,(EGLint)8,
EGL_DEPTH_SIZE,(EGLint)16,
EGL_STENCIL_SIZE,(EGLint)8,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_NONE
};

#include <emscripten/html5.h>

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;

EM_BOOL ms_clk(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL ms_mv(int,const EmscriptenMouseEvent *,void *);
