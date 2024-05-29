#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/boost_defs.hpp"
#include "../../lib/lib_webgpu_cpp20.cpp"
#include <SDL2/SDL.h>

using namespace std;
#include <cstdio> // C++ style
#include <cstdarg> // C++ style

/*   aubio needs  < c++17
#include "/content/RAMDRIVE2/aubio/src/aubio.h"
#include "/content/RAMDRIVE2/aubio/src/utils/parameter.c"
#include "/content/RAMDRIVE2/aubio/src/types.h"
#include "/content/RAMDRIVE2/aubio/src/fvec.c"
#include "/content/RAMDRIVE2/aubio/src/lvec.c"
#include "/content/RAMDRIVE2/aubio/src/cvec.c"
#include "/content/RAMDRIVE2/aubio/src/mathutils.c"
#include "/content/RAMDRIVE2/aubio/src/tempo/tempo.c"
#include "/content/RAMDRIVE2/aubio/src/tempo/beattracking.c"
#include "/content/RAMDRIVE2/aubio/src/spectral/specdesc.c"
#include "/content/RAMDRIVE2/aubio/src/onset/peakpicker.c"
#include "/content/RAMDRIVE2/aubio/src/utils/log.c"
#include "/content/RAMDRIVE2/aubio/src/utils/hist.c"
#include "/content/RAMDRIVE2/aubio/src/utils/scale.c"
#include "/content/RAMDRIVE2/aubio/src/spectral/phasevoc.c"
#include "/content/RAMDRIVE2/aubio/src/spectral/fft.c"
#include "/content/RAMDRIVE2/aubio/src/spectral/statistics.c"
#include "/content/RAMDRIVE2/aubio/src/spectral/ooura_fft8g.c"
#include "/content/RAMDRIVE2/aubio/src/temporal/biquad.c"
#include "/content/RAMDRIVE2/aubio/src/temporal/filter.c"
*/

/*   //  other aubio
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchmcomb.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchyin.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchfcomb.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchschmitt.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchyinfft.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchyinfast.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitchspecacf.c"
#include "/content/RAMDRIVE2/aubio/src/pitch/pitch.c"
*/

#define __EMCSCRIPTEN__ 1

#include <cstdint>

#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <boost/compute/core.hpp>

#include <chrono>
#include <cmath>
#include <exception>
// #include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

#include <algorithm>
#include <stdarg.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <memory>

#include <cassert>
#include <random>
#include <cfloat>
#include <new>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#include <iostream>
#include "../../lib/lib_webgpu.h"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <cstdlib>

#include <functional>

template<class ArgumentType,class ResultType>

#include <boost/preprocessor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/atomic.hpp>
#include <boost/tuple/tuple.hpp>
// #include <boost/integer.hpp>
// #include <boost/bind/bind.hpp>
#include <boost/function.hpp>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

namespace boost::numeric::ublas {
    // Create a vector type specifically for vec4
    using vec4 = vector<float, boost::numeric::ublas::bounded_array<float, 4>>;
}

#define register

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_USE_LONG_DOUBLE
// #define BOOST_NO_EXCEPTIONS

inline int rNd4(int);
// static void WGPU_Run();
// static void ObtainedWebGpuDeviceStart(WGpuDevice,void *);
static void ObtainedWebGpuAdapterStart(WGpuAdapter,void *);
void ObtainedWebGpuDeviceStart(WGpuDevice,void *);
// const char * rd_fl(const char *);
EM_BOOL getCode(const char *);
void raf();
// static void WGPU_Start();
// int cltest();

extern"C"{

void startWebGPU();
void startWebGPUi(int sz);
void startWebGPUbi(int sz);
void runWebGPU();

}

WGpuBuffer indice_Buffer;
WGpuBuffer vertex_Buffer;
WGpuBuffer vertex_Buffer_UV;

WGpuImageCopyTexture videoTextureCopy;
WGpuImageCopyTexture MSTextureCopy;
WGpuExternalTexture extTexture;
WGpuTextureView depthTextureView;
WGpuTextureView depthTextureView2;
WGpuTextureView colorTextureView;
WGpuTextureView videoTextureView;
WGpuTextureView INTextureView;
WGpuTextureView OUTTextureView;
WGpuTextureView OUTTexture2View;
WGpuTextureView MSTextureView;
WGpuTexture depthTexture;
WGpuTexture depthTexture2;
WGpuTexture colorTexture;
WGpuTexture videoTexture;
WGpuTexture MSTexture;
WGpuTexture textureIn;
WGpuTexture textureOut;
WGpuTexture textureOut2;
WGpuTexture __128bit_Texture__;
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuShaderModule fs2;
WGpuBindGroup bindgroup;
WGpuBindGroup bindgroup_2;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuBuffer uniBuffer;
WGpuBuffer srcBuffer;
WGpuBuffer dstBuffer;
WGpuBuffer vidBuffer;
WGpuBuffer uni_iTime_Buffer;
WGpuBuffer uni_iTimeDelta_Buffer;
WGpuBuffer uni_iResolution_Buffer;
WGpuBuffer uni_iResolution_Buffer_2;
WGpuBuffer uni_iFrame_Buffer;

