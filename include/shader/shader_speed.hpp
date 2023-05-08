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

#include <float.h>
#include <math.h>

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_USE_LONG_DOUBLE
#define BOOST_NO_EXCEPTIONS 

#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>

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
// #include <chrono>
#include "../../include/shader/gl.hpp"
#include "../../include/shader/egl.hpp"
#include <emscripten/html5.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp.h"

extern "C"{
  
void str();
  
}

class Compile
{

private:

GLsizei i;

public:

unsigned int cmpl_shd(GLenum type,GLsizei nsrc,const char ** src){
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

inline char cm_hdr_src[500]=
"#version 300 es\n"
"#pragma STDGL(fastmath on)\n"
"#pragma optionNV(fastmath on)\n"
// "#pragma STDGL(fastprecision on)\n"
// "#pragma optionNV(fastprecision on)\n"
// "#pragma STDGL(unroll all)\n"
// "#pragma optionNV(unroll all)\n"
// "#pragma STDGL(ifcvt none)\n"
// "#pragma optionNV(ifcvt none)\n"
// "#pragma STDGL(inline all)\n"
// "#pragma optionNV(inline all)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
// "#define GL_ES 0\n"
"precision mediump int;\n"
"precision highp float;\n";

inline char vrt_bdy_src[100]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

inline char frg_hdr_src[1000]=
"precision mediump sampler3D;precision mediump sampler2D;"
"precision mediump samplerCube;precision mediump sampler2DArray;precision mediump sampler2DShadow;"
"precision mediump isampler2D;precision mediump isampler3D;precision mediump isamplerCube;"
"precision mediump isampler2DArray;precision mediump usampler2D;precision mediump usampler3D;"
"precision mediump usamplerCube;precision mediump usampler2DArray;precision mediump samplerCubeShadow;"
"precision mediump sampler2DArrayShadow;"
"uniform highp float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"uniform vec3 iChannelResolution[4];uniform highp vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"out highp vec4 fragColor;\n";

inline char frg_ftr_src[100]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";

EGLint att_lst2[1000]={ 
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

EGLint ctx_att[500]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)7,
// EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};

EGLint att_lst[1500]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
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
// EGL_COVERAGE_BUFFERS_NV,(EGLint)1, // used to indicate, not set
//  EGL_COVERAGE_SAMPLES_NV,(EGLint)1, // used to indicate, not set
EGL_SAMPLES,(EGLint)32,
// EGL_MIPMAP_LEVEL,(EGLint)1, // used to indicate, not set
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX, // used to indicate, not set
EGL_NONE,EGL_NONE
};

inline EM_BOOL ms_l,clk_l;
using mouse_tensor=boost::numeric::ublas::tensor<boost::atomic<float>>;
using shad_tensor=boost::numeric::ublas::tensor<unsigned int>;
using prg_tensor=boost::numeric::ublas::tensor<unsigned int>;
using sz_tensor=boost::numeric::ublas::tensor<boost::atomic<int>>;
using f_tensor=boost::numeric::ublas::tensor<boost::atomic<float>>;
using d_tensor=boost::numeric::ublas::tensor<boost::atomic<double>>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using i_tensor=boost::numeric::ublas::tensor<boost::atomic<int>>;
using li_tensor=boost::numeric::ublas::tensor<long>;
using void_tensor=boost::numeric::ublas::tensor<boost::atomic<void *>>;

v_tensor sse=v_tensor{2,2};
v_tensor sse2=v_tensor{2,2};
v_tensor sse3=v_tensor{2,2};
v_tensor sse4=v_tensor{1,1};
shad_tensor Sh=shad_tensor{3,3};
prg_tensor S1=prg_tensor{1,1,1};
sz_tensor Si=sz_tensor{1,1};
d_tensor d_time=d_tensor{2,1};
f_tensor f_time=f_tensor{2,1};
f_tensor Fi=f_tensor{2,2};
d_tensor Di=d_tensor{2,2};
i_tensor uni_i=i_tensor{1,1};
f_tensor t_size=f_tensor{1,1};
li_tensor i_size=li_tensor{1,1};
void_tensor cntx=void_tensor{2,2};
i_tensor cntxi=i_tensor{2,2};
mouse_tensor mms=mouse_tensor{2,2};
li_tensor mms2=li_tensor{2,2};

class GPU{

private:

public:

const void EBOin(boost::uint_t<64>::exact EBO){
Sh.at(1,0)=EBO;
return;
}

const void VCOin(boost::uint_t<64>::exact VCO){
Sh.at(2,0)=VCO;
return;
}

const void VBOin(boost::uint_t<64>::exact VBO){
Sh.at(2,1)=VBO;
return;
}

const void setFloats(){
Fi.at(0,0)=1.0f;
Fi.at(0,1)=-1.0f;
Fi.at(1,1)=0.0f;
Di.at(0,0)=1.0;
Di.at(0,1)=-1.0;
Di.at(1,1)=0.0;
return;
}

inline float gF(){
return Fi.at(0,0);
}

inline float gFm1(){
return Fi.at(0,1);
}

inline float gF0(){
return Fi.at(1,1);
}

inline double gD(){
return Di.at(0,0);
}

inline double gDm1(){
return Di.at(0,1);
}

inline double gD0(){
return Di.at(1,1);
}

};

const inline unsigned char gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const unsigned char indc[35]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
inline unsigned int uni_srate,uni_res,uni_fps,smp_chn_res,smp_chn[4],uni_frm;
inline float uni_tme,uni_tme_dlt,uni_mse;

struct{
boost::chrono::duration<float,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<float,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::steady_clock::time_point t2;
boost::chrono::steady_clock::time_point t3;
}u_time;

struct{
unsigned int VBO,EBO,VCO;
}shad;

inline struct{
double wi;
double hi;
}mouse;

boost::atomic<int>Size;
boost::atomic<int>tmm=166666000;
boost::atomic<int>tmm2=1000;
inline struct timespec rem;
inline struct timespec req={0,tmm};
inline struct timespec req2={0,tmm2};
const boost::atomic<int>ele=36;

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

EM_BOOL ms_clk(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

EM_BOOL ms_mv(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mms2.at(0,0)=e->clientX;
mms2.at(0,1)=e->clientY;
}}
return (EM_BOOL)1;
}

