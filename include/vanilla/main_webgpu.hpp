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
    
// namespace compute = boost::compute;

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
// int cltest();

extern"C"{

void startWebGPU();
void runWebGPU();

}
