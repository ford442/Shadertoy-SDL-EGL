#include <boost/cstdfloat.hpp>  // must be first include
#include <cfloat>
#include <climits>
#include <math.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <unistd.h>

#define _XOPEN_SOURCE 700

#pragma pack(4)
// #pragma float_control(precise, on)  // enable precise semantics
#pragma fenv_access(on)             // enable environment sensitivity
// #pragma float_control(except, on)   // enable exception semantics

#pragma STDC FP_CONTRACT ON
#pragma STDC CX_LIMITED_RANGE ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define _XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#define _POSIX_REGEXP 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_USE_LONG_DOUBLE
#define BOOST_NO_EXCEPTIONS

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
// #include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
using namespace std::chrono_literals;
using namespace ::boost::tuples;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;

#include <iostream>

using namespace std;
using namespace boost::numeric::ublas;
using namespace boost::random;

#include <experimental/simd>
using std::experimental::native_simd;
using float_v=std::experimental::simd<float,std::experimental::simd_abi::scalar>;

using tensorVar=tensor<GLfloat>;
using tF=tensor<GLfloat>;
using tf=tensor<float>;
using td=tensor<double>;
using tld=tensor<long double>;
using tensorVarD=tensor<GLdouble>;
using tD=tensor<GLdouble>;
using tI=tensor<GLint>;
using tV=tensor<v128_t>;

#include <cassert>
#include <iomanip>
#include <ctime>

#include <stdio.h>

constexpr float PI = 3.14159265358979323846f;

using glm::mat4x4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

using namespace std;

#include "../../lib/lib_webgpu.h"


WGpuAdapter adapter=0;
WGpuDevice device=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuComputePipeline computePipeline=0;
WGpuQueue queue=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuBufferDescriptor bufferDescriptorI={};
WGpuBufferDescriptor bufferDescriptorO={};
WGpuBufferDescriptor bufferDescriptorM={};
WGpuBufferBindingLayout bufferBindingLayout1={};
WGpuBufferBindingLayout bufferBindingLayout2={};
WGpuBufferBindingLayout bufferBindingLayout3={};
WGpuBuffer inputBuffer=0;
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[2]={};
WGpuBindGroupEntry bindGroupEntry[2]={};
WGpuBindGroup bindGroup=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuQuerySet querySet=0;
void *userDataA;
WGpuRequestAdapterOptions options={};

int bufferSize = 64 * sizeof(float);

const char *computeShader =
"@group(0) @binding(0) var<storage,read> inputBuffer: array<f32,64>;"
"@group(0) @binding(1) var<storage,read_write> outputBuffer: array<f32,64>;"
// The function to evaluate for each element of the processed buffer
"fn f(x: f32) -> f32 {"
"return 2.0 * x + 0.42;"
"}"
"@compute @workgroup_size(32)"
"fn computeStuff(@builtin(global_invocation_id) global_id: vec3<u32>,@builtin(local_invocation_id) local_id: vec3<u32>) {"
    // Apply the function f to the buffer element at index id.x:
// "outputBuffer[global_id.x] = f(inputBuffer[global_id.x]);"
"outputBuffer[0] = 111.0;"
// "mapBuffer[0] = outputBuffer[0];"
"}";

