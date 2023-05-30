#include "../../include/vanilla/main.hpp"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>

struct AdapterUserData {
WGPUAdapter adapter;
bool requestEnded;
};

void onDeviceError (WGPUErrorType type, char const* message, void* pUserData) {
printf( "Uncaptured device error: type (%u)\n", type);
if (message)
printf( "Could not get WebGPU adapter: (%s)\n", message);
};

void onAdapterRequestEnded(WGPURequestAdapterStatus status, WGPUAdapter adapter, char const * message, void * pUserData) {
struct AdapterUserData * userData = (struct AdapterUserData *)pUserData;
if (status == WGPURequestAdapterStatus_Success) {
userData->adapter = adapter;
printf( "Got WebGPU adapter: %s\n", adapter);
} else {
printf( "Could not get WebGPU adapter: %s\n", message);
}
userData->requestEnded = true;
};

WGPUAdapter requestAdapter2(WGPUInstance instance, WGPURequestAdapterOptions const * options) {
struct AdapterUserData userData={NULL, false};
wgpuInstanceRequestAdapter(instance,options,onAdapterRequestEnded,(void*)&userData);
userData.requestEnded=true;
return userData.adapter;
}

struct DeviceUserData {
WGPUDevice device;
bool requestEnded;
};

void onDeviceRequestEnded2(WGPURequestDeviceStatus status, WGPUDevice device, char const * message, void * pUserData) {
struct DeviceUserData * userData = (struct DeviceUserData *)(pUserData);
if (status == WGPURequestDeviceStatus_Success) {
userData->device = device;
printf( "Got WebGPU device: %s\n", device);
} else {
printf( "Could not get WebGPU device");
}
userData->requestEnded = true;
};

WGPUDevice requestDevice2(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor) {
struct DeviceUserData userData = {NULL, false};
wgpuAdapterRequestDevice(adapter,descriptor,onDeviceRequestEnded2,(void*)&userData);
userData.requestEnded=true;
return userData.device;
}

