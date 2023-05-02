#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#pragma STDC FP_CONTRACT ON

// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0

#pragma STDC CX_LIMITED_RANGE ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define _XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP 1

#include "../../include/shader/intrins.hpp"
#include <emscripten.h>
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
#include <chrono>
#include "../../include/shader/gl.hpp"
#include "../../include/shader/egl.hpp"
#include <emscripten/html5.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp.h"
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <float.h>
#include <math.h>
#include "boost/tuple/tuple.hpp"

extern "C"{
  
void str();
  
}

using namespace ::boost::tuples;

class Compile
{

private:

GLsizei i;
  
public:
  
inline GLuint cmpl_shd(GLenum type,GLsizei nsrc,const GLchar ** src){
GLsizei srclens[nsrc];
for(i=0;i<nsrc;i++){
srclens[i]=static_cast<GLsizei>(strlen(src[i]));
}
const GLuint shader=glCreateShader(type);
glShaderSource(shader,nsrc,src,srclens);
glCompileShader(shader);
return shader;
}

};

using namespace boost::numeric::ublas;

const GLchar cm_hdr_src[500]=
"#version 300 es\n"
"#pragma STDGL(fastmath on)\n"
"#pragma optionNV(fastmath on)\n"
"#pragma STDGL(fastprecision on)\n"
"#pragma optionNV(fastprecision on)\n"
// "#pragma STDGL(unroll all)\n"
// "#pragma optionNV(unroll all)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma optionNV(ifcvt none)\n"
"#pragma STDGL(inline all)\n"
"#pragma optionNV(inline all)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
// "#define GL_ES 0\n"
"precision highp float;\n";
// "precision mediump int;\n";

const GLchar vrt_bdy_src[100]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

const GLchar frg_hdr_src[1000]=
"precision lowp sampler3D;precision lowp sampler2D;"
"precision lowp samplerCube;precision lowp sampler2DArray;precision lowp sampler2DShadow;"
"precision lowp isampler2D;precision lowp isampler3D;precision lowp isamplerCube;"
"precision lowp isampler2DArray;precision lowp usampler2D;precision lowp usampler3D;"
"precision lowp usamplerCube;precision lowp usampler2DArray;precision lowp samplerCubeShadow;"
"precision lowp sampler2DArrayShadow;"
"uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out vec4 fragColor;\n";

const GLchar frg_ftr_src[100]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";

const EGLint att_lst2[1000]={ 
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

const EGLint ctx_att[500]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)7,
// EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};

const EGLint att_lst[1500]={
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
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_COVERAGE_BUFFERS_NV,(EGLint)1,
EGL_COVERAGE_SAMPLES_NV,(EGLint)1,
EGL_SAMPLES,(EGLint)1,
EGL_MIPMAP_LEVEL,(EGLint)1,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE,
EGL_NONE,EGL_NONE
};

EM_BOOL ms_l,clk_l;

using gld_tensor=tensor<GLdouble>;
using mouse_tensor=tensor<GLdouble>;
using shad_tensor=tensor<GLuint>;
using sz_tensor=tensor<int>;
using f_tensor=tensor<GLfloat>;
using d_tensor=tensor<GLdouble>;

gld_tensor gld=gld_tensor{10,2};
shad_tensor Sh=shad_tensor{3,2};
sz_tensor Si=sz_tensor{1,1};
f_tensor t_time=f_tensor{3,3};
f_tensor FL=f_tensor{6,1};
f_tensor Fi=f_tensor{1,3};
d_tensor Di=d_tensor{1,3};

