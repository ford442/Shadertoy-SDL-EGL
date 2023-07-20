#include "../../include/vanilla/main_webgpu.h"

WGpuAdapter adapter;
WGpuCanvasContext canvasContext;
WGpuDevice device;
WGpuQueue queue;
WGpuRenderPipeline renderPipeline;

EM_BOOL raf(double time, void *userData){
WGpuCommandEncoder encoder=wgpu_device_create_command_encoder(device,0);
//colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(canvasContext),0);
WGpuRenderPassColorAttachment colorAttachment={wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(canvasContext),0),NULL,WGPU_STORE_OP_STORE,WGPU_LOAD_OP_LOAD};
WGpuRenderPassDescriptor passDesc={1,&colorAttachment};
WGpuRenderPassEncoder pass=wgpu_command_encoder_begin_render_pass(encoder,&passDesc);
wgpu_render_pass_encoder_set_pipeline(pass,renderPipeline);
wgpu_render_pass_encoder_draw(pass,3,1,0,0);
wgpu_render_pass_encoder_end(pass);
WGpuCommandBuffer commandBuffer=wgpu_command_encoder_finish(encoder);
wgpu_queue_submit_one_and_destroy(queue,commandBuffer);
return EM_FALSE;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result, void *userData){
device=result;
queue=wgpu_device_get_queue(device);
canvasContext=wgpu_canvas_get_webgpu_context("canvas");
WGpuCanvasConfiguration config={};
config.format=23;
wgpu_canvas_context_configure(canvasContext,&config);
const char *vertexShader=
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

WGpuShaderModuleDescriptor shaderModuleDesc={};
shaderModuleDesc.code=vertexShader;
WGpuShaderModule vs=wgpu_device_create_shader_module(device,&shaderModuleDesc);
shaderModuleDesc.code=fragmentShader;
WGpuShaderModule fs=wgpu_device_create_shader_module(device,&shaderModuleDesc);
WGpuRenderPipelineDescriptor renderPipelineDesc={};
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.fragment.module=fs;
renderPipelineDesc.fragment.entryPoint="main";
renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
WGpuColorTargetState colorTarget={23};
renderPipelineDesc.fragment.numTargets=1;
renderPipelineDesc.fragment.targets=&colorTarget;
    
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

function strr(){
Module.ccall("runWebGPU",{async:true});
}

function myStopFunction(){
clearInterval(myInterval);
}

function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
    Module.ccall("startWebGPU",{async:true});

// const myInterval=setInterval(strr,1000);
},100);
}

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
document.getElementById('canvas').height=parseInt(window.innerHeight,10);
document.getElementById('canvas').width=parseInt(window.innerHeight,10);

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

document.getElementById('startBtn2').addEventListener('click',function(){
// myStopFunction();
// Module.ccall("runWebGPU",{async:true});
strr();
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

void runWebGPU(){
// WGPU_Run();
}

void runWebGPU2(){
// WGPU_Run2();
}

}

int main(void){
js_main();
// sleep(1);
// WGPU_Start();
return 0;
}