void gpmain() {
WGPUInstanceDescriptor desc = {};
desc.nextInChain = NULL;
WGPUInstance instance = nullptr; // wgpuCreateInstance(&desc);
if (!instance) {
printf( "Skipping initialize WebGPU!\n");
}

printf("Requesting adapter...\n");
  //   WGPUSurface surface = glfwGetWGPUSurface(instance, window);
WGPURequestAdapterOptions adapterOpts = {};
adapterOpts.nextInChain = NULL;
 //    adapterOpts.compatibleSurface = surface;
WGPUAdapter adapter2 = requestAdapter2(instance, &adapterOpts);
printf( "Got adapter: %p\n", adapter2);
printf("Requesting device...\n");
WGPUDeviceDescriptor deviceDesc = {};
deviceDesc.nextInChain = NULL;
deviceDesc.label = "My Device"; // anything works here, that's your call
deviceDesc.requiredFeaturesCount = 0; // we do not require any specific feature
deviceDesc.requiredLimits = NULL; // we do not require any specific limit
deviceDesc.defaultQueue.nextInChain = NULL;
deviceDesc.defaultQueue.label = "The default queue";
    sleep(3);

WGPUDevice device = requestDevice2(adapter2, &deviceDesc);
    sleep(3);

printf( "Got device: %p\n", device);
wgpuDeviceSetUncapturedErrorCallback(device, onDeviceError, NULL /* pUserData */);
WGPUQueue queue = wgpuDeviceGetQueue(device);
WGPUSwapChainDescriptor swapChainDesc = {};
swapChainDesc.width = 640;
swapChainDesc.height = 480;
swapChainDesc.usage = WGPUTextureUsage_RenderAttachment;
 //   WGPUTextureFormat swapChainFormat = wgpuSurfaceGetPreferredFormat(surface, adapter);
  //  swapChainDesc.format = swapChainFormat;
swapChainDesc.presentMode = WGPUPresentMode_Fifo;
 //    WGPUSwapChain swapChain = wgpuDeviceCreateSwapChain(device, surface, &swapChainDesc);
  //   printf( "Swapchain: %p\n", swapChain);
const char* shaderSource = "                                                                \
    @vertex                                                                                     \
    fn vs_main(@builtin(vertex_index) in_vertex_index: u32) -> @builtin(position) vec4<f32> {   \
        var p = vec2<f32>(0.0, 0.0);                                                            \
    }                                                                                           \
    ";

WGPUShaderModuleDescriptor shaderDesc = {};
   // shaderDesc.hintCount = 0;
   // shaderDesc.hints = NULL;
WGPUShaderModuleWGSLDescriptor shaderCodeDesc = {};
shaderCodeDesc.chain.next = NULL;
shaderCodeDesc.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
shaderDesc.nextInChain = &shaderCodeDesc.chain;
shaderCodeDesc.source = shaderSource;
WGPUShaderModule shaderModule = wgpuDeviceCreateShaderModule(device, &shaderDesc);
WGPURenderPipelineDescriptor pipelineDesc = {};
    // pipelineDesc.nextInChain = NULL;
pipelineDesc.vertex.bufferCount = 0;
pipelineDesc.vertex.buffers = NULL;
pipelineDesc.vertex.module = shaderModule;
pipelineDesc.vertex.entryPoint = "vs_main";
pipelineDesc.vertex.constantCount = 0;
pipelineDesc.vertex.constants = NULL;
pipelineDesc.primitive.topology = WGPUPrimitiveTopology_TriangleList;
pipelineDesc.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;
pipelineDesc.primitive.frontFace = WGPUFrontFace_CCW;
pipelineDesc.primitive.cullMode = WGPUCullMode_None;
WGPUFragmentState fragmentState = {};
fragmentState.nextInChain = NULL;
pipelineDesc.fragment = &fragmentState;
fragmentState.module = shaderModule;
fragmentState.entryPoint = "fs_main";
fragmentState.constantCount = 0;
fragmentState.constants = NULL;
WGPUBlendState blendState = {};
blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
blendState.color.operation = WGPUBlendOperation_Add;
blendState.alpha.srcFactor = WGPUBlendFactor_Zero;
blendState.alpha.dstFactor = WGPUBlendFactor_One;
blendState.alpha.operation = WGPUBlendOperation_Add;
 //   WGPUColorTargetState colorTarget = {};
  //  colorTarget.format = swapChainFormat;
 //   colorTarget.blend = &blendState;
 //   colorTarget.writeMask = WGPUColorWriteMask_All; // We could write to only some of the color channels.
    fragmentState.targetCount = 1;
    fragmentState.targets = NULL; // &colorTarget;
  //  pipelineDesc.depthStencil = NULL;
 //   pipelineDesc.multisample.count = 1;
 //   pipelineDesc.multisample.mask = ~0u;
 //   pipelineDesc.multisample.alphaToCoverageEnabled = false;
WGPUPipelineLayoutDescriptor layoutDesc = {};
layoutDesc.nextInChain = NULL;
layoutDesc.bindGroupLayoutCount = 0;
layoutDesc.bindGroupLayouts = NULL;
 //   WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(device, &layoutDesc);
 //   pipelineDesc.layout = layout;
  //  WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(device, &pipelineDesc);
  //  while (!glfwWindowShouldClose(window)) {
     //   glfwPollEvents();
     //   WGPUTextureView nextTexture = wgpuSwapChainGetCurrentTextureView(swapChain);
WGPUCommandEncoderDescriptor encoderDesc = {};
encoderDesc.nextInChain = NULL;
encoderDesc.label = "My command encoder";
WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &encoderDesc);
WGPURenderPassDescriptor renderPassDesc = {};
renderPassDesc.nextInChain = NULL;
    //    WGPURenderPassColorAttachment renderPassColorAttachment = {};
    //    renderPassColorAttachment.view = nextTexture;
    //    renderPassColorAttachment.resolveTarget = NULL;
    //    renderPassColorAttachment.loadOp = WGPULoadOp_Clear;
     //   renderPassColorAttachment.storeOp = WGPUStoreOp_Store;
     //   renderPassColorAttachment.clearValue = (WGPUColor){ 0.9, 0.1, 0.2, 1.0 };
     //   renderPassDesc.colorAttachmentCount = 1;
    //    renderPassDesc.colorAttachments = &renderPassColorAttachment;
    //    renderPassDesc.depthStencilAttachment = NULL;
    //    renderPassDesc.timestampWriteCount = 0;
    //    renderPassDesc.timestampWrites = NULL;
   //     WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);
   //     wgpuRenderPassEncoderSetPipeline(renderPass, pipeline);
  //      wgpuRenderPassEncoderDraw(renderPass, 3, 1, 0, 0);
  //      wgpuRenderPassEncoderEnd(renderPass);
   //     wgpuTextureViewDrop(nextTexture);
WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
cmdBufferDescriptor.nextInChain = NULL;
cmdBufferDescriptor.label = "Command buffer";
WGPUCommandBuffer command = wgpuCommandEncoderFinish(encoder, &cmdBufferDescriptor);
   //     wgpuQueueSubmit(queue, 1, &command);
  //      wgpuSwapChainPresent(swapChain);
  //  }
//    glfwDestroyWindow(window);
//    glfwTerminate();
return;
}

