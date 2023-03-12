#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 2
#pragma STDC CX_LIMITED_RANGE ON

#include <wasm_simd128.h>
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>
#include <unistd.h>

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cfloat>
#include <climits>

#include <unistd.h>

#include <emscripten.h>
#include <emscripten/html5.h>

void avgFrm(short int,int,float *,float *);

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;

extern "C"{
  
void b3();

void nano(short int,int,float *,float *);

}
