#pragma once
#include <cstdlib>
#include <ctime>
#include <random>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../include/shader/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON

v128_t rNd(int);

int rD,Th,Rg,c;
v128_t Dr;

extern"C"{

int r4nd(int);

}
