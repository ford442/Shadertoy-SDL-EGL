#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/boost_defs.hpp"
#include "../../lib/lib_webgpu_cpp20.cpp"

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

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/function.hpp>

inline int rNd4(int randomMax);
// static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData);
static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData);

// static void WGPU_Start();

// int cltest();

extern"C"{

void startWebGPU();

}

using f_tensor=boost::numeric::ublas::tensor<float>;
using wce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wrpe_tensor=boost::numeric::ublas::tensor<WGpuRenderPassEncoder>;
using wcb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wcc_tensor=boost::numeric::ublas::tensor<WGpuCanvasContext>;
using wrp_tensor=boost::numeric::ublas::tensor<WGpuRenderPipeline>;
using wbg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using wbgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using wbgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry>;
using wbge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry>;
using wrpd_tensor=boost::numeric::ublas::tensor<WGpuRenderPassDescriptor>;
using wrpca_tensor=boost::numeric::ublas::tensor<WGpuRenderPassColorAttachment>;


