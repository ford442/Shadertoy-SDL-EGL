#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/defs.h"
#include "../../include/vanilla/boost_defs.h"

#include "../../include/shader/gl.h"
#include "../../include/shader/egl.h"

#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>

#include <random>
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

class webgpu{

public:

std::random_device randomizer;

char wgl_cmp_src[2000];

char * cmp_bdy;

unsigned char * ColorA;

uint32_t workgroupSize;
// double_int53_t DbufferSize;
uint32_t DbufferSize;
uint32_t bufferSize;
// double_int53_t DiBufferSize;
uint32_t DiBufferSize;
uint32_t iBufferSize;
const char * Entry;
uint32_t invocationCount;
uint32_t workgroupCount;
WGPU_MAP_MODE_FLAGS mode1;
void * userDataA;
GLsizei width;
GLsizei height;
GLuint wtexture[4];
WGpuAdapter adapter;
WGpuDevice device;
WGpuQueue queue;
WGpuBindGroupLayout bindGroupLayout;
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
WGpuPipelineLayout pipelineLayout;
WGpuQuerySet querySet;
WGpuComputePassDescriptor computePassDescriptor;
WGpuCommandBufferDescriptor commandBufferDescriptor;
WGpuCommandEncoderDescriptor commandEncoderDescriptor;
WGpuDeviceDescriptor deviceDescriptor;
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[2];
WGpuBindGroupEntry bindGroupEntry[2];
WGpuBufferBindingLayout bufferBindingLayout1;
WGpuBufferBindingLayout bufferBindingLayout2;
WGpuBufferBindingLayout bufferBindingLayout3;
WGpuBufferDescriptor bufferDescriptorI;
WGpuBufferDescriptor bufferDescriptorO;
WGpuBufferDescriptor bufferDescriptorM;
WGpuRequestAdapterOptions options;
WGpuShaderModuleDescriptor shaderModuleDescriptor;
int randomNumber,entropySeed;
int raN;
int raND;

uint32_t * WGPU_Result_Buffer;

inline int rNd4(int randomMax);
static void raf(WGpuDevice device);
static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData);
static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData);
void WGPU_Start();

private:

using mouse_tensor=boost::numeric::ublas::tensor<boost::atomic<float>>;
using shad_tensor=boost::numeric::ublas::tensor<unsigned int>;
using prg_tensor=boost::numeric::ublas::tensor<unsigned int>;
using sz_tensor=boost::numeric::ublas::tensor<int>;
using f_tensor=boost::numeric::ublas::tensor<boost::atomic<float>>;
using d_tensor=boost::numeric::ublas::tensor<double>;
using di_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using i_tensor=boost::numeric::ublas::tensor<int>;
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

static shad_tensor Sh;
static prg_tensor S1;
static sz_tensor Si;
static d_tensor d_time;
static f_tensor Fi;
static d_tensor Di;
static gi_tensor uni_i;
static i_tensor i_view;
static i_tensor i_date;
static f_tensor t_size;
static li_tensor i_size;
static void_tensor cntx;
static i_tensor cntxi;
static mouse_tensor mms;
static li_tensor mms2;
static void_tensor bin;
static wa_tensor WGPU_Adapter;
static wd_tensor WGPU_Device;
static wq_tensor WGPU_Queue;
static cb_tensor WGPU_CommandBuffer;
static wb_tensor WGPU_Buffers;
static ce_tensor WGPU_CommandEncoder;
static cpe_tensor WGPU_ComputePassCommandEncoder;
static cp_tensor WGPU_ComputePipeline;
static pl_tensor WGPU_ComputePipelineLayout;
static cm_tensor WGPU_ComputeModule;
static bg_tensor WGPU_BindGroup;
static bgl_tensor WGPU_BindGroupLayout;
static bgle_tensor WGPU_BindGroupLayoutEntries;
static bge_tensor WGPU_BindGroupEntries;
static bmc_tensor WGPU_MapCallback;
static wdc_tensor WGPU_ComputeDoneCallback;
static oac_tensor WGPU_ObtainedAdapterCallback;
static odc_tensor WGPU_ObtainedDeviceCallback;
static bbl_tensor WGPU_BufferBindingLayout;
static bd_tensor WGPU_BufferDescriptor;
static md_tensor WGPU_ShaderModuleDescriptor;
static di_tensor WGPU_BufferMappedRange;
static uiptr_tensor WGPU_ResultBuffer;
static void_tensor WGPU_UserData;
static rao_tensor WGPU_RequestAdapterOptions;
static dd_tensor WGPU_DeviceDescriptor;

};

extern"C"{

void startWebGPU();

void runWebGPU();

}
