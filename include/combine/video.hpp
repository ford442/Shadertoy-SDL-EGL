#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE OFF
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

void avgFrm(short int,int,float *,float *);

extern "C"{

void b3();
void nano(short int,int,float *,float *);

}

#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <emscripten.h>

#include "../../include/combine/intrins.hpp"
#include <cfloat>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cfloat>
#include <climits>
