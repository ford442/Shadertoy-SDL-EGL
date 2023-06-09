#define _XOPEN_SOURCE 700

#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define _XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#define _POSIX_REGEXP 1

#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1

#pragma pack(4)
#pragma fenv_access(on)
#pragma STDC FP_CONTRACT ON
#pragma STDC CX_LIMITED_RANGE ON

#include <boost/cstdfloat.hpp>  // must be first include

#include <chrono>
#include <iostream>
#include <cassert>
#include <iomanip>
#include <ctime>
#include <stdio.h>
#include <cfloat>
#include <climits>
#include <math.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <unistd.h>
#include <functional>

#include "../../lib/lib_webgpu.h"

uint64_t bufferSize=64*sizeof(float);

WGpuAdapter adapter=0;
WGpuDevice device=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuComputePipeline computePipeline=0;
WGpuQueue queue=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuBufferDescriptor bufferDescriptorI={bufferSize,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={};
WGpuBufferDescriptor bufferDescriptorM={};
WGpuBufferBindingLayout bufferBindingLayout1={};
WGpuBufferBindingLayout bufferBindingLayout2={};
WGpuBufferBindingLayout bufferBindingLayout3={};
WGpuBuffer inputBuffer=0;
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[2]={};
WGpuBindGroupEntry bindGroupEntry[2]={};
WGpuBindGroup bindGroup=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuQuerySet querySet=0;
void *userDataA;
WGpuRequestAdapterOptions options={};

const char *computeShader =
"@group(0) @binding(0) var<storage,read> inputBuffer: array<f32,64>;"
"@group(0) @binding(1) var<storage,read_write> outputBuffer: array<f32,64>;"
"@compute @workgroup_size(32)"
"fn computeStuff(@builtin(global_invocation_id) global_id: vec3<u32>,@builtin(local_invocation_id) local_id: vec3<u32>) {"
"outputBuffer[0] = inputBuffer[0];"
"}";
