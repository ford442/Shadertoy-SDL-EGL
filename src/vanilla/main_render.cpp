#include "../../include/vanilla/main_render.hpp"

static f_tensor sze=f_tensor{2,2};
static wce_tensor wce=wce_tensor{2,2};
static wrpe_tensor wrpe=wrpe_tensor{2,2};
static wcb_tensor wcb=wcb_tensor{2,2};
static wd_tensor wd=wd_tensor{2,2};
static wq_tensor wq=wq_tensor{2,2};
static wa_tensor wa=wa_tensor{2,2};
static wcc_tensor wcc=wcc_tensor{2,2};
static wrp_tensor wrp=wrp_tensor{2,2};

EM_BOOL raf(double time, void *userData){
wce.at(0,0)=wgpu_device_create_command_encoder(wd.at(0,0),0);
colorAttachment=WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER;
colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(wcc.at(0,0)),0);
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.clearValue.r=1.0f;
colorAttachment.clearValue.g=0.0f;
colorAttachment.clearValue.b=1.0f;
colorAttachment.clearValue.a=1.0f;
passDesc={};
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&colorAttachment;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&passDesc);
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
emscripten_get_element_css_size("canvas",&szw,&szh);
sze.at(0,0)=float(szh);
sze.at(0,1)=float(szw);
// wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,sze.at(0,1),sze.at(0,0),0.0,1.0);
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,666,666,0.0,1.0);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),3,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
return EM_FALSE;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result, void *userData){
wd.at(0,0)=result;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
config=WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
config.device=wd.at(0,0);
config.format=navigator_gpu_get_preferred_canvas_format();
wgpu_canvas_context_configure(wcc.at(0,0),&config);

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
"return vec4<f32>(1.0, 0.0, 0.73, 1.0);\n"
"}\n";

multiSamp={};
multiSamp.count=4;
shaderModuleDescV={};
shaderModuleDescF={};
shaderModuleDescV.code=vertexShader;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=fragmentShader;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
WGpuColorTargetState colorTarget={};
colorTarget.format=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
colorTarget.writeMask=15;
vertState={};
vertState.module=fs;
vertState.entryPoint="main";
vertState.numBuffers=0;
vertState.buffers=nullptr;
vertState.numConstants=0;
vertState.constants=nullptr;
priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_NONE; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
fragState={};
fragState.module=fs;
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&colorTarget;
renderPipelineDesc={};
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.primitive=priState;
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.fragment=fragState;
renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc.multisample.count=multiSamp;
wrp.at(0,0)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc);
emscripten_request_animation_frame_loop(raf,0);
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
deviceDesc={};
wgpu_adapter_request_device_async(wa.at(0,0),&deviceDesc,ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(){
options={};
options.powerPreference=WGPU_POWER_PREFERENCE_LOW_POWER;
navigator_gpu_request_adapter_async(&options,ObtainedWebGpuAdapterStart,0);
}

EM_JS(void,js_main,(),{
function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall("startWebGPU");
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
