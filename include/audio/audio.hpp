  
static inline void plt();

extern "C"{  
  
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

#include "boost/tuple/tuple.hpp"

using namespace ::boost::tuples;

#include <cstdint>
#include <SDL2/SDL.h>
#include <GL/gl.h>

GLchar flnm[24];

SDL_AudioDeviceID dev;

struct{
GLubyte * snd;
GLint pos;
GLuint slen;
SDL_AudioSpec request;
}wave;

static inline void SDLCALL bfr(void *,GLubyte *,GLint);

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <climits>
#include <iostream>
#include <emscripten.h>
