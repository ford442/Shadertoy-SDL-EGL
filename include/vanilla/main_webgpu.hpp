// #include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/boost_defs.hpp"

#define __EMCSCRIPTEN__ 1

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
#include <cstdint>
#include <ctime>
#include <vector>
// #include <memory>


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

// #include "../../include/vanilla/openvino/runtime/runtime.hpp"
// #include "../../include/vanilla/openvino/runtime/remote_context.hpp"

// #include <boost/throw_exception.hpp>
    
// namespace compute = boost::compute;

// #include "../../include/vanilla/openvino/openvino.hpp"

// #include "/usr/include/openvino/openvino.hpp"
// #include "/usr/include/openvino/core/core.hpp"
// #include "openvino/c/openvino.h"

// #include "openvino/runtime/tensor.hpp"

#include "../../onnxruntime/include/onnxruntime/core/session/onnxruntime_cxx_api.h"

// #include "oneapi/tbb/tick_count.h"
// #include "oneapi/tbb/task_arena.h"
// #include "oneapi/tbb/task_group.h"

// #include "oneapi/tbb/global_control.h"
// #include "/content/RAMDRIVE2/level-zero/include/ze_api.h"
// #include "/content/RAMDRIVE2/level-zero/include/zet_api.h"
// #include "/content/RAMDRIVE2/level-zero/include/loader/ze_loader.h"

#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

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

// int cltest();

extern"C"{

void startWebGPU();

void runWebGPU();

}

using f_tensor=boost::numeric::ublas::tensor<float>;
static f_tensor sze=f_tensor{2,2};
double szh, szw;


