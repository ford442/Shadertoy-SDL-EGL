#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.h"
#include "../../include/vanilla/defs.h"
#include "../../include/vanilla/gl.h"
#include "../../include/vanilla/boost_defs.h"
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
#include <emscripten/html5_webgpu.h>

#include "../../lib/lib_webgpu.h"

#include "oneapi/tbb/tick_count.h"
#include "oneapi/tbb/task_group.h"
#include "oneapi/tbb/global_control.h"

template<class ArgumentType,class ResultType>
struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};
#include <boost/compute/core.hpp>

inline int rNd4(int randomMax);
static void WGPU_Run();
static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData);
static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData);

static void WGPU_Start();

#include <iostream>

// #include <boost/compute.hpp>
#include <boost/compute/algorithm.hpp>

// namespace compute = boost::compute;

int cltest();

extern"C"{

void startWebGPU();

void runWebGPU();

}

