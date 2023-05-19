#include <emscripten.h>

#pragma once

#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD -1
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

#include "../../include/shader/intrins.h"
#include "boost/tuple/tuple.hpp"
#include <random>

using namespace ::boost::tuples;

class js
{

private:

std::random_device rd;

public:

int32_t rD;
int32_t Th;
v128_t Dr;

inline v128_t rNd(int32_t Th){
std::srand(rd());
rD=std::rand()%Th;
Dr=wasm_i32x4_splat(rD);
return Dr;
}

};

extern"C"{

int32_t c;
v128_t Rg;
int32_t r4nd(int32_t);

}

#include <cstdlib>
