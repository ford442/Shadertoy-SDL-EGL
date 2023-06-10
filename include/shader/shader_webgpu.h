#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/shader/defs.h"
#include "../../include/shader/boost_defs.h"

#include <float.h>
#include <math.h>
#include <new>
#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <algorithm>
#include <cstring>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <climits>
#include <iostream>
#include <ctime>
#include <vector>
#include <functional>

#include "../../include/shader/gl.h"
#include "../../include/shader/egl.h"
#include "../../include/shader/intrins.h"

#include <emscripten/html5.h>
#include <emscripten.h>

#include "../../lib/lib_webgpu.h"

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
srclens[i]=GLsizei(strlen(src[i]));
}
const GLuint shader=glCreateShader(type);
glShaderSource(shader,nsrc,src,srclens);
glCompileShader(shader);
return shader;
}

};

inline char wgl_cmp_src[1000]=
"@group(0)@binding(0)var <storage,read>inputBuffer: array<i32,65536>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<i32,65536>;"
"@compute@workgroup_size(256)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>,@builtin(local_invocation_id)local_id:vec3<u32>){"
"var a:i32=0;{"
"var i:i32=0;"
"loop{"
"if !(i<250){a++;i=0;}if a>250{break;}"
"continuing{"
"outputBuffer[i+a]=i%16;"
"outputBuffer[i+a+1]=i%128;"
"outputBuffer[i+a+2]=i%255;"
"outputBuffer[i+a+3]=255;"
"}"
"}"
"}"
"}";

inline char cm_hdr_src[1900]=
"#version 300 es\n"
"#extension GL_ARB_gpu_shader4 : enable\n"
"#extension GL_ARB_gpu_shader5 : enable\n"
"#extension GL_ARB_gpu_shader_fp64 : enable\n"
"#extension GL_ARB_vertex_attrib_64bit : enable\n"
"#extension GL_NV_shader_buffer_load : enable\n"
"#extension GL_ARB_color_buffer_float : enable\n"
"#extension GL_ARB_shader_atomic_counters : enable\n"
"#extension GL_OES_sample_shading : enable\n"
"#extension GL_OES_vertex_half_float : enable\n"
"#extension GL_ARB_multisample : enable\n"
"#extension GL_ARB_shading_language_420pack : enable\n"
"#extension GL_EXT_multisample_compatibility : enable\n"
"#extension GL_OES_sample_shading : enable\n"
"#extension GL_ARB_framebuffer_object : enable\n"
"#extension GL_ARB_framebuffer_sRGB : enable\n"
"#extension GL_NV_half_float : enable\n"
"#extension GL_ARB_fragment_program : enable\n"
"#extension GL_NV_fragment_program_option : enable\n"
"#extension GL_NV_fragment_program : enable\n"
"#extension GL_NV_fragment_program2 : enable\n"
"#extension GL_EXT_sRGB_write_control : enable\n"
"#extension GL_NV_float_buffer : enable\n"
"#extension GL_EXT_bindable_uniform : enable\n"
"#extension GL_EXT_geometry_shader4 : enable\n"
"#extension GL_ARB_enhanced_layouts : enable\n"
"#pragma STDGL(precision highp uint)\n"
"#pragma STDGL(precision highp atomic_uint)\n"
"#pragma STDGL(precise all)\n"
"#pragma optionNV(precise all)\n"
"#pragma STDGL(strict on)\n"
"#pragma optionNV(strict on)\n"
"#pragma STDGL(invariant none)\n"
"#pragma optionNV(invariant none)\n"
"#pragma STDGL(centroid all)\n"
"#pragma optionNV(centroid all)\n"
"#pragma STDGL(fastmath on)\n"
"#pragma optionNV(fastmath on)\n"
"#pragma STDGL(fastprecision off)\n"
"#pragma optionNV(fastprecision off)\n"
"#pragma STDGL(unroll all)\n"
"#pragma optionNV(unroll all)\n"
"#pragma STDGL(ifcvt none)\n"
"#pragma optionNV(ifcvt none)\n"
"#pragma STDGL(inline all)\n"
"#pragma optionNV(inline all)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 1\n"
"precision highp int;\n"
"precision highp float;\n";

