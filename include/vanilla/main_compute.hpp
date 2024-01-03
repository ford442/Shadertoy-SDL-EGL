#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
// #include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/boost_defs.hpp"
#include "../../lib/lib_webgpu_cpp20.cpp"

#include <aubio/aubio.h>

#define __EMCSCRIPTEN__ 1

#include <cstdint>

#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <boost/compute/core.hpp>

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
#include <emscripten.h>
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

#include <functional>

template<class ArgumentType,class ResultType>

#include <boost/function.hpp>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/function.hpp>

inline int rNd4(int);
// static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice,void *);
static void ObtainedWebGpuAdapterStart(WGpuAdapter,void *);

// static void WGPU_Start();

// int cltest();

extern"C"{

void startWebGPU();
void runWebGPU();

}

using namespace std;
using namespace boost::chrono;
using uiptr_tensor=boost::numeric::ublas::tensor<uint32_t *>;
using wced_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoderDescriptor>;

using wbmc_tensor=boost::numeric::ublas::tensor<WGpuBufferMapCallback>;
using wcpe_tensor=boost::numeric::ublas::tensor<WGpuComputePassEncoder>;
using wcp_tensor=boost::numeric::ublas::tensor<WGpuComputePipeline>;
using i53_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using wstbl_tensor=boost::numeric::ublas::tensor<WGpuStorageTextureBindingLayout>;
using wbms_tensor=boost::numeric::ublas::tensor<WGPU_BUFFER_MAP_STATE>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using void_tensor=boost::numeric::ublas::tensor<void *>;
using wdc_tensor=boost::numeric::ublas::tensor<WGpuOnSubmittedWorkDoneCallback>;

using mouse_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using c_tensor=boost::numeric::ublas::tensor<const char *>;
using f_tensor=boost::numeric::ublas::tensor<float>;
using wce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wrpe_tensor=boost::numeric::ublas::tensor<WGpuRenderPassEncoder>;
using wcb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wcc_tensor=boost::numeric::ublas::tensor<WGpuCanvasContext>;
using wccf_tensor=boost::numeric::ublas::tensor<WGpuCanvasConfiguration>;
using wrp_tensor=boost::numeric::ublas::tensor<WGpuRenderPipeline>;
using wrpid_tensor=boost::numeric::ublas::tensor<WGpuRenderPipelineDescriptor>;
using wpl_tensor=boost::numeric::ublas::tensor<WGpuPipelineLayout>;
using wbg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using wbgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using wbgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry *>;
using wbge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry *>;
using wrpd_tensor=boost::numeric::ublas::tensor<WGpuRenderPassDescriptor>;
using wcpd_tensor=boost::numeric::ublas::tensor<WGpuComputePassDescriptor>;
using wrpca_tensor=boost::numeric::ublas::tensor<WGpuRenderPassColorAttachment>;
using wbbl_tensor=boost::numeric::ublas::tensor<WGpuBufferBindingLayout>;
using wtbl_tensor=boost::numeric::ublas::tensor<WGpuTextureBindingLayout>;
using wsbl_tensor=boost::numeric::ublas::tensor<WGpuSamplerBindingLayout>;
using wbd_tensor=boost::numeric::ublas::tensor<WGpuBufferDescriptor>;
using wao_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterOptions>;
using wdd_tensor=boost::numeric::ublas::tensor<WGpuDeviceDescriptor>;
using wrbe_tensor=boost::numeric::ublas::tensor<WGpuRenderBundleEncoder>;
using wrbed_tensor=boost::numeric::ublas::tensor<WGpuRenderBundleEncoderDescriptor>;
using wrpdsa_tensor=boost::numeric::ublas::tensor<WGpuRenderPassDepthStencilAttachment>;
using u64_tensor=boost::numeric::ublas::tensor<uint32_t>;
using i_tensor=boost::numeric::ublas::tensor<int>;
// using i_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using wt_tensor=boost::numeric::ublas::tensor<WGpuTexture>;
using wtd_tensor=boost::numeric::ublas::tensor<WGpuTextureDescriptor>;
using wtvd_tensor=boost::numeric::ublas::tensor<WGpuTextureViewDescriptor>;
using wtf_tensor=boost::numeric::ublas::tensor<WGPU_TEXTURE_FORMAT>;
using wtv_tensor=boost::numeric::ublas::tensor<WGpuTextureView>;
using js_tensor=boost::numeric::ublas::tensor<uint8_t *>;
using wicb_tensor=boost::numeric::ublas::tensor<WGPUImageCopyBuffer>;
using wicei_tensor=boost::numeric::ublas::tensor<WGpuImageCopyExternalImage>;
using wict_tensor=boost::numeric::ublas::tensor<WGpuImageCopyTexture>;
using ws_tensor=boost::numeric::ublas::tensor<WGpuSampler>;
using wsd_tensor=boost::numeric::ublas::tensor<WGpuSamplerDescriptor>;
using wms_tensor=boost::numeric::ublas::tensor<WGpuMultisampleState>;
using wsm_tensor=boost::numeric::ublas::tensor<WGpuShaderModule>;
using wsmd_tensor=boost::numeric::ublas::tensor<WGpuShaderModuleDescriptor>;
using wcts_tensor=boost::numeric::ublas::tensor<WGpuColorTargetState>;
using wdss_tensor=boost::numeric::ublas::tensor<WGpuDepthStencilState>;
using wvs_tensor=boost::numeric::ublas::tensor<WGpuVertexState>;
using wps_tensor=boost::numeric::ublas::tensor<WGpuPrimitiveState>;
using wfs_tensor=boost::numeric::ublas::tensor<WGpuFragmentState>;
using wcts_tensor=boost::numeric::ublas::tensor<WGpuColorTargetState>;
