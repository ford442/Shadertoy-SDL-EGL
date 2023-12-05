#include "../../include/video/video_test.hpp"

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

EMSCRIPTEN_RESULT ret;

EGLDisplay display;
EGLContext contextegl;
EGLSurface surface;
EGLint config_size,major,minor;

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;

static const EGLint attribut_list[]={
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB,
EGL_NONE
};

static const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,32,
EGL_NONE
};

boost::function<EM_BOOL(int,int,float *,float *)>avgFrm=[](int Fnum,int leng,float *ptr,float *aptr){
max=0.0f;
min=1.0f;
sum=0.0f;
avgSum=0.0f;
minSum=0.0f;
maxSum=0.0f;
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
return EM_TRUE;
};

extern "C" {

EM_BOOL nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
return EM_TRUE;
}

}

EM_JS(void,ma,(),{
"use strict";
const pnnl=document.body;
var vv=document.querySelector("#mv");
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
vv.currentTime+=-(0.016);
}else{
f=false;
}}else if(vv.currentTime<b){
vv.currentTime+=(0.016);
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
function nextPowerOf2(n){
if (n & (n - 1)) {
var m = n;
while (m & (m - 1)) {
m = m | (m >> 1);
}
return m;
} else {
return n;
}
}
pnnl.addEventListener('keydown',doKey);
pnnl.addEventListener('keydown',doKeyUp);
var w$=parseInt(document.querySelector("#wid").innerHTML,10);
var h$=parseInt(document.querySelector("#hig").innerHTML,10);
if(w$<1){w$=640;h$=640;}
vv=document.querySelector("#mv");
var $H=Module.HEAPF64.buffer;
var la=h$*w$*4;
var pointa=nextPowerOf2(77*la);
var agav=new Float64Array($H,pointa,320);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.querySelector("#bcanvas");
const contx=bcanvas.getContext("webgl2",{alpha:true,depth:true,stencil:true,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true});
// contx.getExtension('WEBGL_color_buffer_float');
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
contx.getExtension('EXT_color_buffer_float');
  
// contx.disable(gl.DITHER);

const g=new GPUX({mode:'gpu',canvas:bcanvas,webGl:contx});
const g2=new GPUX({mode:'gpu'});
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
// castle way
// const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
// GE way
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// castle way
// const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
// GE way
const glslAveg=`float Aveg(float a,float b){return(0.999-(((a)-(b))*((a)*(0.999/(0.999-b)))));}`;
const glslStone=`float Stone(float a,float b,float c,float d){return(max(((a-(d-(d*0.5)))+(b-(d-(d*0.5)))+(c-(d-(d*0.5)))*4.0),0.0));}`;
const glslStoned=`float Stoned(float a,float b,float c){return(min((a+c),1.0)-((b*0.3)*0.14));}`;
// g.addNativeFunction('Stone',glslStone,{returnType:'Number'});
// g.addNativeFunction('Stoned',glslStoned,{returnType:'Number'});
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
// GE way
var P=v[this.thread.y][this.thread.x];
var av$=Ave(P[0],P[1],P[2]);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setPipeline(true).setOutput([h$,h$]);

  //castle way
// var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
// var av$=Ave(P[0],P[1],P[2]);
// return[P[0],P[1],P[2],av$];
// }).setTactic("precision").setPrecision('single').setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);

let r=g.createKernel(function(f){
 /*   //castle way
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
*/
  
// GE way
var p=f[this.thread.y][this.thread.x];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
/*
var rr;
var gg;
var bb;
var der=p[0];
var neerg=p[1];
var eulb=p[2];

if(der>0.333){
 rr=Silver(der);
}else{
 rr=GoldR(der);
 }

if(neerg>0.4){
gg=Silver(neerg);
}else{
gg=GoldG(neerg);
}

if(eulb>0.5){
bb=Silver(eulb);
}else{
bb=GoldB(eulb);
}
this.color(GoldR(p[0]),GoldG(p[1]),GoldB(p[2]),aveg);
 */
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setGraphical(true).setOutput([h$,h$]);

w$=parseInt(document.querySelector("#wid").innerHTML,10);
h$=parseInt(document.querySelector("#hig").innerHTML,10);
vv=document.querySelector("#mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
la=h$*w$*4;
sz=(h$*w$)/8;
pointa=nextPowerOf2(77*la);
agav=new Float64Array($H,pointa,320);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
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
w$=parseInt(document.querySelector("#wid").innerHTML,10);
h$=parseInt(document.querySelector("#hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
l=w$*h$*4;
la=h$*w$*4;
sz=(h$*w$)/8;
pointa=nextPowerOf2(77*la);
var agav=new Float64Array($H,pointa,320);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float64Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.querySelector("#mv");
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
pointb=nextPowerOf2(66*la);
// Module.ccall('runWebGPU',{async: true});
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
setTimeout(function(){
M();
},16.66);
};
M();
document.querySelector("#di").onclick=function(){
//   Module.ccall('startWebGPU',{async: true});
T=true;
S();
};
return()=>{
T=true;
};
}
});

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

GLfloat x;
GLfloat y;
EM_BOOL ms_l;

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
return EM_TRUE;
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

std::function<EM_BOOL(float,float,GLfloat,EGLint)>uni=[](float xx,float yy,GLfloat time,EGLint fram){
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
return EM_TRUE;
};

const char *sources[4];
GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

// std::function<void()>renderFrame=[](){
void renderFrame(){
t2=steady_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,indc);
glFlush();
// nanosleep(&req,&rem);
iFrame++;
// glFinish();
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

std::function<EM_BOOL()>strt=[](){
EGLConfig eglconfig=NULL;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
if(eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size)==EGL_TRUE && eglconfig!=NULL){
if(eglBindAPI(EGL_OPENGL_ES_API)!=EGL_TRUE){
}
EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE};
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
if(contextegl==EGL_NO_CONTEXT){
}
else{
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}}
const char *fileloc="/shader/shader1.toy";
EGLint v0=0,v3=3;
GLfloat gF=F;
GLfloat gF0=F0;
GLfloat gFm1=Fm1;
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const char common_shader_header_gles3[]=
"#version 300 es \n"
"#pragma (fastmath on)\n"
"#pragma optionNV(fastmath on)\n"
"#pragma (fastprecision on)\n"
"#extension GL_ALL_EXTENSIONS : enable\n"
"#extension OES_standard_derivatives : disable\n"
"#pragma (STDGL all)\n"
"#pragma optionNV(STDGL all)\n"
"#pragma (precision highp double)\n"
"#pragma (precision highp vec4)\n"
"#pragma (precision highp mat4)\n"
"#pragma (precision highp uint)\n"
"#pragma (precision highp short)\n"
"#pragma (precision highp bool)\n"
"#pragma (precision highp atomic_uint)\n"
// "#pragma (precise none)\n"
// "#pragma STDGL(strict off)\n"
"#pragma optimize(on)\n"
"#pragma debug(off)\n"
"#undef HW_PERFORMANCE \n"
"#define HW_PERFORMANCE 1 \n"
"precision highp float;precision highp int;precision highp sampler3D;precision highp sampler2D;\n";
const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
const char fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution;uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"out vec4 fragColor;\n";
const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";
const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res;
GLuint VCO,ECO,vtx,frag;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
iFrame=0;
clk_l=true;
// Size=EM_ASM_INT({return parseInt(window.innerHeight);});
double wi,hi;
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
eglBindAPI(EGL_OPENGL_ES_API);
// eglBindAPI(EGL_OPENGL_API);
  
const EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
  
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
// EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
//   EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
  
const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_RENDER_BUFFER,EGL_TRIPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,64,
EGL_SAMPLE_BUFFERS,1,
EGL_SAMPLES,8,
EGL_NONE
};
  
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_depth_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_buffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_texture_storage");
emscripten_webgl_enable_extension(ctx,"ARB_texture_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_texture_rg");
emscripten_webgl_enable_extension(ctx,"ARB_texture_rgb10_a2");
// emscripten_webgl_enable_extension(ctx,"EXT_texture_rgb10_a2"); // Colab AI: "EXT_texture_rgb10_a2 is an older extension, while ARB_texture_rgb10_a2 is a newer extension."
emscripten_webgl_enable_extension(ctx,"EXT_texture_integer");
emscripten_webgl_enable_extension(ctx,"EXT_texture_integer_storage");
emscripten_webgl_enable_extension(ctx,"ARB_texture_half_float");
// emscripten_webgl_enable_extension(ctx,"EXT_texture_rg");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
// emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx,"EXT_float_blend");
emscripten_webgl_enable_extension(ctx,"EXT_frag_depth");
emscripten_webgl_enable_extension(ctx,"EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB");
emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx,"EXT_clip_cull_distance");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"OES_depth32");
emscripten_webgl_enable_extension(ctx,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx,"OES_single_precision");
emscripten_webgl_enable_extension(ctx,"GL_EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx,"GL_NV_memory_attachment");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
// eglInitialize(display,&v3,&v0);
// eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
// contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
// surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
// eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// nanosleep(&req,&rem);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
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
EGLint atb_pos=0;
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
glClearColor(gF,gF,gF,gF);
  // glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
// glDisable(GL_BLEND);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_SCISSOR_TEST);
glDepthFunc(GL_LESS);
glClearDepthf(1.0);
glEnable(GL_POLYGON_OFFSET_FILL);
glPolygonOffset(0.0f,0.0f);
// glFrontFace(GL_CW);
glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT,GL_MAX);
glDisable(GL_DITHER);
t1=steady_clock::now();
glViewport(0,0,GLint(Size),GLint(Size));
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
emscripten_set_main_loop((void(*)())renderFrame,0,0);
return EM_TRUE;
};

