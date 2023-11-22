#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/boost_defs.hpp"

#define __EMCSCRIPTEN__ 1

#include <cstdint>

#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>

#include <chrono>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>
#include <stdarg.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <memory>
#include <cassert>
#include <random>
#include <cfloat>
#include <new>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#include <iostream>
#include "../../lib/lib_webgpu.h"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <cstdlib>

// #include <boost/throw_exception.hpp>
    
#include <functional>

#include <boost/function.hpp>

#include <boost/compute/cl.hpp>

#include <boost/compute/core.hpp>
#include <boost/compute/interop/opengl.hpp>

inline int rNd4(int randomMax);
// static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData);
static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData);

// static void WGPU_Start();

// #include <boost/compute.hpp>
// #include <boost/compute/algorithm.hpp>

// namespace compute = boost::compute;

extern"C"{

void startWebGPU();

void runWebGPU();

}

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


static f_tensor sze=f_tensor{2,2};
double szh,szw,wi,hi;
uint32_t workgroupSize;
uint32_t OutputBufferUnits;
uint32_t OutputBufferBytes;
uint32_t InputBufferUnits;
uint32_t InputBufferBytes;
uint64_t WGPU_InputRangeSize;
WGPU_MAP_MODE_FLAGS mode1;
GLsizei width;
GLsizei height;
WGpuTexture textureA;


WGpuBindGroupLayout bindGroupLayout;
WGpuBindGroupLayout bindGroupLayoutB;
WGpuComputePipeline computePipeline;
WGpuBuffer inputBuffer;
WGpuBuffer outputBuffer;
WGpuBuffer mapBuffer;
WGpuBuffer uniBuffer;
WGpuShaderModule cs;
WGpuCommandBuffer commandBuffer;
WGpuCommandEncoder encoder;
WGpuComputePassEncoder computePass;
WGpuBindGroup bindGroup;
WGpuBindGroup bindGroupB;
WGpuPipelineLayout pipelineLayout;
WGpuQuerySet querySet;
WGpuComputePassDescriptor computePassDescriptor;
WGpuCommandBufferDescriptor commandBufferDescriptor;
WGpuCommandEncoderDescriptor commandEncoderDescriptor;
WGpuDeviceDescriptor deviceDescriptor;
WGpuBufferBindingLayout bufferBindingLayout1;
WGpuBufferBindingLayout bufferBindingLayout2;
WGpuBufferBindingLayout bufferBindingLayout3;
WGpuBufferBindingLayout bufferBindingLayout4;
WGpuStorageTextureBindingLayout storageTextureBindingLayout1;
WGpuRequestAdapterOptions options;
WGpuBufferDescriptor bufferDescriptorI;
WGpuBufferDescriptor bufferDescriptorO;
WGpuBufferDescriptor bufferDescriptorM;
WGpuBufferDescriptor bufferDescriptorC;
WGpuTextureDescriptor textureDescriptor;
WGpuTextureViewDescriptor textureViewDescriptor;
WGpuShaderModuleDescriptor shaderModuleDescriptor;
shaderModuleDescriptor;
int randomNumber,entropySeed,raN,raND;
uint32_t * WGPU_Result_Array;
uint32_t * WGPU_Input_Array;
uint32_t * WGPU_Color_Input_Array;
WGpuImageCopyTexture WGPU_Input_Image;
WGpuImageCopyTexture WGPU_Output_Image;
WGpuImageCopyBuffer WGPU_Input_Buffer;
WGpuImageCopyBuffer WGPU_Output_Buffer;
WGpuImageCopyBuffer WGPU_Mapped_Buffer;

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

using namespace std;
