#pragma once
// #pragma pack(4)
// #pragma fenv_access(on)        // enable environment sensitivity
#include <boost/cstdfloat.hpp>  // must be first include

#include "../../include/shader/defs.hpp"
#include "../../include/shader/boost_defs.hpp"
#include "../../include/shader/intrins.hpp"
#include "../../include/shader/egl.hpp"

#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#define register

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include <boost/function.hpp>
#include "boost/tuple/tuple.hpp"
#include <random>
#include <cstdlib>
#include <emscripten.h>
#include <emscripten/html5.h>

using namespace ::boost::tuples;

extern "C"{

EM_JS(void,js_main,(),{
FS.mkdir('/shader');

window.scroll(0,0);
/*
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
const scanvas=document.createElement('canvas');
scanvas.id='mcanvas';
scanvas.imageRendering='auto';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='auto';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='1';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(255,255,255,0)';
document.getElementById("contain1").appendChild(scanvas);
const contxVars={preferLowPowerToHighPerformance:false,alpha:true,depth:true,stencil:false,lowLatency:false,powerPreference:'high-performance',antialias:true};
const context = scanvas.getContext('webgl2',contxVars);
// const gpu=new GPUX({mode:'gpu',webGl:context });
// context.disable(gl.DITHER);
// context.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
// context.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
context.getExtension('GL_EXTENSIONS');
context.getExtension('GL_ALL_EXTENSIONS');
context.getExtension('KHR_no_error');
context.getExtension('GL_REGAL_enable');
context.getExtension('EGL_EXT_client_extensions');
context.getExtension('EGL_ANGLE_platform_angle');
context.getExtension('ARB_spirv_extensions');
context.getExtension('EXT_color_buffer_float');
context.getExtension('ARB_sample_shading');
context.getExtension('ARB_framebuffer_object');
context.getExtension('ARB_framebuffer_sRGB');
context.getExtension('NV_half_float');
context.getExtension('OES_texture_half_float');
context.getExtension('ARB_fragment_program');
context.getExtension('NV_fragment_program_option');
context.getExtension('NV_fragment_program');
context.getExtension('NV_fragment_program2');
context.getExtension('NV_float_buffer');
context.getExtension('ARB_gl_spirv');
context.getExtension('ARB_spirv_extensions');
context.getExtension('EXT_polygon_offset_clamp');
context.getExtension('ARB_shader_atomic_counters');
context.getExtension('ARB_shader_atomic_counter_ops');
context.getExtension('EGL_NV_coverage_sample');
context.getExtension('EGL_NV_coverage_sample_resolve');
context.getExtension('EGL_NV_quadruple_buffer');
context.getExtension('NV_depth_buffer_float');
context.getExtension('ARB_color_buffer_float');
context.getExtension('ARB_color_buffer_half_float');
context.getExtension('ARB_texture_float');
context.getExtension('ARB_texture_half_float');
context.getExtension('EGL_IMG_context_priority');
context.getExtension('OES_element_index_uint');
context.getExtension('OES_sample_variables');
context.getExtension('OES_shader_multisample_interpolation');
context.getExtension('EXT_texture_filter_anisotropic');
context.getExtension('EGL_NV_context_priority_realtime');
context.getExtension('EGL_NV_depth_nonlinear');
context.getExtension('EGL_HI_colorformats');
context.getExtension('EGL_EXT_pixel_format_float');
context.getExtension('EGL_KHR_gl_colorspace');
context.getExtension('EGL_KHR_create_context');
context.getExtension('ARB_robustness');
context.getExtension('EGL_EXT_create_context_robustness');
context.getExtension('EGL_EXT_gl_colorspace_scrgb');
context.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// context.getExtension('EGL_EXT_gl_colorspace_bt2020_pq');
// context.getExtension('EGL_EXT_gl_colorspace_display_p3');
// context.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// context.getExtension('EXT_gl_colorspace_display_p3_passthrough');
// context.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
context.getExtension('OES_texture_float');
context.getExtension('NV_gpu_shader4');
context.getExtension('NV_gpu_shader5');
context.getExtension('NV_vertex_buffer_unified_memory');
context.getExtension('NV_gpu_program5');
context.getExtension('NV_vertex_attrib_integer_64bit');
context.getExtension('ARB_gpu_shader_fp64');
context.getExtension('EXT_vertex_attrib_64bit');
context.getExtension('EXT_sRGB_write_control');
context.getExtension('OES_sample_shading');
context.getExtension('EXT_multisample_compatibility');
context.getExtension('OES_vertex_half_float');
context.getExtension('NV_framebuffer_multisample');
context.getExtension('ARB_enhanced_layouts');
context.getExtension('ARB_shading_language_420pack');
context.getExtension('ARB_get_program_binary');
context.getExtension('ARB_shader_atomic_counters');
context.getExtension('EXT_bindable_uniform');
context.getExtension('EXT_geometry_shader4');
// context.getExtension('ARB_ES2_compatibility'); // limits to OpenGL ES 2.0
context.getExtension('ARB_direct_state_access');
context.getExtension('ARB_multitexture');
context.getExtension('KHR_color_buffer_half_float');
context.getExtension('EXT_texture_norm16');
context.getExtension('EXT_color_buffer_half_float');
context.getExtension('EGL_ANGLE_d3d_texture_client_buffer');
context.getExtension('EGL_ANGLE_direct3d_display');
context.getExtension('EGL_ANGLE_robust_resource_initialization');
context.getExtension('WEBGL_multi_draw');
context.getExtension('WEBGL_color_buffer_float');
context.getExtension('WEBGL_render_shared_exponent');
context.getExtension('EGL_EXT_device_base');
context.getExtension('EGL_EXT_device_query');
context.getExtension('EGL_EXT_output_base');
context.getExtension('EGL_EXT_platform_base');
context.getExtension('EGL_EXT_platform_device');
context.getExtension('EGL_EXT_swap_buffers_with_damage');
context.getExtension('EGL_NV_cuda_event');
context.getExtension('EGL_NV_device_cuda');
context.getExtension('EGL_NV_robustness_video_memory_purge');
context.getExtension('ARB_texture_view');
context.getExtension('EXT_float_32_packed_float');
context.getExtension('EGL_KHR_wait_sync');
context.getExtension('OES_texture_external');
context.getExtension('EGL_ANDROID_image_native_buffer');
context.getExtension('EGL_ANDROID_recordable');
context.getExtension('EGL_ANDROID_framebuffer_target');
context.getExtension('EGL_ANDROID_blob_cache');
context.getExtension('EGL_KHR_fence_sync');
context.getExtension('EGL_ANDROID_native_fence_sync');
context.getExtension('EGL_KHR_image_base');
context.getExtension('OES_EGL_image_external');
context.getExtension('EXT_YUV_target');
context.getExtension('GL_ARB_texture_rgb10_a2ui');
context.getExtension('ARB_texture_multisample');
context.getExtension('EGL_EXT_surface_SMPTE2086_metadata');
context.getExtension('ARB_texture_storage');
context.getExtension('ARB_multisample_texture');
context.getExtension('ARB_texture_cube_map_array');
context.getExtension('ARB_texture_buffer_object');
context.getExtension('ARB_texture_view');
context.getExtension('ARB_shader_storage_buffer_object');
context.getExtension('ARB_compute_shader');
context.getExtension('ARB_tessellation_shader');
context.getExtension('ARB_draw_elements_base_vertex');
context.getExtension('ARB_provoking_vertex');
context.getExtension('ARB_seamless_cube_map_per_texture');
context.getExtension('ARB_texture_compression_rgtc');
context.getExtension('ARB_texture_compression_bptc');
context.getExtension('ARB_texture_compression_astc');
context.getExtension('ARB_texture_filter_minmax');
context.getExtension('ARB_depth_texture');
context.getExtension('ARB_multisample');
context.getExtension('ARB_framebuffer_multisample');
context.getExtension('ARB_shader_objects');
*/

var $shds=[];

function normalResStart(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
setTimeout(function(){
document.getElementById('stat').innerHTML='Sending Start';
document.getElementById('stat').style.backgroundColor='green';
Module.ccall('str',{async:true});
},100);
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('di').click();
}

function shds(xml){
const sparser=new DOMParser();
let htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
let preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxts=txxts.replace(Self,"");
var x=document.getElementById("sh1");
var option=document.createElement("option");
option.text=txxts;
$shds[i+1]='https://glsl.1ink.us/shaders/'+txxts;
option.value=txxts;
x.add(option);
}
}
 
function rrun(){
let shadesNum=$shds[0];
if(shadesNum>0){
var randShade=Module.ccall('r4nd','Number',['Number'],[shadesNum],{async:true})+5;
};
let shdMenu=document.getElementById('sh1');
var path;
if(shdMenu.value!='Default'){
if(shdMenu.value=='Random'){
document.getElementById('path').innerHTML=$shds[randShade];
}else{
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+shdMenu.value;
}
}else{
var fle=document.getElementById('path').innerHTML;
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+fle;
}
var pth=document.getElementById('path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.getElementById('stat').innerHTML='Downloading Shader';
document.getElementById('stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader.glsl',sfil);
document.getElementById('stat').innerHTML='Downloaded Shader';
document.getElementById('stat').style.backgroundColor='blue';
//setTimeout(function(){
normalResStart();
//},350);
}
});
ff.send(null);
}

