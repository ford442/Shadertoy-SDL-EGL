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
