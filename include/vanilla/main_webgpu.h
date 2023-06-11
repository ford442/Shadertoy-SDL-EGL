#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/defs.h"
#include "../../include/shader/gl.h"
#include "../../include/shader/egl.h"

#include <chrono>
#include <iostream>
#include <cassert>
#include <iomanip>
#include <ctime>
#include <stdio.h>
#include <cfloat>
#include <climits>
#include <math.h>
#include <unistd.h>
#include <functional>
#include <emscripten.h>
#include <emscripten/html5.h>

#include "../../lib/lib_webgpu.h"

uint32_t workgroupSize=256;
uint64_t IbufferSize=65536*sizeof(int);
std::vector<int>input(IbufferSize/sizeof(int));
const char * Entry="computeStuff";
uint32_t invocationCount=IbufferSize/sizeof(int);
uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
std::vector<int>outputd(IbufferSize/sizeof(int));
int * resulT[65536];
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;

WGpuAdapter adapter=0;
WGpuDevice device=0;
WGpuQueue queue=0;
WGpuBindGroupLayout bindGroupLayout=0;
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
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[2]={};
WGpuBindGroupEntry bindGroupEntry[2]={};
WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferDescriptor bufferDescriptorI={IbufferSize,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={IbufferSize,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
WGpuBufferDescriptor bufferDescriptorM={IbufferSize,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,true};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};

inline char computeShaderSrc[1000]=
"@group(0)@binding(0)var <storage,read>inputBuffer: array<i32,65536>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<i32,65536>;"
"@compute@workgroup_size(256)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>,@builtin(local_invocation_id)local_id:vec3<u32>){"
"var a:i32=0;{"
"var i:i32=0;"
"loop{"
"if !(i<255){a++;i=0;}if a<255{break;}"
"continuing{outputBuffer[i+a]=i%64;}"
"}"
"}"
"}";

char * computeShader=computeShaderSrc;