class GPU{

private:
float cF=1.0f;
float cF0=0.0f;
float cFm1=-1.0f;
double cD=1.0;
double cDm1=-1.0;
double_t cD0=0.0;

public:

inline GLuint PRGin(GLuint prg){
Sh.at(2,1)=prg;
return 0;
}

inline GLuint PRGout(){
return Sh.at(2,1);
}

inline float setFloats(){
Fi.at(0,0)=1.0f;
Fi.at(0,1)=-1.0f;
Fi.at(0,2)=0.0f;
Di.at(0,0)=1.0;
Di.at(0,1)=-1.0;
Di.at(0,2)=0.0;
return 0.0;
}
  
inline GLfloat gF(){
return Fi.at(0,0);
}

inline GLfloat gFm1(){
return Fi.at(0,1);
}

inline GLfloat gF0(){
return Fi.at(0,2);
}

inline GLdouble gD(){
return Di.at(0,0);
}

inline GLdouble gDm1(){
return Di.at(0,1);
}

inline GLdouble gD0(){
return Di.at(0,2);
}

GLfloat u_iTime_set(GLfloat set){
t_time.at(0,0)=set;
return 0.0;
}

inline GLfloat u_iTime_get(){
return t_time.at(0,0);
}
  
};

const inline GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const inline GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

struct{
  
// GLfloat Ttime=FL.at(0,0);
  GLfloat uni_tme;
// GLfloat Tm=FL.at(4,0);

GLfloat Tdlt=FL.at(1,0);
GLfloat uni_tme_dlt;
GLfloat delt;
GLuint uni_frm;
GLint iFrame;
  
std::chrono::duration<GLfloat,std::chrono::seconds::period>time_spana;
std::chrono::duration<GLfloat,std::chrono::seconds::period>time_spanb;
std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::high_resolution_clock::time_point t3;
}times;

struct{
GLuint EBO=Sh.at(1,0);
GLuint VBO=Sh.at(1,1);
GLuint VCO=Sh.at(2,0);

}shad;

struct{
GLdouble xx=gld.at(0,0);
GLdouble yy=gld.at(0,1);
GLdouble mX=gld.at(1,0);
GLdouble mY=gld.at(1,1);
GLdouble mm=gld.at(2,0);
GLdouble nn=gld.at(2,1);
GLfloat uni_mse=FL.at(6,0);
GLfloat S=FL.at(7,0);
GLfloat mouseY=FL.at(8,0);
GLfloat mouseX=FL.at(9,0);
GLdouble wi=gld.at(3,0);
GLdouble hi=gld.at(3,1);
GLclampf x=FL.at(10,0);
GLclampf y=FL.at(11,0);
}mouse;

int Size=Si.at(12,0);
GLint tmm=166666000;
struct timespec rem;
struct timespec req={0,tmm};
GLint ele=36;
EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

inline EM_BOOL ms_clk(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

inline EM_BOOL ms_mv(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mouse.x=e->clientX;
mouse.y=e->clientY;
}}
return (EM_BOOL)1;
}

class Run{

private:

Compile compile;
  
long int length=0;
char8_t * result=NULL;
GLchar * results=NULL;
GLint iFps;
GLuint uni_srate,uni_res,uni_fps,smp_chn_res,smp_chn[4];
EGLDisplay display;
EGLSurface surface;
EGLContext ctxegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
const GLchar * src[4];
const GLchar * cm_hdr=cm_hdr_src;
const GLchar * vrt_bdy=vrt_bdy_src;
const GLchar * frg_hdr=frg_hdr_src;
const GLchar * frg_ftr=frg_ftr_src;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

GPU gpu;
  
public:

inline void uni(GLfloat xx,GLfloat yy,GLint fram,GLfloat delt){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const GLfloat xxx=xx;
const GLfloat yyy=yy;
mouse.mX=1.0f-(xxx*Size);
mouse.mY=1.0f-(yyy*Size);
clk_l=false;
}
mouse.mm=mouse.S*xx;
mouse.nn=mouse.S*yy;
glUniform4f(mouse.uni_mse,mouse.mm,mouse.nn,mouse.mX,mouse.mY);
}else{
clk_l=true;
}
glUniform1f(times.uni_tme,gpu.u_iTime_get());
glUniform1f(times.uni_tme_dlt,delt);
glUniform1i(times.uni_frm,fram);
return;
}

