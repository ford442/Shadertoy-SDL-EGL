#include "../include/b3emjs.hpp"

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

const pnnl=document.body;
var vv=document.getElementById("mv");
var intervalLoop=null;
var f;
var loopLoop;
var a,b;
var stp;
var mmvv;
 
function backForth(stp){
loopLoop=true;
f=true;
a=stp-(60*0.0166);
b=stp+(60*0.0166);
}

function stpBackForth(){
loopLoop=false;
}

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
}
if (e.code=='KeyZ'){
mmvv=document.getElementById("mv");
mmvv.pause();
stp=mmvv.currentTime;
backForth(stp);
}
if(e.code=='KeyX'){
stpBackForth();
vv.play();
}}

pnnl.addEventListener('keydown',doKey);
var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
const $H=Module.HEAPF32.buffer;
var la=h$*h$*4;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
var sz=(h$*h$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.getElementById("bcanvas");
const gl=bcanvas.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
precision:'highp',logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:false,
imageSmoothingQuality:'high',
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
const g=new GPU({mode:'webgl2',canvas:bcanvas,webGl:gl});
const g2=new GPU({mode:'webgl2'});
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
}).setTactic("precision").setPrecision('single').setPipeline(true).setDynamicOutput(true).setOutput([w$,h$]);
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
}).setTactic("precision").setPrecision('single').setGraphical(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);
gl.disable(gl.DITHER);
gl.drawingBufferColorSpace='display-p3';
gl.getExtension('WEBGL_color_buffer_float');
gl.getExtension('WEBGL_color_buffer_half_float');
gl.getExtension('OES_texture_float_linear');
gl.getExtension('OES_texture_half_float_linear');
gl.getExtension('EXT_float_blend');
gl.getExtension('EXT_frag_depth');
gl.getExtension('EXT_shader_texture_lod');
gl.getExtension('EXT_sRGB');
gl.getExtension('EXT_blend_minmax');
gl.getExtension('ANGLE_instanced_arrays');
gl.getExtension('EXT_disjoint_timer_query');
gl.getExtension('EXT_clip_cull_distance');
gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl.getExtension('KHR_parallel_shader_compile');
gl.getExtension('OES_draw_buffers_indexed');
gl.getExtension('OES_element_index_uint');
gl.getExtension('OES_fbo_render_mipmap');
gl.getExtension('OES_standard_derivatives');
gl.getExtension('OES_vertex_array_object');
gl.getExtension('WEBGL_blend_equation_advanced_coherent');
gl.getExtension('WEBGL_depth_texture');
gl.getExtension('WEBGL_draw_buffers');
gl.getExtension('WEBGL_provoking_vertex');
gl.getExtension('EXT_framebuffer_sRGB');
gl.getExtension('OES_depth32');
gl.getExtension('OES_fixed_point');
gl.getExtension('OES_shader_multisample_interpolation');
gl.getExtension('WEBGL_webcodecs_video_frame');
gl.getExtension('OES_single_precision');
gl.getExtension('GL_EXT_texture_shadow_lod');
gl.getExtension('GL_NV_memory_attachment');
gl.getExtension('NV_depth_nonlinear');
gl.getExtension('EXT_gl_colorspace_display_p3');
gl.getExtension('GL_ARB_multisample');
gl.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
gl.blendColor(1.0,1.0,1.0,1.0);
gl.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);
// gl.unpackColorSpace='display-p3';  // very slow
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
la=h$*h$*4;
var al=w$*h$*8;
sz=(h$*h$)/8;
pointa=77*la;
agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
 
// for(i=0;i<65;i++){
// var j=i+1;
// eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
// }
 
