
#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <avxintrin.h>  // AVX
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2

#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1

#include <unistd.h>

#include "boost/tuple/tuple.hpp"

using namespace ::boost::tuples;

extern "C"{
  
v128_t Rg;
int c;

int r4nd(int);

}

v128_t Dr;

#include <GL/gl.h>

static inline v128_t rNd(GLint);

GLint Th,rD;

#include <cstdlib>
#include <ctime>
#include <random>

std::random_device rd;

#include <emscripten.h>
#include <emscripten/html5.h>