function scanShaders(){
const dxhttp=new XMLHttpRequest();
// dxhttp.withCredentials=false;
dxhttp.addEventListener("load",function(){
shds(this);
});
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
}

let tem=document.getElementById('tim');
let ban=document.getElementById('menuBtn');
let sfr=document.getElementById('slideframe');
var $lt;
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
let slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";});
const pnnl=document.body;

document.getElementById('startBtn2').addEventListener('click',function(){
Module.ccall('swp',{async:true});
rrun();
});

document.getElementById('uniDown').addEventListener('click',function(){
Module.ccall('ud',{async:true});
});

document.getElementById('viewDown').addEventListener('click',function(){
Module.ccall('vd',{async:true});
});

document.getElementById('uniUp').addEventListener('click',function(){
Module.ccall('uu',{async:true});
});

document.getElementById('viewUp').addEventListener('click',function(){
Module.ccall('vu',{async:true});
});

document.getElementById('moveUp').addEventListener('click',function(){
Module.ccall('mu',{async:true});

});document.getElementById('moveDown').addEventListener('click',function(){
Module.ccall('md',{async:true});

});document.getElementById('moveLeft').addEventListener('click',function(){
Module.ccall('ml',{async:true});

});document.getElementById('moveRight').addEventListener('click',function(){
Module.ccall('mr',{async:true});
});

