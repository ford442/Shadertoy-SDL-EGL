#pragma once

#include <emscripten.h>

int Th,rD;

#include <random>
std::random_device rd;

#pragma STDC FP_CONTRACT ON
#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
// #pragma STDC CX_LIMITED_RANGE OFF
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1

// #include "../../include/video/intrins.hpp"

int32_t rNd(int);

// v128_t Dr;

extern "C"{
  
// v128_t Rg;
int c;
int r4nd(int);

}

#include <cstdlib>
#include <ctime>
#include <cfloat>

// #include <emscripten/html5.h>
