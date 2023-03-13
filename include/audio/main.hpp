#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#pragma STDC CX_LIMITED_RANGE ON
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <avxintrin.h>  // AVX

#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <emscripten.h>
#include <emscripten/html5.h>

v128_t rNd(int);

int Th;
v128_t Dr,rD;

extern"C"{

int r4nd(int);

}
