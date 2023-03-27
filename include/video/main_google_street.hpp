#pragma once

#include <emscripten.h>
#include <random>

#include "../../include/video/intrins.hpp"

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

int rNd(int);

extern"C"{

int r4nd(int);

}

#include <cstdlib>
#include <ctime>
// #include <emscripten/html5.h>
