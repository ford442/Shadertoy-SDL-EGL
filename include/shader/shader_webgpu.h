#include <boost/cstdfloat.hpp>  // must be first include
#include <boost/cstdint.hpp>
#include <functional>
#include <algorithm>

template<class ArgumentType,class ResultType>
struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/compute.hpp>
// #include <boost/compute/core.hpp>
#include <boost/compute/interop/opengl.hpp>
#include <boost/compute/algorithm.hpp>

#include "../../include/shader/defs.h"
#include "../../include/shader/boost_defs.h"
#include <random>
#include <cfloat>
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
#include <cstdint>
#include <stdlib.h>
#include <climits>
#include <iostream>
#include <ctime>
#include <vector>
#include <functional>
#include <cassert>
#include "../../include/shader/gl.h"
#include "../../include/shader/egl.h"
#include "../../include/shader/intrins.h"
#include "../../lib/lib_webgpu.h"
#include <emscripten/html5.h>
#include <emscripten.h>

extern "C"{
  
void str();
  
}

class Compile
{

private:

GLsizei i;

public:

boost::uint_t<32>::exact cmpl_shd(GLenum type,GLsizei nsrc,const char ** src){
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

inline char wgl_cmp_src[2000]=
"@group(0)@binding(0)var<storage,read>inputBuffer:array<u32,262144>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<u32,262144>;"
"@group(0)@binding(2)var textureA:texture_storage_2d<rgba32uint,write>;"
"@compute@workgroup_size(4,1,64)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){"
"let f:u32=global_id.x*4*global_id.y;"
"for(var e:u32=0;e<65546;e++){"
"var m=e*4;"
"outputBuffer[m]=inputBuffer[0];"
"outputBuffer[m+1]=0;"
"outputBuffer[m+2]=255-inputBuffer[0];"
"outputBuffer[m+3]=255;"
"}"
"}";

inline char cm_hdr_src[2300]=
"#version 300 es\n"
"#pragma STDGL(precision highp double)\n"
"#pragma STDGL(precision highp uint)\n"
"#pragma STDGL(precision highp _uint)\n"
"#pragma STDGL(precise none)\n"
"#pragma STDGL(strict off)\n"
"#pragma STDGL(invariant all)\n"
"#pragma STDGL(centroid all)\n"
"#pragma STDGL(sample all)\n"
"#pragma STDGL(fastmath on)\n"
"#pragma STDGL(fastprecision on)\n"
"#pragma STDGL(unroll all)\n"
// "#pragma STDGL(ifcvt none)\n"
"#pragma STDGL(inline none)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
"precision highp int;\n"
"precision highp float;\n"
"precision highp sampler3D;precision highp sampler2D;"
"precision highp samplerCube;precision highp sampler2DArray;precision highp sampler2DShadow;"
"precision highp isampler2D;precision highp isampler3D;precision highp isamplerCube;"
"precision highp isampler2DArray;precision highp usampler2D;precision highp usampler3D;"
"precision highp usamplerCube;precision highp usampler2DArray;precision highp samplerCubeShadow;"
"precision highp sampler2DArrayShadow;";
  
inline char vrt_bdy_src[100]=
"layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";

inline char frg_hdr_src[1000]=

"layout (std140) uniform uniBlock{uniform float iSampleRate;uniform float iFrameRate;};"
"uniform int iFrame;uniform float iTime;uniform float iTimeDelta;uniform vec4 iDate;"
"uniform float iChannelTime[4];uniform vec3 iChannelResolution[4];uniform vec3 iResolution;"
"uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
// "uniform sampler2D iChannel4;"
"out vec4 fragColor;\n";

inline char frg_ftr_src[420]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n"
"#define mainImage mainImage0(out dvec4 O,dvec2 U);"
"int _N=3;void mainImage(out dvec4 O,dvec2 U){"
"dvec4 o;O=dvec4(0);"
"mainImage0(o,U+dvec2(k%_N-_N/2,k/_N-_N/2)/double(_N));"
"O += o;}O /= double(_N*_N);O=pow(O,dvec4(2.077038f/1.0f,2.184228lf/1.0f,2.449715lf/1.0f,1.0f));}"
// "O += o;}O /= double(_N*_N);O=pow(O,dvec4(1.0f,1.0f,1.0f,1.0f));}"
"void mainImage0\n\0";

EGLint att_lst2[1000]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_LINEAR_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_LINEAR_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
EGL_GL_COLORSPACE_SRGB_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT,
EGL_NONE,EGL_NONE
};

EGLint ctx_att[500]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)4,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)6,
// EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};

EGLint att_lst[1500]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
EGL_CONFORMANT,EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_TRUE,
EGL_NATIVE_RENDERABLE,EGL_TRUE,
 // EGL_COLOR_DEPTH_10_BIT_EXT, 10,
 // EGL_ALPHA_SIZE_10_BIT_EXT, 10,
