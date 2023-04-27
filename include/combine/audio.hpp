void plt();

extern"C"{  
  
void pl();
  
}

#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
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

char flnm[24];

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
#include <SDL2/SDL.h>

SDL_AudioDeviceID dev;

struct{
Uint8 * snd;
int_fast32_t pos;
Uint32 slen;
SDL_AudioSpec request;
}wave;

void SDLCALL bfr(void *,Uint8 *,int_fast32_t);

#include "../../include/combine/intrins.hpp"