class Run{

private:

Compile compile;

long int length=0;
char8_t * result=NULL;
char * results=NULL;
int32_t iFps;
EGLDisplay display;
EGLSurface surface;
EGLContext ctxegl;
EGLConfig eglconfig;
EGLint config_size,major,minor;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
const char * src[4];
char * cm_hdr=cm_hdr_src;
char * vrt_bdy=vrt_bdy_src;
char * frg_hdr=frg_hdr_src;
char * frg_ftr=frg_ftr_src;

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

GPU gpu;

public:

static inline void nanoPause(){
nanosleep(&req2,&rem);
}

static void PRGin(unsigned int prg){
sse4.at(0,0)=wasm_i64x2_splat(prg);
S1.at(0,0,0)=wasm_i64x2_extract_lane(sse4.at(0,0),0);
return;
}

static void u_iTime_set(double set){
d_time.at(0,0)=set;
sse2.at(0,0)=wasm_f64x2_splat(d_time.at(0,0));
d_time.at(0,0)=wasm_f64x2_extract_lane(sse2.at(0,0),0);
return;
}

static void u_iSize_set(float set){
sse.at(1,0)=wasm_f64x2_splat(set);
t_size.at(0,0)=wasm_f64x2_extract_lane(sse.at(1,0),0);
return;
}
  
static void i_iSize_set(boost::int_t<64>::exact set){
sse3.at(0,0)=wasm_i64x2_splat(set);
i_size.at(0,0)=wasm_i64x2_extract_lane(sse3.at(0,0),0);
return;
}

static void u_iTimeDelta_set(float set){
sse.at(0,1)=wasm_f64x2_splat(set);
f_time.at(1,0)=wasm_f64x2_extract_lane(sse.at(0,1),0);
return;
}

static void uni(){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const long int xxx=mms2.at(0,0);
const long int yyy=mms2.at(0,1);
mms.at(0,0)=(float)xxx;
mms.at(1,0)=(float)(i_size.at(0,0)-yyy);
clk_l=false;
}
mms.at(2,0)=(float)mms2.at(0,0);
mms.at(2,1)=(float)(i_size.at(0,0)-mms2.at(0,1));
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
nanoPause();
}
else{
clk_l=true;
}
glUniform1f(uni_tme,d_time.at(0,0));
nanoPause();
glUniform1f(uni_tme_dlt,f_time.at(1,0));
nanoPause();
glUniform1i(uni_frm,uni_i.at(0,0));
return;
}