var point1=0*la;var $1=new Float32Array($H,point1,la);
var point1=1*la;var $2=new Float32Array($H,point2,la);
var point2=2*la;var $3=new Float32Array($H,point3,la);
var point3=3*la;var $4=new Float32Array($H,point4,la);
var point4=4*la;var $5=new Float32Array($H,point5,la);
var point5=5*la;var $6=new Float32Array($H,point6,la);
var point6=6*la;var $7=new Float32Array($H,point7,la);
var point7=7*la;var $8=new Float32Array($H,point8,la);
var point8=8*la;var $9=new Float32Array($H,point9,la);
var point9=9*la;var $10=new Float32Array($H,point10,la);
var point10=10*la;var $11=new Float32Array($H,point11,la);
var point11=11*la;var $12=new Float32Array($H,point12,la);
var point12=12*la;var $13=new Float32Array($H,point13,la);
var point13=13*la;var $14=new Float32Array($H,point14,la);
var point14=14*la;var $15=new Float32Array($H,point15,la);
var point15=15*la;var $16=new Float32Array($H,point16,la);
var point16=16*la;var $17=new Float32Array($H,point17,la);
var point17=17*la;var $18=new Float32Array($H,point18,la);
var point18=18*la;var $19=new Float32Array($H,point19,la);
var point19=19*la;var $20=new Float32Array($H,point20,la);
var point20=20*la;var $21=new Float32Array($H,point21,la);
var point21=21*la;var $22=new Float32Array($H,point22,la);
var point22=22*la;var $23=new Float32Array($H,point23,la);
var point23=23*la;var $24=new Float32Array($H,point24,la);
var point24=24*la;var $25=new Float32Array($H,point25,la);
var point25=25*la;var $26=new Float32Array($H,point26,la);
var point26=26*la;var $27=new Float32Array($H,point27,la);
var point27=27*la;var $28=new Float32Array($H,point28,la);
var point28=28*la;var $29=new Float32Array($H,point29,la);
var point29=29*la;var $30=new Float32Array($H,point30,la);
var point30=30*la;var $31=new Float32Array($H,point31,la);
var point31=31*la;var $32=new Float32Array($H,point32,la);
var point32=32*la;var $33=new Float32Array($H,point33,la);
var point33=33*la;var $34=new Float32Array($H,point34,la);
var point34=34*la;var $35=new Float32Array($H,point35,la);
var point35=35*la;var $36=new Float32Array($H,point36,la);
var point36=36*la;var $37=new Float32Array($H,point37,la);
var point37=37*la;var $38=new Float32Array($H,point38,la);
var point38=38*la;var $39=new Float32Array($H,point39,la);
var point39=39*la;var $40=new Float32Array($H,point40,la);
var point40=40*la;var $41=new Float32Array($H,point41,la);
var point41=41*la;var $42=new Float32Array($H,point42,la);
var point42=42*la;var $43=new Float32Array($H,point43,la);
var point43=43*la;var $44=new Float32Array($H,point44,la);
var point44=44*la;var $45=new Float32Array($H,point45,la);
var point45=45*la;var $46=new Float32Array($H,point46,la);
var point46=46*la;var $47=new Float32Array($H,point47,la);
var point47=47*la;var $48=new Float32Array($H,point48,la);
var point48=48*la;var $49=new Float32Array($H,point49,la);
var point49=49*la;var $50=new Float32Array($H,point50,la);
var point50=50*la;var $51=new Float32Array($H,point51,la);
var point51=51*la;var $52=new Float32Array($H,point52,la);
var point52=52*la;var $53=new Float32Array($H,point53,la);
var point53=53*la;var $54=new Float32Array($H,point54,la);
var point54=54*la;var $55=new Float32Array($H,point55,la);
var point55=55*la;var $56=new Float32Array($H,point56,la);
var point56=56*la;var $57=new Float32Array($H,point57,la);
var point57=57*la;var $58=new Float32Array($H,point58,la);
var point58=58*la;var $59=new Float32Array($H,point59,la);
var point59=59*la;var $60=new Float32Array($H,point60,la);
var point60=60*la;var $61=new Float32Array($H,point61,la);
var point61=61*la;var $62=new Float32Array($H,point62,la);
var point62=62*la;var $63=new Float32Array($H,point63,la);
 
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);$"+j+".set($$1);");
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
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
// r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
// t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.getElementById("mv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){return;}
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
eval("if ($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");}");
eval("if ($F=="+i+"){var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+"); $F="+loca+";$Bu="+locb+";}");
}
var $bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
Module.ccall("clr",null,["Number","Number","Number"],[agav[201],agav[101],agav[1]]);
Module.ccall("frm");

setTimeout(function(){
M();
if(loopLoop==true){
if(f==true){
if(mmvv.currentTime>a){
mmvv.currentTime-=0.016;
}else{
f=false;
if(mmvv.currentTime<b){
mmvv.currentTime+=0.016;
}else{
f=true;
}}}
if(f==false){
if(mmvv.currentTime<b){
mmvv.currentTime+=0.016;
}else{
f=true;
if(mmvv.currentTime>a){
mmvv.currentTime-=0.016;
}else{
f=false;
}}}}
},16.666666)}
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
return;
}

}