double szh,szw;
int szhI,szwI;
double szhDv,szwDv;
float szhFv,szwFv;
uint64_t tme;
void * userDataA;
void * userDataB;
WGpuTexture textureA;
WGpuBindGroupLayout bindGroupLayout;
WGpuBindGroupLayout bindGroupLayoutB;
WGpuComputePipeline computePipeline;
WGpuBuffer inputBuffer;
WGpuBuffer outputBuffer;
WGpuBuffer mapBuffer;
// WGpuBuffer uniBuffer;
WGpuShaderModule cs;
WGpuCommandBuffer commandBuffer;
WGpuCommandEncoder encoder;
WGpuComputePassEncoder computePass;
WGpuBindGroup bindGroup;
WGpuPipelineLayout pipelineLayout;
WGpuQuerySet querySet;
int randomNumber,entropySeed;
int raN;
int raND;
uint32_t outP;
double_int53_t WGPU_Range_PointerB;
double_int53_t WGPU_Range_PointerC;
long int length2;
void * fram;
static long int length;

using namespace boost::chrono;

using dv_tensor=boost::numeric::ublas::tensor<SDL_AudioDeviceID>;
using void_tensor=boost::numeric::ublas::tensor<boost::atomic<void *>>;
using gi_tensor=boost::numeric::ublas::tensor<boost::atomic<long>>;
using ub_tensor=boost::numeric::ublas::tensor<boost::atomic<unsigned char *>>;
using lu_tensor=boost::numeric::ublas::tensor<boost::atomic<unsigned long>>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using fjs_tensor=boost::numeric::ublas::tensor<float *>;
using wcolor_tensor=boost::numeric::ublas::tensor<WGpuColor>;
using uiptr_tensor=boost::numeric::ublas::tensor<uint32_t *>;
using wced_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoderDescriptor>;
using wbmc_tensor=boost::numeric::ublas::tensor<WGpuBufferMapCallback>;
using wcpe_tensor=boost::numeric::ublas::tensor<WGpuComputePassEncoder>;
using wcp_tensor=boost::numeric::ublas::tensor<WGpuComputePipeline>;
using i53_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using wstbl_tensor=boost::numeric::ublas::tensor<WGpuStorageTextureBindingLayout>;
using wbms_tensor=boost::numeric::ublas::tensor<WGPU_BUFFER_MAP_STATE>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
// using void_tensor=boost::numeric::ublas::tensor<void *>;
using wdc_tensor=boost::numeric::ublas::tensor<WGpuOnSubmittedWorkDoneCallback>;
using mouse_tensor=boost::numeric::ublas::tensor<boost::compute::double_>;
using c_tensor=boost::numeric::ublas::tensor<const char *>;
using c32_tensor=boost::numeric::ublas::tensor<const char32_t *>;
using f_tensor=boost::numeric::ublas::tensor<float>;
using fptr_tensor=boost::numeric::ublas::tensor<float *>;
using wce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wrpe_tensor=boost::numeric::ublas::tensor<WGpuRenderPassEncoder>;
using wcb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wcc_tensor=boost::numeric::ublas::tensor<WGpuCanvasContext>;
using wccf_tensor=boost::numeric::ublas::tensor<WGpuCanvasConfiguration>;
using wrp_tensor=boost::numeric::ublas::tensor<WGpuRenderPipeline>;
using wrpid_tensor=boost::numeric::ublas::tensor<WGpuRenderPipelineDescriptor>;
using wpl_tensor=boost::numeric::ublas::tensor<WGpuPipelineLayout>;
using wbg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using wbgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using wbgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry *>;
using wbge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry *>;
using wrpd_tensor=boost::numeric::ublas::tensor<WGpuRenderPassDescriptor>;
using wcpd_tensor=boost::numeric::ublas::tensor<WGpuComputePassDescriptor>;
using wrpca_tensor=boost::numeric::ublas::tensor<WGpuRenderPassColorAttachment>;
using wbbl_tensor=boost::numeric::ublas::tensor<WGpuBufferBindingLayout>;
using wtbl_tensor=boost::numeric::ublas::tensor<WGpuTextureBindingLayout>;
using wsbl_tensor=boost::numeric::ublas::tensor<WGpuSamplerBindingLayout>;
using wbd_tensor=boost::numeric::ublas::tensor<WGpuBufferDescriptor>;
using wao_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterOptions>;
using wdd_tensor=boost::numeric::ublas::tensor<WGpuDeviceDescriptor>;
using wrbe_tensor=boost::numeric::ublas::tensor<WGpuRenderBundleEncoder>;
using wrbed_tensor=boost::numeric::ublas::tensor<WGpuRenderBundleEncoderDescriptor>;
using wrpdsa_tensor=boost::numeric::ublas::tensor<WGpuRenderPassDepthStencilAttachment>;
using u64_tensor=boost::numeric::ublas::tensor<uint32_t>;
using i_tensor=boost::numeric::ublas::tensor<int>;
// using i_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using ui32_tensor=boost::numeric::ublas::tensor<boost::uint_t<32>::exact>;
using wt_tensor=boost::numeric::ublas::tensor<WGpuTexture>;
using wtd_tensor=boost::numeric::ublas::tensor<WGpuTextureDescriptor>;
using wtvd_tensor=boost::numeric::ublas::tensor<WGpuTextureViewDescriptor>;
using wtf_tensor=boost::numeric::ublas::tensor<WGPU_TEXTURE_FORMAT>;
using wtv_tensor=boost::numeric::ublas::tensor<WGpuTextureView>;
using js_tensor=boost::numeric::ublas::tensor<uint8_t *>;
using js_data_tensor=boost::numeric::ublas::tensor<std::vector<uint8_t>>;
using js_data_tensorf=boost::numeric::ublas::tensor<std::vector<float>>;
using js_data_tensorGL=boost::numeric::ublas::tensor<std::vector<GLubyte>>;
using js_data_tensor64=boost::numeric::ublas::tensor<std::vector<uint64_t>>;
using xyz_tensor=boost::numeric::ublas::tensor<WGpuOrigin3D>;
using xy_tensor=boost::numeric::ublas::tensor<WGpuOrigin2D>;
using wicb_tensor=boost::numeric::ublas::tensor<WGPUImageCopyBuffer>;
using wicei_tensor=boost::numeric::ublas::tensor<WGpuImageCopyExternalImage>;
using wict_tensor=boost::numeric::ublas::tensor<WGpuImageCopyTexture>;
using ws_tensor=boost::numeric::ublas::tensor<WGpuSampler>;
using wsd_tensor=boost::numeric::ublas::tensor<WGpuSamplerDescriptor>;
using wms_tensor=boost::numeric::ublas::tensor<WGpuMultisampleState>;
using wsm_tensor=boost::numeric::ublas::tensor<WGpuShaderModule>;
using wsmd_tensor=boost::numeric::ublas::tensor<WGpuShaderModuleDescriptor>;
using wcts_tensor=boost::numeric::ublas::tensor<WGpuColorTargetState>;
using wdss_tensor=boost::numeric::ublas::tensor<WGpuDepthStencilState>;
using wvs_tensor=boost::numeric::ublas::tensor<WGpuVertexState>;
using wps_tensor=boost::numeric::ublas::tensor<WGpuPrimitiveState>;
using wfs_tensor=boost::numeric::ublas::tensor<WGpuFragmentState>;
using wcts_tensor=boost::numeric::ublas::tensor<WGpuColorTargetState>;
using wvbl_tensor=boost::numeric::ublas::tensor<WGpuVertexBufferLayout>;
using wetd_tensor=boost::numeric::ublas::tensor<WGpuExternalTextureDescriptor>;
using wet_tensor=boost::numeric::ublas::tensor<WGpuExternalTexture>;
using wvbl_tensor=boost::numeric::ublas::tensor<WGpuVertexBufferLayout>;
using wib_tensor=boost::numeric::ublas::tensor<WGpuImageBitmap>;
using d_tensor=boost::numeric::ublas::tensor<double>;
using fjsv_tensor=boost::numeric::ublas::tensor<std::vector<float> *>;
using wict_tensor=boost::numeric::ublas::tensor<WGpuImageCopyTexture>;
using wictt_tensor=boost::numeric::ublas::tensor<WGpuImageCopyTextureTagged>;
using wva_tensor=boost::numeric::ublas::tensor<WGpuVertexAttribute *>;
using clk_tensor=boost::numeric::ublas::tensor<boost::chrono::high_resolution_clock::time_point>;
using timespn_tensor=boost::numeric::ublas::tensor<boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>>;
using vec4_tensor = boost::numeric::ublas::tensor<boost::numeric::ublas::vec4>;

