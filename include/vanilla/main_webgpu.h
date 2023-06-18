#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.h"
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
#include <random>
#include <cfloat>
#include <math.h>
#include <new>

#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../lib/lib_webgpu.h"

inline EM_BOOL ms_l,clk_l;
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
static cb_tensor WGPU_CommandBuffer=cb_tensor{1,1,2};
static wb_tensor WGPU_Buffers=wb_tensor{2,2,2};
static ce_tensor WGPU_CommandEncoder=ce_tensor{1,1,2};
static cpe_tensor WGPU_ComputePassCommandEncoder=cpe_tensor{1,1,2};
static cp_tensor WGPU_ComputePipeline=cp_tensor{1,1,1};
static pl_tensor WGPU_ComputePipelineLayout=pl_tensor{1,1,1};
static cm_tensor WGPU_ComputeModule=cm_tensor{1,1,1};
static bg_tensor WGPU_BindGroup=bg_tensor{1,1,1};
static bgl_tensor WGPU_BindGroupLayout=bgl_tensor{1,1,1};
static bgle_tensor WGPU_BindGroupLayoutEntries=bgle_tensor{1,1,1};
static bge_tensor WGPU_BindGroupEntries=bge_tensor{1,1,1};
static bmc_tensor WGPU_MapCallback=bmc_tensor{1,1,2};
static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,2};
static oac_tensor WGPU_ObtainedAdapterCallback=oac_tensor{1,1,2};
static odc_tensor WGPU_ObtainedDeviceCallback=odc_tensor{1,1,2};
static bbl_tensor WGPU_BufferBindingLayout=bbl_tensor{1,1,3};
static bd_tensor WGPU_BufferDescriptor=bd_tensor{1,1,3};
static md_tensor WGPU_ShaderModuleDescriptor=md_tensor{1,1,3};
static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
static void_tensor WGPU_UserData=void_tensor{1,1,1};
static rao_tensor WGPU_RequestAdapterOptions=rao_tensor{1,1,1};
static dd_tensor WGPU_DeviceDescriptor=dd_tensor{1,1,1};
static iptr_tensor WGPU_ResultBuffer=iptr_tensor{1,1,1};

/*
inline int rNd4(int randomMax);
static void raf(WGpuDevice device);
static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData);
static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData);

void WGPU_Start();

extern"C"{

void startWebGPU();

void runWebGPU();

}
*/
