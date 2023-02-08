
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cfloat>
#include <climits>

#include <unistd.h>

#include <emscripten.h>
#include <emscripten/html5.h>

void avgFrm(int Fnum,int leng,float *ptr,float *aptr);

extern "C"{

void b3();
void nano(int Fnum,int leng,float *ptr,float *aptr);

}