static inline boost::function<EM_BOOL()>jsmain=[](){ma();return EM_TRUE;};

extern "C" {

EM_BOOL str(){
strt();
return EM_TRUE;
}

EM_BOOL b3(){
jsmain();
return EM_TRUE;
}

}


extern "C"{

int rNd(int Th){
  std::random_device rd;
  std::srand(rd());
  int rD=std::rand()%Th;
  return rD;
}

int(* RnD)(int){&rNd};

int r4nd(int tH){
  int Rg=(*RnD)(tH);
  return Rg;
}

}

EM_JS(void,js_main,(),{
"use strict";
const bezl=document.getElementById('circle');
window.scroll(0,0);
const switchy=document.getElementById('di');
var vide=document.querySelectorAll('video');
let $tim=document.getElementById('tim');
let $itim=document.getElementById('itim');
var nn=window.innerHeight;
document.getElementById('canvasSize').innerHTML=window.innerHeight;
bezl.height=parseInt(window.innerHeight,10);
bezl.width=parseInt(window.innerWidth,10);
switchy.click();
var lockVid=0;

function spKey(e){
if(e.code=='Space'){
e.preventDefault();
if(lockVid==0){lockVid=1;};
if(lockVid==1){lockVid=0;};
};
if(e.code=='KeyZ'){lockVid=1;};
if(e.code=='KeyX'){lockVid=0;};
}

const pnnl=document.body;
pnnl.addEventListener('keydown',spKey);

var $vids=[];
var $shds=[];

function vids(xml){
const vparser=new DOMParser();
const htmlDocv=vparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocv.getElementsByTagName('pre')[0].getElementsByTagName('a');
$vids[0]=preList.length;
for(var i=1;i<preList.length;i++){
var vtxxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
vtxxt=vtxxt.replace(Self,"");
let vidMenu1=document.getElementById('vi1').value;
let ar1=vidMenu1+'video/'+vtxxt;
let ar2=Self+'video/'+vtxxt;
if(vidMenu1!='Default'){
$vids[i]=ar1;
}else{
$vids[i]=ar2;
};
};
}

function scanVideos(){
const fxhttp=new XMLHttpRequest();
// fxhttp.withCredentials=false;
fxhttp.addEventListener("load",function(){
vids(this);
});
let vidMenua1=document.getElementById('vi1').value;
if(vidMenua1!='Default'){
var looc=vidMenua1+'video/';
}else{
var looc='video/';
};
fxhttp.open('GET',looc,true);
fxhttp.send();
}

function shds(xml){
const sparser=new DOMParser();
const htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,'');
txxt=txxt.replace(Self,'');
$shds[i+1]='https://glsl.1ink.us/shadersALL/'+txxt;
};
var randShade=Math.random();
randShade=Math.floor($shds[0]*randShade)+5;
document.querySelector('#path').innerHTML=$shds[randShade];
var pth=document.querySelector('#path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
ff.onload=function(oEvent){
const sarrayBuffer=ff.response;
if(sarrayBuffer){
const sfil=new Uint8ClampedArray(sarrayBuffer);
setTimeout(function(){
FS.writeFile('/shader/shader1.toy',sfil);
},150);
setTimeout(function(){
// normalResStart();
},150);
};};
ff.send(null);
};

function scanShaders(){
const dxhttp=new XMLHttpRequest();
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
// console.log(this);
shds(this);
}};
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
}

