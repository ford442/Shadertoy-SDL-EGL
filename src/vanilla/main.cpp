#include "../../include/vanilla/main.hpp"


int main() {
state.canvas.name = "canvas";
state.wgpu.device = emscripten_webgpu_get_device();
state.wgpu.queue = wgpuDeviceGetQueue(state.wgpu.device);

resize(0, NULL, NULL); // set size and create swapchain
emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, false, resize);
WGPUShaderModule shader_triangle = create_shader(wgsl_triangle, NULL);

WGPUVertexAttribute vertex_attrib[2] = {
[0] = {
.format = WGPUVertexFormat_Float32x2,
.offset = 0,
.shaderLocation = 0,
},
[1] = {
.format = WGPUVertexFormat_Float32x3,
.offset = 2 * sizeof(float),
.shaderLocation = 1,
}
};
WGPUVertexBufferLayout vertex_buffer_layout = {
.arrayStride = 5 * sizeof(float),
.attributeCount = 2,
.attributes = vertex_attrib,
};
    
WGPUBindGroupLayoutDescriptor BindGroupLayoutDescriptor;
WGPUPipelineLayoutDescriptor PipelineLayoutDescriptor;
WGPURenderPipelineDescriptor RenderPipelineDescriptor;
WGPUBindGroupLayoutEntry BindGroupLayoutEntry;
        
WGPUBindGroupLayout bindgroup_layout = wgpuDeviceCreateBindGroupLayout(state.wgpu.device, &BindGroupLayoutDescriptor{
.entryCount = 1,
.entries = &BindGroupLayoutEntry{
.binding = 0,
.visibility = WGPUShaderStage_Vertex,
.buffer = {
.type = WGPUBufferBindingType_Uniform,
}
},
});
WGPUPipelineLayout pipeline_layout = wgpuDeviceCreatePipelineLayout(state.wgpu.device, &PipelineLayoutDescriptor{
.bindGroupLayoutCount = 1,
.bindGroupLayouts = &bindgroup_layout,
});

WGPUFragmentState FragmentState;
WGPUColorTargetState ColorTargetState;
WGPUBlendState BlendState;
WGPUBindGroupEntry BindGroupEntry;

state.wgpu.pipeline = wgpuDeviceCreateRenderPipeline(state.wgpu.device, &RenderPipelineDescriptor{
.layout = pipeline_layout,
.vertex = {
.module = shader_triangle,
.entryPoint = "vs_main",
.bufferCount = 1,
.buffers = &vertex_buffer_layout,
},
.primitive = {
.frontFace = WGPUFrontFace_CCW,
.cullMode = WGPUCullMode_None,
.topology = WGPUPrimitiveTopology_TriangleList,
.stripIndexFormat = WGPUIndexFormat_Undefined,
},
.fragment = &FragmentState{
.module = shader_triangle,
.entryPoint = "fs_main",
.targetCount = 1,
.targets = &ColorTargetState{
.format = WGPUTextureFormat_BGRA8Unorm,
.writeMask = WGPUColorWriteMask_All,
.blend = &BlendState{
.color = {
.operation = WGPUBlendOperation_Add,
.srcFactor = WGPUBlendFactor_One,
.dstFactor = WGPUBlendFactor_One,
},
.alpha = {
.operation = WGPUBlendOperation_Add,
.srcFactor = WGPUBlendFactor_One,
.dstFactor = WGPUBlendFactor_One,
},
},
},
},
.multisample = {
.count = 1,
.mask = 0xFFFFFFFF,
.alphaToCoverageEnabled = false,
},
.depthStencil = NULL,
});

wgpuBindGroupLayoutRelease(bindgroup_layout);
wgpuPipelineLayoutRelease(pipeline_layout);
wgpuShaderModuleRelease(shader_triangle);

float const vertex_data[] = {
       -0.5f, -0.5f,     1.0f, 0.0f, 0.0f, // bottom-left
        0.5f, -0.5f,     0.0f, 1.0f, 0.0f, // bottom-right
        0.5f,  0.5f,     0.0f, 0.0f, 1.0f, // top-right
       -0.5f,  0.5f,     1.0f, 1.0f, 0.0f, // top-left
};
uint16_t index_data[] = {
        0, 1, 2,
        0, 2, 3,
};
state.res.vbuffer = create_buffer(vertex_data, sizeof(vertex_data), WGPUBufferUsage_Vertex);
state.res.ibuffer = create_buffer(index_data, sizeof(index_data), WGPUBufferUsage_Index);
    
state.res.ubuffer = create_buffer(&state.var.rot, sizeof(state.var.rot), WGPUBufferUsage_Uniform);
state.res.bindgroup = wgpuDeviceCreateBindGroup(state.wgpu.device, &(WGPUBindGroupDescriptor){
.layout = wgpuRenderPipelineGetBindGroupLayout(state.wgpu.pipeline, 0),
.entryCount = 1,
.entries = &BindGroupEntry{
.binding = 0,
.offset = 0,
.buffer = state.res.ubuffer,
.size = sizeof(state.var.rot),
},
});