EGL_RED_SIZE,(EGLint)10,
EGL_GREEN_SIZE,(EGLint)10,
EGL_BLUE_SIZE,(EGLint)10,
EGL_ALPHA_SIZE,(EGLint)10,
EGL_DEPTH_SIZE,(EGLint)32,
EGL_STENCIL_SIZE,(EGLint)32,
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,16,
EGL_GL_COLORSPACE_KHR, EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_LINEAR_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
EGL_GL_COLORSPACE_SRGB_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT,
// EGL_COVERAGE_BUFFERS_NV,(EGLint)1, // used to indicate, not set
//  EGL_COVERAGE_SAMPLES_NV,(EGLint)4, // used to indicate, not set
EGL_SAMPLES,16,
// EGL_MIPMAP_LEVEL,(EGLint)1, // used to indicate, not set
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX, // used to indicate, not set
EGL_NONE,EGL_NONE
};

inline EM_BOOL ms_l,clk_l;
using mouse_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using shad_tensor=boost::numeric::ublas::tensor<GLuint>;
using prg_tensor=boost::numeric::ublas::tensor<GLuint>;
using sz_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using f_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using d_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using i_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using iptr_tensor=boost::numeric::ublas::tensor<int *>;
using uiptr_tensor=boost::numeric::ublas::tensor<uint32_t *>;
using gi_tensor=boost::numeric::ublas::tensor<GLint>;
using li_tensor=boost::numeric::ublas::tensor<long>;
using void_tensor=boost::numeric::ublas::tensor<void *>;
using bgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry *>;
using bge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry *>;
using bmc_tensor=boost::numeric::ublas::tensor<WGpuBufferMapCallback>;
using wdc_tensor=boost::numeric::ublas::tensor<WGpuOnSubmittedWorkDoneCallback>;
using oac_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterCallback>;
using odc_tensor=boost::numeric::ublas::tensor<WGpuRequestDeviceCallback>;
using bbl_tensor=boost::numeric::ublas::tensor<WGpuBufferBindingLayout>;
using bd_tensor=boost::numeric::ublas::tensor<WGpuBufferDescriptor>;
using md_tensor=boost::numeric::ublas::tensor<WGpuShaderModuleDescriptor>;
using dd_tensor=boost::numeric::ublas::tensor<WGpuDeviceDescriptor>;
using rao_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterOptions>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using cb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using ce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using cpe_tensor=boost::numeric::ublas::tensor<WGpuComputePassEncoder>;
using cp_tensor=boost::numeric::ublas::tensor<WGpuComputePipeline>;
using pl_tensor=boost::numeric::ublas::tensor<WGpuPipelineLayout>;
using cm_tensor=boost::numeric::ublas::tensor<WGpuShaderModule>;
using bg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using bgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using i53_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using tex_tensor=boost::numeric::ublas::tensor<WGpuTexture>;
using td_tensor=boost::numeric::ublas::tensor<WGpuTextureDescriptor>;
using stbl_tensor=boost::numeric::ublas::tensor<WGpuStorageTextureBindingLayout>;
using tv_tensor=boost::numeric::ublas::tensor<WGpuTextureView>;
using tvd_tensor=boost::numeric::ublas::tensor<WGpuTextureViewDescriptor>;
using ced_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoderDescriptor>;
using bms_tensor=boost::numeric::ublas::tensor<WGPU_BUFFER_MAP_STATE>;

