#include <boost/cstdfloat.hpp>  // must be first include
#include "include/vanilla/avx.h"
#include <immintrin.h> 
#include "include/vanilla/defs.h"
#include "include/vanilla/gl.h"
#include "include/vanilla/boost_defs.h"
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
#include <ctime>
#include <vector>
#include <functional>
#include <cassert>
#include <random>
#include <cfloat>
#include <math.h>
#include <new>
#include <emscripten.h>
#include <webgl/webgl2.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#include <iostream>
#include "../../lib/lib_webgpu.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <SDL2/SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1

#include <GLES3/gl3.h>
// #include <GLES3/gl31.h>
// #include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GL/gl.h>
#include <GL/glext.h>

template<class ArgumentType,class ResultType>
struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

inline int rNd4(int randomMax);
static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData);
static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData);
static void WGPU_Start();

extern"C"{

void startWebGPU();

void runWebGPU();

}

inline char wgl_cmp_src[2000]=
"@group(0)@binding(0)var<storage,read>inputBuffer:array<f32,262144>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<f32,262144>;"
"@group(0)@binding(2)var textureA:texture_storage_2d<rgba32uint,write>;"
"@compute@workgroup_size(4,1,64)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){"
"let f:u32=global_id.z;"
"let g:u32=global_id.x;"
"outputBuffer[global_id.x]=inputBuffer[global_id.x];"
"}";

using mouse_tensor=boost::numeric::ublas::tensor<float>;
using shad_tensor=boost::numeric::ublas::tensor<boost::uint_t<32>::exact>;
using prg_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using sz_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using f_tensor=boost::numeric::ublas::tensor<float>;
using d_tensor=boost::numeric::ublas::tensor<double>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using i_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using iptr_tensor=boost::numeric::ublas::tensor<int *>;
using fptr_tensor=boost::numeric::ublas::tensor<float *>;
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
static prg_tensor S1=prg_tensor{1,1,1};
static sz_tensor Si=sz_tensor{1,1};
static d_tensor d_time=d_tensor{2,2};
static f_tensor Fi=f_tensor{2,2};
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
WGpuBufferDescriptor bufferDescriptorI={InputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={OutputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
WGpuBufferDescriptor bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
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

WGpuBufferMapCallback mapCallbackRun2=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), WGPU_BufferRange.at(0,0,1) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.getElementById('outText').innerHTML=$0;
},WGPU_ResultBuffer.at(0,0,0)[0]);
// std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
// sleep(1);
// WGPU_Run();
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerC=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,0)=WGPU_Range_PointerC;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_BufferRange.at(0,0,0),0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.getElementById('outText').innerHTML=$0;
},WGPU_ResultBuffer.at(0,0,0)[0]);
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,1),&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
usleep(10);
// WGPU_Run();
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun2=[](WGpuQueue queue,void *userData){
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
// WGPU_BUFFER_MAP_STATE statebe=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
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
// input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
// std::cout << "Random input:" << std::endl;
// std::cout << raN << std::endl;
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
// WGPU_Queue.at(0,0,1)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&WGPU_Input_Image,&WGPU_ColorBuffer.at(0,0,0),1024,0,1,1,1);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
 // wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
//  WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
// wgpu_object_destroy(WGPU_Buffers.at(2,0,2));
 // wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
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
raN=rNd4(256);
// input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
// std::cout << "Random input int:" << std::endl;
// std::cout << raN << std::endl;
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
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
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

static void WGPU_Run2(){
return;
}

static void ObtainedWebGpuDeviceStart2(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
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
  wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,0));

// navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
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
WGPU_ComputeDoneCallback.at(0,0,2)=onComputeDoneRun2;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
WGPU_MapCallback.at(0,0,2)=mapCallbackRun2;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
return;
}

// void avgFrm(int Fnum,int leng,float *ptr,float *aptr);

extern "C" {

void runWebGPU(){
WGPU_Run();
}

}

void avgFrm(int Fnum,int leng,float *ptr,float *aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float Wsum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for (int i=0;i<leng;i++){
WGPU_InputBuffer.at(0,0,0)[0]=ptr[i];
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
}
// runWebGPU();
Wsum=WGPU_ResultBuffer.at(0,0,0)[0]/leng;
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
}
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
}
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
}
aptr[200]=maxSum/32;
return;
}

extern "C" {

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}

}