inline char vrt_bdy_src[100]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

inline char frg_hdr_src[1000]=
"precision highp sampler3D;precision highp sampler2D;"
"precision highp samplerCube;precision highp sampler2DArray;precision highp sampler2DShadow;"
"precision highp isampler2D;precision highp isampler3D;precision highp isamplerCube;"
"precision highp isampler2DArray;precision highp usampler2D;precision highp usampler3D;"
"precision highp usamplerCube;precision highp usampler2DArray;precision highp samplerCubeShadow;"
"precision highp sampler2DArrayShadow;"
"layout (std140) uniform uniBlock{"
"uniform float iSampleRate;"
"uniform float iFrameRate;"
"};"
"uniform int iFrame;"
"uniform float iTime;"
"uniform float iTimeDelta;"
"uniform vec4 iDate;"
"uniform float iChannelTime[4];"
"uniform vec3 iChannelResolution[4];"
"uniform vec3 iResolution;"
"uniform vec4 iMouse;"
"uniform sampler2D iChannel0;"
"uniform sampler2D iChannel1;"
"uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
"out vec4 fragColor;\n";

inline char frg_ftr_src[420]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n"
"#define mainImage mainImage0(out dvec4 O,dvec2 U);"
"int _N=16;void mainImage(out dvec4 O,dvec2 U){"
"dvec4 o;O=dvec4(0);"
"mainImage0(o,U+dvec2(k%_N-_N/2,k/_N-_N/2)/double(_N));"
"O += o;}O /= double(_N*_N);O=pow(O,dvec4(2.077038lf/1.0lf,2.184228lf/1.0,2.449715lf/1.0lf,1.0lf));}"
"void mainImage0\n\0";

EGLint att_lst2[1000]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
EGL_NONE,EGL_NONE
};

EGLint ctx_att[500]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
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
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,EGL_TRUE,
// EGL_COVERAGE_BUFFERS_NV,(EGLint)1, // used to indicate, not set
//  EGL_COVERAGE_SAMPLES_NV,(EGLint)4, // used to indicate, not set
EGL_SAMPLES,8,
// EGL_MIPMAP_LEVEL,(EGLint)1, // used to indicate, not set
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX, // used to indicate, not set
EGL_NONE,EGL_NONE
};

inline EM_BOOL ms_l,clk_l;
using mouse_tensor=boost::numeric::ublas::tensor<boost::atomic<float>>;
using shad_tensor=boost::numeric::ublas::tensor<unsigned int>;
using prg_tensor=boost::numeric::ublas::tensor<unsigned int>;
using sz_tensor=boost::numeric::ublas::tensor<int>;
using f_tensor=boost::numeric::ublas::tensor<boost::atomic<float>>;
using d_tensor=boost::numeric::ublas::tensor<double>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using i_tensor=boost::numeric::ublas::tensor<int>;
using gi_tensor=boost::numeric::ublas::tensor<GLint>;
using li_tensor=boost::numeric::ublas::tensor<long>;
using void_tensor=boost::numeric::ublas::tensor<void *>;

static v_tensor sse=v_tensor{2,2};
static v_tensor sse2=v_tensor{2,2};
static v_tensor sse3=v_tensor{2,2};
static v_tensor sse4=v_tensor{1,1};
static shad_tensor Sh=shad_tensor{3,3};
static prg_tensor S1=prg_tensor{1,1,1};
static sz_tensor Si=sz_tensor{1,1};
static d_tensor d_time=d_tensor{2,2};
static f_tensor Fi=f_tensor{2,2};
static d_tensor Di=d_tensor{2,2};
static gi_tensor uni_i=gi_tensor{1,1};
static i_tensor i_view=i_tensor{1,2};
static f_tensor t_size=f_tensor{1,2};
static li_tensor i_size=li_tensor{1,2};
static void_tensor cntx=void_tensor{2,2};
static i_tensor cntxi=i_tensor{2,2};
static mouse_tensor mms=mouse_tensor{2,2};
static li_tensor mms2=li_tensor{2,2};
static void_tensor bin=void_tensor{1,1};

