#include <emscripten.h>
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
#include <iostream>
#include <locale> // utf-16
#include <uchar.h> // utf-16
#include "../../include/shader/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 1
#pragma STDC CX_LIMITED_RANGE OFF
#pragma STDC FP_CONTRACT ON
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

// #include <stdfloat>  //  c++23
// double_t wi,hi;
double wi,hi;
float cMouseY,cMouseX,mouseY,mouseX;
const float F=1.0f,Fm1=-1.0f;
const float_t F0=0.0f;
// float F0=0.0f;
// double Ttime,Tdlt,Dm1=-1.0,D=1.0;
const double Dm1=-1.0,D=1.0;
// double Dm1=-1.0,D=1.0;
double Ttime,Tdlt;
const double_t D0=0.0;
// long double D0=0.0;
// double D0=0.0;
std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;
std::chrono::steady_clock::time_point t3;
struct timespec rem;
struct timespec req={0,16666666};

#include "../../include/shader/gl.hpp"

const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
GLint fram;
GLfloat mX,mY,mm,nn;
GLfloat delt,Tm;
GLuint atb_pos;
GLclampf x,y,gF=F,gF0=F0,gFm1=Fm1,y1y=F;
GLclampd gD=D,gD0=D0,gDm1=Dm1;
GLfloat g1g=F,S;
GLsizei s4=4,i;
// const GLuint vtx,frag;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res,VCO,ECO,uni_mse,shader,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps;
typedef struct{GLclampf XYZW[4];}Vertex;
Vertex vrt[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
const GLchar * src[4];
const GLchar cm_hdr_src[]=
"#version 300 es\n"
"#define mainImage mainImage0(out vec4 O,vec2 U);\n"
"#extension EGL_KHR_gl_colorspace : enable\n"
// "#extension EGL_EXT_gl_colorspace_scrgb : enable\n"
// "#extension EGL_EXT_gl_colorspace_scrgb_linear : enable\n"
// "#extension EGL_EXT_gl_colorspace_bt2020_pq_linear : enable\n"
// "#extension EGL_EXT_gl_colorspace_bt2020_pq : enable\n"
"#extension EGL_EXT_gl_colorspace_display_p3 : enable\n"
// "#extension EGL_EXT_gl_colorspace_display_p3_linear : enable\n"
"#pragma STDGL(precise all)\n"
"#pragma optionNV(precise all)\n"
"#pragma STDGL(fastmath off)\n"
"#pragma optionNV(fastmath off)\n"
"#pragma STDGL(fastprecision off)\n"
"#pragma optionNV(fastprecision off)\n"
"#pragma STDGL(unroll none)\n"
"#pragma optionNV(unroll none)\n"
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
"precision highp float;precision highp int;precision mediump sampler3D;precision highp sampler2D;"
"precision mediump samplerCube;precision highp sampler2DArray;precision lowp sampler2DShadow;"
"precision highp isampler2D;precision mediump isampler3D;precision mediump isamplerCube;"
"precision highp isampler2DArray;precision highp usampler2D;precision mediump usampler3D;"
"precision mediump usamplerCube;precision highp usampler2DArray;precision lowp samplerCubeShadow;"
"precision lowp sampler2DArrayShadow;\n";
const GLchar vrt_bdy_src[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
const GLchar frg_hdr_src[]=
"uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out vec4 fragColor;\n"
"int _N=3;\n"
"void mainImage(out vec4 O,vec2 U){\n"
"vec4 o;O=vec4(0);\n"
"for(int k=0;k<_N*_N;k++)\n"
"{mainImage0(o,U+vec2(k%_N-_N/2,k/_N-_N/2)/float(_N));O+=o;}\n"
"O/=float(_N*_N);\n"
"O=pow(O,vec4(2.2/1.));\n"
"}\n"
"void mainImage0\n";
const GLchar frg_ftr_src[]=
"\n void main(){mainImage(fragColor,fragCoord.xy);fragColor.a=1.0;}\0";
const GLchar * cm_hdr=cm_hdr_src;
const GLchar * vrt_bdy=vrt_bdy_src;
const GLchar * frg_hdr=frg_hdr_src;
const GLchar * frg_ftr=frg_ftr_src;

void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint cmpl_shd(GLenum,GLsizei,const GLchar **);

GLchar * rd_fl(const char *);

// char16_t * rd_fl(const char *);

#include "../../include/shader/egl.hpp"

// int_fast32_t iFrame,iwi,ihi;
int iFrame,iwi,ihi;
// long iFrame,iwi,ihi;
GLint iFps,sSize;
// int iFrame,iFps,Size;
void Rend();
EGLDisplay display;
EGLSurface surface;
EGLContext ctxegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;
EGLint att_lst2[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_LINEAR_EXT,
EGL_NONE
};
const EGLint ctx_att[]={
EGL_CONTEXT_CLIENT_VERSION,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE
};
const EGLint att_lst[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
// EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_RED_SIZE,(EGLint)16,
EGL_GREEN_SIZE,(EGLint)16,
EGL_BLUE_SIZE,(EGLint)16,
EGL_ALPHA_SIZE,(EGLint)16,
EGL_DEPTH_SIZE,(EGLint)32,
EGL_STENCIL_SIZE,(EGLint)16,
EGL_BUFFER_SIZE,(EGLint)32,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_SAMPLES,(EGLint)32,
// EGL_MIPMAP_LEVEL,(EGLint)32,
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};

#include <emscripten/html5.h>

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;

EM_BOOL ms_clk(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL ms_mv(int,const EmscriptenMouseEvent *,void *);

extern "C"{
  
void str();
  
}
