#pragma once
#include <cstdlib>
#include <ctime>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../../include/shader/intrins.hpp"

v128_t rNd(int);

int rD,Th,Rg;
v128_t Dr;

extern"C"{

int r4nd(int);

}