uint64_t IbufferSize=65536*sizeof(int);
WGpuBuffer inputBuffer=0;
WGpuBuffer outputBuffer=0;
WGpuBufferDescriptor bufferDescriptorI={65536*sizeof(int),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={65536*sizeof(int),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
int * resulT[65536];
void * userDataA;
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
uint32_t workgroupSize=256;
uint32_t invocationCount=65536;
uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
WGpuAdapter adapter=0;
WGpuDevice device=0;
WGpuDeviceDescriptor deviceDescriptor={};
WGpuQueue queue=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuComputePipeline computePipeline=0;
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroup bindGroup=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[2]={};
WGpuBindGroupEntry bindGroupEntry[2]={};
WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBuffer mapBuffer=0;
WGpuBufferDescriptor bufferDescriptorM={};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
const char * Entry="computeStuff";

class GPU{

private:

public:

const void EBOin(boost::uint_t<32>::exact EBO){
Sh.at(1,0)=EBO;
return;
}

const void VCOin(boost::uint_t<32>::exact VCO){
Sh.at(2,0)=VCO;
return;
}

const void VBOin(boost::uint_t<32>::exact VBO){
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

static inline float gF(){
return Fi.at(0,0);
}

static inline float gFm1(){
return Fi.at(0,1);
}

static inline float gF0(){
return Fi.at(1,1);
}

static inline double gD(){
return Di.at(0,0);
}

static inline double gDm1(){
return Di.at(0,1);
}

static inline double gD0(){
return Di.at(1,1);
}

};

const inline unsigned char gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const unsigned char indc[35]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
inline GLint uni_srate=0,uni_dte=0,uni_res=0,uni_fps=0,smp_chn_res0=0,smp_chn_res1=0,smp_chn_res2=0,smp_chn_res3=0,smp_chn[4],uni_frm=0;
inline GLfloat uni_chn_tme3=0.0f,uni_chn_tme2=0.0f,uni_chn_tme1=0.0f,uni_chn_tme0=0.0f,uni_tme=0.0f,uni_tme_dlt=0.0f,uni_mse=0.0f;

struct{
boost::chrono::duration<double,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<double,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
}u_time;

union{
unsigned int VBO,EBO,VCO;
}shad;

inline struct{
double wi=0.0;
double hi=0.0;
}mouse;

int Size=0;
boost::atomic<int>tmm=166666000;
boost::atomic<int>tmm2=1000;
inline struct timespec rem;
inline struct timespec req={0,tmm};
inline struct timespec req2={0,tmm2};
const int ele=36;

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

static char8_t * result=NULL;
static char * results=NULL;
static long int length=0;
unsigned int uniBlock;

class Run{

private:

Compile compile;

int32_t iFps=60;
EGLDisplay display=nullptr;
EGLSurface surface=nullptr;
EGLContext ctxegl=nullptr;
EGLConfig eglconfig=nullptr;
EGLint config_size=0,major,minor=0;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
const char * src[4];
char * cm_hdr=cm_hdr_src;
char * vrt_bdy=vrt_bdy_src;
char * frg_hdr=frg_hdr_src;
char * frg_ftr=frg_ftr_src;

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;

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
t_size.at(0,1)=wasm_f64x2_extract_lane(sse.at(1,0),0);
return;
}
  
static void i_iSize_set(boost::int_t<32>::exact set){
sse3.at(0,0)=wasm_i64x2_splat(set);
i_size.at(0,0)=wasm_i64x2_extract_lane(sse3.at(0,0),0);
i_size.at(0,1)=wasm_i64x2_extract_lane(sse3.at(0,0),0);
return;
}

static void u_iTimeDelta_set(double set){
sse.at(0,1)=wasm_f64x2_splat(set);
d_time.at(1,1)=wasm_f64x2_extract_lane(sse.at(0,1),0);
return;
}

void uniUP(){
t_size.at(0,1)=t_size.at(0,1)*1.01;
glUniform3f(uni_res,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res0,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res1,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res2,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res3,t_size.at(0,1),t_size.at(0,1),gpu.gF());
//  glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
return;
}

void uniDOWN(){
t_size.at(0,1)=t_size.at(0,1)*0.99;
glUniform3f(uni_res,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res0,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res1,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res2,t_size.at(0,1),t_size.at(0,1),gpu.gF());
glUniform3f(smp_chn_res3,t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
return;
}

static void viewUP(){
i_size.at(0,1)=i_size.at(0,1)*1.5;
glViewport((GLint)0,(GLint)0,i_size.at(0,1),i_size.at(0,1));
return;
}

static void viewDOWN(){
i_size.at(0,1)=i_size.at(0,1)/1.5;
glViewport((GLint)0,(GLint)0,i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveDOWN(){
i_view.at(0,0)=i_view.at(0,0)-1;
glViewport((GLint)i_view.at(0,0),(GLint)i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveUP(){
i_view.at(0,0)=i_view.at(0,0)+1;
glViewport((GLint)i_view.at(0,0),(GLint)i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveLEFT(){
i_view.at(0,1)=i_view.at(0,1)-1;
glViewport((GLint)i_view.at(0,0),(GLint)i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveRIGHT(){
i_view.at(0,1)=i_view.at(0,1)+1;
glViewport((GLint)i_view.at(0,0),(GLint)i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}
  
union{

static void uni(){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const long int xxx=mms2.at(0,0);
const long int yyy=mms2.at(0,1);
mms.at(0,0)=float(xxx);
mms.at(1,0)=float((i_size.at(0,0)-yyy));
clk_l=false;
}
mms.at(2,0)=float(mms2.at(0,0));
mms.at(2,1)=float(i_size.at(0,0)-mms2.at(0,1));
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
// nanoPause();
}
else{
clk_l=true;
}
glUniform1f(uni_tme,d_time.at(0,0));
glUniform1f(uni_chn_tme0,d_time.at(0,0));
glUniform1f(uni_chn_tme1,d_time.at(0,0));
glUniform1f(uni_chn_tme2,d_time.at(0,0));
glUniform1f(uni_chn_tme3,d_time.at(0,0));
glUniform1f(uni_tme_dlt,d_time.at(1,1));

const time_t timE=time(0);
struct tm *datE=localtime(&timE);
short yr=1900+datE->tm_year;
short mn=1+datE->tm_mon;
short dy=datE->tm_mday-1;
short hr=5+datE->tm_hour;
short mi=datE->tm_min;
short sc=datE->tm_sec;
short shaderToySeconds=(hr*3600)+(mi*60)+(sc);
if(int(d_time.at(0,0))%60==0){
// glUniform4i(uni_dte,yr,mn,dy,shaderToySeconds);
}

if(uni_i.at(0,0)%30==0.0){
if(shaderToySeconds%2==0.0){
glActiveTexture(GL_TEXTURE0);
glUniform1i(smp_chn[0],0);
glActiveTexture(GL_TEXTURE1);
glUniform1i(smp_chn[1],1);
glActiveTexture(GL_TEXTURE5);
glUniform1i(smp_chn[2],5);
glActiveTexture(GL_TEXTURE3);
glUniform1i(smp_chn[3],3);
}else{
glActiveTexture(GL_TEXTURE5);
glUniform1i(smp_chn[0],5);
glActiveTexture(GL_TEXTURE5);
glUniform1i(smp_chn[1],5);
glActiveTexture(GL_TEXTURE5);
glUniform1i(smp_chn[2],5);
glActiveTexture(GL_TEXTURE5);
glUniform1i(smp_chn[3],5);
}
}
  // buffer frame/time
// glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
// glBufferSubData(GL_UNIFORM_BUFFER,8,4,&uni_i.at(0,0)); 
// glBufferSubData(GL_UNIFORM_BUFFER,12,4,&d_time.at(0,0)); 
// glBindBuffer(GL_UNIFORM_BUFFER,0);
glUniform1i(uni_frm,uni_i.at(0,0));
return;
}

static void swap(){
emscripten_cancel_main_loop();
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=int(mouse.hi);
i_iSize_set(Size);
u_iSize_set(float(mouse.hi));
i_view.at(0,0)=0;
i_view.at(0,1)=0;
mms.at(0,0)=0.5*t_size.at(0,0);
mms.at(0,1)=0.5*t_size.at(0,0);
mms.at(1,0)=0.5*t_size.at(0,0);
mms.at(1,1)=0.5*t_size.at(0,0);
glUniform3f(uni_res,t_size.at(0,0),t_size.at(0,0),GPU::gF());
glUniform3f(smp_chn_res0,t_size.at(0,0),t_size.at(0,0),GPU::gF());
glUniform3f(smp_chn_res1,t_size.at(0,0),t_size.at(0,0),GPU::gF());
glUniform3f(smp_chn_res2,t_size.at(0,0),t_size.at(0,0),GPU::gF());
glUniform3f(smp_chn_res3,t_size.at(0,0),t_size.at(0,0),GPU::gF());
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
glViewport(0,0,i_size.at(0,1),i_size.at(0,1));  //  viewport/scissor after UsePrg runs at full resolution
glScissor(0,0,i_size.at(0,1),i_size.at(0,1));
u_iTime_set(0.0);
u_iTimeDelta_set(0.0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
glFlush();
glFinish();
glDeleteProgram(S1.at(0,0,0));
glDeleteBuffers(1,&Sh.at(2,1));
glDeleteBuffers(1,&Sh.at(1,0));
glDeleteVertexArrays(1,&Sh.at(2,0));
// nanoPause();
return;
}

static void Rend(){
uni_i.at(0,0)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<double,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<double,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
if(ms_l==true){
mms.at(0,1)=round(mms2.at(0,0)/i_size.at(0,0));
mms.at(1,1)=round((mms2.at(0,1))/i_size.at(0,0));
}
uni();
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
// nanoPause();
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

}procc;

static void raf(WGpuDevice device){
bufferDescriptorM={65536*sizeof(int),WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};

std::vector<float>input(65536);
std::vector<unsigned int>outputd(65536);
char * cmp_bdy=wgl_cmp_src;
shaderModuleDescriptor={cmp_bdy,0,NULL};
  
mapBuffer=wgpu_device_create_buffer(device,&bufferDescriptorM);
inputBuffer=wgpu_device_create_buffer(device,&bufferDescriptorI);
outputBuffer=wgpu_device_create_buffer(device,&bufferDescriptorO);
for(int i=0;i<input.size();++i){
input[i]=i;
}
cs=wgpu_device_create_shader_module(device,&shaderModuleDescriptor);
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=bufferBindingLayout1;
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=bufferBindingLayout2;
bindGroupLayout=wgpu_device_create_bind_group_layout(device,bindGroupLayoutEntries,2);
pipelineLayout=wgpu_device_create_pipeline_layout(device,&bindGroupLayout,1);
computePipeline=wgpu_device_create_compute_pipeline(device,cs,Entry,pipelineLayout,NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=inputBuffer;
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=0;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=outputBuffer;
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=0;
bindGroup=wgpu_device_create_bind_group(device,bindGroupLayout,bindGroupEntry,2);
encoder=wgpu_device_create_command_encoder(device,0);
computePass=wgpu_command_encoder_begin_compute_pass(encoder,&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(computePass,computePipeline);
wgpu_encoder_set_bind_group(computePass,0,bindGroup,0,0);
queue=wgpu_device_get_queue(device);
wgpu_queue_write_buffer(queue,inputBuffer,0,input.data(),input.size()*sizeof(int));
wgpu_compute_pass_encoder_dispatch_workgroups(computePass,uint32_t(256),uint32_t(256),uint32_t(1));
wgpu_encoder_end(computePass);
wgpu_command_encoder_copy_buffer_to_buffer(encoder,outputBuffer,0,mapBuffer,0,65536*sizeof(int));
commandBuffer=wgpu_encoder_finish(encoder);
WGpuOnSubmittedWorkDoneCallback onComputeDone=[](WGpuQueue queue,void *userData){
WGpuBufferMapCallback mapCallback=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
double output=wgpu_buffer_get_mapped_range(mapBuffer,uint32_t(0),65536*sizeof(int));
wgpu_buffer_read_mapped_range(mapBuffer,output,0,&resulT,65536*sizeof(int));
GLsizei width=256;
GLsizei height=256;
GLuint wtexture=0;
int Colora[width*height];
for(int g=0;g<65536;g++){
Colora[g]=255; // int(resulT[g]);
Colora[g+1]=0; // int(resulT[g+1]);
Colora[g+2]=255; // int(resulT[g+2]);
Colora[g+3]=255; // int(resulT[g+3]);
}
glGenTextures(1,&wtexture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,wtexture);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA_INTEGER,width,height,0,GL_RGBA_INTEGER,GL_INT,Colora);
glGenerateMipmap(GL_TEXTURE_2D);
};
wgpu_buffer_map_async(mapBuffer,mapCallback,&userDataA,mode1,uint32_t(0),65536*sizeof(int));
};
wgpu_queue_set_on_submitted_work_done_callback(queue,onComputeDone,0);
wgpu_queue_submit_one_and_destroy(queue,commandBuffer);
return;
}
  

static void ObtainedWebGpuDevice(WGpuDevice result,void * userData){
device=result;
raf(device);
}

static void ObtainedWebGpuAdapter(WGpuAdapter result,void * userData){
adapter=result;
wgpu_adapter_request_device_async(adapter,&deviceDescriptor,ObtainedWebGpuDevice,0);
}

void strt(){
navigator_gpu_request_adapter_async(&options,ObtainedWebGpuAdapter,0);
typedef struct{GLfloat XYZW[4];}Vertex;
gpu.setFloats();
const Vertex vrt[8]={{gpu.gFm1(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gFm1(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()}};
// const Vertex vrt[8]={{gpu.gDm1(),gpu.gDm1(),gpu.gD(),gpu.gD()},{gpu.gD(),gpu.gDm1(),gpu.gD(),gpu.gD()},{gpu.gD(),gpu.gD(),gpu.gD(),gpu.gD()},{gpu.gDm1(),gpu.gD(),gpu.gD(),gpu.gD()},{gpu.gDm1(),gpu.gDm1(),gpu.gDm1(),gpu.gD()},{gpu.gD(),gpu.gDm1(),gpu.gDm1(),gpu.gD()},{gpu.gD(),gpu.gD(),gpu.gDm1(),gpu.gD()},{gpu.gDm1(),gpu.gD(),gpu.gD(),gpu.gD()}};
::boost::tuples::tie(Fi,sse);
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
eglconfig=NULL;
uni_i.at(0,0)=0;
clk_l=true;
const char * frag_body=procc.rd_fl(Fnm);
std::string frag_body_S=frag_body;
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
cntxi.at(0,0)=ctx;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglBindAPI(EGL_OPENGL_API);
eglChooseConfig(display,att_lst,&eglconfig,(EGLint)1,&config_size);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglInitialize(display,&major,&minor);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
cntx.at(0,0)=ctxegl;
eglMakeCurrent(display,surface,surface,cntx.at(0,0));
emscripten_webgl_make_context_current(cntxi.at(0,0));
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glUseProgram(0);
nanoPause();
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=int(mouse.hi);
i_iSize_set(Size);
u_iSize_set(mouse.hi);
i_view.at(0,0)=0;
i_view.at(0,1)=0;
mms.at(0,0)=0.5*t_size.at(0,0);
mms.at(0,1)=0.5*t_size.at(0,0);
mms.at(1,0)=0.5*t_size.at(0,0);
mms.at(1,1)=0.5*t_size.at(0,0);
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_sample_shading");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_framebuffer_object");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_framebuffer_sRGB");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_fragment_program");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_fragment_program_option");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_fragment_program");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_fragment_program2");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_float_buffer");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_sample_shading");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_gl_spirv");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_spirv_extensions");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counter_ops");
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
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_robustness");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_create_context_robustness");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_gpu_shader4");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_gpu_shader5");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_vertex_buffer_unified_memory");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_gpu_program5");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_vertex_attrib_integer_64bit");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_sRGB_write_control");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_sample_shading");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_multisample_compatibility");
emscripten_webgl_enable_extension(cntxi.at(0,0),"OES_vertex_half_float");
emscripten_webgl_enable_extension(cntxi.at(0,0),"NV_framebuffer_multisample");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_enhanced_layouts");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shading_language_420pack");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_get_program_binary");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(cntxi.at(0,0),"EXT_bindable_uniform");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_EXT_geometry_shader4");
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
glClearDepth(Di.at(0,0));
glEnable(GL_DEPTH_TEST);
glDisable(GL_DITHER);
// glDepthFunc(GL_LEQUAL);
glDepthFunc(GL_LESS);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
glFrontFace(GL_CW);
glEnable(GL_CULL_FACE);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR,SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
glClearColor(Fi.at(1,1),Fi.at(1,1),Fi.at(1,1),Fi.at(0,0));
glGenBuffers((GLsizei)1,&shad.VBO);
gpu.VBOin(shad.VBO);
glBindBuffer(GL_ARRAY_BUFFER,Sh.at(2,1));
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_STREAM_DRAW);
nanoPause();
glGenBuffers((GLsizei)1,&shad.EBO);
gpu.EBOin(shad.EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Sh.at(1,0));
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STREAM_DRAW);
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
unsigned int uniIndex=glGetUniformBlockIndex(S1.at(0,0,0),"uniBlock");   
glUniformBlockBinding(S1.at(0,0,0),0,uniIndex);
glGenBuffers(1,&uniBlock);
glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
glBufferData(GL_UNIFORM_BUFFER,8,NULL,GL_STREAM_DRAW);
glBindBufferBase(GL_UNIFORM_BUFFER,0,uniBlock);
glBindBuffer(GL_UNIFORM_BUFFER,0);
GLsizei * binLength;
GLenum * binaryFormat;
void * GLbin;
glDetachShader(S1.at(0,0,0),frag);
glDetachShader(S1.at(0,0,0),vtx);
glGetProgramBinary(S1.at(0,0,0),sizeof(GLbin),binLength,binaryFormat,&GLbin);
bin.at(0,0)=GLbin;
nanoPause();
glProgramBinary(S1.at(0,0,0),*binaryFormat,bin.at(0,0),*binLength);
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
const GLuint atb_pos=glGetAttribLocation(S1.at(0,0,0),"iPosition");
glEnableVertexAttribArray(atb_pos);
nanoPause();
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_dte=glGetUniformLocation(S1.at(0,0,0),"iDate");
uni_tme=glGetUniformLocation(S1.at(0,0,0),"iTime");
uni_tme_dlt=glGetUniformLocation(S1.at(0,0,0),"iTimeDelta");
uni_chn_tme0=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[0]");
uni_chn_tme1=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[1]");
uni_chn_tme2=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[2]");
uni_chn_tme3=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[3]");
uni_frm=glGetUniformLocation(S1.at(0,0,0),"iFrame");
uni_fps=glGetUniformLocation(S1.at(0,0,0),"iFrameRate");
uni_res=glGetUniformLocation(S1.at(0,0,0),"iResolution");
uni_mse=glGetUniformLocation(S1.at(0,0,0),"iMouse");
uni_srate=glGetUniformLocation(S1.at(0,0,0),"iSampleRate");
smp_chn_res0=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[0]");
smp_chn_res1=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[1]");
smp_chn_res2=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[2]");
smp_chn_res3=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[3]");
smp_chn[0]=glGetUniformLocation(S1.at(0,0,0),"iChannel0");
smp_chn[1]=glGetUniformLocation(S1.at(0,0,0),"iChannel1");
smp_chn[2]=glGetUniformLocation(S1.at(0,0,0),"iChannel2");
smp_chn[3]=glGetUniformLocation(S1.at(0,0,0),"iChannel3");
    
  /*
  // uni non-block
GLuint Ubuffer;
glGenBuffers(1,&Ubuffer);
glBindBuffer(GL_UNIFORM_BUFFER_EXT,Ubuffer);
glBufferData(GL_UNIFORM_BUFFER_EXT,4,NULL,GL_DYNAMIC_DRAW);
UniformBufferEXT(S1.at(0,0,0),uni_tme,Ubuffer);
// glBindBufferBase(GL_UNIFORM_BUFFER,0,uniBlock);
*/
  
    // texture
GLsizei width=1;
GLsizei height=1;
GLuint texture=0,textureb=0,texturec=0,textured=0;
unsigned char* Colora=new unsigned char[width*height*sizeof(unsigned char)];
Colora[0]=0;
Colora[1]=222;
Colora[2]=0;
Colora[3]=230;
glGenTextures(1,&texture);
glActiveTexture(GL_TEXTURE5);
glBindTexture(GL_TEXTURE_2D,texture);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,Colora);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[0],0);
unsigned char* Colorb=new unsigned char[width*height*sizeof(unsigned char)];
Colorb[0]=0;
Colorb[1]=255;
Colorb[2]=0;
Colorb[3]=128;
glGenTextures(1,&textureb);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D,textureb);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,Colorb);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[1],1);
unsigned char* Colorc=new unsigned char[width*height*sizeof(unsigned char)];
Colorc[0]=80;
Colorc[1]=0;
Colorc[2]=130;
Colorc[3]=200;
glGenTextures(1,&texturec);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D,texturec);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,Colorc);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[2],2);
unsigned char* Colord=new unsigned char[width*height*sizeof(unsigned char)];
Colord[0]=128;
Colord[1]=128;
Colord[2]=128;
Colord[3]=128;
glGenTextures(1,&textured);
glActiveTexture(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D,textured);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,Colord);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[3],3);

  // date/time
