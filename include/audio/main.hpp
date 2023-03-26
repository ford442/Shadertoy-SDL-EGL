#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <avxintrin.h>  // AVX
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2

#define POSIX_TIMERS 1
#define XOPEN_REALTIME 1
#include <unistd.h>

extern "C"{
  
v128_t Rg;
int c;

int r4nd(int);

}

v128_t rNd(int);

int Th,rD;
v128_t Dr;

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

#include <cstdlib>
#include <ctime>
#include <random>

std::random_device rd;

#include <emscripten.h>
#include <emscripten/html5.h>