extern "C"{  
  
EM_BOOL pl();
  
}

static gi_tensor audio_on=gi_tensor{1,1};
ub_tensor sound=ub_tensor{1,1,1};
gi_tensor sound_pos=gi_tensor{1,1};
gi_tensor sound_lft=gi_tensor{1,1};
gi_tensor sound_siz=gi_tensor{1,1};
lu_tensor sound_pos_u=lu_tensor{1,1};
v_tensor sse=v_tensor{1,2};
v_tensor sse2=v_tensor{1,1};
v_tensor sse3=v_tensor{1,1};
fptr_tensor WGPU_AudioInputBuffer=fptr_tensor{1,1};
#include <math.h>

class Oscillator {
public:
Oscillator(float frequency) {
this->frequency = frequency;
this->phase = 0.0f;
}

float generate() {
  
    float sample = sin(2.0f * M_PI * this->frequency * this->phase);
    this->phase += 1.0f / 44100.0f;
  
    return sample;
}

private:
float frequency;
float phase;
};


struct{
register GLubyte * snd;
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
static EM_BOOL snd_pos(GLint set){
sse3.at(0,0)=wasm_i64x2_splat(set);
sound_pos.at(0,0)=wasm_i64x2_extract_lane(sse3.at(0,0),0);
return EM_TRUE;
}

static EM_BOOL snd_lft(long long set){
sse.at(0,1)=wasm_i64x2_splat(set);
sound_lft.at(0,0)=wasm_i64x2_extract_lane(sse.at(0,1),0);
return EM_TRUE;
}

static EM_BOOL snd_pos_u(unsigned long long set){
sse2.at(0,0)=wasm_u64x2_splat(set);
sound_pos_u.at(0,0)=wasm_u64x2_extract_lane(sse2.at(0,0),0);
return EM_TRUE;
}


static void SDLCALL bfr(void * unused,GLubyte * stm,GLint len){
EM_ASM({console.log('bfr');}); 
if(audio_on.at(0,0)==5){
if(sound_pos.at(0,0)>=sound_siz.at(0,0)){
EM_ASM({console.log('stopping (if (sound_pos...)');}); 
audio_on.at(0,0)=10;
}
int bytes_to_copy=std::min(len,int(sound_lft.at(0,0))); 
::boost::tuples::tie(stm,len);
wave.wptr=sound.at(0,1,0)+sound_pos.at(0,0);
snd_lft(sound_pos_u.at(0,0)-sound_pos.at(0,0));
SDL_UnlockAudioDevice(wave.dev);
EM_ASM({console.log('memcopy sound');});
SDL_memcpy(stm,wave.wptr,sound_lft.at(0,0));
stm+=sound_lft.at(0,0);
len-=sound_lft.at(0,0);
wave.wptr += bytes_to_copy; // Advance the pointer
sound_pos.at(0, 0) += bytes_to_copy; 
snd_lft(sound_pos_u.at(0,0));
SDL_LockAudioDevice(wave.dev);
}
SDL_memcpy(stm,wave.wptr,len);
snd_pos(sound_pos.at(0,0)+len);
return;
}

boost::function<EM_BOOL()>plt=[this](){
audio_on.at(0,0)=0;
const int SAMPLE_RATE=44100;
// const int BUFFER_SIZE=1024;
Oscillator oscillator(440.0f);
::boost::tuples::tie(sound,sound_pos,sound_pos_u);
::boost::tuples::tie(wave,sse,sse2);
::boost::tuples::tie(bfr,request);
request.freq=SAMPLE_RATE;
request.format=AUDIO_S32;
request.channels=2;
request.samples=128;
SDL_memset(&request,0,sizeof(request));
snd_pos(0);
// SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);
// SDL_LoadWAV(flnm,&request,&wave.snd,&wave.slen);

int buffer_size=64*request.samples*request.channels*sizeof(float);

float* buffer=(float*)buffer_size;
  
for(int i=0;i<buffer_size/8.0; i += 2) { // Assuming stereo
float sample = oscillator.generate();         // Generate new sample
buffer[i] = sample;                           // Left channel
buffer[i + 1] = sample;                       // Right channel
}

sound_siz.at(0,0)=buffer_size;
wave.slen=buffer_size;
sound.at(0,1,0)=(unsigned char *)buffer;
WGPU_AudioInputBuffer.at(0,0)=buffer;
wave.snd=sound.at(0,1,0);
snd_pos_u(0);
snd_lft(sound_siz.at(0,0));
// request.callback=bfr;
    
// EM_ASM({console.log('SDL_OpenAudioDevice');}); 
wave.dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&request,NULL,0);
SDL_QueueAudio(wave.dev,sound.at(0,1,0),sound_siz.at(0,0));
SDL_PauseAudioDevice(wave.dev,SDL_FALSE);
audio_on.at(0,0)=5;
    EM_ASM({console.log('Got audio data.');}); 

return EM_TRUE;
};

};
