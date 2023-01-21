#include "../include/b3emjs.hpp"

void egl(){
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_TRUE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_FALSE;
attr_js.preserveDrawingBuffer=EM_FALSE;
attr_js.enableExtensionsByDefault=EM_TRUE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
eglBindAPI(EGL_OPENGL_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
emscripten_webgl_make_context_current(ctx_js);
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=(int)hi_js;
emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_element_index_uint");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_depth32");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_fixed_point");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_single_precision");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_float_blend");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_frag_depth");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_sRGB");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_depth32");
// emscripten_webgl_enable_extension(ctx_js,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_js,"GL_EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_js,"GL_EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx_js,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_js,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx_js,"EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_multisample");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_gpu_shader4");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_gpu_shader5");
glViewport((GLint)0,(GLint)0,GLsizei(Size_js),GLsizei(Size_js));
glDisable(GL_DITHER);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
return;
}

void avgFrm(short int Fnum,int leng,float * ptr,float * aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
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

void nano(short int Fnum,int leng,float * ptr,float * aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,ma,(),{

"use strict";
var lvv=document.getElementById("ldv");
var vv=document.getElementById("mv");
var intervalLoop=null;
var f;
var loopLoop;
var sh4d=true;
var a,b;
var stp=document.getElementById("mv").currentTime;
var loopPart=(stp-(Math.floor(stp))+1.0)*2;
var mmvv=document.getElementById("mv");
var paus;
function stpBackForth(){
loopLoop=false;
}

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
if(paus==true){
paus=false;
};
if(paus==false){
paus=true;
};
};
if (e.code=='KeyZ'){
mmvv=document.getElementById("mv");
mmvv.pause();
stp=document.getElementById("mv").currentTime;
loopPart=(stp-(Math.floor(stp))+1.0)*2;
// console.log(stp);
loopLoop=true;
f=false;
// backForth(stp);
};
if(e.code=='KeyX'){
loopLoop=false;
// stpBackForth();
vv.play();
};
if(e.code=='KeyA'){
sh4d=true;
};
if(e.code=='KeyS'){
sh4d=false;
};
}

const pnnl=document.body;
pnnl.addEventListener('keydown',doKey);
// var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
// var h$=vv.videoHeight;
var w$=vv.videoWidth;
const $H=Module.HEAPF64.buffer;
var la=h$*h$*8;
var pointa=77*la;
var agav=new Float64Array($H,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var bcanvas=document.getElementById("bcanvas");
var gl=bcanvas.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
precision:'highp',
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
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

const g=new GPU({mode:'webgl2',canvas:bcanvas,webGl:gl});
const g2=new GPU({mode:'webgl2'});  //  A / B    'webgl2' / 'gpu' / 'cpu'
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((g-f)*((g)*(g-f)))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
const Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0]*0.8,Pa[1],Pa[2]*1.2);
}).setTactic("speed").setDynamicOutput(true).setOutput([sz]);
const t=g.createKernel(function(v){
const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
const av$=Ave(P[0]*0.8,P[1],P[2]*1.2);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setPrecision("single").setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
const r=g.createKernel(function(f){
const p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
const $amax=this.constants.amax;
const $amin=this.constants.amin;
const $aavg=this.constants.aavg;
const alph=Alphe($amax,$amin,$aavg,p[3]);
const Min=(4.0*(($amax-($aavg-$amin))/2.0));
const ouT=Math.max(Min,alph);
const aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setOutput([w$,h$]);
gl.getExtension('WEBGL_color_buffer_float');
gl.getExtension('WEBGL_color_buffer_half_float');
gl.getExtension('GL_OES_texture_float_linear');
gl.getExtension('GL_OES_texture_half_float_linear');
gl.getExtension('GL_EXT_float_blend');
gl.getExtension('GL_EXT_frag_depth');
gl.getExtension('GL_EXT_shader_texture_lod');
gl.getExtension('GL_EXT_sRGB');
gl.getExtension('GL_EXT_blend_minmax');
gl.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
gl.getExtension('GL_EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl.getExtension('KHR_parallel_shader_compile');
gl.getExtension('GL_OES_draw_buffers_indexed');
gl.getExtension('GL_OES_element_index_uint');
gl.getExtension('GL_OES_fbo_render_mipmap');
gl.getExtension('GL_OES_standard_derivatives');
gl.getExtension('GL_OES_vertex_array_object');
gl.getExtension('WEBGL_blend_equation_advanced_coherent');
gl.getExtension('WEBGL_depth_texture');
gl.getExtension('WEBGL_draw_buffers');
gl.getExtension('WEBGL_provoking_vertex');
gl.getExtension('EXT_framebuffer_sRGB');
gl.getExtension('OES_depth32');
gl.getExtension('GL_OES_fixed_point');
gl.getExtension('GL_OES_shader_multisample_interpolation');
gl.getExtension('WEBGL_webcodecs_video_frame');
gl.getExtension('GL_OES_single_precision');
// gl.getExtension('GL_EXT_texture_shadow_lod');
gl.getExtension('EGL_NV_memory_attachment');
gl.getExtension('EGL_NV_depth_nonlinear');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
gl.getExtension('GL_ARB_multisample');

// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl.blendColor(1.0,1.0,1.0,1.0);
gl.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
 
 gl.drawingBufferColorSpace='display-p3';
gl.disable(gl.DITHER);

// w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
// var h$=vv.videoHeight;
var w$=vv.videoWidth;
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);$"+j+".set($$1,0,la);");
}
var d=S();if(d)d();d=S();function S(){
    
gl.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl.hint(gl.GENERATE_MIPMAP_HINT,gl.FASTEST);
 
// w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
// var h$=vv.videoHeight;
var w$=vv.videoWidth;
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float64Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.getElementById("mv");
lvv=document.getElementById("ldv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
};
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
eval("if($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";}");
}
pointb=66*la;
setTimeout(function(){
M();
if(loopLoop==true){
if(f==true){
if(document.getElementById("mv").currentTime>(stp-loopPart)){
mmvv.currentTime-=0.013333;
}else{
f=false;
if(document.getElementById("mv").currentTime<(stp)){
document.getElementById("mv").currentTime+=0.013333;
}else{
f=true;
}}} /*
if(f==false){
if(document.getElementById("mv").currentTime<(stp)){
document.getElementById("mv").currentTime+=0.013333;
}else{
f=true;
if(document.getElementById("mv").currentTime>(stp-loopPart)){
document.getElementById("mv").currentTime-=0.013333;
}else{
f=false;
}}
} */
}else{
// if($F%4!=0){
var $bb=R(vv);$B.set($bb,0,sz);
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
// };
// };
Module.ccall("clr",null,["Number","Number","Number"],[agav[201],agav[101],agav[1]]);
// if($F%2==0){
};
if(sh4d==true){
Module.ccall("frm");
};
},13.333333)}
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
return;
}

void b3(){
ma();
return;
}
 
}