static v_tensor sse=v_tensor{2,2};
static v_tensor sse2=v_tensor{2,2};
static v_tensor sse3=v_tensor{2,2};
static v_tensor sse4=v_tensor{1,1};
static shad_tensor Sh=shad_tensor{3,3};
static shad_tensor TX=shad_tensor{3,3};
static prg_tensor S1=prg_tensor{1,1,1};
static sz_tensor Si=sz_tensor{1,1};
static d_tensor d_time=d_tensor{2,2};
static f_tensor Fi=f_tensor{3,3};
static d_tensor Di=d_tensor{2,2};
static gi_tensor uni_i=gi_tensor{1,1};
static i_tensor i_view=i_tensor{1,2};
static i_tensor i_date=i_tensor{2,2};
static f_tensor t_size=f_tensor{1,2};
static li_tensor i_size=li_tensor{1,2};
static void_tensor cntx=void_tensor{2,2};
static i_tensor cntxi=i_tensor{2,2};
static mouse_tensor mms=mouse_tensor{2,2};
static li_tensor mms2=li_tensor{2,2};
static void_tensor bin=void_tensor{1,1};
static wa_tensor WGPU_Adapter=wa_tensor{1,1,2};
static wd_tensor WGPU_Device=wd_tensor{1,1,2};
static wq_tensor WGPU_Queue=wq_tensor{1,1,2};
static cb_tensor WGPU_CommandBuffer=cb_tensor{1,1,3};
static wb_tensor WGPU_Buffers=wb_tensor{3,3,3};
static ce_tensor WGPU_CommandEncoder=ce_tensor{1,1,4};
static cpe_tensor WGPU_ComputePassCommandEncoder=cpe_tensor{1,1,3};
static cp_tensor WGPU_ComputePipeline=cp_tensor{1,1,1};
static pl_tensor WGPU_ComputePipelineLayout=pl_tensor{1,1,1};
static cm_tensor WGPU_ComputeModule=cm_tensor{1,1,1};
static bg_tensor WGPU_BindGroup=bg_tensor{1,1,2};
static bgl_tensor WGPU_BindGroupLayout=bgl_tensor{1,1,2};
static bgle_tensor WGPU_BindGroupLayoutEntries=bgle_tensor{1,1,2};
static bge_tensor WGPU_BindGroupEntries=bge_tensor{1,1,2};
static bmc_tensor WGPU_MapCallback=bmc_tensor{1,1,3};
static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
static oac_tensor WGPU_ObtainedAdapterCallback=oac_tensor{1,1,2};
static odc_tensor WGPU_ObtainedDeviceCallback=odc_tensor{1,1,2};
static bbl_tensor WGPU_BufferBindingLayout=bbl_tensor{1,1,4};
static bd_tensor WGPU_BufferDescriptor=bd_tensor{1,1,4};
static md_tensor WGPU_ShaderModuleDescriptor=md_tensor{1,1,3};
static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
static void_tensor WGPU_UserData=void_tensor{1,1,2};
static rao_tensor WGPU_RequestAdapterOptions=rao_tensor{1,1,1};
static dd_tensor WGPU_DeviceDescriptor=dd_tensor{1,1,1};
static uiptr_tensor WGPU_ResultBuffer=uiptr_tensor{1,1,1};
static uiptr_tensor WGPU_InputBuffer=uiptr_tensor{1,1,1};
static i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
static i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
static tex_tensor WGPU_Texture=tex_tensor{1,1,1};
static td_tensor WGPU_TextureDescriptor=td_tensor{1,1,1};
static stbl_tensor WGPU_StorageTextureBindingLayout=stbl_tensor{1,1,1};
static tvd_tensor WGPU_TextureViewDescriptor=tvd_tensor{1,1,1};
static tv_tensor WGPU_TextureView=tv_tensor{1,1,1};
static uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
static ced_tensor WGPU_CommandEncoderDescriptor=ced_tensor{1,1,1};
static bms_tensor WGPU_BufferStatus=bms_tensor{1,1,1};

uint32_t workgroupSize=64;
uint32_t OutputBufferUnits=262144;
uint32_t OutputBufferBytes=262144*4;
uint32_t InputBufferUnits=262144;
uint32_t InputBufferBytes=262144*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytes;

const char * Entry="computeStuff";
// uint32_t invocationCount=BufferMapSize/sizeof(int);
// uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
void * userDataB;
GLsizei width=256;
GLsizei height=256;
GLuint wtexture[4];
GLuint colorBuffer;
GLuint renderBufferA;
GLuint renderBufferB;
GLuint renderBufferC;
GLuint srgbTexture;
GLuint frameBuffer;
GLuint depthBuffer;
WGpuTexture textureA;
  WGpuAdapter adapter=0;
  WGpuDevice device=0;
  WGpuQueue queue=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuBindGroupLayout bindGroupLayoutB=0;
WGpuComputePipeline computePipeline=0;
WGpuBuffer inputBuffer=0;
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroup bindGroup=0;
WGpuBindGroup bindGroupB=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[3]={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntriesB[2]={};
WGpuBindGroupEntry bindGroupEntry[3]={};
WGpuBindGroupEntry bindGroupEntryB[2]={};
WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayout1={1,34,2};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
std::vector<float>color_input(InputBufferUnits);
std::vector<uint8_t>input(InputBufferBytes);
std::vector<uint8_t>outputd(OutputBufferBytes);
std::vector<uint8_t>outpute(OutputBufferBytes);
WGpuBufferDescriptor bufferDescriptorI={262144*4,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={262144*4,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
WGpuBufferDescriptor bufferDescriptorM={262144*4,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorC={262144*4,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};

// 14 = R32FLOAT   34 = RGBA32UINT
WGpuTextureDescriptor textureDescriptorA={256,256,1,1,1,2,34,WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST};
WGpuTextureViewDescriptor textureViewDescriptorA={34,WGPU_TEXTURE_VIEW_DIMENSION_2D};
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={cmp_bdy,0,NULL};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;
uint32_t * WGPU_Result_Array=new uint32_t[OutputBufferBytes];
uint32_t * WGPU_Input_Array=new uint32_t[InputBufferBytes];
uint32_t * WGPU_Color_Input_Array=new uint32_t[InputBufferBytes];
WGpuImageCopyTexture WGPU_Input_Image={};
WGpuImageCopyTexture WGPU_Output_Image={};
WGpuImageCopyBuffer WGPU_Input_Buffer={};
WGpuImageCopyBuffer WGPU_Output_Buffer={};
WGpuImageCopyBuffer WGPU_Mapped_Buffer={};

unsigned char * ColorA=new unsigned char[262144*sizeof(unsigned char)];

inline int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), WGPU_BufferRange.at(0,0,1) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
raN=rNd4(3);
  /*
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
  */
}
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
  int rndm=0;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerC=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,0)=WGPU_Range_PointerC;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),  WGPU_BufferRange.at(0,0,0) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