const time_t timE=time(0);
struct tm *datE=localtime(&timE);
short yr=1900+datE->tm_year;
short mn=1+datE->tm_mon;
short dy=datE->tm_mday-1;
short hr=5+datE->tm_hour;
short mi=datE->tm_min;
short sc=datE->tm_sec;
short shaderToySeconds=(hr*3600)+(mi*60)+(sc);
glUniform4i(uni_dte,yr,mn,dy,shaderToySeconds);
// glUniform1f(uni_srate,44100.0f);
glUniform3f(uni_res,t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res0,t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res1,t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res2,t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res3,t_size.at(0,0),t_size.at(0,0),gpu.gF());
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
nanoPause();
glViewport((GLint)0,(GLint)0,i_size.at(0,1),i_size.at(0,1));  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,i_size.at(0,1),i_size.at(0,1));
u_iTime_set(0.0);
u_iTimeDelta_set(0.0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<double,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<double,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
float iRate=44100.0f;
glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
glBufferSubData(GL_UNIFORM_BUFFER,0,4,&iRate); 
glBufferSubData(GL_UNIFORM_BUFFER,4,4,&iFps); 
glBindBuffer(GL_UNIFORM_BUFFER,0);
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
glFlush();
glFinish();
nanoPause();
emscripten_set_main_loop((void(*)())Run::procc.Rend,0,0);
return;
}
  
};
