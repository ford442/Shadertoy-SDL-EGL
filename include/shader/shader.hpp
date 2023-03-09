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
// #include <stdfloat>  //  c++23

// double_t wi,hi;
double wi,hi;

float cMouseY,cMouseX,mouseY,mouseX,F=1.0f,Fm1=-1.0f;
// float_t F0=0.0f;
float F0=0.0f;
// double Ttime,TtimeDelta,Dm1=-1.0,D=1.0;
long double Ttime,TtimeDelta,Dm1=-1.0,D=1.0;
// double_t D0=0.0;
long double D0=0.0;
std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;
std::chrono::steady_clock::time_point t3;

struct timespec rem;
struct timespec req={0,16666666};

#include "../../include/shader/gl.hpp"

const char * filename=reinterpret_cast<const char *>("/shader/shader1.toy");

GLint fram;
GLfloat mX,mY,mm,nn;
GLfloat delt,shtime;
GLuint atb_pos;
GLclampf x,y,gF=F,gF0=F0,gFm1=Fm1,y1y=F;
GLclampd gD=D,gD0=D0,gDm1=Dm1;
GLfloat g1g=F,S;
GLsizei s4=4,i;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res,VCO,ECO,vtx,frag,uni_mse,shader,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps;
typedef struct{GLclampf XYZW[4];}Vertex;
const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
GLchar * sources[4];
GLchar common_shader_header_gles3[]=
"#version 300 es\n"
"#extension EGL_KHR_gl_colorspace : enable\n"
"#extension EGL_EXT_gl_colorspace_scrgb : enable\n"
"#extension EGL_EXT_gl_colorspace_bt2020_pq : enable\n"
"#extension EGL_EXT_gl_colorspace_display_p3 : enable\n"
"#pragma STDGL(precise none)\n"
"#pragma optionNV(precise none)\n"
"#pragma STDGL(fastmath off)\n"
"#pragma optionNV(fastmath off)\n"
"#pragma STDGL(fastprecision off)\n"
"#pragma optionNV(fastprecision off)\n"
"#pragma STDGL(unroll none)\n"
"#pragma optionNV(unroll none)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma optionNV(ifcvt none)\n"
"#pragma STDGL(inline none)\n"
"#pragma optionNV(inline none)\n"
"#pragma STDGL(strict off)\n"
"#pragma optionNV(strict off)\n"
"#pragma optionNV(invariant none)\n"
"#pragma STDGL(invariant none)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
  
  /*
"precision highp int;precision highp float;precision highp sampler3D;precision highp sampler2D;"
"precision highp samplerCube;precision highp sampler2DArray;precision highp sampler2DShadow;"
"precision highp isampler2D;precision highp isampler3D;precision highp isamplerCube;"
"precision highp isampler2DArray;precision highp usampler2D;precision highp usampler3D;"
"precision highp usamplerCube;precision highp usampler2DArray;precision highp samplerCubeShadow;"
"precision highp sampler2DArrayShadow;\n";
GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;gl_PointSize=1.0;}\n";
GLchar fragment_shader_header_gles3[]=
"uniform highp float iTime;uniform highp float iTimeDelta;uniform highp float iFrameRate;uniform highp vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform highp vec3 iChannelResolution[4];uniform highp vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out highp vec4 fragColor;\n";
*/

"precision mediump int;precision mediump float;precision mediump sampler3D;precision mediump sampler2D;"
"precision mediump samplerCube;precision mediump sampler2DArray;precision mediump sampler2DShadow;"
"precision mediump isampler2D;precision mediump isampler3D;precision highp isamplerCube;"
"precision mediump isampler2DArray;precision mediump usampler2D;precision mediump usampler3D;"
"precision mediump usamplerCube;precision mediump usampler2DArray;precision mediump samplerCubeShadow;"
"precision mediump sampler2DArrayShadow;\n";
GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;gl_PointSize=1.0;}\n";
GLchar fragment_shader_header_gles3[]=
"uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out vec4 fragColor;\n";


GLchar fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\0";
GLchar * common_shader_header=common_shader_header_gles3;
GLchar * vertex_shader_body=vertex_shader_body_gles3;
GLchar * fragment_shader_header=fragment_shader_header_gles3;
GLchar * fragment_shader_footer=fragment_shader_footer_gles3;

void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint compile_shader(GLenum,GLsizei,GLchar **);

GLchar * read_file(const char *);
// char16_t * read_file(const char *);

#include "../../include/shader/egl.hpp"

// int_fast32_t iFrame,iwi,ihi;
long long iFrame,iwi,ihi;
GLint iFps,sSize;
// int iFrame,iFps,Size;

void renderFrame();

EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;

EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE
};

EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
//EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE
};

EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT|EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
// EGL_CONFIG_CAVEAT,EGL_NONE,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
// EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_TRANSPARENT_TYPE,EGL_TRANSPARENT_RGB,
// EGL_TRANSPARENT_RED_VALUE,(EGLint)1000000000,
// EGL_TRANSPARENT_GREEN_VALUE,(EGLint)1000000000,
// EGL_TRANSPARENT_BLUE_VALUE,(EGLint)0,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_RED_SIZE,(EGLint)64,
EGL_GREEN_SIZE,(EGLint)64,
EGL_BLUE_SIZE,(EGLint)64,
EGL_ALPHA_SIZE,(EGLint)64,
EGL_DEPTH_SIZE,(EGLint)64,
EGL_STENCIL_SIZE,(EGLint)64,
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_SAMPLES,(EGLint)64,
EGL_MIPMAP_LEVEL,(EGLint)64,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
EGL_NONE
};

#include <emscripten.h>
#include <emscripten/html5.h>

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;

EM_BOOL mouse_call_click(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL mouse_call_move(int,const EmscriptenMouseEvent *,void *);

extern "C"{

void str();

}
