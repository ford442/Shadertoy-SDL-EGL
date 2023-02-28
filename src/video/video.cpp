#include "../../include/video/video.hpp"

void egl(){
eglconfig_js=NULL;
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
eglSize=(GLsizei)hi_js;
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_TRUE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_TRUE;
attr_js.preserveDrawingBuffer=EM_FALSE;
attr_js.enableExtensionsByDefault=EM_FALSE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
// eglSurfaceAttrib(display_js,surface_js,EGL_MIPMAP_LEVEL,(EGLint)1);
emscripten_webgl_make_context_current(ctx_js);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glDisable(GL_DITHER);
glEnable(GL_SCISSOR_TEST);
emscripten_webgl_enable_extension(ctx_js,"EXT_color_buffer_float");  //  required for float/alpha (must be 'EXT_color_buffer_float' and not 'GL_EXT_color_buffer_float')
emscripten_webgl_enable_extension(ctx_js,"EXT_pixel_format_float");  //  required for float/alpha (must be 'EXT_pixel_format_float' and not 'EGL_EXT_pixel_format_float')
emscripten_webgl_enable_extension(ctx_js,"IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx_js,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_gpu_shader5");
emscripten_webgl_enable_extension(ctx_js,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_bt2020_linear");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx_js,"ARB_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_webcodecs_video_frame");
// emscripten_webgl_enable_extension(ctx_js,"OES_texture_float_linear");
// emscripten_webgl_enable_extension(ctx_js,"OES_texture_half_float_linear");
// emscripten_webgl_enable_extension(ctx_js,"OES_element_index_uint");
// emscripten_webgl_enable_extension(ctx_js,"OES_fbo_render_mipmap");
// emscripten_webgl_enable_extension(ctx_js,"OES_vertex_array_object");
// emscripten_webgl_enable_extension(ctx_js,"OES_draw_buffers_indexed");
// emscripten_webgl_enable_extension(ctx_js,"OES_fixed_point");
// emscripten_webgl_enable_extension(ctx_js,"OES_single_precision");
// emscripten_webgl_enable_extension(ctx_js,"OES_standard_derivatives");
// emscripten_webgl_enable_extension(ctx_js,"OES_float_blend");
// emscripten_webgl_enable_extension(ctx_js,"OES_frag_depth");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shader_texture_lod");
// emscripten_webgl_enable_extension(ctx_js,"OES_sRGB");
// emscripten_webgl_enable_extension(ctx_js,"OES_depth32");
// emscripten_webgl_enable_extension(ctx_js,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_js,"GL_disjoint_timer_query");
// emscripten_webgl_enable_extension(ctx_js,"EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx_js,"GL_disjoint_timer_query_webgl2");
// emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx_js,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_js,"KHR_parallel_shader_compile");
// emscripten_webgl_enable_extension(ctx_js,"EXT_texture_shadow_lod");
// emscripten_webgl_enable_extension(ctx_js,"EGL_NV_memory_attachment");
/// emscripten_webgl_enable_extension(ctx_js,"ATI_pixel_format_float"); 
// emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_multisample");
// emscripten_webgl_enable_extension(ctx_js,"ARB_robustness");
// emscripten_webgl_enable_extension(ctx_js,"ARB_robust_buffer_access_behavior");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"OES_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"EXT_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"AMD_pinned_memory");
// emscripten_webgl_enable_extension(ctx_js,"GL_ARB_blend_func_extended");
// emscripten_webgl_enable_extension(ctx_js,"ARB_buffer_storage");
// emscripten_webgl_enable_extension(ctx_js,"ARB_compatibility");
// emscripten_webgl_enable_extension(ctx_js,"ARB_compute_shader");
// emscripten_webgl_enable_extension(ctx_js,"ARB_enhanced_layouts");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shadow");
// emscripten_webgl_enable_extension(ctx_js,"ARB_sync");
// emscripten_webgl_enable_extension(ctx_js,"ARB_tessellation_shader");
// emscripten_webgl_enable_extension(ctx_js,"ARB_texture_float");
// emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_multisample");
// emscripten_webgl_enable_extension(ctx_js,"EXT_geometry_shader");
// emscripten_webgl_enable_extension(ctx_js,"MESA_shader_integer_functions");
// emscripten_webgl_enable_extension(ctx_js,"OES_geometry_shader");
// emscripten_webgl_enable_extension(ctx_js,"ARB_texture_stencil8");
// emscripten_webgl_enable_extension(ctx_js,"GL_OES_draw_buffers_indexed");
// emscripten_webgl_enable_extension(ctx_js,"GL_ARB_draw_buffers_blend");
// emscripten_webgl_enable_extension(ctx_js,"ARB_cull_distance");
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
glViewport((GLint)0,(GLint)0,eglSize,eglSize);
glScissor((GLint)0,(GLint)0,eglSize,eglSize);
return;
}

void avgFrm(short int Fnum,int leng,float *ptr,float *aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for(int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];
}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];
}
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

