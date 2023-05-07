extern "C"{  
  
void pl();
  
}

// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT OFF
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1


#include <float.h>
#include <math.h>

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1

#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/atomic.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <boost/cstdint.hpp>

using namespace ::boost::tuples;
using namespace boost::numeric::ublas;

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

using void_tensor=tensor<boost::atomic<void *>>;
using i_tensor=tensor<boost::atomic<int32_t *>>;
using ub_tensor=tensor<boost::atomic<unsigned char **>>;
using lu_tensor=tensor<boost::atomic<long unsigned int *>>;
using li_tensor=tensor<boost::atomic<long int *>>;
using f_tensor=tensor<boost::atomic<float *>>;
using d_tensor=tensor<boost::atomic<double *>>;
using void_tensor=tensor<boost::atomic<void *>>;
using v_tensor=tensor<v128_t>;

ub_tensor sound=ub_tensor{1,1};

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
wave.wptr=*(sound.at(0,0)+wave.pos);
wave.lft=wave.slen-wave.pos;
while(wave.lft<=len){
SDL_UnlockAudioDevice(wave.dev);
SDL_memcpy(stm,wave.wptr,wave.lft);
stm+=wave.lft;
len-=wave.lft;
wave.wptr=sound.at(0,0);
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
tie(wave.snd,bfr,sound);
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=1024;
SDL_memset(&request,0,sizeof(request));
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=1024;
wave.pos=0;
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
sound.at(0,0)=wave.snd;
SDL_LoadWAV(flnm,&request,&sound.at(0,0),&wave.slen);
request.callback=bfr;
wave.dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&request,NULL,0);
SDL_PauseAudioDevice(wave.dev,SDL_FALSE);
return;
}
  
};