function normalResStart(){
bezl.width=window.innerWidth;
bezl.height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('bcanvas').width=window.innerHeight;
document.getElementById('bcanvas').height=window.innerHeight;
document.getElementById('acanvas').width=window.innerHeight;
document.getElementById('acanvas').height=window.innerHeight;
setTimeout(function(){
Module.ccall('b3');
},250);
// setTimeout(function(){
// Module.ccall('b3_egl');
// },750);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
bezl.width=window.innerWidth;
bezl.height=window.innerHeight;
switchy.click();
},450);
}
  
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt;

function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();var slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
var $ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});setTimeout(function(){slt=tem.innerHTML;},8);},16);});

function loada(){
var mv,lo;
if(lockVid!=1){
bezl.height=parseInt(window.innerHeight,10);
bezl.width=parseInt(window.innerWidth,10);
document.getElementById('ldv').addEventListener('canplay',function(){
var nn=window.innerHeight;
var vvh=this.videoHeight;
var vvw=this.videoWidth;
document.getElementById('ldv').height=parseInt(nn,10);
document.getElementById('ldv').width=this.videoWidth;
document.getElementById('wid').innerHTML=window.innerHeight;
document.getElementById('hig').innerHTML=window.innerHeight;
var $sc=this.duration;
var mic=Math.round($sc*1000000);
if(mic>0){
var $pt=Module.ccall('r4nd','Number',['Number'],[mic]);
};
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.getElementById('idur').innerHTML=mic/1000000;
document.getElementById('itim').innerHTML=$pt;
});
$lt=Math.round(tem.innerHTML);
var $ldt=$tim.innerHTML;
var $ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var vidNum=($vids[0]-5);
if(vidNum>0){
var rnum=Module.ccall('r4nd','Number',['Number'],[vidNum]);
};
let vidSrc=$vids[rnum+5];
var $h=window.innerHeight;
var he=document.getElementById('hig').innerHTML;
var wi=document.getElementById('wid').innerHTML;
var r$=he/$h;
var $w=wi/r$;
var $hi=he-parseInt(window.innerHeight,10);
if($hi>1){$h=parseInt(window.innerHeight,10);var $r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;}
var $hg=$h+'px';
mv=vide[0].id;
lo=vide[1].id;
vide[0].id=lo;
vide[1].id=mv;
document.getElementById('mv').play();
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("wrap").style.pointerEvents="auto";
document.getElementById('ldv').src=vidSrc;
document.getElementById('ldv').currentTime=$itim.innerHTML;
document.getElementById('ldv').load();
switchy.click();
}
setTimeout(function(){
loada();
},$ldt);
}

document.getElementById('startBtn').addEventListener('click',function(){
scanShaders();
scanVideos();
loada();
});

});

void(*jss)(){&js_main};

int main(){
EM_ASM({
FS.mkdir("/shader");
});
jss();
return 0;
}
