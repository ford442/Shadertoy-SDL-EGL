#include "../include/b3emjs.hpp"

EM_JS(void,ma,(),{

"use strict";
var alphCan=document.getElementById("acanvas");
var lvv=document.getElementById("ldv");
var vv=document.getElementById("mv");
var sh4d=true;
var stp,Lstp;
var stpInc=0.01;
var setTim;
var timFrm=10.0;
var loopLoop;
var loopPart;
var mmvv;
var revv;
var $bb;
   
function forwardLoop(){
setTim=mmvv.currentTime;
setTim+=stpInc;
if(setTim<stp){
mmvv.currentTime=setTim;
}else{
revv=true;
};
}
 
function reverseLoop(){
setTim=mmvv.currentTime;
setTim-=stpInc;
if(setTim>=Lstp){
mmvv.currentTime=setTim;
}else{
revv=false;
};
}
  
function doKey(e){
if(e.code=='Space'){
e.preventDefault();
};
if (e.code=='KeyZ'){
mmvv=document.getElementById("mv");
mmvv.pause();
stp=document.getElementById("mv").currentTime;
loopPart=(stp+2.5)-(Math.floor(stp));
Lstp=stp-loopPart;
stp-=loopPart/2.0;
setTim=stp;
loopLoop=true;
revv=true;
};
if(e.code=='KeyX'){
loopLoop=false;
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
var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
// var h$=vv.videoHeight;
// var w$=vv.videoWidth;
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
const bcanvas=document.getElementById("bcanvas");
const gl_js=bcanvas.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
precision:'highp',
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:false,
imageSmoothingQuality:'medium',
preserveDrawingBuffer:true,
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
gl_js.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl_js.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
gl_js.getExtension('WEBGL_color_buffer_float');
gl_js.getExtension('WEBGL_color_buffer_half_float');
gl_js.getExtension('OES_texture_float_linear');
gl_js.getExtension('OES_texture_half_float_linear');
gl_js.getExtension('EXT_float_blend');
gl_js.getExtension('EXT_frag_depth');
gl_js.getExtension('EXT_shader_texture_lod');
gl_js.getExtension('EXT_sRGB');
gl_js.getExtension('EXT_blend_minmax');
gl_js.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
gl_js.getExtension('EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl_js.getExtension('KHR_parallel_shader_compile');
gl_js.getExtension('OES_draw_buffers_indexed');
gl_js.getExtension('OES_element_index_uint');
gl_js.getExtension('OES_fbo_render_mipmap');
gl_js.getExtension('OES_standard_derivatives');
gl_js.getExtension('OES_vertex_array_object');
gl_js.getExtension('WEBGL_blend_equation_advanced_coherent');
gl_js.getExtension('WEBGL_depth_texture');
gl_js.getExtension('WEBGL_draw_buffers');
gl_js.getExtension('WEBGL_provoking_vertex');
gl_js.getExtension('EXT_framebuffer_sRGB');
gl_js.getExtension('OES_depth32');
gl_js.getExtension('OES_fixed_point');
gl_js.getExtension('OES_shader_multisample_interpolation');
gl_js.getExtension('WEBGL_webcodecs_video_frame');
gl_js.getExtension('OES_single_precision');
// gl.getExtension('EXT_texture_shadow_lod');
gl_js.getExtension('EGL_NV_memory_attachment');
gl_js.getExtension('EGL_NV_depth_nonlinear');
gl_js.getExtension('EXT_gl_colorspace_display_p3');
gl_js.getExtension('EXT_gl_colorspace_display_p3_linear');
gl_js.getExtension('EXT_gl_colorspace_bt2020_linear');
gl_js.getExtension('ARB_multisample');
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl_js.blendColor(1.0,1.0,1.0,1.0);
gl_js.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl_js.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
gl_js.disable(gl.DITHER);
gl_js.drawingBufferColorSpace='display-p3';
const g=new GPU({mode:'webgl2',canvas:bcanvas,webGl:gl_js});
const g2=new GPU({mode:'gpu'});  //  A / B    'webgl2' / 'gpu' / 'cpu'
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((f-g)*((g)*(g-f))))))+0.7)/4.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
const Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0]*0.8,Pa[1],Pa[2]*1.2);
}).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setOptimizeFloatMemory(true).setOutput([sz]);
const t=g.createKernel(function(v){
const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
// const av$=Ave(P[0]*0.8,P[1],P[2]*1.2);
const av$=Ave(P[0],P[1],P[2]);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setPrecision('single').setDynamicOutput(true).setOutput([w$,h$]);
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
}).setTactic("precision").setGraphical(true).setArgumentTypes(["HTMLCanvas"]).setDynamicOutput(true).setOutput([w$,h$]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
// var h$=vv.videoHeight;
// var w$=vv.videoWidth;
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var r"+i+",$"+i+",$$"+i+";");
};
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for(var i=0;i<65;i++){
var j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H,point"+j+",la);$"+j+".set($$1,0,la);");
};
var d=S();if(d)d();d=S();function S(){
vv=document.getElementById("mv");
lvv=document.getElementById("ldv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
// var h$=vv.videoHeight;
// var w$=vv.videoWidth;
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(var i=0;i<65;i++){
var j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H,point"+j+",la);");
};
pointb=66*la;
var $B=new Float64Array($H,pointb,sz);
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
};
};
$bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;
if(sh4d==true){
Module.ccall("frm");
};
setTimeout(function(){
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
Module.ccall("clr",null,["Number","Number","Number"],[agav[200],agav[100],agav[0]]);
M();
if(loopLoop==true){
if(revv==true){
reverseLoop();
}else{
forwardLoop();
};
};
},timFrm)};
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

void b3(){
ma();
};
 
};
