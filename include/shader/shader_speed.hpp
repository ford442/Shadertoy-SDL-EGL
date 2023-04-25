#include <emscripten.h>

extern "C"{
  
void str();
  
}

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#include "../../include/shader/intrins.hpp"

#pragma STDC FP_CONTRACT ON
// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD -1

#pragma STDC CX_LIMITED_RANGE ON

#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define _XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1

#include <float.h>
#include <math.h>
#include "boost/tuple/tuple.hpp"

using namespace ::boost::tuples;

const float_t F=1.0f,Fm1=-1.0f;
const double_t Dm1=-1.0,D=1.0;
const double_t D0=0.0;
const float_t F0=0.0f;

#include <algorithm>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
// #include <locale> // utf-16
// #include <uchar.h> // utf-16
// #include <stdfloat>  //  c++23

#include <time.h>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/typeof/boost/chrono/chrono.hpp>

// using namespace std::chrono_literals;

boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
int32_t tmm=166666660;
struct timespec rem;
struct timespec req={0,tmm};

#include "../../include/shader/gl.hpp"

GLfloat xx;
GLfloat yy;
GLfloat Tm;
GLfloat delt;
GLdouble wi,hi;
GLfloat Tdlt;
int32_t ele=36;
boost::chrono::duration<float_t,boost::chrono::seconds::period>time_spana;
double_t Ttime;
boost::chrono::duration<double_t,boost::chrono::seconds::period>time_spanb;
GLint iFrame,iFps,fram;
GLfloat mouseY,mouseX;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
// int32_t Size;
int32_t Size;
GLfloat mX,mY,mm,nn;
GLfloat gF=F,gF0=F0,gFm1=Fm1;
GLclampf x,y;
GLdouble gD=1.0,gD0=0.0,gDm1=-1.0;
float S;
GLsizei s4=4,i;
GLuint EBO,VBO,VCO,ECO;
GLuint uni_mse,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps,smp_chn_res,smp_chn[4];
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
// "#pragma STDGL(unroll none)\n"
// "#pragma optionNV(unroll none)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma optionNV(ifcvt none)\n"
// "#pragma STDGL(inline none)\n"
// "#pragma optionNV(inline none)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
"precision mediump float;\n";

const GLchar vrt_bdy_src[]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

const GLchar frg_hdr_src[]=
"precision lowp sampler3D;precision lowp sampler2D;"
"precision lowp samplerCube;precision lowp sampler2DArray;precision lowp sampler2DShadow;"
"precision lowp isampler2D;precision lowp isampler3D;precision lowp isamplerCube;"
"precision lowp isampler2DArray;precision lowp usampler2D;precision lowp usampler3D;"
"precision lowp usamplerCube;precision lowp usampler2DArray;precision lowp samplerCubeShadow;"
"precision lowp sampler2DArrayShadow;"
"uniform float iTime;uniform lowp float iTimeDelta;uniform float iFrameRate;uniform lowp vec4 iDate;uniform lowp float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform lowp vec3 iChannelResolution[4];uniform highp vec3 iResolution;uniform vec4 iMouse;uniform lowp float iSampleRate;"
"out highp vec4 fragColor;\n";

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

static const EGLint att_lst2[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
EGL_NONE,EGL_NONE
};

static const EGLint ctx_att[]={
// EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)7,
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};
static const EGLint att_lst[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
// EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_RED_SIZE,(EGLint)32,
EGL_GREEN_SIZE,(EGLint)32,
EGL_BLUE_SIZE,(EGLint)32,
EGL_ALPHA_SIZE,(EGLint)32,
EGL_DEPTH_SIZE,(EGLint)32,
EGL_STENCIL_SIZE,(EGLint)32,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_COVERAGE_BUFFERS_NV,(EGLint)1,
EGL_COVERAGE_SAMPLES_NV,(EGLint)1,
EGL_SAMPLES,(EGLint)1,
EGL_MIPMAP_LEVEL,(EGLint)1,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE,
EGL_NONE,EGL_NONE
};

#include <emscripten/html5.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp.h"

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;

EM_BOOL ms_clk(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL ms_mv(int,const EmscriptenMouseEvent *,void *);
