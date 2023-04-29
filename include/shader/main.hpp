#include <emscripten.h>

#pragma once

// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
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

#include "../../include/shader/intrins.hpp"
#include "boost/tuple/tuple.hpp"
#include <random>

using namespace ::boost::tuples;

class js
{

private:


std::random_device rd;

public:

int rD;
int Th;
v128_t Dr;

v128_t rNd(int Th){
std::srand(rd());
rD=std::rand()%Th;
Dr=wasm_i32x4_splat(rD);
return Dr;
}

};

void(*jss)(){&js_main};

extern"C"{

int c;
v128_t Rg;
int r4nd(int);

}

#include <cstdlib>
