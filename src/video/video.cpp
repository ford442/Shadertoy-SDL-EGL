#include "../../include/video/video.hpp"

void avgFrm(int Fnum,int leng,float *ptr,float *aptr){
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

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}

}

extern "C" {

EM_JS(void,ma,(),{
// "use strict";
const pnnl=document.body;
var vv=document.getElementById("mv");
var intervalBackward;

function back(){
intervalBackward=setInterval(function(){
if(vv.currentTime==0){
clearInterval(intervalBackward);
}else{
vv.currentTime+=-(0.016);
}
},16.66);
};

var intervalForward;

function forward(){
intervalForward=setInterval(function(){
vv.currentTime+=-(0.016);
},16.66);
};

var intervalLoop;
var stp,a,b,f;

function backForth(stp){
var a=(stp/1000.0);
var b=(stp/1000.0)+1.0;
f=true;
intervalLoop=setInterval(function(){
if(f==true){
if(vv.currentTime>a){
vv.currentTime+=-(0.016666);
}else{
f=false;
}}else if(vv.currentTime<b){
vv.currentTime+=(0.016666);
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

var Mov=1;

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
if(Mov==1){vv=document.getElementById("mv");Mov=0;vv.pause();}
else if(Mov==0){vv=document.getElementById("mv");Mov=1;vv.play();}
}
if (e.code=='KeyW'){vv=document.getElementById("mv");Mov=1;vv.pause();forward();}
if (e.code=='KeyS'){vv=document.getElementById("mv");Mov=1;vv.pause();back();}
if (e.code=='KeyZ'){vv=document.getElementById("mv");Mov=1;vv.pause();var stp=vv.currentTime*1000.0;
backForth(stp);}
if (e.code=='KeyX'){vv=document.getElementById("mv");stpBackForth();vv.play();}
}

function doKeyUp(e){
if (e.code=='KeyS'){Mov=0;stpBack();vv.pause();}
if (e.code=='KeyW'){Mov=0;stpForward();vv.pause();}
}

pnnl.addEventListener('keydown',doKey);
pnnl.addEventListener('keydown',doKeyUp);
let w$=parseInt(document.getElementById("wid").innerHTML,10);
let h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
let $H=Module.HEAPF32.buffer;
let la=h$*h$*4;
var pointa=77*la;
let agav=new Float32Array($H,pointa,300);
let sz=(h$*h$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.getElementById("bcanvas");
const contx=bcanvas.getContext("webgl2",{logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:true,stencil:true,imageSmoothingEnabled:true,preserveDrawingBuffer:false,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true,willReadFrequently:false});
contx.getExtension('WEBGL_color_buffer_float');
contx.getExtension('WEBGL_color_buffer_half_float');
contx.getExtension('OES_texture_float_linear');
contx.getExtension('OES_texture_half_float_linear');
contx.getExtension('EXT_float_blend');
contx.getExtension('EXT_frag_depth');
contx.getExtension('EXT_shader_texture_lod');
contx.getExtension('EXT_sRGB');
contx.getExtension('EXT_blend_minmax');
contx.getExtension('ANGLE_instanced_arrays');
contx.getExtension('EXT_disjoint_timer_query');

contx.getExtension('EXT_clip_cull_distance');
contx.getExtension('EXT_disjoint_timer_query_webgl2');
contx.getExtension('KHR_parallel_shader_compile');
contx.getExtension('OES_draw_buffers_indexed');
contx.getExtension('OES_element_index_uint');
contx.getExtension('OES_fbo_render_mipmap');
contx.getExtension('OES_standard_derivatives');
contx.getExtension('OES_vertex_array_object');
contx.getExtension('WEBGL_blend_equation_advanced_coherent');
contx.getExtension('WEBGL_depth_texture');
contx.getExtension('WEBGL_draw_buffers');
contx.getExtension('WEBGL_provoking_vertex');
contx.getExtension('EXT_framebuffer_sRGB');
contx.getExtension('OES_depth32');
contx.getExtension('OES_fixed_point');
contx.getExtension('OES_shader_multisample_interpolation');
contx.getExtension('WEBGL_webcodecs_video_frame');
contx.getExtension('OES_single_precision');
contx.getExtension('GL_EXT_texture_shadow_lod');
contx.getExtension('GL_NV_memory_attachment');
  
//   contx.disable(gl.DITHER);

const g=new GPUX({canvas:bcanvas,webGl:contx});
const g2=new GPUX();
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
  
const glslStone=`float Stone(float a,float b,float c,float d){return(max(((a-(d-(d*0.5)))+(b-(d-(d*0.5)))+(c-(d-(d*0.5)))*4.0),0.0));}`;
const glslStoned=`float Stoned(float a,float b,float c){return(min((a+c),1.0)-((b*0.3)*0.14));}`;
  
g.addNativeFunction('Stone',glslStone,{returnType:'Number'});
g.addNativeFunction('Stoned',glslStoned,{returnType:'Number'});
  
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
let R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setOptimizeFloatMemory(true).setArgumentTypes(["HTMLVideo"]).setOutput([sz]);
let t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPrecision('single').setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
let r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
var Min=(4.0*(($amax-($favg-$amin))/2.0));
var ouT=Math.max(Min,alph);
  // send p[0],p[1],p[2],ouT => return grr
  var rng=Stone(p[0],p[1],p[2],ouT);
// var rng=ouT-(ouT*0.5);
// var grr=(p[0]-rng)+(p[1]-rng)+(p[2]-rng);
// grr=grr*4.0;
// grr=Math.max(grr,0.0);
    // send p[x],p[x] => return r/g/b
var rr=Stoned(p[0],p[1],rng);
var gg=Stoned(p[1],p[3],rng);
var bb=Stoned(p[2],p[3],rng);
// var rr=Math.min((p[0]+grr),1.0)-((p[1])*0.14);
// var gg=Math.min((p[1]+grr),1.0)-((p[3]*0.3)*0.14);
// var bb=Math.min((p[2]+grr),1.0)-((p[3]*0.3)*0.14);
  var ss=(Ave(rr,gg,bb)-p[3]);
  var aveg=Aveg(p[3],ouT)+ss;

this.color(rr,gg,bb,aveg);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
let l=w$*h$*16;
la=h$*h$*4;
let al=w$*h$*8;
sz=(h$*h$)/8;
pointa=77*la;
agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
eval("$"+j+".set($$1);");
}
var d=S();if(d)d();d=S();function S(){
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
l=w$*h$*16;
la=h$*h$*4;
al=w$*h$*8;
sz=(h$*h$)/8;
pointa=77*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.getElementById("mv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
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
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}
})

}

void b3_egl(){
void(*b3e)(){&egl};
b3e();
return;
}
  
void b3(){
void(*B3)(){&vid};
B3();
return;
}
  
}
