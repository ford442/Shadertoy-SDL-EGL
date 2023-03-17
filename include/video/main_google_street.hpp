#pragma once
#include <cstdlib>
#include <ctime>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../include/video/intrins.hpp"

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON

int rNd(int);

extern"C"{

int r4nd(int);

}
