char flnm[24];
  
void plt();

extern "C"{  
  
void pl();
  
}

#include <cstdint>
#include <SDL2/SDL.h>

SDL_AudioDeviceID dev;

struct{
Uint8 * snd;
int_fast32_t pos;
Uint32 slen;
SDL_AudioSpec request;
}wave;

void SDLCALL bfr(void *,Uint8 *,int_fast32_t);

#include <emscripten.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cfloat>
#include <climits>
#include <iostream>