document.getElementById('sizeUp').addEventListener('click',function(){
// document.getElementById('scanvas').style.width=window.innerHeight*1.01;
// document.getElementById('scanvas').style.height=window.innerHeight*1.01;
// document.getElementById('scanvas').width=window.innerHeight*1.01;
//document.getElementById('scanvas').height=window.innerHeight*1.01;
// Module.ccall('vu');
setTimeout(function(){
Module.ccall('uu',{async:true});
},100);
setTimeout(function(){
// document.getElementById('scanvas').style.width=window.innerHeight;
// document.getElementById('scanvas').style.height=window.innerHeight;
// document.getElementById('scanvas').width=window.innerHeight;
//document.getElementById('scanvas').height=window.innerHeight;
},200);
// Module.ccall('vd');
});
 
document.getElementById('sizeDown').addEventListener('click',function(){
// document.getElementById('scanvas').style.width=window.innerHeight*0.99;
// document.getElementById('scanvas').style.height=window.innerHeight*0.99;
// document.getElementById('scanvas').width=window.innerHeight*0.99;
//document.getElementById('scanvas').height=window.innerHeight*0.99;
// Module.ccall('vd');
setTimeout(function(){
Module.ccall('ud',{async:true});
},100);
setTimeout(function(){
// document.getElementById('scanvas').style.width=window.innerHeight;
// document.getElementById('scanvas').style.height=window.innerHeight;
// document.getElementById('scanvas').width=window.innerHeight;
//document.getElementById('scanvas').height=window.innerHeight;
},200);
// Module.ccall('vu',{async:true});
});

document.getElementById('startBtn').addEventListener('click',function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
document.getElementById('stat').innerHTML='Scanning Shaders';
document.getElementById('stat').style.backgroundColor='yellow';
rrun();
});

scanShaders();

setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},100);

function Key(e){
if(e.code=='KeyQ'){document.getElementById('startBtn').click();};
if(e.code=='KeyE'){document.getElementById('startBtn2').click();};
if(e.code=='KeyD'){document.getElementById('uniUp').click();};
if(e.code=='KeyA'){document.getElementById('uniDown').click();};
if(e.code=='KeyW'){document.getElementById('viewUp').click();};
if(e.code=='KeyS'){document.getElementById('viewDown').click();};
if(e.code=='KeyJ'){document.getElementById('moveLeft').click();};
if(e.code=='KeyK'){document.getElementById('moveRight').click();};
if(e.code=='KeyI'){document.getElementById('moveDown').click();};
if(e.code=='KeyM'){document.getElementById('moveUp').click();};
if(e.code=='Digit1'){document.getElementById('sizeDown').click();};
if(e.code=='Digit3'){document.getElementById('sizeUp').click();};
}
pnnl.addEventListener('keydown',Key);

});

}

static inline boost::function<EM_BOOL()>jss=[](){
js_main();
return EM_TRUE;
};

int r4nd4(int);

class js
{

private:

public:
 
std::random_device rd;

// v128_t Dr;

inline int rNd(int Th){
nm=Th*rd();
std::srand(nm);
rD=std::rand()%Th;
// Dr=wasm_i32x4_splat(rD);
return rD;
}

};

extern"C"{

int TH;
int RG;
int r4nd(int);

}
