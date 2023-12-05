#include <emscripten.h>
#include "../../include/shader/intrins.hpp"
  
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
#include <boost/preprocessor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/atomic.hpp>
#include <boost/tuple/tuple.hpp>
// #include <boost/integer.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using dv_tensor=boost::numeric::ublas::tensor<SDL_AudioDeviceID>;
using void_tensor=boost::numeric::ublas::tensor<boost::atomic<void *>>;
using gi_tensor=boost::numeric::ublas::tensor<boost::atomic<long>>;
using ub_tensor=boost::numeric::ublas::tensor<boost::atomic<unsigned char *>>;
using lu_tensor=boost::numeric::ublas::tensor<boost::atomic<unsigned long>>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;

ub_tensor sound=ub_tensor{1,1,1};
gi_tensor sound_pos=gi_tensor{1,1};
gi_tensor sound_lft=gi_tensor{1,1};
lu_tensor sound_pos_u=lu_tensor{1,1};
v_tensor sse=v_tensor{1,2};
v_tensor sse2=v_tensor{1,1};
v_tensor sse3=v_tensor{1,1};
dv_tensor dv=dv_tensor{1,1};

struct{
register GLubyte * snd;
register long pos;
SDL_AudioDeviceID dev;
register GLuint slen;
register GLubyte * wptr;
}wave;

SDL_AudioStatus status;
int chunkSize=4096;
int remaining;
int queued;

class Audio{

private:

char flnm[24];
SDL_AudioSpec request;

public:

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

void plLoop(){
  // Retrieve audio data chunk
Uint8 *chunk=sound.at(0,1,0);
remaining=chunkSize;
  // Feed audio data to the device
while(remaining>0){
status=SDL_GetAudioDeviceStatus(dv.at(0,0));
if(status==SDL_AUDIO_STOPPED){
      // Playback has ended
      // Pause audio device
// SDL_PauseAudioDevice(dv.at(0,0),true);
      // Handle playback completion
      // ...
break;
}
queued=SDL_QueueAudio(dv.at(0,0),chunk,remaining);
if(queued<=0){
      // Audio device is full, wait for some space
SDL_Delay(10);
}else{
remaining-=queued;
chunk+=queued;
}
}
}

const boost::function<EM_BOOL()>plt=[this](){
::boost::tuples::tie(sound,sound_pos,sound_pos_u);
::boost::tuples::tie(wave,sse,sse2);
::boost::tuples::tie(request);
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=4096;
request.callback=nullptr;
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_RWops *rw=SDL_RWFromFile(flnm,"rb");
SDL_Init(SDL_INIT_AUDIO);
SDL_LoadWAV_RW(rw,1,&request,&wave.snd,&wave.slen);
const char * devName=SDL_GetAudioDeviceName(0,SDL_FALSE);
wave.dev=SDL_OpenAudioDevice(devName,SDL_FALSE,&request,NULL,0);
dv.at(0,0)=wave.dev;
SDL_PauseAudioDevice(dv.at(0,0),false);
emscripten_set_main_loop((void(*)())pLoop,0,0);
return EM_TRUE;
};

};
