#include "../../include/video/video_jebus.hpp"

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <SDL2/SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1

#include <GLES3/gl31.h>
// #include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3platform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
// #include <EGL/eglplatform.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <emscripten/html5_webgl.h>

void avgFrm(int Fnum,int leng,float *ptr,float *aptr){
float max=0.0f;
float min=1.0f;
float sum=0.0f;
float avgSum=0.0f;
float minSum=0.0f;
float maxSum=0.0f;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
}
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
}
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
}
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
}
aptr[200]=maxSum/32;
return;
}

extern "C" {

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}

}

extern "C" {

EM_JS(void,ma,(),{
"use strict";
const pnnl=document.body;
let vv=document.querySelector("#mv");
let intervalBackward;

function back(){
intervalBackward=setInterval(function(){
if(vv.currentTime==0){
clearInterval(intervalBackward);
}else{
vv.currentTime+=-0.032;
}
},16);
};

let intervalForward;

function forward(){
intervalForward=setInterval(function(){
vv.currentTime+=-0.032;
},16);
};

let intervalLoop;
let stp,a,b,f;

function backForth(stp){
a=stp/1000.0;
b=(stp/1000.0)+3.0;
f=true;
intervalLoop=setInterval(function(){
if(f==true){
if(vv.currentTime>a){
vv.currentTime+=-0.016;
}else{
f=false;
}}else if(vv.currentTime<b){
vv.currentTime+=0.016;
}else{
f=true;
}
},16.66);
};

function stpForward(){
clearInterval(intervalForward);
}

function stpBack(){
clearInterval(intervalBackward);
}

function stpBackForth(){
clearInterval(intervalLoop);
}

let Mov=1;

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
if(Mov==1){vv=document.querySelector("#mv");Mov=0;vv.pause();}
else if(Mov==0){vv=document.querySelector("#mv");Mov=1;vv.play();}
}
if (e.code=='KeyW'){vv=document.querySelector("#mv");Mov=1;vv.pause();forward();}
if (e.code=='KeyS'){vv=document.querySelector("#mv");Mov=1;vv.pause();back();}
if (e.code=='KeyZ'){vv=document.querySelector("#mv");Mov=1;vv.pause();var stp=vv.currentTime*1000.0;
backForth(stp);}
if (e.code=='KeyX'){vv=document.querySelector("#mv");stpBackForth();vv.play();}
}

function doKeyUp(e){
if (e.code=='KeyS'){Mov=0;stpBack();vv.pause();}
if (e.code=='KeyW'){Mov=0;stpForward();vv.pause();}
}

pnnl.addEventListener('keydown',doKey);
pnnl.addEventListener('keydown',doKeyUp);
let w$=parseInt(document.querySelector("#wid").innerHTML,10);
let h$=parseInt(document.querySelector("#hig").innerHTML,10);
let blank$$=parseInt(document.querySelector("#blnnk").innerHTML,10);
let ch$=parseInt(window.innerHeight,10);
vv=document.querySelector("#mv");
let $H=Module.HEAPF32.buffer;

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}
}

