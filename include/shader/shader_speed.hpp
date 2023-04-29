#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

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

struct
{
const float_t F=1.0f,Fm1=-1.0f;
const double_t Dm1=-1.0,D=1.0;
const double_t D0=0.0;
const float_t F0=0.0f;
}cpu;

struct
{
GLfloat gF=cpu.F,gF0=cpu.F0,gFm1=cpu.Fm1;
GLdouble gD=1.0,gD0=0.0,gDm1=-1.0;
}gpu;

typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vrt[]={{gpu.gFm1,gpu.gFm1,gpu.gF,gpu.gF},{gpu.gF,gpu.gFm1,gpu.gF,gpu.gF},{gpu.gF,gpu.gF,gpu.gF,gpu.gF},{gpu.gFm1,gpu.gF,gpu.gF,gpu.gF},{gpu.gFm1,gpu.gFm1,gpu.gFm1,gpu.gF},{gpu.gF,gpu.gFm1,gpu.gFm1,gpu.gF},{gpu.gF,gpu.gF,gpu.gFm1,gpu.gF},{gpu.gFm1,gpu.gF,gpu.gF,gpu.gF}};

const GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

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
"precision mediump float;precision mediump int;\n";

const GLchar vrt_bdy_src[]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

const GLchar frg_hdr_src[]=
"precision lowp sampler3D;precision lowp sampler2D;"
"precision lowp samplerCube;precision lowp sampler2DArray;precision lowp sampler2DShadow;"
"precision lowp isampler2D;precision lowp isampler3D;precision lowp isamplerCube;"
"precision lowp isampler2DArray;precision lowp usampler2D;precision lowp usampler3D;"
"precision lowp usamplerCube;precision lowp usampler2DArray;precision lowp samplerCubeShadow;"
"precision lowp sampler2DArrayShadow;"
"uniform highp float iTime;uniform highp float iTimeDelta;uniform highp float iFrameRate;uniform lowp vec4 iDate;uniform lowp float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform highp vec3 iResolution;uniform vec4 iMouse;uniform highp float iSampleRate;"
"out highp vec4 fragColor;\n";

const GLchar frg_ftr_src[]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";


static const EGLint att_lst2[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
EGL_NONE,EGL_NONE
};

static const EGLint ctx_att[]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)7,
// EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};
static const EGLint att_lst[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
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
EGL_DEPTH_SIZE,(EGLint)24,
EGL_STENCIL_SIZE,(EGLint)8,
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,(EGLint)1,
EGL_COVERAGE_BUFFERS_NV,(EGLint)1,
EGL_COVERAGE_SAMPLES_NV,(EGLint)1,
EGL_SAMPLES,(EGLint)1,
EGL_MIPMAP_LEVEL,(EGLint)1,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE,
EGL_NONE,EGL_NONE
};

class Run
{

private:
  
long int length=0;
char8_t * result=NULL;
GLchar * results=NULL;
  
std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::high_resolution_clock::time_point t3;
  int32_t tmm=166666660;
struct timespec rem;
struct timespec req={0,tmm};

// using namespace std::chrono;

GLfloat S,xx,yy,Tm,delt,Tdlt,mouseY,mouseX,mX,mY,mm,nn;
GLdouble wi,hi,Ttime;
GLint Size,iFrame,iFps,fram,ele=36;
std::chrono::duration<GLdouble,std::chrono::seconds::period>time_spana;
std::chrono::duration<GLdouble,std::chrono::seconds::period>time_spanb;
GLclampf x,y;
GLuint EBO,VBO,VCO,ECO;
GLuint uni_mse,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm,uni_fps,smp_chn_res,smp_chn[4];
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
EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;
EM_BOOL ms_l,clk_l;
  
public:

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
x=e->clientX;
y=e->clientY;
}}
return (EM_BOOL)1;
}

inline void uni(GLfloat xx,GLfloat yy,GLfloat Tm,GLint fram,GLfloat delt){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const GLfloat xxx=xx;
const GLfloat yyy=yy;
mX=1.0-(xxx*Size);
mY=1.0-(yyy*Size);
clk_l=false;
}
mm=S*xx;
nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,Tm);
glUniform1f(uni_tme_dlt,delt);
glUniform1i(uni_frm,fram);
return;
}

// static inline void(*un)(GLfloat,GLfloat,GLfloat,GLint,GLfloat){&uni};

