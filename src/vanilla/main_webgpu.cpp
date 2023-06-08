#include "../../include/vanilla/main_webgpu.h"

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

float bufferSize=64*sizeof(float);

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
"outputBuffer[0] = inputBuffer[0];"
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
input[i]=42.42;
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
uint32_t workgroupSize=1;
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
std::cout << "wgpu_buffer_read_mapped_range" << std::endl;
double output=wgpu_buffer_get_mapped_range(mapBuffer,uint32_t(0),bufferSize);
std::cout << "output var:" << output << std::endl;
std::cout << "output var:" << &output << std::endl;
std::vector<double>outputd(bufferSize/sizeof(double));
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
init4();
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
Module.ccall('wgpu_init1',{async:true});
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
sleep(1);
js_main();
sleep(1);
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
navigator_gpu_request_adapter_async(&options,ObtainedWebGpuAdapter,0);
return 0;
}