EM_JS(void,ma,(),{
"use strict";
const pnnl=document.body;
var vv=document.getElementById("mv");
var intervalBackward;

function back(){
intervalBackward=setInterval(function(){
if(vv.currentTime==0){
clearInterval(intervalBackward);
}else{
vv.currentTime+=-(0.016);
}
},16.66);
};

var intervalForward;

function forward(){
intervalForward=setInterval(function(){
vv.currentTime+=-(0.016);
},16.66);
};

var intervalLoop;
var stp,a,b,f;

function backForth(stp){
var a=(stp/1000.0);
var b=(stp/1000.0)+1.0;
f=true;
intervalLoop=setInterval(function(){
if(f==true){
if(vv.currentTime>a){
vv.currentTime+=-(0.016666);
}else{
f=false;
}}else if(vv.currentTime<b){
vv.currentTime+=(0.016666);
}else{
f=true;
}
},16.66);
};

function stpForward(){
clearInterval(intervalForward);
}

function stpBack(){
clearInterval(intervalBackward);
}

function stpBackForth(){
clearInterval(intervalLoop);
}

var Mov=1;

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
if(Mov==1){vv=document.getElementById("mv");Mov=0;vv.pause();}
else if(Mov==0){vv=document.getElementById("mv");Mov=1;vv.play();}
}
if (e.code=='KeyW'){vv=document.getElementById("mv");Mov=1;vv.pause();forward();}
if (e.code=='KeyS'){vv=document.getElementById("mv");Mov=1;vv.pause();back();}
if (e.code=='KeyZ'){vv=document.getElementById("mv");Mov=1;vv.pause();var stp=vv.currentTime*1000.0;
backForth(stp);}
if (e.code=='KeyX'){vv=document.getElementById("mv");stpBackForth();vv.play();}
}

function doKeyUp(e){
if (e.code=='KeyS'){Mov=0;stpBack();vv.pause();}
if (e.code=='KeyW'){Mov=0;stpForward();vv.pause();}
}

pnnl.addEventListener('keydown',doKey);
pnnl.addEventListener('keydown',doKeyUp);
let w$=parseInt(document.getElementById("wid").innerHTML,10);
let h$=parseInt(document.getElementById("hig").innerHTML,10);
if(w$<1){w$=640;h$=640;}
vv=document.getElementById("mv");
let $H=Module.HEAPF32.buffer;
let la=h$*h$*4;
var pointa=77*la;
let agav=new Float32Array($H,pointa,300);
let sz=(h$*h$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.getElementById("bcanvas");
const contx=bcanvas.getContext("webgl2",{logarithmicDepthBuffer:false,colorSpace:'display-p3',alpha:true,depth:true,stencil:true,imageSmoothingEnabled:true,preserveDrawingBuffer:false,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true,willReadFrequently:false});
contx.getExtension('WEBGL_color_buffer_float');
contx.getExtension('WEBGL_color_buffer_half_float');
contx.getExtension('OES_texture_float_linear');
contx.getExtension('OES_texture_half_float_linear');
contx.getExtension('EXT_float_blend');
contx.getExtension('EXT_frag_depth');
contx.getExtension('EXT_shader_texture_lod');
contx.getExtension('EXT_sRGB');
contx.getExtension('EXT_blend_minmax');
contx.getExtension('ANGLE_instanced_arrays');
contx.getExtension('EXT_disjoint_timer_query');
contx.getExtension('EXT_clip_cull_distance');
contx.getExtension('EXT_disjoint_timer_query_webgl2');
contx.getExtension('KHR_parallel_shader_compile');
contx.getExtension('OES_draw_buffers_indexed');
contx.getExtension('OES_element_index_uint');
contx.getExtension('OES_fbo_render_mipmap');
contx.getExtension('OES_standard_derivatives');
contx.getExtension('OES_vertex_array_object');
contx.getExtension('WEBGL_blend_equation_advanced_coherent');
contx.getExtension('WEBGL_depth_texture');
contx.getExtension('WEBGL_draw_buffers');
contx.getExtension('WEBGL_provoking_vertex');
contx.getExtension('EXT_framebuffer_sRGB');
contx.getExtension('OES_depth32');
contx.getExtension('OES_fixed_point');
contx.getExtension('OES_shader_multisample_interpolation');
contx.getExtension('WEBGL_webcodecs_video_frame');
contx.getExtension('OES_single_precision');
contx.getExtension('GL_EXT_texture_shadow_lod');
contx.getExtension('GL_NV_memory_attachment');
contx.getExtension('EXT_color_buffer_float');
  
contx.disable(gl.DITHER);

const g=new GPUX({mode:'gpu',canvas:bcanvas,webGl:contx});
const g2=new GPUX({mode:'gpu'});
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;

// castle way
// const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
// GE way
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// castle way
// const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
// GE way
const glslAveg=`float Aveg(float a,float b){return(0.999-(((a)-(b))*((a)*(0.999/(0.999-b)))));}`;

const glslStone=`float Stone(float a,float b,float c,float d){return(max(((a-(d-(d*0.5)))+(b-(d-(d*0.5)))+(c-(d-(d*0.5)))*4.0),0.0));}`;
const glslStoned=`float Stoned(float a,float b,float c){return(min((a+c),1.0)-((b*0.3)*0.14));}`;
  
// g.addNativeFunction('Stone',glslStone,{returnType:'Number'});
// g.addNativeFunction('Stoned',glslStoned,{returnType:'Number'});
  
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});

