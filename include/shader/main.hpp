int rD,Th;

#pragma once

#include "../../include/shader/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE OFF
#pragma STDC FP_CONTRACT ON
#undef FLT_ROUNDS
#define FLT_ROUNDS 1
#define POSIX_TIMERS 1
#define XOPEN_REALTIME 1
#define POSIX_ASYNC_IO 1
#define POSIX_PRIO_IO 1
#define POSIX_SYNC_IO 1

v128_t rNd(int);

v128_t Dr;

#include <random>

std::random_device rd;

extern"C"{

int c;
v128_t Rg;
int r4nd(int);

}

#include <emscripten.h>
#include <cstdlib>
