extern "C"{  
  
void pl();
  
}

// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
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

inline struct{
GLubyte * snd;
GLint pos;
SDL_AudioDeviceID dev;
GLuint slen;
GLubyte * wptr;
GLint lft;
}wave;

class Audio{

private:

GLchar flnm[24];
SDL_AudioSpec request;

public:

static inline void SDLCALL bfr(void * unused,GLubyte * stm,GLint len){
tie(len,wave.lft);
tie(stm,wave.wptr);
wave.wptr=wave.snd+wave.pos;
wave.lft=wave.slen-wave.pos;
while(wave.lft<=len){
SDL_UnlockAudioDevice(wave.dev);
SDL_memcpy(stm,wave.wptr,wave.lft);
stm+=wave.lft;
len-=wave.lft;
wave.wptr=wave.snd;
wave.lft=wave.slen;
wave.pos=0;
SDL_LockAudioDevice(wave.dev);
}
SDL_memcpy(stm,wave.wptr,len);
wave.pos+=len;
return;
}

inline void plt(){
tie(wave.pos,wave.slen);
tie(request,wave.dev);
tie(wave.snd,bfr);
SDL_memset(&request,0,sizeof(request));
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=1024;
wave.pos=0;
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
SDL_LoadWAV(flnm,&request,&wave.snd,&wave.slen);
request.callback=bfr;
wave.dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&request,NULL,0);
SDL_PauseAudioDevice(wave.dev,SDL_FALSE);
return;
}
  
};