let R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setOptimizeFloatMemory(true).setArgumentTypes(["HTMLVideo"]).setOutput([sz]);

let t=g.createKernel(function(v){
// GE way
var P=v[this.thread.y][this.thread.x];
var av$=Ave(P[0],P[1],P[2]);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setPipeline(true).setOutput([h$,h$]);

  //castle way
// var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
// var av$=Ave(P[0],P[1],P[2]);
// return[P[0],P[1],P[2],av$];
// }).setTactic("precision").setPrecision('single').setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);

let r=g.createKernel(function(f){
 /*   //castle way
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
var Min=(4.0*(($amax-($favg-$amin))/2.0));
var ouT=Math.max(Min,alph);
  // send p[0],p[1],p[2],ouT => return grr
  var rng=Stone(p[0],p[1],p[2],ouT);
// var rng=ouT-(ouT*0.5);
// var grr=(p[0]-rng)+(p[1]-rng)+(p[2]-rng);
// grr=grr*4.0;
// grr=Math.max(grr,0.0);
    // send p[x],p[x] => return r/g/b
var rr=Stoned(p[0],p[1],rng);
var gg=Stoned(p[1],p[3],rng);
var bb=Stoned(p[2],p[3],rng);
// var rr=Math.min((p[0]+grr),1.0)-((p[1])*0.14);
// var gg=Math.min((p[1]+grr),1.0)-((p[3]*0.3)*0.14);
// var bb=Math.min((p[2]+grr),1.0)-((p[3]*0.3)*0.14);
  var ss=(Ave(rr,gg,bb)-p[3]);
  var aveg=Aveg(p[3],ouT)+ss;
this.color(rr,gg,bb,aveg);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);
*/
  
// GE way
var p=f[this.thread.y][this.thread.x];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
/*
var rr;
var gg;
var bb;
var der=p[0];
var neerg=p[1];
var eulb=p[2];

if(der>0.333){
 rr=Silver(der);
}else{
 rr=GoldR(der);
 }

if(neerg>0.4){
gg=Silver(neerg);
}else{
gg=GoldG(neerg);
}

if(eulb>0.5){
bb=Silver(eulb);
}else{
bb=GoldB(eulb);
}
this.color(GoldR(p[0]),GoldG(p[1]),GoldB(p[2]),aveg);
 */
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setGraphical(true).setOutput([h$,h$]);

w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
let l=w$*h$*16;
la=h$*h$*4;
let al=w$*h$*8;
sz=(h$*h$)/8;
pointa=77*la;
agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
eval("$"+j+".set($$1);");
}
var d=S();if(d)d();d=S();function S(){
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
l=w$*h$*16;
la=h$*h$*4;
al=w$*h$*8;
sz=(h$*h$)/8;
pointa=77*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.getElementById("mv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){return;}
for(i=64;i>0;i--){
var loca=$F+1;if(loca>64){loca=1;}
var locb=$Bu+1;if(locb>64){locb=1;}
eval("if ($F==="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
}
var $bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;
Module.ccall('runWebGPU',{async: true});
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
setTimeout(function(){
M();
},16.66);
};
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}
});

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);
static const char *read_file(const char *filename);
  
extern "C" {

SDL_AudioDeviceID dev;
struct{Uint8* snd;int pos;Uint32 slen;SDL_AudioSpec spec;}wave;

void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
return;
}}

void qu(int rc){
SDL_Quit();
return;
}

void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
}

void SDLCALL bfr(void *unused,Uint8* stm,int len){
Uint8* wptr;
int lft;
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while (lft<=len){
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
}

void plt(){
char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
return;
}

}

GLfloat x;
GLfloat y;
EM_BOOL ms_l;

void uni(float xx,float yy,GLfloat time,EGLint fram);
GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources);

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 0;
}

