#pragma pack(4)
#pragma float_control(precise, on)  // enable precise semantics
#pragma fenv_access(on)             // enable environment sensitivity
#pragma float_control(except, on)   // enable exception semantics

#include <boost/cstdfloat.hpp>  // must be first include

#include <emscripten.h>
#include <emscripten/html5.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu_cpp.h"
// #include <torch/script.h>
// #include <torch/csrc/api/include/torch/all.h>
// #include <ATen/ATen.h>
// #include "/usr/include/x86_64-linux-gnu/gmp.h"
// #include "./mpfr.h"
// #include "./gmp.h"

// #include "/usr/include/gmpxx.h"

#include <experimental/simd>
using std::experimental::native_simd;
using float_v=std::experimental::simd<float,std::experimental::simd_abi::scalar>;

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1

#include "boost/tuple/tuple.hpp"
#include "boost/timer/timer.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/avx.hpp"
#include <boost/numeric/ublas/tensor.hpp>
// #include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <time.h>
#include <chrono>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <boost/context/fiber.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
using namespace std::chrono_literals;
using namespace ::boost::tuples;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;

#include <iostream>

using namespace std;
using namespace boost::numeric::ublas;
using namespace boost::multiprecision;
using namespace boost::random;

using tensorVar=tensor<GLfloat>;
using tF=tensor<GLfloat>;
using tensorVarD=tensor<GLdouble>;
using tD=tensor<GLdouble>;
using tI=tensor<GLint>;
using tV=tensor<v128_t>;

WGPUDevice device;
WGPUQueue queue;
WGPUSwapChain swapchain;

WGPURenderPipeline pipeline;
WGPUBuffer vertBuf; // vertex buffer with triangle position and colours
WGPUBuffer indxBuf; // index buffer
WGPUBuffer uRotBuf; // uniform buffer (containing the rotation angle)
WGPUBindGroup bindGroup;


EM_BOOL raf(double time, void *userData)
{
  WGPUCommandEncoder encoder = wgpu_device_create_command_encoder(device, 0);

  WGpuRenderPassColorAttachment colorAttachment = WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER;
  colorAttachment.view = wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(canvasContext), 0);

  WGpuRenderPassDescriptor passDesc = {};
  passDesc.numColorAttachments = 1;
  passDesc.colorAttachments = &colorAttachment;

  WGpuRenderPassEncoder pass = wgpu_command_encoder_begin_render_pass(encoder, &passDesc);
  wgpu_render_pass_encoder_set_pipeline(pass, renderPipeline);
  wgpu_render_pass_encoder_draw(pass, 3, 1, 0, 0);
  wgpu_render_pass_encoder_end(pass);

  WGpuCommandBuffer commandBuffer = wgpu_command_encoder_finish(encoder);

  wgpu_queue_submit_one_and_destroy(queue, commandBuffer);

  return EM_FALSE; // Render just one frame, static content
}

void ObtainedWebGpuDevice(WGpuDevice result, void *userData)
{
  device = result;
  queue = wgpu_device_get_queue(device);

  canvasContext = wgpu_canvas_get_webgpu_context("canvas");

  WGpuCanvasConfiguration config = WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
  config.device = device;
  config.format = navigator_gpu_get_preferred_canvas_format();
  wgpu_canvas_context_configure(canvasContext, &config);

  const char *vertexShader =
    "@vertex\n"
    "fn main(@builtin(vertex_index) vertexIndex : u32) -> @builtin(position) vec4<f32> {\n"
      "var pos = array<vec2<f32>, 3>(\n"
        "vec2<f32>(0.0, 0.5),\n"
        "vec2<f32>(-0.5, -0.5),\n"
        "vec2<f32>(0.5, -0.5)\n"
      ");\n"

      "return vec4<f32>(pos[vertexIndex], 0.0, 1.0);\n"
    "}\n";

  const char *fragmentShader =
    "@fragment\n"
    "fn main() -> @location(0) vec4<f32> {\n"
      "return vec4<f32>(1.0, 0.5, 0.3, 1.0);\n"
    "}\n";

  WGpuShaderModuleDescriptor shaderModuleDesc = {};
  shaderModuleDesc.code = vertexShader;
  WGpuShaderModule vs = wgpu_device_create_shader_module(device, &shaderModuleDesc);

  shaderModuleDesc.code = fragmentShader;
  WGpuShaderModule fs = wgpu_device_create_shader_module(device, &shaderModuleDesc);

  WGpuRenderPipelineDescriptor renderPipelineDesc = WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER;
  renderPipelineDesc.vertex.module = vs;
  renderPipelineDesc.vertex.entryPoint = "main";
  renderPipelineDesc.fragment.module = fs;
  renderPipelineDesc.fragment.entryPoint = "main";

  WGpuColorTargetState colorTarget = WGPU_COLOR_TARGET_STATE_DEFAULT_INITIALIZER;
  colorTarget.format = config.format;
  renderPipelineDesc.fragment.numTargets = 1;
  renderPipelineDesc.fragment.targets = &colorTarget;

  renderPipeline = wgpu_device_create_render_pipeline(device, &renderPipelineDesc);

  emscripten_request_animation_frame_loop(raf, 0);
}