rndm=rNd4(3);
  /*
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
  */
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
return;
};

static void raf(){
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorA;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
WGPU_ColorBuffer.at(0,0,0)=WGPU_Color_Input_Array;
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=4096;
WGPU_Output_Buffer.rowsPerImage=256;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=4096;
WGPU_Mapped_Buffer.rowsPerImage=256;
raN=rNd4(256);
input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(WGPU_Device.at(0,0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayout1;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
bindGroupLayoutEntries[2].binding=2;
bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[2].type=4;
bindGroupLayoutEntries[2].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(WGPU_Device.at(0,0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(WGPU_Device.at(0,0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(WGPU_Device.at(0,0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=InputBufferBytes;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=OutputBufferBytes;
bindGroupEntry[2].binding=2;
bindGroupEntry[2].resource=WGPU_Texture.at(0,0,0);
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(WGPU_Device.at(0,0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
}
return;
}

static void WGPU_Run(){
int RraN=rNd4(256);
input[0]=RraN;
WGPU_InputBuffer.at(0,0,0)[0]=RraN;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,1),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
}
return;
}

static void ObtainedWebGpuDeviceStart2(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,1)=result;
raf();
return;
}

static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,1),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

static void ObtainedWebGpuAdapterStart2(WGpuAdapter result,void * userData){
WGPU_Adapter.at(0,0,1)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
}

static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData){
adapter=result;
WGPU_Adapter.at(0,0,0)=result;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

void WGPU_Start(){
WGPU_UserData.at(0,0,0)=userDataA;
WGPU_UserData.at(0,0,1)=userDataB;
WGPU_ObtainedDeviceCallback.at(0,0,0)=ObtainedWebGpuDeviceStart;
WGPU_ObtainedDeviceCallback.at(0,0,1)=ObtainedWebGpuDeviceStart2;
WGPU_DeviceDescriptor.at(0,0,0)=deviceDescriptor;
WGPU_RequestAdapterOptions.at(0,0,0)=options;
WGPU_ObtainedAdapterCallback.at(0,0,0)=ObtainedWebGpuAdapterStart;
WGPU_ObtainedAdapterCallback.at(0,0,1)=ObtainedWebGpuAdapterStart2;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_ComputeDoneCallback.at(0,0,1)=onComputeDoneRun;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
return;
}
  
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
Fi.at(1,2)=0.5f;
Fi.at(0,1)=-1.0f;
Fi.at(2,0)=-0.5f;
Fi.at(1,1)=0.0f;
Di.at(0,0)=1.0;
Di.at(0,1)=-1.0;
Di.at(1,1)=0.0;
return;
}

static inline float gF(){
return Fi.at(0,0);
}

static inline float gF5(){
return Fi.at(1,2);
}

static inline float gFm1(){
return Fi.at(0,1);
}

static inline float gFm5(){
return Fi.at(2,0);
}

static inline float gF0(){
return Fi.at(1,1);
}

static inline boost::compute::double_ gD(){
return Di.at(0,0);
}

static inline boost::compute::double_ gDm1(){
return Di.at(0,1);
}

static inline boost::compute::double_ gD0(){
return Di.at(1,1);
}

};

const inline unsigned char gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
const unsigned char indc[35]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
// const unsigned char indc[10]={gu0,gu1,gu2,gu3,gu4,gu5,gu6,gu7,gu8,gu9};
inline GLint uni_srate=0,uni_dte=0,uni_res=0,uni_fps=0,smp_chn_res[4]={},smp_chn[5],uni_frm=0;
inline GLfloat uni_tme=0.0f,uni_tme_dlt=0.0f,uni_mse=0.0f;
inline GLfloat uni_chn_tme[4];

struct{
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
}u_time;

union{
boost::uint_t<32>::exact VBO,EBO,VCO;
}shad;

inline struct{
boost::compute::double_ wi=0.0;
boost::compute::double_ hi=0.0;
}mouse;

int Size=0;
int tmm=166666000;
int tmm2=1000;
inline struct timespec rem;
inline struct timespec req={0,tmm};
inline struct timespec req2={0,tmm2};
const int32_t ele=36;
// const int ele=10;

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

static char * result=NULL;
static char * results=NULL;
static long int length=0;
boost::uint_t<32>::exact uniBlock;

class Run{

private:

Compile compile;

int32_t iFps=120;
EGLDisplay display=nullptr;
EGLSurface surface=nullptr;
EGLContext ctxegl=nullptr;
EGLConfig eglconfig=nullptr;
EGLint config_size=0,major,minor=0;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");
const char * src[4];
char * vrt_bdy=vrt_bdy_src;
char * frg_hdr=frg_hdr_src;
char * frg_ftr=frg_ftr_src;
char * cm_hdr=cm_hdr_src;

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;

GPU gpu;

public:

static inline void nanoPause(){
nanosleep(&req2,&rem);
}

static void PRGin(boost::uint_t<64>::exact prg){
sse4.at(0,0)=wasm_i64x2_splat(prg);
S1.at(0,0,0)=wasm_i64x2_extract_lane(sse4.at(0,0),0);
return;
}

static void u_iTime_set(boost::compute::double_ set){
// d_time.at(0,0)=set;
// sse2.at(0,0)=wasm_f64x2_splat(d_time.at(0,0));
sse2.at(0,0)=wasm_f64x2_splat(set);
// d_time.at(0,0)=wasm_f64x2_extract_lane(sse2.at(0,0),0);
return;
}

static void u_iSize_set(boost::compute::double_ set){
sse.at(1,0)=wasm_f32x4_splat(set);
t_size.at(0,0)=wasm_f32x4_extract_lane(sse.at(1,0),0);
t_size.at(0,1)=wasm_f32x4_extract_lane(sse.at(1,0),0);
return;
}

// static void i_iSize_set(boost::int_t<32>::exact set){
static void i_iSize_set(int32_t set){
sse3.at(0,0)=wasm_i32x4_splat(set);
i_size.at(0,0)=wasm_i32x4_extract_lane(sse3.at(0,0),0);
i_size.at(0,1)=wasm_i32x4_extract_lane(sse3.at(0,0),0);
return;
}

static void u_iTimeDelta_set(boost::compute::double_ set){
sse.at(0,1)=wasm_f64x2_splat(set);
// d_time.at(1,1)=wasm_f64x2_extract_lane(sse.at(0,1),0);
return;
}

void uniUP(){
t_size.at(0,1)=t_size.at(0,1)*1.01;
glUniform3f(uni_res,t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[0],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[1],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[2],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[3],t_size.at(0,1),t_size.at(0,1),gpu.gF());
//  glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
return;
}

void uniDOWN(){
t_size.at(0,1)=t_size.at(0,1)*0.99;
glUniform3f(uni_res,t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[0],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[1],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[2],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform3f(smp_chn_res[3],t_size.at(0,1),t_size.at(0,1),gpu.gF());
// glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
return;
}

static void viewUP(){
i_size.at(0,1)=i_size.at(0,1)*1.5;
glViewport(0,0,i_size.at(0,1),i_size.at(0,1));
return;
}

static void viewDOWN(){
i_size.at(0,1)=i_size.at(0,1)/1.5;
glViewport(0,0,i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveDOWN(){
i_view.at(0,0)=i_view.at(0,0)-1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveUP(){
i_view.at(0,0)=i_view.at(0,0)+1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveLEFT(){
i_view.at(0,1)=i_view.at(0,1)-1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}

static void moveRIGHT(){
i_view.at(0,1)=i_view.at(0,1)+1;
glViewport(i_view.at(0,0),i_view.at(0,1),i_size.at(0,1),i_size.at(0,1));
return;
}
  
union{

static void Rend(){
uni_i.at(0,0)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
if(ms_l==true){
mms.at(0,1)=round(mms2.at(0,0)/i_size.at(0,0));
mms.at(1,1)=round((mms2.at(0,1))/i_size.at(0,0));
}
// retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
// retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
// retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
// retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const long xxx=mms2.at(0,0);
const long yyy=mms2.at(0,1);
mms.at(0,0)=float(xxx);
mms.at(1,0)=float((i_size.at(0,0)-yyy));
clk_l=false;
}
mms.at(2,0)=float(mms2.at(0,0));
mms.at(2,1)=float(i_size.at(0,0)-mms2.at(0,1));
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
}
else{
clk_l=true;
}
// glUniform1f(uni_tme,d_time.at(0,0));
 //   boost::compute::interop::opengl::set_uniform(uni_tme,wasm_f64x2_extract_lane(sse2.at(0,0),0));
 glUniform1f(uni_tme,wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[0],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[1],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[2],wasm_f64x2_extract_lane(sse2.at(0,0),0));
glUniform1f(uni_chn_tme[3],wasm_f64x2_extract_lane(sse2.at(0,0),0));
// glUniform1f(uni_tme_dlt,d_time.at(1,1));
glUniform1f(uni_tme_dlt,wasm_f64x2_extract_lane(sse.at(0,1),0));

  // webgpu
  /*
const time_t timE=time(0);
struct tm *datE=localtime(&timE);
int yr=1900+datE->tm_year;
int mn=1+datE->tm_mon;
int dy=datE->tm_mday-1;
int hr=5+datE->tm_hour;
int mi=datE->tm_min;
int sc=datE->tm_sec;
int shaderToySeconds=(hr*3600)+(mi*60)+(sc);
i_date.at(1,0)=dy;
i_date.at(1,1)+=int(d_time.at(0,0));
// glUniform4i(uni_dte,i_date.at(0,0),i_date.at(0,1),i_date.at(1,0),i_date.at(1,1));
int tfrm=(uni_i.at(0,0)%4);

if(uni_i.at(0,0)%45==0){
raN=rNd4(3);
WGPU_Run();   //  launch WebGPU
glUniform1i(smp_chn[raN],raN);
// glBindTexture(GL_TEXTURE_2D,0);
}

if(uni_i.at(0,0)%15==0){
  
raN=rNd4(3);
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
glUniform1i(smp_chn[raN],raN);
}

  // buffer frame/time
// glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
// glBufferSubData(GL_UNIFORM_BUFFER,8,4,&uni_i.at(0,0)); 
// glBufferSubData(GL_UNIFORM_BUFFER,12,4,&d_time.at(0,0)); 
// glBindBuffer(GL_UNIFORM_BUFFER,0);
  glUniform1i(smp_chn[0],0);
 glUniform1i(smp_chn[1],1);
 glUniform1i(smp_chn[2],2);
 glUniform1i(smp_chn[3],3);
 */

glUniform1i(uni_frm,uni_i.at(0,0));
// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
// glClearDepth(1.0);
// glSampleCoverage(1.0,GL_FALSE);
glDrawElements(GL_TRIANGLES,ele,GL_UNSIGNED_BYTE,indc);
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
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
glViewport(0,0,i_size.at(0,0),i_size.at(0,0));  //  viewport/scissor after UsePrg runs at full resolution
// glScissor(0,0,i_size.at(0,1),i_size.at(0,1));
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
result=static_cast<char *>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
results=reinterpret_cast<char *>(result);
return results;
}
return nullptr;
}

}procc;

void strt(){
emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
typedef struct{GLfloat XYZW[4];}Vertex;
gpu.setFloats();
/*
const Vertex vrt[10]={
{gpu.gFm5(),gpu.gFm5(),gpu.gF5()},
{gpu.gF0(),gpu.gF0(),gpu.gF5()},
{gpu.gF5(),gpu.gF5(),gpu.gF()},
{gpu.gF(),gpu.gF5(),gpu.gFm5()},
{gpu.gF5(),gpu.gF(),gpu.gF0()},
{gpu.gF5(),gpu.gF5(),gpu.gF5()},
{gpu.gF(),gpu.gF(),gpu.gFm5()},
{gpu.gFm5(),gpu.gF5(),gpu.gF0()},
{gpu.gF0(),gpu.gFm5(),gpu.gF5()},
{gpu.gF5(),gpu.gF0(),gpu.gF()}
};
*/
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
attr.renderViaOffscreenBackBuffer=EM_TRUE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
cntxi.at(0,0)=ctx;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglChooseConfig(display,att_lst,&eglconfig,1,&config_size);
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
// nanoPause();
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
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_direct_state_access");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_precision_hint_nicest");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_ES2_compatibility");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(cntxi.at(0,0),"ARB_texture_storage");
emscripten_webgl_enable_extension(cntxi.at(0,0),"GL_ARB_ES3_compatibility");
// glEnable(GL_FRAMEBUFFER_SRGB);
// glEnable(GL_COLOR_CONVERSION_SRGB);
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
// glClearDepth(Di.at(0,0));
glEnable(GL_DEPTH_TEST);
glDisable(GL_DITHER);
// glDepthFunc(GL_LEQUAL);
// glDepthFunc(GL_LESS);
// glEnable(GL_BLEND);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
// glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
// glStencilFunc(GL_ALWAYS,1,0xFF);
// glStencilMask(0xFF);
glFrontFace(GL_CW);
// glCullFace(GL_FRONT);
// glEnable(GL_CULL_FACE);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
 // glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
// glBlendEquation(GL_FUNC_SUBTRACT);
//   glClearColor(1.0f,1.0f,1.0f,1.0f);
glGenBuffers((GLsizei)1,&shad.VBO);
gpu.VBOin(shad.VBO);
glBindBuffer(GL_ARRAY_BUFFER,Sh.at(2,1));
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_STATIC_DRAW);
/*
    // Boost Compute / Interop / OpenGL
boost::compute::device CLdevice=boost::compute::system::default_device();
boost::compute::interop::opengl::buffer_object_interface buffer_object(CLdevice,GL_ARRAY_BUFFER);
boost::compute::vertex_array_object vertex_array(CLdevice);
auto CLcontext=boost::compute::interop::opengl::context(CLdevice);
auto command_queue=boost::compute::command_queue(CLcontext,CLdevice);
std::cout << "Got OpenCL context:" << CLcontext << '\n'; 
vertex_array.bind_buffer(GL_ARRAY_BUFFER,buffer_object);
vertex_array.set_attribute_pointer(0,4,GL_FLOAT,GL_FALSE,0,0);
boost::compute::interop::opengl::buffer vertex_buffer(CLcontext,sizeof(float)*4);
vertex_buffer.write(new float[8]{gpu.gFm1(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gF(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},{gpu.gFm1(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gFm1(),gpu.gFm1(),gpu.gF()},{gpu.gF(),gpu.gF(),gpu.gFm1(),gpu.gF()},{gpu.gFm1(),gpu.gF(),gpu.gF(),gpu.gF()},0,sizeof(float)*4);
buffer_object.bind(GL_ARRAY_BUFFER);
buffer_object.set_data(vertex_buffer);
   */
     
// nanoPause();
glGenBuffers((GLsizei)1,&shad.EBO);
gpu.EBOin(shad.EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Sh.at(1,0));
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
  //    boost::compute::buffer index_buffer(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);

// nanoPause();
src[0]=cm_hdr;
src[1]=vrt_bdy;
boost::uint_t<32>::exact vtx=compile.cmpl_shd(GL_VERTEX_SHADER,2,src);
src[0]=cm_hdr;
src[1]=frg_hdr;
src[2]=frag_body;
src[3]=frg_ftr;
boost::uint_t<32>::exact frag=compile.cmpl_shd(GL_FRAGMENT_SHADER,4,src);
boost::uint_t<32>::exact shd_prg=glCreateProgram();
PRGin(shd_prg);
::boost::tuples::tie(Sh,shd_prg);
::boost::tuples::tie(frag,vtx);
glAttachShader(S1.at(0,0,0),frag);
glAttachShader(S1.at(0,0,0),vtx);
glBindAttribLocation(S1.at(0,0,0),0,"iPosition");
glLinkProgram(S1.at(0,0,0));
boost::uint_t<32>::exact uniIndex=glGetUniformBlockIndex(S1.at(0,0,0),"uniBlock");   
glUniformBlockBinding(S1.at(0,0,0),0,uniIndex);
glGenBuffers(1,&uniBlock);
glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
glBufferData(GL_UNIFORM_BUFFER,8,NULL,GL_DYNAMIC_DRAW);
glBindBufferBase(GL_UNIFORM_BUFFER,0,uniBlock);
glBindBuffer(GL_UNIFORM_BUFFER,0);
GLsizei * binLength;
GLenum * binaryFormat;
void * GLbin;
glDetachShader(S1.at(0,0,0),frag);
glDetachShader(S1.at(0,0,0),vtx);
glGetProgramBinary(S1.at(0,0,0),sizeof(GLbin),binLength,binaryFormat,&GLbin);
bin.at(0,0)=GLbin;
// nanoPause();
glProgramBinary(S1.at(0,0,0),*binaryFormat,bin.at(0,0),*binLength);
// nanoPause();
// glGenRenderbuffers(1,&colorBuffer);

  //  multisample
glGenRenderbuffers(1,&TX.at(0,0,0));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,0,0));
glRenderbufferStorageMultisample(GL_RENDERBUFFER,8,GL_RGB10_A2,i_size.at(0,0),i_size.at(0,0));
glGenFramebuffers(1,&TX.at(1,0,0));
glBindFramebuffer(GL_FRAMEBUFFER,TX.at(1,0,0));
glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_RENDERBUFFER,TX.at(0,0,0));
glGenRenderbuffers(1,&TX.at(0,0,1));
glBindRenderbuffer(GL_RENDERBUFFER,TX.at(0,0,1));
glRenderbufferStorageMultisample(GL_RENDERBUFFER,8,GL_DEPTH_COMPONENT32F,i_size.at(0,0),i_size.at(0,0));
// glRenderbufferStorageMultisample(GL_RENDERBUFFER,0,GL_DEPTH32F_STENCIL8,i_size.at(0,0),i_size.at(0,0));
// glClearDepth(1.0f);
glBindFramebuffer(GL_FRAMEBUFFER,TX.at(1,0,0));
glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,TX.at(0,0,1));
// glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,TX.at(0,0,1));
// glStencilMask(1);
// glClearStencil(1);

  //  sRGB
glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TX.at(1,0,0));
// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glClear(GL_COLOR_BUFFER_BIT);
glBindFramebuffer(GL_FRAMEBUFFER,0);
glClearColor(1.0,1.0,1.0,1.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glFlush();

glUseProgram(S1.at(0,0,0));
// nanoPause();
glUniform1i(glGetUniformLocation(S1.at(0,0,0),"renderBuffer"),0);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&shad.VCO);
gpu.VCOin(shad.VCO);
glBindVertexArray(Sh.at(2,0));
// nanoPause();
const GLuint atb_pos=glGetAttribLocation(S1.at(0,0,0),"iPosition");
glEnableVertexAttribArray(atb_pos);
// nanoPause();
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_dte=glGetUniformLocation(S1.at(0,0,0),"iDate");
uni_tme=glGetUniformLocation(S1.at(0,0,0),"iTime");
uni_tme_dlt=glGetUniformLocation(S1.at(0,0,0),"iTimeDelta");
uni_chn_tme[0]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[0]");
uni_chn_tme[1]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[1]");
uni_chn_tme[2]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[2]");
uni_chn_tme[3]=glGetUniformLocation(S1.at(0,0,0),"iChannelTime[3]");
uni_frm=glGetUniformLocation(S1.at(0,0,0),"iFrame");
uni_fps=glGetUniformLocation(S1.at(0,0,0),"iFrameRate");
uni_res=glGetUniformLocation(S1.at(0,0,0),"iResolution");
uni_mse=glGetUniformLocation(S1.at(0,0,0),"iMouse");
uni_srate=glGetUniformLocation(S1.at(0,0,0),"iSampleRate");
smp_chn_res[0]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[0]");
smp_chn_res[1]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[1]");
smp_chn_res[2]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[2]");
smp_chn_res[3]=glGetUniformLocation(S1.at(0,0,0),"iChannelResolution[3]");
smp_chn[0]=glGetUniformLocation(S1.at(0,0,0),"iChannel0");
smp_chn[1]=glGetUniformLocation(S1.at(0,0,0),"iChannel1");
smp_chn[2]=glGetUniformLocation(S1.at(0,0,0),"iChannel2");
smp_chn[3]=glGetUniformLocation(S1.at(0,0,0),"iChannel3");
// smp_chn[4]=glGetUniformLocation(S1.at(0,0,0),"iChannel4");
    
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
/*
glGenTextures(1,&wtexture[0]);
glGenTextures(1,&wtexture[1]);
glGenTextures(1,&wtexture[2]);
glGenTextures(1,&wtexture[3]);
GLsizei width1=256;
GLsizei height1=256;
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,wtexture[0]);
// glBindTextureUnit(GLuint(0),wtexture[0]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[0],0);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D,wtexture[1]);
// glBindTextureUnit(GLuint(1),wtexture[1]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[1],1);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D,wtexture[2]);
// glBindTextureUnit(GLuint(2),wtexture[2]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[2],2);
glGenTextures(1,&wtexture[3]);
glActiveTexture(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D,wtexture[3]);
// glBindTextureUnit(GLuint(3),wtexture[3]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width1,height1,0,GL_RGBA,GL_UNSIGNED_BYTE,ColorA);
glGenerateMipmap(GL_TEXTURE_2D);
glUniform1i(smp_chn[3],3);
WGPU_Start();
usleep(125);
  
  // date/time
const time_t timE=time(0);
struct tm *datE=localtime(&timE);
int yr=1900+datE->tm_year;
int mn=1+datE->tm_mon;
int dy=datE->tm_mday-1;
int hr=5+datE->tm_hour;
int mi=datE->tm_min;
int sc=datE->tm_sec;
int shaderToySeconds=(hr*3600)+(mi*60)+(sc);
i_date.at(0,0)=yr;
i_date.at(0,1)=mn;
i_date.at(1,0)=dy;
i_date.at(1,1)=shaderToySeconds;
// glUniform4i(uni_dte,i_date.at(0,0),i_date.at(0,1),i_date.at(1,0),i_date.at(1,1));
// glUniform1f(uni_srate,44100.0f);

  */