void raf(WGpuDevice device){
std::cout << "skipping querySet" << std::endl;
std::vector<float>input(bufferSize/sizeof(float));
// computePassDescriptor.timestampWrites=&timestampWrites;
// computePassDescriptor.numTimestampWrites=0;
bufferDescriptorI.mappedAtCreation=false;
bufferDescriptorI.size=bufferSize;
bufferDescriptorI.usage=WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST;
bufferDescriptorO.mappedAtCreation=false;
bufferDescriptorO.size=bufferSize;
bufferDescriptorO.usage=WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC;
bufferDescriptorM.mappedAtCreation=false;
bufferDescriptorM.size=bufferSize;
bufferDescriptorM.usage=WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST;
mapBuffer=wgpu_device_create_buffer(device,&bufferDescriptorM);
inputBuffer=wgpu_device_create_buffer(device,&bufferDescriptorI);
outputBuffer=wgpu_device_create_buffer(device,&bufferDescriptorO);
for(int i=0;i<input.size();++i){
input[i]=21.0021f;
}
shaderModuleDescriptor={computeShader,0,NULL};
std::cout << "wgpu_device_create_shader_module" << std::endl;
cs=wgpu_device_create_shader_module(device,&shaderModuleDescriptor);
std::cout << "create bindgroup layout" << std::endl;
bufferBindingLayout1.type=3;
bufferBindingLayout2.type=2;
bufferBindingLayout3.type=2;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=bufferBindingLayout1;
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=bufferBindingLayout2;
// bindGroupLayoutEntries[2].binding=2;
// bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
// bindGroupLayoutEntries[2].type=1;
// bindGroupLayoutEntries[2].layout.buffer=bufferBindingLayout3;
bindGroupLayout=wgpu_device_create_bind_group_layout(device,bindGroupLayoutEntries,2);
const char * Entry="computeStuff";
std::cout << "wgpu_device_create_compute_pipeline" << std::endl;
pipelineLayout=wgpu_device_create_pipeline_layout(device,&bindGroupLayout,1);
computePipeline=wgpu_device_create_compute_pipeline(device,cs,Entry,pipelineLayout,NULL,0);
std::cout << "create bindgroup" << std::endl;
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=inputBuffer;
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=0; 
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=outputBuffer;
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=0;
// bindGroupEntry[2].binding=2;
// bindGroupEntry[2].resource=mapBuffer;
// bindGroupEntry[2].bufferBindOffset=0;
// bindGroupEntry[2].bufferBindSize=0;
bindGroup=wgpu_device_create_bind_group(device,bindGroupLayout,bindGroupEntry,2);
std::cout << "creating encoder" << std::endl;
encoder=wgpu_device_create_command_encoder(device,0);
std::cout << "wgpu_command_encoder_begin_compute_pass" << std::endl;
computePass=wgpu_command_encoder_begin_compute_pass(encoder,&computePassDescriptor);
std::cout << "wgpu_compute_pass_encoder_set_pipeline" << std::endl;
wgpu_compute_pass_encoder_set_pipeline(computePass,computePipeline);	
std::cout << "wgpu_encoder_set_bind_group" << std::endl;
wgpu_encoder_set_bind_group(computePass,0,bindGroup,0,0);
uint32_t invocationCount=bufferSize/sizeof(float);
uint32_t workgroupSize=32;
queue=wgpu_device_get_queue(device);
std::cout << "filling input buffer" << std::endl;
wgpu_queue_write_buffer(queue,inputBuffer,0,input.data(),input.size()*sizeof(float));
	// This ceils invocationCount / workgroupSize
uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
std::cout << "inputBuffer: " << inputBuffer << std::endl;
std::cout << "input: " << input[0] << std::endl;
	// dispatch workgroups
std::cout << "dispatch workgroups:" << workgroupCount << ",1,1" << std::endl;
// wgpu_compute_pass_encoder_dispatch_workgroups(computePass,workgroupCount,uint32_t(1),uint32_t(1));
wgpu_compute_pass_encoder_dispatch_workgroups(computePass,uint32_t(2),uint32_t(1),uint32_t(1));
std::cout << "wgpu_encoder_end" << std::endl;
wgpu_encoder_end(computePass);
	// copy output buff	
std::cout << "at wgpu_command_encoder_copy_buffer_to_buffer" << std::endl;
wgpu_command_encoder_copy_buffer_to_buffer(encoder,outputBuffer,0,mapBuffer,0,bufferSize);
std::cout << "at commandBuffer=wgpu_encoder_finish(encoder);" << std::endl;
commandBuffer=wgpu_encoder_finish(encoder);
WGpuOnSubmittedWorkDoneCallback onComputeDone=[](WGpuQueue queue,void *userData){
std::cout << "at computeDoneCall" << std::endl;
WGpuBufferMapCallback mapCallback=[](WGpuBuffer buffer,void *userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
std::cout << "at mapCallback!" << std::endl;
// std::vector<double>output(bufferSize/sizeof(float));
std::cout << "wgpu_buffer_read_mapped_range" << std::endl;
auto output=wgpu_buffer_get_mapped_range(mapBuffer,uint32_t(0),bufferSize);
std::cout << &output << std::endl;
double * outputd;
wgpu_buffer_read_mapped_range(mapBuffer,0,0,&outputd,bufferSize);
std::cout << &outputd << std::endl;
};
std::cout << "at wgpu WGpuOnSubmittedWorkDoneCallback!" << std::endl;
std::cout << "wgpu_buffer_map_async" << std::endl;
WGPU_MAP_MODE_FLAGS mode1=0x1; // WGPU_MAP_MODE_READ
wgpu_buffer_map_async(mapBuffer,mapCallback,&userDataA,mode1,uint32_t(0),bufferSize);
};
wgpu_queue_set_on_submitted_work_done_callback(queue,onComputeDone,0);
std::cout << "at wgpu_queue_submit_one_and_destroy" << std::endl;
wgpu_queue_submit_one_and_destroy(queue,commandBuffer);
return;
}

