#pragma once
#include <cstdlib>
#include <ctime>
#include <random>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../include/video/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

v128_t rNd(int);

extern"C"{

int c;
int r4nd(int);

}