glUniform3f(uni_res,4096.0f,4096.0f,gpu.gF());
glUniform3f(uni_res,t_size.at(0,0),t_size.at(0,0),gpu.gF());
glUniform3f(smp_chn_res[0],256.0f,256.0f,gpu.gF());
glUniform3f(smp_chn_res[1],256.0f,256.0f,gpu.gF());
glUniform3f(smp_chn_res[2],256.0f,256.0f,gpu.gF());
glUniform3f(smp_chn_res[3],256.0f,256.0f,gpu.gF());
mms.at(2,0)=t_size.at(0,0)*0.5;
mms.at(2,1)=t_size.at(0,0)*0.5;
glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
// nanoPause();
glViewport((GLint)0,(GLint)0,8192,8192);  //  viewport/scissor after UsePrg runs at full resolution
glViewport((GLint)0,(GLint)0,i_size.at(0,0),i_size.at(0,0));  //  viewport/scissor after UsePrg runs at full resolution
// glEnable(GL_SCISSOR_TEST);
// glScissor((GLint)0,(GLint)0,i_size.at(0,1),i_size.at(0,1));
u_iTime_set(0.0);
u_iTimeDelta_set(0.0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_iTime_set(u_time.time_spana.count());
u_iTimeDelta_set(u_time.time_spanb.count());
float iRate=192000.0f;
glBindBuffer(GL_UNIFORM_BUFFER,uniBlock);
glBufferSubData(GL_UNIFORM_BUFFER,0,4,&iRate); 
glBufferSubData(GL_UNIFORM_BUFFER,4,4,&iFps); 
glBindBuffer(GL_UNIFORM_BUFFER,0);
// glClear(GL_COLOR_BUFFER_BIT);
// glClear(GL_DEPTH_BUFFER_BIT);
// glClear(GL_STENCIL_BUFFER_BIT);
emscripten_set_main_loop((void(*)())Run::procc.Rend,0,0);
return;
}
  
};
