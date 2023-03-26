
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1

#include "../../include/combine/intrins.hpp"
#include <SDL2/SDL.h>
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
#include <iostream>

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#pragma STDC FP_CONTRACT OFF
#pragma STDC CX_LIMITED_RANGE OFF
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

char flnm[24];
SDL_AudioDeviceID dev;
int r;

struct{
Uint8 * snd;
int_fast32_t pos;
Uint32 slen;
SDL_AudioSpec request;
}wave;

void SDLCALL bfr(void *,Uint8 *,int_fast32_t);
  
void plt();

extern"C"{  
  
void pl();
  
}