using namespace std;
using namespace std::chrono;

steady_clock::time_point t1,t2;
GLuint uni_frm,uni_tme,uni_res,shader;
double Ttime;
EGLint iFrame;
GLsizei s4=4;
// int v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v10=10,v16=16,v24=24,v32=32,v64=64;
int a,b;
float F=1.0;
float F0=0.0;
float Fm1=-1.0;
float mouseX;
float mouseY;
float cMouseX;
float cMouseY;
int Size;
GLfloat S;
EM_BOOL clk_l;
GLsizei i;
struct timespec rem;
struct timespec req={0,16666000};
GLuint uni_mse;

void uni(float xx,float yy,GLfloat time,EGLint fram){
GLfloat mX,mY;
if(ms_l==true){
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clk_l=false;
}
GLfloat mm=S*xx;
GLfloat nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,time);
glUniform1i(uni_frm,fram);
return;
}

const char *sources[4];
GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

void renderFrame(){
EMSCRIPTEN_RESULT ret;
t2=steady_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,indc);
glFlush();
// nanosleep(&req,&rem);
iFrame++;
glFinish();
return;
}

static const char *read_file(const char *filename){
char *result=NULL;
long length=0;
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
}
result=static_cast<char*>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return nullptr;
}

GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;i++){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

void strt(){
emscripten_cancel_main_loop();
// nanosleep(&req,&rem);
const char *fileloc="/shader/shader1.toy";
EGLint v0=0,v3=3;
GLfloat gF=F;
GLfloat gF0=F0;
GLfloat gFm1=Fm1;
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const char common_shader_header_gles3[]=
"#version 300 es \n"
// "#undef HW_PERFORMANCE \n"
// "#define HW_PERFORMANCE 0 \n"
"precision highp float;precision highp int;precision highp sampler3D;precision highp sampler2D;\n";
const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
const char fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution;uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"out vec4 fragColor;\n";
const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";
const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res;
GLuint VCO,ECO,vtx,frag;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EGLint config_size,major,minor,atb_pos;
iFrame=0;
clk_l=true;
// Size=EM_ASM_INT({return parseInt(window.innerHeight);});
double wi,hi;
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
// eglBindAPI(EGL_OPENGL_ES_API);
eglBindAPI(EGL_OPENGL_API);
  
const EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
  
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,4,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
  
const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_RENDER_BUFFER,EGL_TRIPLE_BUFFER_NV,
  
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,64,
EGL_SAMPLE_BUFFERS,1,
EGL_SAMPLES,16,
EGL_NONE
};
  
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx,"EXT_float_blend");
emscripten_webgl_enable_extension(ctx,"EXT_frag_depth");
emscripten_webgl_enable_extension(ctx,"EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB");
emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx,"EXT_clip_cull_distance");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"OES_depth32");
emscripten_webgl_enable_extension(ctx,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx,"OES_single_precision");
emscripten_webgl_enable_extension(ctx,"GL_EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx,"GL_NV_memory_attachment");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// nanosleep(&req,&rem);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STREAM_DRAW);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STREAM_DRAW);
// nanosleep(&req,&rem);
static const char* default_fragment_shader=(char*)read_file(fileloc);
// nanosleep(&req,&rem);
// nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
// nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
// nanosleep(&req,&rem);
shd_prg=glCreateProgram();
// nanosleep(&req,&rem);
glAttachShader(shd_prg,vtx);
// nanosleep(&req,&rem);
glAttachShader(shd_prg,frag);
// nanosleep(&req,&rem);
atb_pos=0;
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
// nanosleep(&req,&rem);
glUseProgram(shd_prg);
// nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays(1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_TRUE,0,(GLvoid*)0);
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
glUniform3f(uni_res,S,S,1.0);
glUniform3f(smp_chn_res,S,S,1.0);
glClearColor(gF,gF,gF,gF);
  // glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
// glDisable(GL_BLEND);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_SCISSOR_TEST);
glDepthFunc(GL_LESS);
  glClearDepth(1.0);
glEnable(GL_POLYGON_OFFSET_FILL);
glPolygonOffset(0.0f,0.0f);

// glFrontFace(GL_CW);
glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT,GL_MAX);
  glDisable(GL_DITHER);
t1=steady_clock::now();
glViewport(0,0,GLint(Size),GLint(Size));
emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
}

extern "C" {

void startWebGPU(){
WGPU_Start();
}

void str(){
strt();
return;
}

void pl(){
plt();
return;
}

void b3(){
ma();
return;
}

}

int main(){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
