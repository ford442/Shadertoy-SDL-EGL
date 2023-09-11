#include "../../include/vanilla/main_render.hpp"

WGpuAdapter adapter;
WGpuCanvasContext canvasContext;
WGpuDevice device;
WGpuQueue queue;
WGpuRenderPipeline renderPipeline;

EM_BOOL raf(double time, void *userData){
WGpuCommandEncoder encoder=wgpu_device_create_command_encoder(device,0);
// WGpuCommandEncoder encoder=wgpu_device_create_command_encoder_simple(device);
WGpuRenderPassColorAttachment colorAttachment={};
colorAttachment.view=wgpu_canvas_context_get_current_texture_view(canvasContext); 
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
colorAttachment.clearValue.r=1.0f;
colorAttachment.clearValue.g=0.0f;
colorAttachment.clearValue.b=1.0f;
colorAttachment.clearValue.a=1.0f;
WGpuRenderPassDescriptor passDesc={1,&colorAttachment};
WGpuRenderPassEncoder pass=wgpu_command_encoder_begin_render_pass(encoder,&passDesc);
wgpu_render_pass_encoder_set_pipeline(pass,renderPipeline);
wgpu_render_pass_encoder_set_viewport(pass, 0.0, 0.0, sze.at(0,0), sze.at(0,0), 0.0, 1.0);
wgpu_render_pass_encoder_draw(pass,3,1,0,0);
wgpu_render_pass_encoder_end(pass);
WGpuCommandBuffer commandBuffer=wgpu_command_encoder_finish(encoder);
wgpu_queue_submit_one(queue,commandBuffer);
return EM_FALSE;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result, void *userData){
emscripten_get_element_css_size("zcanvas",&szw,&szh);
sze.at(0,0)=float(szh);
device=result;
queue=wgpu_device_get_queue(device);
canvasContext=wgpu_canvas_get_webgpu_context("zcanvas");
WGpuCanvasConfiguration config={};
config.device = device;
config.usage = WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
config.format = navigator_gpu_get_preferred_canvas_format();
wgpu_canvas_context_configure(canvasContext, &config);

const char *vertexShader=
"@vertex\n"
"fn main_v(@builtin(vertex_index) vertexIndex : u32) -> @builtin(position) vec4<f32> {\n"
"var pos = array<vec2<f32>, 3>(\n"
"vec2<f32>(0.0,0.5),\n"
"vec2<f32>(-0.5,-0.5),\n"
"vec2<f32>(0.5,-0.5)\n"
");\n"
"return vec4<f32>(pos[vertexIndex],0.0,1.0);\n"
"}\n";
const char *fragmentShader=
"@fragment\n"
"fn main_f() -> @location(0) vec4<f32> {\n"
"return vec4<f32>(1.0,0.5,0.3,1.0);\n"
"}\n";

WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
shaderModuleDescV.code=vertexShader;
WGpuShaderModule vs=wgpu_device_create_shader_module(device,&shaderModuleDescV);
shaderModuleDescF.code=fragmentShader;
WGpuShaderModule fs=wgpu_device_create_shader_module(device,&shaderModuleDescF);
WGpuColorTargetState colorTarget={};
colorTarget.format=config.format;
WGpuVertexState vertState={};
vertState.module=fs;
vertState.entryPoint="main_v";
vertState.numBuffers=0;
vertState.buffers=nullptr;
vertState.numConstants = 0;
vertState.constants = nullptr;
WGpuPrimitiveState priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_NONE; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
WGpuFragmentState fragState={};
fragState.module=fs;
fragState.entryPoint="main_f";
fragState.numTargets=1;
fragState.targets=&colorTarget;
WGpuRenderPipelineDescriptor renderPipelineDesc={};
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.primitive=priState;
renderPipelineDesc.vertex.entryPoint="main_v";
renderPipelineDesc.fragment=fragState;
renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipeline=wgpu_device_create_render_pipeline(device,&renderPipelineDesc);
emscripten_request_animation_frame_loop(raf,0);
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
adapter=result;
WGpuDeviceDescriptor deviceDesc={};
wgpu_adapter_request_device_async(adapter,&deviceDesc,ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(){
WGpuRequestAdapterOptions options={};
options.powerPreference=WGPU_POWER_PREFERENCE_LOW_POWER;
navigator_gpu_request_adapter_async(&options,ObtainedWebGpuAdapterStart,0);
}

EM_JS(void,js_main,(),{
let winSize=parseInt(window.innerHeight,10);
const scanvas=document.createElement('canvas');
scanvas.id='zcanvas';
scanvas.imageRendering='pixelated';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='none';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='999995';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(0,0,0,255)';
document.getElementById("contain1").appendChild(scanvas);

const contxVars={
// colorType:'float32',
// precision:'highp',
preferLowPowerToHighPerformance:false,
alpha:true,
depth:false,
stencil:false,
// preserveDrawingBuffer:false,
premultipliedAlpha:false,
// imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:true,
powerPreference:'high-performance',
// antialias:false
};
const ctx=scanvas.getContext('webgl2',contxVars);
const gpu=new GPUX({mode:'gpu',webGl:ctx });

function normalResStart(){
setTimeout(function(){
  
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall("startWebGPU");
// const myInterval=setInterval(strr,1000);
},100);
document.getElementById('status').style.backgroundColor="green";
}

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
document.getElementById('canvas').height=parseInt(window.innerHeight,10);
document.getElementById('canvas').width=parseInt(window.innerHeight,10);
document.getElementById('status').height=20;
document.getElementById('status').width=parseInt(window.innerHeight,10);

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
},16);
});

document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});

setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);
});

extern"C"{

void startWebGPU(){
WGPU_Start();
}

}

int main(void){
js_main();
return 0;
}