void ObtainedWebGpuAdapter(WGpuAdapter result, void *userData)
{
  adapter = result;

  WGpuDeviceDescriptor deviceDesc = {};
  wgpu_adapter_request_device_async(adapter, &deviceDesc, ObtainedWebGpuDevice, 0);
}


class tens{

private:
  
// boost::random::random_device rng;
float lol,olo;
tensorVar A=tensorVar{8,4};
tensorVar Aa=tensorVar{2,3};
uint128_t tst128;

public:

float rtt(float nm){
A.at(0,0)=nm;
tensorVar B=A;
lol=static_cast<float>(B.at(4,4));
olo=lol*100;
// float llo=rng();
return olo;
}

};

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

inline int32_t Size;

inline EM_BOOL ms_l,clk_l;

inline struct{
float xx;
float yy;
float mX;
float mY;
float mm;
float nn;
float S;
float mouseY;
float mouseX;
double wi;
double hi;
GLclampf x;
GLclampf y;
}mouse;

inline EM_BOOL ms_clk(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

inline EM_BOOL ms_mv(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mouse.x=e->clientX;
mouse.y=e->clientY;
}}
return (EM_BOOL)1;
}

void mss(){
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=static_cast<int32_t>(mouse.hi);
mouse.S=static_cast<float>(mouse.hi);
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const float xxx=mouse.mouseX;
const float yyy=mouse.mouseY;
EM_ASM({
console.log($0);
},xxx);
mouse.mX=1.0f-(xxx*Size);
mouse.mY=1.0f-(yyy*Size);
clk_l=false;
}
mouse.mm=mouse.x*Size;
mouse.nn=Size*mouse.y;
}else{
clk_l=true;
EM_ASM({
console.log($0);
},mouse.nn);
}
return;
}

static tI inte=tI{1,1};
static tF sdeci=tF{1,1};
static tV q=tV{1,1};
static tV intrn=tV{1,4};
static boost::atomic<float>farray;
static v128_t aa,vv,xx,l,tt;

class funcs{

private:
  
public:

union{
float tuple_float_short(float num){
float cc,pp,uu,cc2,pp2,uu2,nn;
int r;
float Tdlt;

cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
for(r=0;r<100;r++){
tie(cc,pp,uu);
tie(cc2,pp2,uu2);
}
t1=std::chrono::steady_clock::now();
for(r=0;r<100;r++){
nn=cc+pp+uu+cc2+pp2+uu2;
}
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return nn;
}
  
float tuple_float_long(float num){float cc,pp,uu,cc2,pp2,uu2,nn;
float Tdlt;
int r;
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
for(r=0;r<100;r++){
tie(cc,pp,uu,cc2,pp2,uu2);
}
t1=std::chrono::steady_clock::now();
for(r=0;r<100;r++){
nn=cc+pp+uu+cc2+pp2+uu2;
}
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uu;
}

GLfloat tuple_gl(GLfloat num){
float Tdlt;
t1=std::chrono::steady_clock::now();
GLfloat ggg=num,ppg=num,uug=num;
tie(ggg,ppg,uug);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uug;
}

v128_t tuple_avx(float num){
float Tdlt;
t1=std::chrono::steady_clock::now();
aa=wasm_i32x4_splat(num);
vv=wasm_i32x4_splat(num);
xx=wasm_i32x4_splat(num);
tie(aa,vv,xx);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return xx;
}

v128_t simd_test(float * a){
float Tdlt;
t1=std::chrono::steady_clock::now();
int m=a[0]*1000.0;
l=wasm_i32x4_splat(m);
tt=wasm_f32x4_add(l,l);
t2=std::chrono::steady_clock::now();
std::chrono::duration<float, std::chrono::milliseconds::period> time_span=std::chrono::duration<float,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return tt;
}

v128_t double_add(float fl){
tie(inte,sdeci,q,intrn);
inte.at(0,0)=std::floor(fl);
sdeci.at(0,0)=fl-inte.at(0,0);
intrn.at(0,0)=wasm_f32x4_make(inte.at(0,0),sdeci.at(0,0),sdeci.at(0,0),sdeci.at(0,0));
intrn.at(0,1)=wasm_f32x4_make(1.0,100.0,10.0,1.0);
intrn.at(0,0)=wasm_f32x4_div(intrn.at(0,0),intrn.at(0,1));
intrn.at(0,2)=wasm_f32x4_sqrt(intrn.at(0,0));
intrn.at(0,0)=wasm_f32x4_mul(intrn.at(0,2),intrn.at(0,2));
intrn.at(0,3)=wasm_f32x4_mul(intrn.at(0,0),intrn.at(0,1));
return intrn.at(0,3);
}
  
// native_simd<float> noblock(float y){
float noblock(float y){
__m64 p={6.0,6.0};
// __m64 pt={12.0,12.0};
// __m64 py3=_mm_adds_pi16_(p,pt);
// int reet=_m_to_int_(py3);
// int reet2=_mm_cvtsi64_si32_(py3);
// int tsst=_mm_extract_epi32(pt,1);
float_v reet=7.7f;
farray=y;
// boost::float128_t tyt=farray;
return farray;
 //   std::cout << ::at::ones({3,4}, at::CPU(at::kFloat)) << "\n";
 // emscripten_set_main_loop((void(*)())mss,0,0);

}

}rnn;

};
