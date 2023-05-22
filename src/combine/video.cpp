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

void frm(){
video.FrM();
return;
}

}

EM_JS(void,vid,(),{

"use strict";

var vv=document.getElementById('mv');
var sh4d=false;
let stp,Lstp;
let stpInc=0.016;
let setTim;
// const timFrm=16.666;
let timFrm=10.42;
var lockVid;
var loopLoop;
var loopPart;
var mmvv;
let revv;
var $bb;

function forwardLoop(){
// setTim=mmvv.currentTime;
if(setTim<=stp){
setTim+=stpInc;

mmvv.currentTime=setTim;
}else{
revv=true;
}
}

function reverseLoop(){
// setTim=mmvv.currentTime;
if(setTim>=Lstp){
setTim-=stpInc;

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
mmvv=document.getElementById('mv');
mmvv.pause();
stp=document.getElementById('mv').currentTime;
loopPart=(stp+2.5)-(Math.floor(stp));
setTim=stp;
Lstp=Math.floor(stp-loopPart);
stp=Math.floor(stp);
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
let $H=Module.HEAPF32.buffer;
var inh=window.innerHeight;
var s$=parseInt(inh,10);
var w$=parseInt(inh,10);
var h$=parseInt(inh,10);
// w$=parseInt(document.getElementById("wid").innerHTML,10);
// h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=h$*w$*8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
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
let gljs=bCan.getContext("webgl2",{
preferLowPowerToHighPerformance:false,
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:true,
preserveDrawingBuffer:false,
premultipliedAlpha:false,
desynchronized:false,
lowLatency:true,
powerPreference:'high-performance',
antialias:true,
majorVersion:2,
minorVersion:0
});
gljs.getExtension('OES_texture_float_linear');
gljs.getExtension('EXT_color_buffer_float');  //  required for float/alpha   -- WEBGL2 --
  /*
gl.getExtension('EGL_KHR_gl_colorspace');
// gl.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
gl.getExtension('EXT_texture_filter_anisotropic');
*/
// gl.getExtension('ARB_blend_func_extended');
  
  
gljs.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gljs.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect

gljs.disable(gl.DITHER);
// gl.drawingBufferColorMetadata={mode:'extended'};
// gl.renderbufferStorage(gl.RENDERBUFFER,gl.RGBAF32,bCan.height,bCan.height);
gljs.blendColor(1.0,1.0,1.0,1.0);
  
gljs.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gljs.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
  
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
// gl.unpackColorSpace='display-p3';  // very slow
gljs.drawingBufferColorSpace='display-p3';
const g=new GPU({mode:'gpu',canvas:bcanvas,webGl:gljs});
const g2=new GPU({mode:'gpu'});

const glslSilver=`float Silver(float a){return((a+0.75+0.75+((a+0.75)/2.0))/4.0);}`;
const glslGoldR=`float GoldR(float a){return((a+0.831+0.831+0.831+((a+0.831)/2.0))/5.0);}`;
const glslGoldG=`float GoldG(float a){return((a+0.686+0.686+0.686+((a+0.686)/2.0))/5.0);}`;
const glslGoldB=`float GoldB(float a){return((a+0.215+0.215+0.215+((a+0.215)/2.0))/5.0);}`;
  
const glslRoseR=`float RoseR(float a){return((a+0.86+0.86+0.86+((a+0.86)/2.0))/5.0);}`;
const glslRoseG=`float RoseG(float a){return((a+0.13+0.13+0.13+((a+0.13)/2.0))/5.0);}`;
const glslRoseB=`float RoseB(float a){return((a+0.86+0.86+0.86+((a+0.86)/2.0))/5.0);}`;
  
  
const glslGreenR=`float GreenR(float a){return((a+0.11+0.11+0.11+((a+0.11)/2.0))/5.0);}`;
const glslGreenG=`float GreenG(float a){return((a+0.73+0.73+0.73+((a+0.73)/2.0))/5.0);}`;
const glslGreenB=`float GreenB(float a){return((a+0.14+0.14+0.14+((a+0.14)/2.0))/5.0);}`;

const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
  
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float f,float g) {return (1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25)));}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;

  
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});

g.addNativeFunction('GreenR',glslGreenR,{returnType:'Number'});
g.addNativeFunction('GreenG',glslGreenG,{returnType:'Number'});
g.addNativeFunction('GreenB',glslGreenB,{returnType:'Number'});
  
g.addNativeFunction('RoseR',glslRoseR,{returnType:'Number'});
g.addNativeFunction('RoseG',glslRoseG,{returnType:'Number'});
g.addNativeFunction('RoseB',glslRoseB,{returnType:'Number'});
  
const R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setOutput([sz]);
const t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.05));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setPipeline(true).setOutput([s$,s$]);
//     }).setConstants({nblnk:nblank$,blnk:blank$}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput([s$,s$]);
const r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
  /*
//  // 
var rr;
var gg;
var bb;
var der=p[0];
var neerg=p[1];
var eulb=p[2];
// if(der>0.333){
 rr=GreenR(der);
// }else{
// rr=RoseR(der);
// }
// if(neerg>0.4){
gg=GreenG(neerg);
// }else{
// gg=RoseG(neerg);
// }
// if(eulb>0.5){
bb=GreenB(eulb);
// }else{
// bb=RoseB(eulb);
// }//   
 */
// this.color(GreenR(p[0]),GreenG(p[1]),GreenB(p[2]),aveg);
// this.color(rr,gg,bb,aveg);
// 
  
//   var silvrr=Ave(p[0],p[1],p[2]);
// this.color(silvrr,silvrr,p[2],aveg);
  
this.color(p[0],p[1],p[2],aveg);
  
}).setTactic("precision").setDynamicOutput(true).setGraphical(true).setOutput([h$,w$]);
// }).setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]}).setTactic("precision").setGraphical(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([$S,$S]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
  var s$=parseInt(inh,10);

var blank$=Math.max((((w$-s$)*0.0)/8.0),0);
var nblank$=Math.max((((s$-w$)*0.0)/8.0),0);
la=h$*w$*8;
pointa=77*la;
agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
};
var pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float32Array($H,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
// eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);var $$1=0.0;$"+j+".fill($$1);");
};
var d=S();if(d){d()};d=S();function S(){
vv=document.getElementById("mv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
  s$=parseInt(window.innerHeight,10);

blank$=Math.max((((w$-s$)*0.0)/8.0),0);
nblank$=Math.max((((s$-w$)*0.0)/8.0),0);
la=h$*w$*8;
pointa=77*la;
agav=new Float32Array($H,pointa,300);  // has to var?
R.setOutput([sz]);
for(var i=0;i<65;i++){
j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float32Array($H,point"+j+",la);");
};
var pointb=66*la;
$B=new Float32Array($H,pointb,sz);  // has to var?
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
}
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
if($F==i){
eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
}};
$bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;  // has to revar?
if($F%2==0){
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
Module.ccall("clr",null,["Number","Number","Number"],[agav[200],agav[$F+100],agav[0]]);
}
if(sh4d==1){
Module.ccall("frm",null,[],[]);
}
setTimeout(function(){
M();
if(loopLoop==true){
if(revv==true){
reverseLoop();
}else{
forwardLoop();
}
}
},16)}
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

void b3(){
video.avgr.resetAvg();
B3();
return;
}

}