float cc,pp,uu;
float cc2,pp2,uu2;
float ccc,ppc,uuc;
float cc2c,pp2c,uu2c;

funcs Funcs;
tens Tens;

extern "C"{
  
float js_double(float nem){ 
v128_t rtt=Funcs.rnn.double_add(nem);
float retrnI=wasm_f32x4_extract_lane(rtt,0);
float retrnD=wasm_f32x4_extract_lane(rtt,4);
return retrnI;
}
  
float js_Tensors(float nm){ 
return Tens.rtt(nm);
}
  
float js_tuple_float_short(float nm){ 
return Funcs.rnn.tuple_float_short(nm);
}
  
float js_tuple_float_long(float nm){ 
return Funcs.rnn.tuple_float_long(nm);
}

GLfloat js_tuple_gl(float nm){
return Funcs.rnn.tuple_gl(nm);
}
  
float js_tuple_avx(float nm){
v128_t ans=Funcs.rnn.tuple_avx(nm);
float retrn=wasm_f32x4_extract_lane(ans,0);
return retrn;
}

float js_tuple_avx_gl(GLfloat nm){
v128_t ans=Funcs.rnn.tuple_avx(nm);
GLfloat retrn=wasm_f32x4_extract_lane(ans,0);
return retrn;
}
  
float js_simd(float * aa){
v128_t cc=Funcs.rnn.simd_test(aa);
// wasm_v128_store(&out[i], prod);
float c=wasm_f32x4_extract_lane(cc,0);
float d=wasm_f32x4_extract_lane(cc,1);
float ce=wasm_f32x4_extract_lane(cc,2);
float de=wasm_f32x4_extract_lane(cc,3);
float re=c+d+ce+de;
return re;
}

float js_noblock(float yy){
float tt=(float)Funcs.rnn.noblock(yy);
return tt;
}
  
void wgpu_init1(){
init1();
return;
}
  
void wgpu_init2(){
init2();
return;
}
  
void wgpu_init3(){
init3();
return;
}
  
void wgpu_init4(){
// init4();
return;
}

}

EM_JS(void,js_main,(),{

"use strict";

function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall('js_hello');
var tst=[10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,];
const $H=Module.HEAPF32.buffer;
const $P=Module.HEAPF32.subarray(0,32);
$P.set(tst,0);
console.log('Javascript HEAPF32: ',$H);
let pointa=800;
var sim=new Float32Array($H,pointa,32);
sim.set(tst,0);
console.log("intrins function:");
var reslt=Module.ccall('js_simd',"Number",["Number"],[pointa]);
console.log(reslt);
},400);
setTimeout(function(){
console.log("float function short:");
var reslt=Module.ccall('js_tuple_float_short',"Number",["Number"],[1.0]);
console.log(reslt);
},500);
setTimeout(function(){
console.log("float function long:");
var reslt=Module.ccall('js_tuple_float_long',"Number",["Number"],[1.0]);
console.log(reslt);
},600);
setTimeout(function(){
console.log("gl function:");
var reslt=Module.ccall('js_tuple_gl',"Number",["Number"],[1.0]);
console.log(reslt);
},700);
setTimeout(function(){
console.log("avx function:");
var reslt=Module.ccall('js_tuple_avx',"Number",["Number"],[1.0]);
console.log(reslt);
},800);
setTimeout(function(){
console.log("avx gl function:");
var reslt=Module.ccall('js_tuple_avx_gl',"Number",["Number"],[1.0]);
console.log(reslt);
},900);
setTimeout(function(){
console.log("Tensor class def:");
var reslt=Module.ccall('js_Tensors',"Number",["Number"],[1.0]);
console.log(reslt);
},1000);
setTimeout(function(){
console.log("Intrins Tensor:");
var reslt=Module.ccall('js_double',"Number",["Number"],[1.0]);
console.log(reslt);
},1100);
setTimeout(function(){
console.log("noblock (and native_simd):");
var pointa=800;
var reslt=Module.ccall('js_noblock',"Number",["Number"],[pointa]);
console.log(reslt);
},1200);
setTimeout(function(){
console.log("noblock (and native_simd):");
Module.ccall('wgpu_init1');
},1400);
setTimeout(function(){
Module.ccall('wgpu_init2');
},2600);
setTimeout(function(){
Module.ccall('wgpu_init3');
},3800);
setTimeout(function(){
// Module.ccall('wgpu_init4');
},5000);
}
  
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt=tem.innerHTML;

function grab$lt(){
$lt=Math.round($lt);
}

$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16)
;});
document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});
setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);

});
  
int main(void){
js_main();
gpmain();
return 0;

}