void nano(short int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,vid,(),{

"use strict";

var vv=document.getElementById("mv");
var sh4d=true;
var stp,Lstp;
const stpInc=0.016;
var setTim;
const timFrm=16.666;
var loopLoop;
var loopPart;
var mmvv;
var revv;
var $bb;
function forwardLoop(){
// setTim=mmvv.currentTime;
setTim+=stpInc;
if(setTim<stp){
mmvv.currentTime=setTim;
}else{
revv=true;
}
}
function reverseLoop(){
// setTim=mmvv.currentTime;
setTim-=stpInc;
if(setTim>=Lstp){
mmvv.currentTime=setTim;
}else{
revv=false;
}
}
function doKey(e){
if(e.code=='Space'){
e.preventDefault();
}
if (e.code=='KeyZ'){
mmvv=document.getElementById("mv");
mmvv.pause();
stp=document.getElementById("mv").currentTime;
loopPart=(stp+2.5)-(Math.floor(stp));
setTim=stp;
Lstp=stp-loopPart;
stp-=loopPart/2.0;
loopLoop=true;
revv=true;
}
if(e.code=='KeyX'){
loopLoop=false;
vv.play();
}
if(e.code=='KeyA'){
sh4d=true;
}
if(e.code=='KeyS'){
sh4d=false;
}
}
const pnnl=document.body;
pnnl.addEventListener('keydown',doKey);
const $H=Module.HEAPF32.buffer;
const $BB=Module.HEAPF32.buffer;
var $S=parseInt(window.innerHeight,10);
var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=h$*w$*4;
var pointa=77*la;
var agav=new Float32Array($BB,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var blank$=Math.max((((w$-h$)*0.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*0.0)/8.0),0);
let bCan=document.getElementById("bcanvas");
let gl=bCan.getContext("webgl2",{
colorType:'float32',
preferLowPowerToHighPerformance:false,
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
precision:'highp',
imageSmoothingEnabled:true,
imageSmoothingQuality:'medium',
preserveDrawingBuffer:false,
premultipliedAlpha:false,
desynchronized:false,
lowLatency:true,
powerPreference:'high-performance',
antialias:true,
willReadFrequently:false,
xrCompatible:false,
majorVersion:2,
minorVersion:0
});

const g=new GPU({canvas:bcanvas,webGl:gl});
const g2=new GPU();
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(0.999-(((a)-(b))*((a)*(0.999/(0.999-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
let R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setOptimizeFloatMemory(false).setDynamicOutput(true).setOutput([sz]);
let t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
// var minuss=(av$-0.9)*(av$/(av$-0.9));
// av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setPipeline(true).setOutput([$S,$S]);
let r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
//   var silvrr=Ave(p[0],p[1],p[2]);
// this.color(silvrr,silvrr,p[2],aveg);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setGraphical(true).setOutput([$S,$S]);
gl.getExtension('EXT_color_buffer_float');
gl.getExtension('EXT_pixel_format_float');
gl.getExtension('EXT_float_blend');
gl.getExtension('NV_memory_attachment');
gl.getExtension('NV_depth_nonlinear');
gl.getExtension('IMG_context_priority');     //     vv  required for realtime
gl.getExtension('NV_context_priority_realtime'); // ^^
gl.getExtension('ARB_gl_spirv');
gl.getExtension('ARB_spirv_extensions');
gl.getExtension('ARB_invalidate_subdata');
gl.getExtension('ARB_texture_storage');
gl.getExtension('ARB_ES2_compatibility');
gl.getExtension('ARB_ES3_compatibility');
gl.getExtension('ARB_ES3_1_compatibility');
gl.getExtension('ARB_ES3_2_compatibility');
gl.getExtension('EXT_gpu_shader5');
gl.getExtension('ARB_blend_func_extended');
gl.getExtension('OES_sample_variables');                  //  vv
gl.getExtension('OES_shader_multisample_interpolation');  //  ^^
gl.getExtension('KHR_gl_colorspace');
gl.getExtension('EXT_gl_colorspace_scrgb_linear');
// gl.getExtension('EXT_gl_colorspace_display_p3');
// gl.getExtension('EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EXT_gl_colorspace_bt2020_linear');
// gl.getExtension('WEBGL_color_buffer_float');
// gl.getExtension('WEBGL_color_buffer_half_float');
// gl.getExtension('OES_texture_float_linear');
// gl.getExtension('OES_texture_half_float_linear');
// gl.getExtension('EXT_frag_depth');
// gl.getExtension('EXT_shader_texture_lod');
// gl.getExtension('EXT_sRGB');
// gl.getExtension('EXT_blend_minmax');
// gl.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
// gl.getExtension('EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
// gl.getExtension('KHR_parallel_shader_compile');
// gl.getExtension('OES_draw_buffers_indexed');
// gl.getExtension('OES_element_index_uint');
// gl.getExtension('OES_fbo_render_mipmap');
// gl.getExtension('OES_standard_derivatives');
// gl.getExtension('OES_vertex_array_object');
// /gl.getExtension('WEBGL_blend_equation_advanced_coherent');
// gl.getExtension('WEBGL_depth_texture');
// gl.getExtension('WEBGL_draw_buffers');
// gl.getExtension('WEBGL_provoking_vertex');
// gl.getExtension('EXT_framebuffer_sRGB');
// gl.getExtension('OES_depth32');
// gl.getExtension('OES_fixed_point');
// gl.getExtension('WEBGL_webcodecs_video_frame');
// gl.getExtension('OES_single_precision');
// gl.getExtension('EXT_texture_shadow_lod');
// gl.getExtension('EXT_framebuffer_sRGB');
// emscripten_webgl_enable_extension(ctx,"OES_gpu_shader5");
// gl.getExtension('AMD_pinned_memory');
// gl.getExtension('ARB_buffer_storage');
// gl.getExtension('ARB_color_buffer_float');
// gl.getExtension('ARB_compatibility');
// gl.getExtension('ARB_compute_shader');
// gl.getExtension('ARB_enhanced_layouts');
// gl.getExtension('ARB_shadow');
// gl.getExtension('ARB_sync');
// gl.getExtension('ARB_tessellation_shader');
// gl.getExtension('ARB_texture_float');
// gl.getExtension('EXT_framebuffer_multisample');
// gl.getExtension('EXT_geometry_shader');
// gl.getExtension('MESA_shader_integer_functions');
// gl.getExtension('OES_geometry_shader');
// gl.getExtension('ARB_texture_stencil8');
// gl.getExtension('OES_draw_buffers_indexed');
// gl.getExtension('ARB_draw_buffers_blend');
// gl.getExtension('ARB_cull_distance');
// gl.getExtension('ARB_gpu_shader_fp64');
// gl.getExtension('EXT_vertex_attrib_64bit');
// gl.renderbufferStorage(gl.RENDERBUFFER,gl.RGBAF32,bCan.height,bCan.height);
// gl.drawingBufferColorMetadata={mode:'extended'};
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
// gl.disable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
gl.disable(gl.DITHER);
gl.blendColor(1.0,1.0,1.0,1.0);
gl.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
gl.drawingBufferColorSpace='display-p3';
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*0.0)/8.0),0);
la=h$*w$*4;
sz=(h$*w$)/8;
pointa=77*la;
agav=new Float32Array($BB,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
};
var pointb=77*la;
var $B=new Float32Array($BB,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
};
var d=S();if(d)d();d=S();function S(){
vv=document.getElementById("mv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*0.0)/8.0),0);
$S=parseInt(window.innerHeight,10);
// t.setOutput([$S,$S]);
// r.setOutput([$S,$S]);
la=h$*w$*4;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float32Array($BB,pointa,300);  // has to var?
R.setOutput([sz]);
for(var i=0;i<65;i++){
j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
};
pointb=66*la;
var $B=new Float32Array($BB,pointb,sz);  // has to var?
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
};
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;};
var locb=$Bu+1;
if(locb>64){locb=1;};
if($F==i){
eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
};};
$bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;  // has to revar?
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
setTimeout(function(){
M();
if(loopLoop==true){
if(revv==true){
reverseLoop();
}else{
forwardLoop();
};
};
},16.6)}
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}

});

extern "C" {

void b3_egl(){
egl();
}

void b3(){
vid();
return;
}

}