emscripten_set_main_loop(draw, 0, 1);

wgpuRenderPipelineRelease(state.wgpu.pipeline);
wgpuSwapChainRelease(state.wgpu.swapchain);
wgpuQueueRelease(state.wgpu.queue);
wgpuDeviceRelease(state.wgpu.device);

return 0;
}
WGPURenderPassDescriptor RenderPassDescriptor;
WGPURenderPassColorAttachment RenderPassColorAttachment;

void draw() {
state.var.rot += 0.1f;
state.var.rot = state.var.rot >= 360.f ? 0.0f : state.var.rot;
wgpuQueueWriteBuffer(state.wgpu.queue, state.res.ubuffer, 0, &state.var.rot, sizeof(state.var.rot));

WGPUTextureView back_buffer = wgpuSwapChainGetCurrentTextureView(state.wgpu.swapchain);

WGPUCommandEncoder cmd_encoder = wgpuDeviceCreateCommandEncoder(state.wgpu.device, NULL);

WGPURenderPassEncoder render_pass = wgpuCommandEncoderBeginRenderPass(cmd_encoder, &RenderPassDescriptor{
.colorAttachmentCount = 1,
.colorAttachments = &RenderPassColorAttachment{
.view = back_buffer,
.loadOp = WGPULoadOp_Clear,
.storeOp = WGPUStoreOp_Store,
.clearValue = (WGPUColor){ 0.2f, 0.2f, 0.3f, 1.0f }
},
});

wgpuRenderPassEncoderSetPipeline(render_pass, state.wgpu.pipeline);
wgpuRenderPassEncoderSetBindGroup(render_pass, 0, state.res.bindgroup, 0, 0);
wgpuRenderPassEncoderSetVertexBuffer(render_pass, 0, state.res.vbuffer, 0, WGPU_WHOLE_SIZE);
wgpuRenderPassEncoderSetIndexBuffer(render_pass, state.res.ibuffer, WGPUIndexFormat_Uint16, 0, WGPU_WHOLE_SIZE);
wgpuRenderPassEncoderDrawIndexed(render_pass, 6, 1, 0, 0, 0);

wgpuRenderPassEncoderEnd(render_pass);

WGPUCommandBuffer cmd_buffer = wgpuCommandEncoderFinish(cmd_encoder, NULL); // after 'end render pass'

wgpuQueueSubmit(state.wgpu.queue, 1, &cmd_buffer);

wgpuRenderPassEncoderRelease(render_pass);
wgpuCommandEncoderRelease(cmd_encoder);
wgpuCommandBufferRelease(cmd_buffer);
wgpuTextureViewRelease(back_buffer);
}

int resize(int event_type, const EmscriptenUiEvent* ui_event, void* user_data) {
(void)event_type, (void)ui_event, (void)user_data; // unused

double w, h;
emscripten_get_element_css_size(state.canvas.name, &w, &h);

state.canvas.width = (int)w;
state.canvas.height = (int)h;
emscripten_set_canvas_element_size(state.canvas.name, state.canvas.width, state.canvas.height);

if (state.wgpu.swapchain) {
wgpuSwapChainRelease(state.wgpu.swapchain);
state.wgpu.swapchain = NULL;
}
state.wgpu.swapchain = create_swapchain();
return 1;
}

WGPUSwapChain create_swapchain() {
WGPUSurface surface = wgpuInstanceCreateSurface(NULL, &(WGPUSurfaceDescriptor){
.nextInChain = (WGPUChainedStruct*)(&(WGPUSurfaceDescriptorFromCanvasHTMLSelector){
.chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector,
.selector = state.canvas.name,
})
});

return wgpuDeviceCreateSwapChain(state.wgpu.device, surface, &(WGPUSwapChainDescriptor){
.usage = WGPUTextureUsage_RenderAttachment,
.format = WGPUTextureFormat_BGRA8Unorm,
.width = state.canvas.width,
.height = state.canvas.height,
.presentMode = WGPUPresentMode_Fifo,
});
}

WGPUShaderModule create_shader(const char* code, const char* label) {
WGPUShaderModuleWGSLDescriptor wgsl = {
.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor,
.source = code,
};

return wgpuDeviceCreateShaderModule(state.wgpu.device, &(WGPUShaderModuleDescriptor){
.nextInChain = (WGPUChainedStruct*)(&wgsl),
.label = label,
});
}

WGPUBuffer create_buffer(const void* data, size_t size, WGPUBufferUsage usage) {
WGPUBuffer buffer = wgpuDeviceCreateBuffer(state.wgpu.device, &(WGPUBufferDescriptor){
.usage = WGPUBufferUsage_CopyDst | usage,
.size = size,
});
wgpuQueueWriteBuffer(state.wgpu.queue, buffer, 0, data, size);
return buffer;
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
return 0;

}