inline void Rend(){
iFrame++;
t3=t2;
t2=std::chrono::high_resolution_clock::now();
time_spana=std::chrono::duration<GLdouble,std::chrono::seconds::period>(t2-t1);
time_spanb=std::chrono::duration<GLdouble,std::chrono::seconds::period>(t2-t3);
Ttime=time_spana.count();
Tdlt=time_spanb.count();
mouseX=x/S;
mouseY=(S-y)/S;
run.uni(mouseX,mouseY,Ttime,iFrame,Tdlt);
// glClear(GL_COLOR_BUFFER_BIT);
// glClear(GL_DEPTH_BUFFER_BIT);
// glClear(GL_STENCIL_BUFFER_BIT);
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
// glFlush();
// glFinish();
// nanosleep(&req,&rem);
return;
}
  
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
tie(cpu.F,cpu.Fm1,cpu.F0);
tie(gpu.gF,gpu.gFm1,gpu.gF0);
tie(cpu.D,cpu.Dm1,cpu.D0);
tie(gpu.gD,gpu.gDm1,gpu.gD0);
tie(iFrame,iFps);
tie(mouseY,mouseX,x,y);
tie(gu0,gu1,gu2,gu3);
tie(gu4,gu5,gu6);
tie(gu7,gu8,gu9);
tie(Tdlt,Ttime);
tie(mouseY,mouseX);
tie(hi,wi,S);
tie(mX,mY,mm,nn);
tie(s4,i);
tie(t1,t2,t3);
tie(EBO,VBO);
tie(VCO,ECO);
tie(config_size,major,minor);
tie(display,surface,eglconfig);
tie(attr,ctxegl,ctx);
tie(uni_fps,uni_srate,uni_frm,fram);
tie(uni_tme,uni_tme_dlt,Tm,delt);
tie(smp_chn_res,smp_chn,uni_res);
tie(cm_hdr_src,vrt_bdy_src,frg_hdr_src,frg_ftr_src);
tie(vrt,indc,ele);
tie(retCl,retMu,retMd,retMv);
tie(retSa,retSb,retSc);
tie(ms_l,clk_l);
tie(un,Rend,uni);
tie(time_spana,time_spanb);
tie(xx,yy,uni_mse);
tie(rem,req,tmm);
eglconfig=NULL;
iFrame=0;
clk_l=true;
GLchar * frag_body=rd_fl(Fnm);
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
eglBindAPI(EGL_OPENGL_API);
//   eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,att_lst,&eglconfig,(EGLint)1,&config_size);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
eglMakeCurrent(display,surface,surface,ctxegl);
emscripten_webgl_make_context_current(ctx);
glUseProgram(0);
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=static_cast<int32_t>(hi);
S=static_cast<GLfloat>(wi);
// S=Size;
mX=0.5*S;
mY=0.5*S;
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
glClearDepth(D);
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
glClearColor(gF0,gF0,gF0,gF);
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_STREAM_DRAW);
// nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STREAM_DRAW);
// nanosleep(&req,&rem);
src[0]=cm_hdr;
src[1]=vrt_bdy;
const GLuint vtx=cmpl_shd(GL_VERTEX_SHADER,2,src);
src[0]=cm_hdr;
src[1]=frg_hdr;
// src[2]=frg_aa;
src[2]=frag_body;
src[3]=frg_ftr;
const GLuint frag=cmpl_shd(GL_FRAGMENT_SHADER,4,src);
// nanosleep(&req,&rem);
const GLuint shd_prg=glCreateProgram();
tie(shd_prg,frag,vtx);
glAttachShader(shd_prg,frag);
glAttachShader(shd_prg,vtx);
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&VCO);
glBindVertexArray(VCO);
const GLuint atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_tme_dlt=glGetUniformLocation(shd_prg,"iTimeDelta");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_fps=glGetUniformLocation(shd_prg,"iFrameRate");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
uni_srate=glGetUniformLocation(shd_prg,"iSampleRate");
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
glUniform1f(uni_srate,44100.0f);
glUniform3f(uni_res,S,S,gF);
glUniform3f(smp_chn_res,S,S,gF);
iFps=96.0;
glUniform1f(uni_fps,iFps);
glViewport((GLint)0,(GLint)0,Size,Size);  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,Size,Size);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
t1=std::chrono::high_resolution_clock::now();
t3=std::chrono::high_resolution_clock::now();
time_spanb=std::chrono::duration<float_t,std::chrono::seconds::period>(t2-t3);
time_spana=std::chrono::duration<double_t,std::chrono::seconds::period>(t2-t1);
nanosleep(&req,&rem);
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
glFlush();
glFinish();
nanosleep(&req,&rem);
emscripten_set_main_loop((void(*)())Rend,0,0);
return;
}
  
};





// static inline void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

// static inline GLuint cmpl_shd(GLenum,GLsizei,const GLchar **);

// static inline GLchar * rd_fl(const char *);




// static inline EM_BOOL ms_clk(int,const EmscriptenMouseEvent *,void *);

// static inline EM_BOOL ms_mv(int,const EmscriptenMouseEvent *,void *);