void swap(){
emscripten_cancel_main_loop();
glDeleteProgram(S1.at(0,0,0));
glDeleteBuffers(1,&Sh.at(2,1));
glDeleteBuffers(1,&Sh.at(1,0));
glDeleteVertexArrays(1,&Sh.at(2,0));
nanoPause();
}

static void Rend(){
uni_i.at(0,0)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::steady_clock::now();
u_time.time_spana=boost::chrono::duration<float,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<float,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
if(ms_l==true){
mms.at(0,1)=round(mms2.at(0,0)/i_size.at(0,0));
mms.at(1,1)=round((mms2.at(0,1))/i_size.at(0,0));
}
uni();
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
nanoPause();
return;
}

inline char * rd_fl(const char * Fnm){
FILE * file=fopen(Fnm,"r");
::boost::tuples::tie(result,results,file);
if(file){
int32_t stat=fseek(file,(int32_t)0,SEEK_END);
if(stat!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
stat=fseek(file,(int32_t)0,SEEK_SET);
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
results=reinterpret_cast<char *>(result);
return results;
}
return nullptr;
}

void strt(){
typedef struct{boost::atomic<float> XYZW[4];}Vertex;
gpu.setFloats();
const Vertex vrt[8]={{gpu.gFm1(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gFm1(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()}};
::boost::tuples::tie(Fi,f_time,sse);
::boost::tuples::tie(uni_i,iFps,Si,sse3);
::boost::tuples::tie(cntx,mms);
::boost::tuples::tie(i_size,cntxi);
::boost::tuples::tie(mouse.hi,mouse.wi,d_time);
::boost::tuples::tie(u_time.t1,u_time.t2,u_time.t3);
::boost::tuples::tie(shad.EBO,shad.VBO,shad.VCO,sse4);
::boost::tuples::tie(config_size,major,minor);
::boost::tuples::tie(display,surface,eglconfig);
::boost::tuples::tie(attr,ctxegl,ctx);
::boost::tuples::tie(cm_hdr_src,vrt_bdy_src,frg_hdr_src,frg_ftr_src);
::boost::tuples::tie(vrt,indc,ele);
::boost::tuples::tie(retCl,retMu,retMd,retMv);
::boost::tuples::tie(retSa,retSb,retSc);
::boost::tuples::tie(ms_l,clk_l);
::boost::tuples::tie(u_time.time_spana,u_time.time_spanb);
::boost::tuples::tie(rem,req,tmm);
eglBindAPI(EGL_OPENGL_API);
eglconfig=NULL;
uni_i.at(0,0)=0;
clk_l=true;
const char * frag_body=rd_fl(Fnm);
std::string frag_body_S=frag_body;
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
cntxi.at(0,0)=ctx;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,att_lst,&eglconfig,(EGLint)1,&config_size);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
cntx.at(0,0)=ctxegl;
eglMakeCurrent(display,surface,surface,cntx.at(0,0));
emscripten_webgl_make_context_current(cntxi.at(0,0));
glUseProgram(0);
nanoPause();
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=static_cast<int>(mouse.hi);
i_iSize_set(Size);
u_iSize_set(mouse.hi);
mms.at(0,0)=0.5*t_size.at(0,0);
mms.at(0,1)=0.5*t_size.at(0,0);
mms.at(1,0)=0.5*t_size.at(0,0);
mms.at(1,1)=0.5*t_size.at(0,0);
// emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_sample_shading");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_gl_spirv");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_spirv_extensions");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_polygon_offset_clamp");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counters");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_depth_buffer_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_color_buffer_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_color_buffer_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_texture_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_texture_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_element_index_uint");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_sample_variables");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_HI_colorformats");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_KHR_create_context");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_robustness");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_create_context_robustness");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_bt2020_linear");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_gpu_shader_fp64");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_sRGB_write_control");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_sample_shading");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_multisample_compatibility");
// emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_vertex_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_framebuffer_multisample");
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
glClearDepth(Di.at(0,0));
glEnable(GL_DEPTH_TEST);
// glDepthFunc(GL_LEQUAL);
glDepthFunc(GL_LESS);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
// glDisable(GL_DITHER);
glFrontFace(GL_CW);
glEnable(GL_CULL_FACE);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
glClearColor(Fi.at(1,1),Fi.at(1,1),Fi.at(1,1),Fi.at(0,0));
glGenBuffers((GLsizei)1,&shad.VBO);
gpu.VBOin(shad.VBO);
glBindBuffer(GL_ARRAY_BUFFER,Sh.at(2,1));
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_DYNAMIC_DRAW);
nanoPause();
glGenBuffers((GLsizei)1,&shad.EBO);
gpu.EBOin(shad.EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Sh.at(1,0));
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
nanoPause();
src[0]=cm_hdr;
src[1]=vrt_bdy;
unsigned int vtx=compile.cmpl_shd(GL_VERTEX_SHADER,2,src);
src[0]=cm_hdr;
src[1]=frg_hdr;
src[2]=frag_body;
src[3]=frg_ftr;
unsigned int frag=compile.cmpl_shd(GL_FRAGMENT_SHADER,4,src);
unsigned int shd_prg=glCreateProgram();
PRGin(shd_prg);
::boost::tuples::tie(Sh,shd_prg);
::boost::tuples::tie(frag,vtx);
glAttachShader(S1.at(0,0,0),frag);
glAttachShader(S1.at(0,0,0),vtx);
glBindAttribLocation(S1.at(0,0,0),0,"iPosition");
glLinkProgram(S1.at(0,0,0));
nanoPause();
glUseProgram(S1.at(0,0,0));
nanoPause();
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&shad.VCO);
gpu.VCOin(shad.VCO);
glBindVertexArray(Sh.at(2,0));
nanoPause();
const GLuint atb_pos=glGetAttribLocation(S1.at(0,0),"iPosition");
glEnableVertexAttribArray(atb_pos);
nanoPause();
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_tme=glGetUniformLocation(S1.at(0,0,0),"iTime");
uni_tme_dlt=glGetUniformLocation(S1.at(0,0,0),"iTimeDelta");
uni_frm=glGetUniformLocation(S1.at(0,0,0),"iFrame");
uni_fps=glGetUniformLocation(S1.at(0,0,0),"iFrameRate");
uni_res=glGetUniformLocation(S1.at(0,0,0),"iResolution");
uni_mse=glGetUniformLocation(S1.at(0,0,0),"iMouse");
uni_srate=glGetUniformLocation(S1.at(0,0,0),"iSampleRate");
smp_chn_res=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution");
smp_chn[0]=glGetUniformLocation(S1.at(0,0,0),"iChannel0");
smp_chn[1]=glGetUniformLocation(S1.at(0,0,0),"iChannel1");
smp_chn[2]=glGetUniformLocation(S1.at(0,0,0),"iChannel2");
smp_chn[3]=glGetUniformLocation(S1.at(0,0,0),"iChannel3");
glUniform1f(uni_srate,44100.0f);
nanoPause();
glUniform3f(uni_res,t_size.at(0,0),t_size.at(0,0),gpu.gF());
nanoPause();
glUniform3f(smp_chn_res,t_size.at(0,0),t_size.at(0,0),gpu.gF());
nanoPause();
iFps=60;
glUniform1f(uni_fps,iFps);
nanoPause();
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
nanoPause();
glViewport((GLint)0,(GLint)0,i_size.at(0,0),i_size.at(0,0));  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,i_size.at(0,0),i_size.at(0,0));
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
u_iTime_set(0.0f);
u_iTimeDelta_set(0.0f);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::steady_clock::now();
u_time.t3=boost::chrono::steady_clock::now();
u_time.time_spanb=boost::chrono::duration<float,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<float,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
glFlush();
glFinish();
nanoPause();
emscripten_set_main_loop((void(*)())Run::Rend,0,0);
return;
}
  
};
