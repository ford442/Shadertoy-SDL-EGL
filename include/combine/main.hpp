#pragma once

#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <random>
#include <emscripten.h>
// #include <emscripten/html5.h>

#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE OFF
#pragma STDC FP_CONTRACT OFF
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1

#include "../../include/combine/intrins.hpp"

v128_t rNd(int);
int rD;
v128_t Dr;
std::random_device rd;

extern"C"{

int c;
v128_t Rg;
int r4nd(int);

}
