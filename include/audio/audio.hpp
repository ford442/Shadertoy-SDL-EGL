  
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

static inline struct{
GLubyte * snd;
GLint pos;
GLuint slen;
SDL_AudioSpec request;
}wave;

// static inline void SDLCALL bfr(void *,GLubyte *,GLint);

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

class Audio{

public:

static inline void SDLCALL bfr(void * unused,GLubyte * stm,GLint len){
GLubyte * wptr;
GLint lft;
tie(len,lft);
tie(stm,wptr);
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while(lft<=len){
SDL_UnlockAudioDevice(dev);
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
SDL_LockAudioDevice(dev);
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
}

static inline void plt(){
tie(wave,bfr);
tie(wave.snd,dev);
tie(wave.pos,wave.slen,wave.request);
SDL_memset(&wave.request,0,sizeof(wave.request));
wave.request.freq=44100;
wave.request.format=AUDIO_S32;
wave.request.channels=2;
wave.request.samples=1024;
wave.pos=0;
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
SDL_LoadWAV(flnm,&wave.request,&wave.snd,&wave.slen);
wave.request.callback=bfr;
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.request,NULL,0);
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
}
  
};
