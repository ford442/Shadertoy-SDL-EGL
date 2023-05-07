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
using gi_tensor=tensor<boost::atomic<int32_t>>;
using ub_tensor=tensor<boost::atomic<unsigned char *>>;
using lu_tensor=tensor<boost::atomic<long unsigned int *>>;
using li_tensor=tensor<boost::atomic<long int *>>;
using f_tensor=tensor<boost::atomic<float *>>;
using d_tensor=tensor<boost::atomic<double *>>;
using void_tensor=tensor<boost::atomic<void *>>;
using v_tensor=tensor<v128_t>;

ub_tensor sound=ub_tensor{1,2};
gi_tensor sound_pos=gi_tensor{2,2};

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
wave.wptr=(sound.at(0,0)+sound_pos.at(0,0));
sound_pos.at(0,1)=wave.slen-sound_pos.at(0,0);
while(sound_pos.at(0,1)<=len){
SDL_UnlockAudioDevice(wave.dev);
SDL_memcpy(stm,wave.wptr,sound_pos.at(0,1));
stm+=sound_pos.at(0,1);
len-=sound_pos.at(0,1);
wave.wptr=sound.at(0,0);
sound_pos.at(0,1)=wave.slen;
sound_pos.at(0,0)=0;
SDL_LockAudioDevice(wave.dev);
}
SDL_memcpy(stm,wave.wptr,len);
sound_pos.at(0,0)+=len;
return;
}


inline void plt(){
tie(len,wave.lft);
tie(stm,wave.wptr);
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
sound_pos.at(0,0)=0;
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
SDL_LoadWAV(flnm,&request,&wave.snd,&wave.slen);
sound.at(0,0)=wave.snd;
request.callback=bfr;
wave.dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&request,NULL,0);
SDL_PauseAudioDevice(wave.dev,SDL_FALSE);
return;
}
  
};
