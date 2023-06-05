#pragma once

#include "../../include/combine/defs.h"
#include "../../include/combine/intrins.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <emscripten.h>

std::random_device rd;

int rD=0;
v128_t rNd(int);
v128_t Dr;

extern"C"{

int c=0;
v128_t Rg;
int r4nd(int);

}
