#pragma once
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../include/combine/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON

v128_t rNd(int);

extern"C"{

int c;
int r4nd(int);

}
