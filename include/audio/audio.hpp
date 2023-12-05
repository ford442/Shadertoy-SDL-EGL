#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include "/content/RAMDRIVE2/emsdk/upstream/emscripten/cache/ports/sdl2_mixer/SDL_mixer-release-2.0.4/SDL_mixer.h"

#include "/usr/include/aubio/aubio.h"

#include <emscripten.h>
#include "../../include/shader/intrins.hpp"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
  
extern "C"{  
  
EM_BOOL pl();
  
}

#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD_OPTIMIZED 
// #pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT OFF

// #undef _FLT_ROUNDS
// #define _FLT_ROUNDS 1

#include <float.h>
#include <math.h>
#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#define register

#define BOOST_UBLAS_USE_LONG_DOUBLE 1
// #define BOOST_NO_EXCEPTIONS
#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS 1
#define BOOST_UBLAS_TYPE_CHECK 0

#include <cstdint>
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

#include <boost/preprocessor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/atomic.hpp>
#include <boost/tuple/tuple.hpp>
// #include <boost/integer.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using void_tensor=boost::numeric::ublas::tensor<boost::atomic<void *>>;
using gi_tensor=boost::numeric::ublas::tensor<boost::atomic<int>>;
using ub_tensor=boost::numeric::ublas::tensor<Mix_Music *>;
using wptr_tensor=boost::numeric::ublas::tensor<boost::atomic<unsigned char *>>;
using lu_tensor=boost::numeric::ublas::tensor<boost::atomic<unsigned long>>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;

ub_tensor sound=ub_tensor{1,1,1};
wptr_tensor soundp=wptr_tensor{1,1,1};
gi_tensor sound_pos=gi_tensor{1,1};
gi_tensor sound_lft=gi_tensor{1,1};
lu_tensor sound_pos_u=lu_tensor{1,1};
v_tensor sse=v_tensor{1,2};
v_tensor sse2=v_tensor{1,1};
v_tensor sse3=v_tensor{1,1};

struct{
register Mix_Music * snd;
register long pos=0;
SDL_AudioDeviceID dev;
register GLuint slen=0;
register GLubyte * wptr;
}wave;

class Audio{

private:

GLchar flnm[24];
SDL_AudioSpec request;

public:

// static EM_BOOL snd_pos(boost::atomic<short int> set){
const static EM_BOOL snd_pos(GLint set){
sse3.at(0,0)=wasm_i64x2_splat(set);
sound_pos.at(0,0)=wasm_i64x2_extract_lane(sse3.at(0,0),0);
return EM_TRUE;
}

const static EM_BOOL snd_lft(long long set){
sse.at(0,1)=wasm_i64x2_splat(set);
sound_lft.at(0,0)=wasm_i64x2_extract_lane(sse.at(0,1),0);
return EM_TRUE;
}

const static EM_BOOL snd_pos_u(unsigned long long set){
sse2.at(0,0)=wasm_u64x2_splat(set);
sound_pos_u.at(0,0)=wasm_u64x2_extract_lane(sse2.at(0,0),0);
return EM_TRUE;
}
/*
static void SDLCALL bfr(void * unused,GLubyte * stm,GLint len){
::boost::tuples::tie(stm,len);
wave.wptr=soundp.at(0,1,0)+sound_pos.at(0,0);
snd_lft(sound_pos_u.at(0,0)-sound_pos.at(0,0));
while(sound_lft.at(0,0)<=len){
SDL_UnlockAudioDevice(wave.dev);
SDL_memcpy(stm,wave.wptr,sound_lft.at(0,0));
stm+=sound_lft.at(0,0);
len-=sound_lft.at(0,0);
wave.wptr=soundp.at(0,1,0);
snd_lft(sound_pos_u.at(0,0));
snd_pos(0);
SDL_LockAudioDevice(wave.dev);
}
SDL_memcpy(stm,wave.wptr,len);
snd_pos(sound_pos.at(0,0)+len);
return;
}
*/
boost::function<EM_BOOL()>plc=[this](){
::boost::tuples::tie(sound,sound_pos,sound_pos_u);
::boost::tuples::tie(wave,sse,sse2);
// ::boost::tuples::tie(bfr,request);
request.freq=44100;
request.format=AUDIO_S32;
// request.format=MIX_DEFAULT_FORMAT;
request.channels=2;
request.samples=4096;
SDL_memset(&request,0,sizeof(request));
snd_pos(0);
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
// SDL_LoadWAV(flnm,&request,&wave.snd,&wave.slen);
Mix_Music * music=NULL;
music=Mix_LoadMUS(flnm);
// soundp.at(0,1,0)=Mix_LoadMUS(flnm);
snd_pos_u(wave.slen);
request.callback=nullptr;
// wave.dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&request,NULL,0);
// if(Mix_PlayingMusic()==0){
Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
wave.dev=Mix_OpenAudio(44100,AUDIO_S32,2,4096);
//Play the music
Mix_PlayMusic(music,1);
// }
SDL_PauseAudioDevice(wave.dev,SDL_FALSE);
return EM_TRUE;
};

boost::function<void()>plt=[this](){emscripten_set_main_loop((void(*)())plc(),0,0);

};

};
