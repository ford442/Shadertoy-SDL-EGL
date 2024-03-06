#include <emscripten.h>
#include "../../include/shader/intrins.hpp"
#include "../../onnxruntime/include/onnxruntime/core/session/onnxruntime_cxx_api.h"

template <typename T>
T vectorProduct(const std::vector<T>& v){
return accumulate(v.begin(),v.end(),1,std::multiplies<T>());
}

using namespace std;

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

// SDL_AudioStatus status;

class Audio{

private:

GLchar flnm[24];
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

static void SDLCALL bfr(void * unused,GLubyte * stm,GLint len){
// ::boost::tuples::tie(stm,len);
// status=SDL_GetAudioDeviceStatus(dv.at(0,0));
wave.wptr=sound.at(0,1,0)+sound_pos.at(0,0);
snd_lft(sound_pos_u.at(0,0)-sound_pos.at(0,0));
while(sound_lft.at(0,0)<=len){
SDL_UnlockAudioDevice(wave.dev);
SDL_memcpy(stm,wave.wptr,sound_lft.at(0,0));
stm+=sound_lft.at(0,0);
len-=sound_lft.at(0,0);
wave.wptr=sound.at(0,1,0);
snd_lft(sound_pos_u.at(0,0));
snd_pos(0);
SDL_LockAudioDevice(dv.at(0,0));
}
SDL_memcpy(stm,wave.wptr,len);
snd_pos(sound_pos.at(0,0)+len);
//  if(status==SDL_AUDIO_STOPPED){
// SDL_PauseAudioDevice(wave.dev,SDL_TRUE);
// EM_ASM({
// document.getElementById('musicBtn').click();
// });
// }
return;
}

const static inline boost::function<const EM_BOOL()>ort=[](){
std::vector<int64_t>inputDims;
Ort::AllocatorWithDefaultOptions allocator;
std::cout << "got ORT allocator" << std::endl;
if (inputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting input batch size to " << 1 << "." << std::endl;
inputDims.at(0)=1;
inputDims.at(1)=3;
inputDims.at(2)=96;
}
size_t inputTensorSize=vectorProduct(inputDims);
std::cout << "setting inputTensorSize:" << inputTensorSize << std::endl;
std::vector<float> inputTensorValues(inputTensorSize);
std::cout << "setting inputTensorValues " <<  std::endl;
std::vector<float>floats={7.0f,7.0f,1.0f,1.0f,10.0f};

for (int64_t i = 0; i < 1; ++i)
{
std::copy(floats.begin(),floats.end(),inputTensorValues.begin()+i*inputTensorSize);
}
std::string text_prompt="two birds";
std::vector<float>text_prompt_vector;
for(char c : text_prompt){
text_prompt_vector.push_back(c);
}
Ort::MemoryInfo memoryInfo=Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator,OrtMemTypeCPU);
std::cout << "Establishing memoryInfo" << std::endl;
std::vector<Ort::Value>inputTensors;
inputTensors.push_back(Ort::Value::CreateTensor<float>(memoryInfo,inputTensorValues.data(),inputTensorSize,&inputDims.at(0),4));
std::cout << "Establishing Tensor" << std::endl;
return EM_TRUE;
};

const boost::function<EM_BOOL()>plt=[this](){
::boost::tuples::tie(sound,sound_pos,sound_pos_u);
::boost::tuples::tie(wave,sse,sse2);
::boost::tuples::tie(bfr,request);
request.freq=44100;
request.format=AUDIO_S32;
request.channels=2;
request.samples=128;
SDL_memset(&request,0,sizeof(request));
snd_pos(0);
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_RWops *rw=SDL_RWFromFile(flnm,"rb");
SDL_Init(SDL_INIT_AUDIO);
SDL_LoadWAV_RW(rw,1,&request,&wave.snd,&wave.slen);
sound.at(0,1,0)=wave.snd;
snd_pos_u(wave.slen);
request.callback=bfr;
const char * devName=SDL_GetAudioDeviceName(0,SDL_FALSE);
wave.dev=SDL_OpenAudioDevice(devName,SDL_FALSE,&request,NULL,0);
dv.at(0,0)=wave.dev;
SDL_PauseAudioDevice(dv.at(0,0),SDL_FALSE);
return EM_TRUE;
};

};