void ObtainedWebGpuDevice(WGpuDevice result,void *userData){
device=result;
raf(device);
}
/*
//   WGpuShaderModule vs = wgpu_device_create_shader_module(device, &shaderModuleDesc);
WGpuProgrammableStageDescriptor stageDesc{};
stageDesc.module=cs;
stageDesc.entryPoint="computeStuff";
stageDesc.constantCount=0;
stageDesc.constants=NULL;
WGpuRenderPipelineDescriptor renderPipelineDesc = WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER;
//  skipped somehow
WGpuComputePipelineDescriptor computePipelineDesc={};
computePipelineDesc.compute=stageDesc;
wgpu_device_create_compute_pipeline(WGpuDevice device,WGpuShaderModule computeModule, const char *entryPoint NOTNULL,WGpuPipelineLayout layout,const WGpuPipelineConstant *constants,int numConstants);
 emscripten_set_main_loop(raf,0);
 */

void ObtainedWebGpuAdapter(WGpuAdapter result,void *userData){
adapter=result;
wgpu_adapter_request_device_async(adapter,&deviceDescriptor,ObtainedWebGpuDevice,0);
}


void init1(){

options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
navigator_gpu_request_adapter_async(&options,ObtainedWebGpuAdapter,0);

}

void init2(){

}

void init3(){
}

void init4(){

}

#include <functional>

tf sx=tf{2,2};
std::function<float(float,float)>TensorAdd(){
return[](float a,float b){sx.at(0,0)=a;sx.at(0,1)=b;sx.at(1,0)=sx.at(0,0)+sx.at(0,1);return sx.at(1,0);};
}
auto tensorAdd=TensorAdd();

td sy=td{2,2};

std::function<double(double,double)>DoubleAdd(){
return[](double a,double b){
sy.at(0,0)=a;
sy.at(0,1)=b;
sy.at(1,0)=sy.at(0,0)+sy.at(0,1);
return sy.at(1,0);};
}
auto doubleAdd=DoubleAdd();

tV sz=tV{2,2};
std::function<v128_t(v128_t,v128_t)>IntrinsAdd(){
return[](v128_t a,v128_t b){
sz.at(0,0)=a;
sz.at(0,1)=b;
sz.at(1,0)=wasm_f64x2_add(a,b);
return sz.at(1,0);
};
}
auto intrinsAdd=IntrinsAdd();

class tens{

private:

float lol,olo;
tensorVar A=tensorVar{8,4};
tensorVar Aa=tensorVar{2,3};

public:

float rtt(float nm){
long long timE=time(0);
struct tm *datE=localtime(&timE);
short yr=1900+datE->tm_year;
short mn=1+datE->tm_mon;
short dy=datE->tm_mday;
short hr=datE->tm_hour;
short mi=datE->tm_min;
short sc=datE->tm_sec;
setprecision(3);
std::cout << "--------------------------" << std::endl;
std::cout << "-----ctime----------------" << std::endl;
std::cout << "-------" << timE << "----------" << std::endl;
  std::cout << yr << std::endl;
  std::cout << mn << std::endl;
  std::cout << dy << std::endl;
  std::cout << hr << std::endl;
  std::cout << mi << std::endl;
  std::cout << sc << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
float ppi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;
double ppd=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
long double ppD=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L;
std::cout << "-float------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppi <<"-----" << std::endl;
std::cout << "-double------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppd <<"-----" << std::endl; 
std::cout << "-long double------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppD <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "Tensor adding input: 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
sx.at(1,1)=tensorAdd(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f,3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f);
std::cout << "----------float-----------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< sx.at(1,1) <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
sy.at(1,1)=doubleAdd(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679,3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679);
std::cout << "-----------double---------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< sy.at(1,1) <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
sz.at(1,1)=intrinsAdd(wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f),wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f));
// szz.at(1,1)=intrinsLDAdd(wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L),wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L));
std::cout << "------intrins-------------" << std::endl;
float ou2=wasm_f64x2_extract_lane(sz.at(1,1),0);
double ou3=wasm_f64x2_extract_lane(sz.at(1,1),0);
// long double ou5=wasm_f64x2_extract_lane(szz.at(1,1),0);
std::cout << fixed << setprecision(64) << "--float---"<< ou2 <<"-----" << std::endl;
std::cout << fixed << setprecision(64) << "--double---"<< ou3 <<"-----" << std::endl;
// std::cout << fixed << setprecision(64) << "--long double---"<< ou5 <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
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
  
float noblock(float y){
__m64 p={6.0,6.0};
float_v reet=7.7f;
farray=y;
return farray;
}

}rnn;

};
