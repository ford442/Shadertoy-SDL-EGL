#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
// #pragma STDC CX_LIMITED_RANGE OFF
#pragma STDC FP_CONTRACT ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1

void avgFrm(short int,int,float *,float *);

extern "C"{
  
void b3_egl();
void str();
void b3();
void nano(short int,int,float *,float *);

}

void renderFrame();

double wi_js,hi_js;
double wi,hi;
float cMouseY,cMouseX,mouseY,mouseX;

float Fv=1.0f;
float Fm1v=1.0f;
const float * F=&Fv,Fm1=&Fm1v;

double TtimeDelta;

double * Dv=1.0;
double * Dm1v=-1.0;
const double Dm1=&Dm1v,D=&Dv;

int iFrame,iwi,ihi;
double Ttime;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader1.toy");

#include <math.h>
float_t * F0v=0.0f;
double_t * D0v=0.0;
const float_t F0=&F0v;
const double_t D0=&D0v;

#include <time.h>
#include <chrono>

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;
std::chrono::steady_clock::time_point t3;

struct timespec rem;
struct timespec req={0,16666666};

// #include <stdfloat>  //  c++23

#include "../../include/combine/gl.hpp"

void clrclr(GLclampf,GLclampf,GLclampf);

extern "C"{

void clr(GLclampf,GLclampf,GLclampf);

}

void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

int Size_js,sSize;
GLclampf avrg,drk,brt,avr;
GLint iFps;
GLclampf mX,mY;
GLclampf mm,nn;
GLuint atb_pos;

GLclampf x,y,gF=&Fv,gF0=&F0v,gFm1=&Fm1v;
GLclampd gD=&Dv,gD0=&D0v,gDm1=&Dm1v;

GLfloat g1g=&Fv,S;

GLsizei s4=4,i;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res,VCO,ECO,vtx,frag,uni_mse,shader,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps;
typedef struct{GLclampf XYZW[4];}Vertex;
const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};

GLubyte * gu0v=0,gu1v=1,gu2v=2,gu3v=3,gu4v=4,gu5v=5,gu6v=6,gu7v=7,gu8v=8,gu9v=9;
const GLubyte gu0=&gu0v,gu1=&gu1v,gu2=&gu2v,gu3=&gu3v,gu4=&gu4v,gu5=&gu5v,gu6=&gu6v,gu7=&gu7v,gu8=&gu8v,gu9=&gu9v;

const GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
const GLchar * sources[4];
const GLchar common_shader_header_gles3[]=
"#version 300 es\n"
// "#extension EGL_KHR_gl_colorspace : enable\n"
// "#extension EGL_EXT_gl_colorspace_scrgb : enable\n"
// "#extension EGL_EXT_gl_colorspace_scrgb_linear : enable\n"
// "#extension EGL_EXT_gl_colorspace_bt2020_pq : enable\n"
// "#extension EGL_EXT_gl_colorspace_display_p3 : enable\n"
// "#extension EGL_EXT_gl_colorspace_display_p3_linear : enable\n"
"#pragma STDGL(precise all)\n"
"#pragma optionNV(precise all)\n"
"#pragma STDGL(fastmath off)\n"
"#pragma optionNV(fastmath off)\n"
"#pragma STDGL(fastprecision off)\n"
"#pragma optionNV(fastprecision off)\n"
"#pragma STDGL(unroll auto)\n"
"#pragma optionNV(unroll auto)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma optionNV(ifcvt none)\n"
"#pragma STDGL(inline all)\n"
"#pragma optionNV(inline all)\n"
"#pragma STDGL(strict on)\n"
"#pragma optionNV(strict on)\n"
"#pragma optionNV(invariant none)\n"
"#pragma STDGL(invariant none)\n"
"#pragma optionNV(centroid all)\n"
"#pragma STDGL(centroid all)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
"precision highp float;precision mediump int;precision mediump sampler3D;precision mediump sampler2D;"
"precision mediump samplerCube;precision mediump sampler2DArray;precision mediump sampler2DShadow;"
"precision mediump isampler2D;precision mediump isampler3D;precision mediump isamplerCube;"
"precision mediump isampler2DArray;precision mediump usampler2D;precision mediump usampler3D;"
"precision mediump usamplerCube;precision mediump usampler2DArray;precision mediump samplerCubeShadow;"
"precision mediump sampler2DArrayShadow;\n";
const GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
const GLchar fragment_shader_header_gles3[]=
"uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out vec4 fragColor;\n";
const GLchar fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\0";
const GLchar * common_shader_header=common_shader_header_gles3;
const GLchar * vertex_shader_body=vertex_shader_body_gles3;
const GLchar * fragment_shader_header=fragment_shader_header_gles3;
const GLchar * fragment_shader_footer=fragment_shader_footer_gles3;

GLchar * rd_fl(const char *);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

#include "../../include/combine/egl.hpp"

void egl();

EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;

EGLint const attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE
};

EGLint const anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE
};

EGLint const attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
// EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_TRANSPARENT_TYPE,EGL_TRANSPARENT_RGB,
// EGL_TRANSPARENT_RED_VALUE,(EGLint)1000000000,
// EGL_TRANSPARENT_GREEN_VALUE,(EGLint)1000000000,
// EGL_TRANSPARENT_BLUE_VALUE,(EGLint)0,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_RED_SIZE,(EGLint)8,
EGL_GREEN_SIZE,(EGLint)8,
EGL_BLUE_SIZE,(EGLint)8,
EGL_ALPHA_SIZE,(EGLint)8,
EGL_DEPTH_SIZE,(EGLint)24,
EGL_STENCIL_SIZE,(EGLint)8,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_COVERAGE_BUFFERS_NV,(EGLint)1,
EGL_COVERAGE_SAMPLES_NV,(EGLint)32,
EGL_SAMPLES,(EGLint)32,
// EGL_MIPMAP_LEVEL,(EGLint)1,
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};

EGLContext contextegl_js;
EGLDisplay display_js;
EGLSurface surface_js;
EGLConfig eglconfig_js;
EGLint config_size_js,major_js,minor_js;

EGLint const attribut_list_js[]={ 
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE
};

EGLint const anEglCtxAttribs2_js[]={
EGL_CONTEXT_CLIENT_VERSION,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE
};

EGLint const attribute_list_js[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR|EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_CONFIG_CAVEAT,EGL_NONE,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_TRANSPARENT_TYPE,EGL_TRANSPARENT_RGB,
// EGL_TRANSPARENT_RED_VALUE,(EGLint)128,
// EGL_TRANSPARENT_GREEN_VALUE,(EGLint)128,
// EGL_TRANSPARENT_BLUE_VALUE,(EGLint)0,
// // EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_RED_SIZE,(EGLint)8,
EGL_GREEN_SIZE,(EGLint)8,
EGL_BLUE_SIZE,(EGLint)8,
EGL_ALPHA_SIZE,(EGLint)8,
EGL_DEPTH_SIZE,(EGLint)24,
EGL_STENCIL_SIZE,(EGLint)8,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_COVERAGE_BUFFERS_NV,(EGLint)1,
EGL_COVERAGE_SAMPLES_NV,(EGLint)32,
EGL_SAMPLES,(EGLint)32,
// EGL_MIPMAP_LEVEL,(EGLint)1,
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};

#include <emscripten.h>
#include <emscripten/html5.h>

EmscriptenWebGLContextAttributes attr_js;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx_js;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;

EM_BOOL mouse_call_click(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL mouse_call_move(int,const EmscriptenMouseEvent *,void *);

#include "../../include/combine/intrins.hpp"
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <iostream>