inline void Rend(){
times.iFrame++;
times.t3=times.t2;
times.t2=std::chrono::high_resolution_clock::now();
times.time_spana=std::chrono::duration<GLfloat,std::chrono::seconds::period>(times.t2-times.t1);
times.time_spanb=std::chrono::duration<GLfloat,std::chrono::seconds::period>(times.t2-times.t3);
gpu.u_iTime_set(times.time_spana.count());
times.Tdlt=times.time_spanb.count();
if(ms_l==true){
mouse.mouseX=mouse.x/mouse.S;
mouse.mouseY=(mouse.S-mouse.y)/mouse.S;
}
uni(mouse.mouseX,mouse.mouseY,times.iFrame,times.Tdlt);
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
return;
}

void(rndr)(){Run::Rend();};

inline GLchar * rd_fl(const char * Fnm){
FILE * file=fopen(Fnm,"r");
tie(result,results,file);
if(file){
int stat=fseek(file,(int)0,SEEK_END);
if(stat!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
stat=fseek(file,(int)0,SEEK_SET);
if(stat!=0){
fclose(file);
return nullptr;
}
result=static_cast<char8_t *>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
results=reinterpret_cast<GLchar *>(result);
return results;
}
return nullptr;
}
  
inline void strt(){
typedef struct{GLfloat XYZW[4];}Vertex;
gpu.setFloats();
const Vertex vrt[]={{gpu.gFm1(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gFm1(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()}};

  /*
Fi.at(0,0)=1.0f;
Fi.at(0,2)=0.0f;
Fi.at(0,1)=-1.0f;
Di.at(0,0)=1.0;
Di.at(0,2)=0.0;
Di.at(0,1)=-1.0; */
tie(Fi,Di);
// tie(cpu,gpu);
// tie(cpu.F,cpu.Fm1,cpu.F0);
// tie(gpu.gF,gpu.gFm1,gpu.gF0);
// tie(cpu.D,cpu.Dm1,cpu.D0);
// tie(gpu.gD,gpu.gDm1,gpu.gD0);
tie(times.iFrame,iFps);
tie(mouse.mouseY,mouse.mouseX,mouse.x,mouse.y);
// tie(gu0,gu1,gu2,gu3);
// tie(gu4,gu5,gu6);
// tie(gu7,gu8,gu9);
tie(times.Tdlt,t_time);
tie(mouse.mouseY,mouse.mouseX);
tie(mouse.hi,mouse.wi,mouse.S);
tie(mouse.mX,mouse.mY,mouse.mm,mouse.nn);
tie(times.t1,times.t2,times.t3);
tie(shad.EBO,shad.VBO,shad.VCO);
tie(config_size,major,minor);
tie(display,surface,eglconfig);
tie(attr,ctxegl,ctx);
tie(uni_fps,uni_srate,times.uni_frm);
tie(times.uni_tme,times.uni_tme_dlt);
tie(smp_chn_res,smp_chn,uni_res);
tie(cm_hdr_src,vrt_bdy_src,frg_hdr_src,frg_ftr_src);
tie(vrt,indc,ele);
tie(retCl,retMu,retMd,retMv);
tie(retSa,retSb,retSc);
tie(ms_l,clk_l);
tie(times.time_spana,times.time_spanb);
tie(mouse.xx,mouse.yy,mouse.uni_mse);
tie(rem,req,tmm);
eglBindAPI(EGL_OPENGL_API);
eglconfig=NULL;
times.iFrame=0;
clk_l=true;
const GLchar * frag_body=rd_fl(Fnm);
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,att_lst,&eglconfig,(EGLint)1,&config_size);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
eglMakeCurrent(display,surface,surface,ctxegl);
emscripten_webgl_make_context_current(ctx);
glUseProgram(0);
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=static_cast<int>(mouse.hi);
mouse.S=static_cast<float>(Size);
// mouse.S=Size;
mouse.mX=0.5*mouse.S;
mouse.mY=0.5*mouse.S;
emscripten_webgl_enable_extension(ctx,"ARB_sample_shading");
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(ctx,"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(ctx,"NV_depth_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_half_float");
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
// emscripten_webgl_enable_extension(ctx,"EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_create_context");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx,"EXT_create_context_robustness");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB_write_control");
emscripten_webgl_enable_extension(ctx,"OES_sample_shading");
emscripten_webgl_enable_extension(ctx,"EXT_multisample_compatibility");
emscripten_webgl_enable_extension(ctx,"OES_vertex_half_float");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"NV_framebuffer_multisample");
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
glClearDepth(gpu.gD());
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
// glEnable(GL_DEPTH_TEST);
// glDepthFunc(GL_LESS);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
glDisable(GL_DITHER);
glFrontFace(GL_CW);
glEnable(GL_CULL_FACE);
// glDisable(GL_BLEND);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
// glClearColor(gpu.gF0,gpu.gF0,gpu.gF0,gpu.gF);
glClearColor(Fi.at(0,2),Fi.at(0,2),Fi.at(0,2),Fi.at(0,0));
glGenBuffers((GLsizei)1,&shad.VBO);
glBindBuffer(GL_ARRAY_BUFFER,shad.VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_STREAM_DRAW);
nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&shad.EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,shad.EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STREAM_DRAW);
nanosleep(&req,&rem);
src[0]=cm_hdr;
src[1]=vrt_bdy;
const GLuint vtx=compile.cmpl_shd(GL_VERTEX_SHADER,2,src);
src[0]=cm_hdr;
src[1]=frg_hdr;
// src[2]=frg_aa;
src[2]=frag_body;
src[3]=frg_ftr;
const GLuint frag=compile.cmpl_shd(GL_FRAGMENT_SHADER,4,src);
const GLuint shd_prg=glCreateProgram();
tie(shd_prg,frag,vtx);
glAttachShader(shd_prg,frag);
glAttachShader(shd_prg,vtx);
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
gpu.PRGin(shd_prg);
glUseProgram(gpu.PRGout());
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&shad.VCO);
glBindVertexArray(shad.VCO);
const GLuint atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
times.uni_tme=glGetUniformLocation(shd_prg,"iTime");
times.uni_tme_dlt=glGetUniformLocation(shd_prg,"iTimeDelta");
times.uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_fps=glGetUniformLocation(shd_prg,"iFrameRate");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
mouse.uni_mse=glGetUniformLocation(shd_prg,"iMouse");
uni_srate=glGetUniformLocation(shd_prg,"iSampleRate");
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
glUniform1f(uni_srate,44100.0f);
glUniform3f(uni_res,mouse.S,mouse.S,gpu.gF());
glUniform3f(smp_chn_res,mouse.S,mouse.S,gpu.gF());
iFps=96;
glUniform1f(uni_fps,iFps);
mouse.mm=mouse.S*0.5;
mouse.nn=mouse.S*0.5;
glUniform4f(mouse.uni_mse,mouse.mm,mouse.nn,mouse.mX,mouse.mY);
glViewport((GLint)0,(GLint)0,Size,Size);  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,Size,Size);
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
times.t1=std::chrono::high_resolution_clock::now();
times.t3=std::chrono::high_resolution_clock::now();
times.time_spanb=std::chrono::duration<float_t,std::chrono::seconds::period>(times.t2-times.t3);
times.time_spana=std::chrono::duration<double_t,std::chrono::seconds::period>(times.t2-times.t1);
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
glFlush();
glFinish();
  emscripten_set_main_loop((void(*)())rndr,0,0);
return;
}
  
};

inline EM_BOOL ms_clk(int,const EmscriptenMouseEvent *,void *);

inline EM_BOOL ms_mv(int,const EmscriptenMouseEvent *,void *);