let la=nearestPowerOf2((((h$+(blank$$*2))*h$*4)/4)*4);
let pointa=77*la;
let agav=new Float32Array($H,pointa,300);
let sz=(h$*h$)/8;
let blank$=Math.max((w$-h$)/4,0);
let nblank$=Math.max((h$-w$)/2,0);
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.querySelector("#bcanvas");
const contx=bcanvas.getContext("webgl2",{colorType:'float32',precision:'highp',colorSpace:'display-p3',alpha:true,depth:true,stencil:true,preserveDrawingBuffer:true,premultipliedAlpha:false,desynchronized:false,lowLatency:false,powerPreference:'high-performance',antialias:true,willReadFrequently:false});
contx.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
contx.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
contx.getExtension('ARB_robust_buffer_access_behavior');
// contx.getExtension('ARB_ES3_compatibility');
// contx.getExtension('GL_EXTENSIONS');
contx.getExtension('GL_ALL_EXTENSIONS');
// contx.getExtension('KHR_no_error');
// contx.getExtension('GL_REGAL_enable');
// contx.getExtension('OES_fragment_precision_high'); // deprecated
contx.getExtension('EGL_EXT_client_extensions');
contx.getExtension('EGL_ANGLE_platform_angle');
contx.getExtension('EXT_color_buffer_float'); // GLES float
contx.getExtension('EXT_color_buffer_half_float'); // GLES half-float
contx.getExtension('EXT_float_blend'); // GLES float
contx.getExtension('OES_blend_equation_separate');
contx.getExtension('OES_blend_func_separate');
contx.getExtension('OES_blend_subtract');
// contx.getExtension('ARB_texture_float'); // OpenGL 1.5/2.0
contx.getExtension('OES_texture_float');
// contx.getExtension('ARB_compatibility');
// contx.getExtension('ARB_texture_half_float'); // OpenGL 1.5/2.0
contx.getExtension('OES_texture_half_float');
contx.getExtension('OES_element_index_uint');
contx.getExtension('OES_shader_multisample_interpolation');
contx.getExtension('ARB_framebuffer_object');
contx.getExtension('ARB_framebuffer_sRGB');
contx.getExtension('NV_half_float');
contx.getExtension('ARB_fragment_program');
contx.getExtension('NV_fragment_program_option');
contx.getExtension('NV_fragment_program');
contx.getExtension('NV_fragment_program2');
contx.getExtension('NV_float_buffer');
contx.getExtension('ARB_gl_spirv');
contx.getExtension('ARB_spirv_extensions');
contx.getExtension('EXT_polygon_offset_clamp');
contx.getExtension('ARB_shader_atomic_counters');
contx.getExtension('ARB_shader_atomic_counter_ops');
contx.getExtension('EGL_NV_coverage_sample');
contx.getExtension('EGL_NV_coverage_sample_resolve');
contx.getExtension('EGL_NV_quadruple_buffer');
contx.getExtension('ARB_depth_buffer_float');
contx.getExtension('NV_depth_buffer_float');
// contx.getExtension('ARB_color_buffer_float'); // non-ES
// contx.getExtension('ARB_color_buffer_half_float'); // non-ES
contx.getExtension('OES_sample_shading');
contx.getExtension('OES_sample_variables');
contx.getExtension('OES_get_program_binary');
contx.getExtension('OES_texture_external');
contx.getExtension('OES_vertex_half_float');
contx.getExtension('EGL_IMG_context_priority');
contx.getExtension('EXT_texture_filter_anisotropic');
contx.getExtension('EGL_NV_context_priority_realtime');
contx.getExtension('EGL_NV_depth_nonlinear');
contx.getExtension('EGL_HI_colorformats');
contx.getExtension('EGL_EXT_pixel_format_float');
contx.getExtension('EGL_KHR_gl_colorspace');
contx.getExtension('EGL_KHR_create_context');
// contx.getExtension('ARB_robustness'); // OpenGL 1.1
// contx.getExtension('KHR_robustness'); // upgraded by gl4.5 to es31
// contx.getExtension('EXT_robustness'); // old GLES 1.1/2.0
contx.getExtension('EGL_EXT_create_context_robustness');
contx.getExtension('EGL_EXT_gl_colorspace_scrgb');
contx.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// contx.getExtension('EGL_EXT_gl_colorspace_bt2020_pq');
// contx.getExtension('EGL_EXT_gl_colorspace_display_p3');
// contx.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// contx.getExtension('EXT_gl_colorspace_display_p3_passthrough');
// contx.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
contx.getExtension('NV_gpu_shader4');
contx.getExtension('NV_gpu_shader5');
contx.getExtension('NV_vertex_buffer_unified_memory');
contx.getExtension('NV_gpu_program5');
contx.getExtension('NV_vertex_attrib_integer_64bit');
contx.getExtension('ARB_gpu_shader_fp64');
contx.getExtension('EXT_vertex_attrib_64bit');
contx.getExtension('EXT_sRGB_write_control');
// contx.getExtension('EXT_multisample_compatibility');
contx.getExtension('NV_framebuffer_multisample');
contx.getExtension('ARB_enhanced_layouts');
contx.getExtension('ARB_shading_language_420pack');
// contx.getExtension('ARB_get_program_binary'); // OpenGL 3.0 / 3.2 compat
contx.getExtension('ARB_shader_atomic_counters');
contx.getExtension('EXT_bindable_uniform');
// contx.getExtension('EXT_geometry_shader4');
// contx.getExtension('ARB_ES2_compatibility'); // limits to OpenGL ES 2.0?
contx.getExtension('ARB_direct_state_access');
contx.getExtension('ARB_multitexture');
// contx.getExtension('KHR_color_buffer_half_float');
contx.getExtension('EXT_texture_norm16');
contx.getExtension('EGL_ANGLE_create_context_extensions_enabled');
contx.getExtension('EGL_ANGLE_d3d_texture_client_buffer');
contx.getExtension('EGL_ANGLE_direct3d_display');
// contx.getExtension('EGL_ANGLE_robust_resource_initialization');
contx.getExtension('EGL_KHR_create_context_no_error');
contx.getExtension('EGL_ANGLE_program_cache_control');
contx.getExtension('EGL_ANGLE_create_context_client_arrays');
contx.getExtension('EGL_CHROMIUM_create_context_bind_generates_resource');
contx.getExtension('WEBGL_multi_draw');
// contx.getExtension('WEBGL_color_buffer_float');
contx.getExtension('WEBGL_render_shared_exponent');
contx.getExtension('EGL_EXT_device_base');
contx.getExtension('EGL_EXT_device_query');
contx.getExtension('EGL_EXT_output_base');
contx.getExtension('EGL_EXT_platform_base');
contx.getExtension('EGL_EXT_platform_device');
contx.getExtension('EGL_EXT_swap_buffers_with_damage');
contx.getExtension('EGL_NV_cuda_event');
contx.getExtension('EGL_NV_device_cuda');
// contx.getExtension('EGL_NV_robustness_video_memory_purge');
contx.getExtension('ARB_texture_view');
contx.getExtension('EXT_float_32_packed_float');
contx.getExtension('EGL_KHR_wait_sync');
contx.getExtension('EGL_ANDROID_image_native_buffer');
contx.getExtension('EGL_ANDROID_recordable');
contx.getExtension('EGL_ANDROID_framebuffer_target');
contx.getExtension('EGL_ANDROID_blob_cache');
contx.getExtension('EGL_KHR_fence_sync');
contx.getExtension('EGL_ANDROID_native_fence_sync');
contx.getExtension('EGL_KHR_image');
// contx.getExtension('EGL_KHR_image_base');
contx.getExtension('OES_EGL_image_external');
contx.getExtension('OES_EGL_image_external_essl3');
contx.getExtension('EXT_YUV_target');
// contx.getExtension('ARB_texture_rgb10_a2ui');
// contx.getExtension('ARB_texture_multisample');
contx.getExtension('EGL_EXT_surface_SMPTE2086_metadata');
//  contx.getExtension('ARB_texture_storage'); //  NEW 4.2??
contx.getExtension('ARB_multisample_texture');
contx.getExtension('ARB_texture_cube_map_array');
contx.getExtension('ARB_texture_buffer_object');
contx.getExtension('ARB_texture_view');
contx.getExtension('ARB_shader_storage_buffer_object');
contx.getExtension('ARB_compute_shader');
contx.getExtension('ARB_tessellation_shader');
contx.getExtension('ARB_draw_elements_base_vertex');
contx.getExtension('ARB_provoking_vertex');
contx.getExtension('ARB_seamless_cube_map_per_texture');
contx.getExtension('ARB_texture_compression_rgtc');
contx.getExtension('ARB_texture_compression_bptc');
contx.getExtension('ARB_texture_compression_astc');
contx.getExtension('ARB_texture_filter_minmax');
contx.getExtension('ARB_depth_texture');
//  contx.getExtension('ARB_multisample'); // OLD 2001!!
contx.getExtension('ARB_framebuffer_multisample');
//  contx.getExtension('ARB_shader_objects'); // OLD 2004!!
contx.getExtension('OES_vertex_array_object');
contx.getExtension('WEBGL_compressed_texture_s3tc');
contx.getExtension('WEBGL_compressed_texture_etc');
contx.getExtension('EXT_blend_func_extended');
contx.getExtension('EGL_KHR_swap_behavior');
contx.getExtension('EXT_sRGB');
contx.getExtension('EXT_texture_sRGB');
contx.getExtension('ARB_buffer_storage');
contx.getExtension('ARB_enhanced_multisample_interpolation');
contx.getExtension('ARB_texture_storage_multisample');
contx.getExtension('EXT_texture_lod_bias');
contx.getExtension('ARB_shader_image_load_store');
contx.getExtension('ARB_shader_bit_arithmetic');
contx.getExtension('ARB_shader_texture_adodge');
contx.getExtension('ARB_shader_texture_lod');
contx.getExtension('ARB_shader_subroutine');
contx.getExtension('EGL_EXT_buffer_age');
contx.getExtension('EGL_EXT_multisample_swap_control');
contx.getExtension('EGL_EXT_texture_format_2D_lock');
contx.getExtension('EGL_EXT_texture_share_group');
contx.getExtension('EGL_EXT_texture_surface');
contx.getExtension('ARB_texture_filter_minmax_hq');
contx.getExtension('EXT_texture_compression_astc');
contx.getExtension('ARB_texture_gather');
contx.getExtension('EXT_texture_buffer');
contx.getExtension('EGL_EXT_swap_request');
contx.getExtension('EGL_EXT_image_transform');
contx.getExtension('EGL_EXT_surface_orientation');
contx.getExtension('EGL_EXT_surface_pixel_format_float');
contx.getExtension('EGL_EXT_create_surface_with_modifiers');
contx.getExtension('ARB_pipeline_statistics_query');
contx.getExtension('ARB_occlusion_query2');
contx.getExtension('ARB_timer_query');
contx.getExtension('ARB_transform_feedback3');
contx.getExtension('EXT_shader_framebuffer_fetch_nonms');
contx.getExtension('EGL_EXT_swap_buffers_with_damage');
contx.getExtension('EGL_EXT_create_context_with_modifiers');
contx.getExtension('EGL_EXT_request_priority');
contx.getExtension('EGL_EXT_create_surface_from_window');
contx.getExtension('EGL_EXT_surface_attachment');
contx.getExtension('EXT_texture_storage');

