#include "../../include/combine/video.hpp"

Video video;

extern "C" {

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
video.avgr.clrclr(cllr,alp,avr);
return;
}

void nano(short int Fnum,int leng,float *ptr,float *aptr){
video.avgr.avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,vid,(),{
  
"use strict";

var vv=document.getElementById("mv");
var sh4d=true;
var stp,Lstp;
const stpInc=0.016666;
var setTim;
const timFrm=10.419;
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
const $H=Module.HEAPF64.buffer;
const $BB=Module.HEAPF32.buffer;
// var inh=window.innerHeight;
var $S=parseInt(window.innerHeight,10);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=h$*w$*8;
var lab=h$*w$*4;
var pointa=77*lab;
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
colorType:'float64',
preferLowPowerToHighPerformance:false,
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:false,
precision:'highp',
imageSmoothingEnabled:false,
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
gl.getExtension('EXT_color_buffer_float');  //  required for float/alpha   -- WEBGL2 --
// gl.getExtension('EXT_pixel_format_float');
// gl.getExtension('ARB_blend_func_extended');
// gl.getExtension('KHR_gl_colorspace');
// gl.getExtension('EXT_gl_colorspace_scrgb_linear');
// gl.getExtension('EXT_gl_colorspace_display_p3');
// gl.getExtension('EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EXT_gl_colorspace_bt2020_linear');
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
const g=new GPUX({mode:'gpu',canvas:bcanvas,webGl:gl});
const g2=new GPUX({mode:'gpu'});
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
}).setTactic("speed").setOptimizeFloatMemory(true).setDynamicOutput(true).setOutput([sz]);
let t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
// var minuss=(av$-0.9)*(av$/(av$-0.9));
// av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setPipeline(true).setOutput([h$,w$]);
let r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
// var silvrr=Ave(p[0],p[1],p[2]);
// this.color(silvrr,silvrr,p[2],aveg);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setGraphical(true).setOutput([h$,w$]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*0.0)/8.0),0);
la=h$*w$*8;
lab=h$*w$*4;
sz=(h$*w$)/8;
pointa=77*lab;
agav=new Float32Array($BB,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
};
var pointb=77*la;
var $B=new Float32Array($BB,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
// eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var $$1=0.0;$"+j+".fill($$1);");
};
var d=S();if(d)d();d=S();function S(){
vv=document.getElementById("mv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*0.0)/8.0),0);
$S=parseInt(window.innerHeight,10);
la=h$*w$*8;
lab=h$*w$*4;
sz=(h$*w$)/8;
pointa=77*lab;
var agav=new Float32Array($BB,pointa,300);  // has to var?
R.setOutput([sz]);
for(var i=0;i<65;i++){
j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
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

void(*B3)(){&vid};

extern "C" {

void b3_egl(){
Video::egl();
return;
}

void b3(){
video.avgr.resetAvg();
B3();
return;
}

}