contx.disable(gl.DITHER);
// contx.drawingBufferColorMetadata={mode:'extended'};
// contx.drawingBufferColorSpace='display-p3';

const g=new GPUX({canvas:bcanvas,webGl:contx});
const g2=new GPUX();
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslSilver=`float Silver(float a){return((a+0.75+0.75+((a+0.75)/2.0))/4.0);}`;
const glslGoldR=`float GoldR(float a){return((a+0.831+0.831+0.831+((a+0.831)/2.0))/5.0);}`;
const glslGoldG=`float GoldG(float a){return((a+0.686+0.686+0.686+((a+0.686)/2.0))/5.0);}`;
const glslGoldB=`float GoldB(float a){return((a+0.215+0.215+0.215+((a+0.215)/2.0))/5.0);}`;

// const glslAlphe1=`float AlpheV1(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
const glslAlphe1=`float AlpheV1(float a,float b,float c,float d,float e,float f,float g){return((g+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/4.0);}`;
  
const glslAlphe2=`float AlpheV2(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;

g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('AlpheV2',glslAlphe2,{returnType:'Number'});
g.addNativeFunction('AlpheV1',glslAlphe1,{returnType:'Number'});
g.addNativeFunction('Silver',glslSilver,{returnType:'Number'});
g.addNativeFunction('GoldR',glslGoldR,{returnType:'Number'});
g.addNativeFunction('GoldG',glslGoldG,{returnType:'Number'});
g.addNativeFunction('GoldB',glslGoldB,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});

let R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setOptimizeFloatMemory(true).setOutput([sz]).setStrictIntegers(false).setFixIntegerDivisionAccuracy(false);

let t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([h$+(blank$$),h$]).setStrictIntegers(false).setFixIntegerDivisionAccuracy(false);

let tt=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x];
return[P[0],P[1],P[2],P[3]];
}).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([h$,h$]).setStrictIntegers(false).setFixIntegerDivisionAccuracy(false);

let r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=AlpheV1($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
//  var alph=AlpheV2($amax,$amin,$aavg,p[3]);
var Min=4.0*(($amax-($favg-$amin))/2.0);
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([h$,h$]).setStrictIntegers(false).setFixIntegerDivisionAccuracy(false);

w$=parseInt(document.querySelector("#wid").innerHTML,10);
h$=parseInt(document.querySelector("#hig").innerHTML,10);
blank$$=parseInt(document.querySelector("#blnnk").innerHTML,10);
vv=document.querySelector("#mv");
blank$=Math.max((w$-h$)/4,0);
nblank$=Math.max((h$-w$)/2,0);
la=nearestPowerOf2((((h$+(blank$$*2))*h$*4)/4)*4);
sz=(h$*h$)/8;
pointa=77*la;
// agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$$});
var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
eval("$"+j+".set($$1);");
}
var d=S();if(d)d();d=S();function S(){
w$=parseInt(document.querySelector("#wid").innerHTML,10);
h$=parseInt(document.querySelector("#hig").innerHTML,10);
blank$$=parseInt(document.querySelector("#blnnk").innerHTML,10);
blank$=Math.max((w$-h$)/4,0);
nblank$=Math.max((h$-w$)/2,0);
la=nearestPowerOf2((((h$+(blank$$*2))*h$*4)/4)*4);
sz=(h$*h$)/8;
pointa=77*la;
// var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$$});
var T=false;
function M(){
vv=document.querySelector("#mv");
r.setConstants({nblnk:nblank$,blnk:blank$$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$$});
  if(T){return;}
for(i=64;i>0;i--){
var loca=$F+1;if(loca>64){loca=1;}
var locb=$Bu+1;if(locb>64){locb=1;}
eval("if ($F==="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
}
var $bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
setTimeout(function(){
M();
},16.66);
}
M();
document.querySelector("#di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}
})

}

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);
static const char8_t *read_file(const char *filename);
  
extern "C" {

SDL_AudioDeviceID dev;
struct{Uint8* snd;int pos;Uint32 slen;SDL_AudioSpec spec;}wave;

void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
return;
}}

void qu(int rc){
SDL_Quit();
return;
}

void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
}

void SDLCALL bfr(void *unused,Uint8* stm,int len){
Uint8* wptr;
int lft;
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while (lft<=len){
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
}

void plt(){
char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
return;
}

}


GLfloat x;
GLfloat y;
EM_BOOL ms_l;

void uni(float xx,float yy,GLfloat time,EGLint fram);
GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources);

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 0;
}

using namespace std;
using namespace std::chrono;

steady_clock::time_point t1,t2;
GLuint uni_frm,uni_tme,uni_res,shader;
double Ttime;
EGLint iFrame;
GLsizei s4=4;
// int v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v10=10,v16=16,v24=24,v32=32,v64=64;
int a,b;
float F=1.0;
float F0=0.0;
float Fm1=-1.0;
float mouseX;
float mouseY;
float cMouseX;
float cMouseY;
int Size;
GLfloat S;
EM_BOOL clk_l;
GLsizei i;
struct timespec rem;
struct timespec req={0,16666000};
GLuint uni_mse;

void uni(float xx,float yy,GLfloat time,EGLint fram){
GLfloat mX,mY;
if(ms_l==true){
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clk_l=false;
}
GLfloat mm=S*xx;
GLfloat nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,time);
glUniform1i(uni_frm,fram);
return;
}

const char *sources[4];
GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

void renderFrame(){
EMSCRIPTEN_RESULT ret;
t2=steady_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,indc);
glFlush();
// nanosleep(&req,&rem);
iFrame++;
glFinish();
return;
}

static const char8_t *read_file(const char *filename){
char8_t *result=NULL;
long length=0;
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
}
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return nullptr;
}

GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;i++){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

void strt(){
emscripten_cancel_main_loop();
// nanosleep(&req,&rem);
const char *fileloc="/shader/shader1.toy";
EGLint v0=0,v3=3;
GLfloat gF=F;
GLfloat gF0=F0;
GLfloat gFm1=Fm1;
  
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};

const char common_shader_header_gles3[]=
"#version 300 es\n"
"#pragma STDGL(precision highp double)\n"
"#pragma STDGL(precision highp uint)\n"
"#pragma STDGL(precision highp atomic_uint)\n"
// "#pragma STDGL(precise none)\n"
// "#pragma STDGL(strict off)\n"
"#pragma STDGL(invariant all)\n"
"#pragma STDGL(centroid all)\n"
"#pragma STDGL(sample all)\n"
"#pragma STDGL(fastmath on)\n"
"#pragma STDGL(fastprecision off)\n"
"#pragma STDGL(unroll all)\n"
// "#pragma STDGL(ifcvt none)\n"
"#pragma STDGL(inline none)\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 1\n"
"precision highp int;\n"
"precision highp float;\n"
"precision highp sampler3D;precision highp sampler2D;"
"precision highp samplerCube;precision highp sampler2DArray;precision highp sampler2DShadow;"
"precision highp isampler2D;precision highp isampler3D;precision highp isamplerCube;"
"precision highp isampler2DArray;precision highp usampler2D;precision highp usampler3D;"
"precision highp usamplerCube;precision highp usampler2DArray;precision highp samplerCubeShadow;"
"precision highp sampler2DArrayShadow;\n";
  
const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
  
const char fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution;uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"out vec4 fragColor;\n";
  
const char fragment_shader_footer_gles3[]=
"void main(){mainImage(fragColor,gl_FragCoord.xy);}\n"
"#define mainImage mainImage0(out dvec4 O,dvec2 U);"
"int _N=3;void mainImage(out dvec4 O,dvec2 U){"
"dvec4 o;O=dvec4(0);"
"mainImage0(o,U+dvec2(k%_N-_N/2,k/_N-_N/2)/double(_N));"
"O += o;}O /= double(_N*_N);O=pow(O,dvec4(2.077038f/1.0f,2.184228f/1.0f,2.449715f/1.0f,1.0f));}"
// "O += o;}O /= double(_N*_N);O=pow(O,dvec4(1.077038f/1.0,1.184228f/1.0,1.449715f/1.0,1.0));}"
"void mainImage0\n\0";
  
const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res;
GLuint VCO,ECO,vtx,frag;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EGLint config_size,major,minor,atb_pos;
iFrame=0;
clk_l=true;
// Size=EM_ASM_INT({return parseInt(window.innerHeight);});
double wi,hi;
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
// eglBindAPI(EGL_OPENGL_ES_API);
eglBindAPI(EGL_OPENGL_API);
  
const EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
  
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,4,
EGL_CONTEXT_MINOR_VERSION_KHR,6,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
  
const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,8,
EGL_GREEN_SIZE,8,
EGL_BLUE_SIZE,8,
EGL_ALPHA_SIZE,8,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,8,
EGL_BUFFER_SIZE,64,
EGL_SAMPLE_BUFFERS,16,
EGL_SAMPLES,16,
EGL_NONE
};
  
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_TRUE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
// emscripten_webgl_enable_extension(ctx,"WEBGL_compatibility"); // limits to WebGL 1.0
  /*
emscripten_webgl_enable_extension(ctx,"ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx,"ARB_ES3_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"GL_ALL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"KHR_no_error");
// emscripten_webgl_enable_extension(ctx,"GL_REGAL_enable");
// emscripten_webgl_enable_extension(ctx,"OES_fragment_precision_high"); // deprecated
emscripten_webgl_enable_extension(ctx,"EGL_EXT_client_extensions");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_platform_angle");
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float"); // GLES float
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_half_float"); // GLES half-float
emscripten_webgl_enable_extension(ctx,"EXT_float_blend"); // GLES float
emscripten_webgl_enable_extension(ctx,"OES_blend_equation_separate");
emscripten_webgl_enable_extension(ctx,"OES_blend_func_separate");
emscripten_webgl_enable_extension(ctx,"OES_blend_subtract");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_float"); // OpenGL 1.5/2.0
emscripten_webgl_enable_extension(ctx,"OES_texture_float");
emscripten_webgl_enable_extension(ctx,"ARB_compatibility");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_half_float"); // OpenGL 1.5/2.0
emscripten_webgl_enable_extension(ctx,"OES_texture_half_float");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"NV_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_fragment_program");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program_option");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program2");
emscripten_webgl_enable_extension(ctx,"NV_float_buffer");
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(ctx,"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(ctx,"ARB_depth_buffer_float");
emscripten_webgl_enable_extension(ctx,"NV_depth_buffer_float");
// emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float"); // non-ES
// emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_half_float"); // non-ES
emscripten_webgl_enable_extension(ctx,"OES_sample_shading");
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_get_program_binary");
emscripten_webgl_enable_extension(ctx,"OES_texture_external");
emscripten_webgl_enable_extension(ctx,"OES_vertex_half_float");
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_create_context");
// emscripten_webgl_enable_extension(ctx,"ARB_robustness"); // OpenGL 1.1
// emscripten_webgl_enable_extension(ctx,"KHR_robustness"); // upgraded by gl4.5 to es31
// emscripten_webgl_enable_extension(ctx,"EXT_robustness"); // old GLES 1.1/2.0
emscripten_webgl_enable_extension(ctx,"EGL_EXT_create_context_robustness");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3_passthrough");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"NV_gpu_shader4");
emscripten_webgl_enable_extension(ctx,"NV_gpu_shader5");
emscripten_webgl_enable_extension(ctx,"NV_vertex_buffer_unified_memory");
emscripten_webgl_enable_extension(ctx,"NV_gpu_program5");
emscripten_webgl_enable_extension(ctx,"NV_vertex_attrib_integer_64bit");
emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB_write_control");
// emscripten_webgl_enable_extension(ctx,"EXT_multisample_compatibility");
emscripten_webgl_enable_extension(ctx,"NV_framebuffer_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_enhanced_layouts");
emscripten_webgl_enable_extension(ctx,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx,"ARB_get_program_binary"); // OpenGL 3.0 / 3.2 compat
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"EXT_bindable_uniform");
// emscripten_webgl_enable_extension(ctx,"EXT_geometry_shader4");
// emscripten_webgl_enable_extension(ctx,"ARB_ES2_compatibility"); // limits to OpenGL ES 2.0?
emscripten_webgl_enable_extension(ctx,"ARB_direct_state_access");
emscripten_webgl_enable_extension(ctx,"ARB_multitexture");
// emscripten_webgl_enable_extension(ctx,"KHR_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"EXT_texture_norm16");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_create_context_extensions_enabled");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_d3d_texture_client_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_direct3d_display");
// emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_robust_resource_initialization");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_create_context_no_error");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_program_cache_control");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_create_context_client_arrays");
emscripten_webgl_enable_extension(ctx,"EGL_CHROMIUM_create_context_bind_generates_resource");
emscripten_webgl_enable_extension(ctx,"WEBGL_multi_draw");
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_render_shared_exponent");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_device_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_device_query");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_output_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_platform_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_platform_device");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_swap_buffers_with_damage");
emscripten_webgl_enable_extension(ctx,"EGL_NV_cuda_event");
emscripten_webgl_enable_extension(ctx,"EGL_NV_device_cuda");
// emscripten_webgl_enable_extension(ctx,"EGL_NV_robustness_video_memory_purge");
emscripten_webgl_enable_extension(ctx,"ARB_texture_view");
emscripten_webgl_enable_extension(ctx,"EXT_float_32_packed_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_wait_sync");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_image_native_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_recordable");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_framebuffer_target");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_blob_cache");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_fence_sync");
emscripten_webgl_enable_extension(ctx,"EGL_ANDROID_native_fence_sync");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_image");
// emscripten_webgl_enable_extension(ctx,"EGL_KHR_image_base");
emscripten_webgl_enable_extension(ctx,"OES_EGL_image_external");
emscripten_webgl_enable_extension(ctx,"OES_EGL_image_external_essl3");
emscripten_webgl_enable_extension(ctx,"EXT_YUV_target");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_rgb10_a2ui");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_multisample");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_surface_SMPTE2086_metadata");
//  emscripten_webgl_enable_extension(ctx,"ARB_texture_storage"); //  NEW 4.2??
emscripten_webgl_enable_extension(ctx,"ARB_multisample_texture");
emscripten_webgl_enable_extension(ctx,"ARB_texture_cube_map_array");
emscripten_webgl_enable_extension(ctx,"ARB_texture_buffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_texture_view");
emscripten_webgl_enable_extension(ctx,"ARB_shader_storage_buffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_compute_shader");
emscripten_webgl_enable_extension(ctx,"ARB_tessellation_shader");
emscripten_webgl_enable_extension(ctx,"ARB_draw_elements_base_vertex");
emscripten_webgl_enable_extension(ctx,"ARB_provoking_vertex");
emscripten_webgl_enable_extension(ctx,"ARB_seamless_cube_map_per_texture");
emscripten_webgl_enable_extension(ctx,"ARB_texture_compression_rgtc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_compression_bptc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_compression_astc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_filter_minmax");
emscripten_webgl_enable_extension(ctx,"ARB_depth_texture");
//  emscripten_webgl_enable_extension(ctx,"ARB_multisample"); // OLD 2001!!
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_multisample");
//  emscripten_webgl_enable_extension(ctx,"ARB_shader_objects"); // OLD 2004!!
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"WEBGL_compressed_texture_s3tc");
emscripten_webgl_enable_extension(ctx,"WEBGL_compressed_texture_etc");
emscripten_webgl_enable_extension(ctx,"EXT_blend_func_extended");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_swap_behavior");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB");
emscripten_webgl_enable_extension(ctx,"EXT_texture_sRGB");
emscripten_webgl_enable_extension(ctx,"ARB_buffer_storage");
emscripten_webgl_enable_extension(ctx,"ARB_enhanced_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"ARB_texture_storage_multisample");
emscripten_webgl_enable_extension(ctx,"EXT_texture_lod_bias");
emscripten_webgl_enable_extension(ctx,"ARB_shader_image_load_store");
emscripten_webgl_enable_extension(ctx,"ARB_shader_bit_arithmetic");
emscripten_webgl_enable_extension(ctx,"ARB_shader_texture_adodge");
emscripten_webgl_enable_extension(ctx,"ARB_shader_texture_lod");
emscripten_webgl_enable_extension(ctx,"ARB_shader_subroutine");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_buffer_age");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_multisample_swap_control");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_texture_format_2D_lock");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_texture_share_group");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_texture_surface");
emscripten_webgl_enable_extension(ctx,"ARB_texture_filter_minmax_hq");
emscripten_webgl_enable_extension(ctx,"EXT_texture_compression_astc");
emscripten_webgl_enable_extension(ctx,"ARB_texture_gather");
emscripten_webgl_enable_extension(ctx,"EXT_texture_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_swap_request");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_image_transform");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_surface_orientation");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_surface_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_create_surface_with_modifiers");
emscripten_webgl_enable_extension(ctx,"ARB_pipeline_statistics_query");
emscripten_webgl_enable_extension(ctx,"ARB_occlusion_query2");
emscripten_webgl_enable_extension(ctx,"ARB_timer_query");
emscripten_webgl_enable_extension(ctx,"ARB_transform_feedback3");
emscripten_webgl_enable_extension(ctx,"EXT_shader_framebuffer_fetch_nonms");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_swap_buffers_with_damage");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_create_context_with_modifiers");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_request_priority");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_create_surface_from_window");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_surface_attachment");
emscripten_webgl_enable_extension(ctx,"EXT_texture_storage");
*/
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
// glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
// glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
// glHint(GL_TEXTURE_COMPRESSION_HINT,GL_NICEST);
// glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
// nanosleep(&req,&rem);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
// nanosleep(&req,&rem);
static const char* default_fragment_shader=(char*)read_file(fileloc);
// nanosleep(&req,&rem);
// nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
// nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
// nanosleep(&req,&rem);
shd_prg=glCreateProgram();
// nanosleep(&req,&rem);
glAttachShader(shd_prg,vtx);
// nanosleep(&req,&rem);
glAttachShader(shd_prg,frag);
// nanosleep(&req,&rem);
atb_pos=0;
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
// nanosleep(&req,&rem);
glUseProgram(shd_prg);
// nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays(1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_TRUE,0,(GLvoid*)0);
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
glUniform3f(uni_res,S,S,1.0);
glUniform3f(smp_chn_res,S,S,1.0);
glClearColor(gF0,gF0,gF0,gF);
// glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
// glDisable(GL_BLEND);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_SCISSOR_TEST);
// glDepthFunc(GL_LESS);
// glFrontFace(GL_CW);
// glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
// glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_DITHER);
t1=steady_clock::now();
glViewport(0,0,GLint(Size),GLint(Size));
emscripten_set_main_loop((void(*)())renderFrame,0,0);
// emscripten_set_main_loop_timing(2,1);
return;
}

extern "C" {

void str(){
strt();
return;
}

void pl(){
plt();
return;
}

void b3(){
ma();
return;
}

}

int main(void){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
