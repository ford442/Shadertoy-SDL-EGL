#include "b3.hpp"
#include <vector>

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
};
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
};
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
};
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
};
aptr[200]=maxSum/32;
return;
};

extern "C" {

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
};

};

EM_JS(void,ma,(),{
"use strict";
const pnnl=document.body;
var vv=document.getElementById("mv");
  /*
let intervalBackward;

function back(){
intervalBackward=setInterval(function(){
if(vv.currentTime==0){
clearInterval(intervalBackward);
}else{
vv.currentTime+=-(0.016);
};
},16.66);
};

let intervalForward;

function forward(){
intervalForward=setInterval(function(){
vv.currentTime+=-(0.016);
},16.66);
};

var intervalLoop=null;
var stp;
var f;
  
function backForth(stp){
var a=stp-0.888;
var b=stp+0.888;
intervalLoop=setInterval(function(){
if(f==true){
if(vv.currentTime>=a){
vv.currentTime-=0.016;
}else{
f=false;
if(vv.currentTime<=b){
vv.currentTime+=0.016;
}else{
var f=true;
};};
if(f==false){
if(vv.currentTime<=b){
vv.currentTime+=0.016;
}else{
f=true;
if(vv.currentTime>=a){
vv.currentTime-=0.016;
}else{
var f=false;
};};
},16.6);
};

function stpForward(){
clearInterval(intervalForward);
};

function stpBack(){
clearInterval(intervalBackward);
};

function stpBackForth(){
clearInterval(intervalLoop);
};

var Mov=1;

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
if(Mov==1){vv=document.getElementById("mv");Mov=0;vv.pause();}
else if(Mov==0){vv=document.getElementById("mv");Mov=1;vv.play();}
};
if (e.code=='KeyW'){vv=document.getElementById("mv");Mov=1;vv.pause();forward();}
if (e.code=='KeyS'){vv=document.getElementById("mv");Mov=1;vv.pause();back();}
if (e.code=='KeyZ'){vv=document.getElementById("mv");Mov=1;vv.pause();
var stp=vv.currentTime;
backForth(stp);}
if (e.code=='KeyX'){vv=document.getElementById("mv");stpBackForth();vv.play();}
};

function doKeyUp(e){
if (e.code=='KeyS'){Mov=0;stpBack();vv.pause();}
if (e.code=='KeyW'){Mov=0;stpForward();vv.pause();}
};

pnnl.addEventListener('keydown',doKey);
pnnl.addEventListener('keydown',doKeyUp);
  
  
  */
let w$=parseInt(document.getElementById("wid").innerHTML,10);
let h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
let $H=Module.HEAPF32.buffer;
let la=h$*h$*4;
var pointa=77*la;
let agav=new Float32Array($H,pointa,300);
let sz=(h$*h$)/8;
var avag=0.750000;
var min=1.000000;
var max=0.000000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
const bcanvas=document.getElementById("bcanvas");
const contx=bcanvas.getContext("webgl2",{preferLowPowerToHighPerformance:false,precision:'highp',logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:false,stencil:false,imageSmoothingEnabled:true,preserveDrawingBuffer:false,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true,willReadFrequently:true,majorVersion:2,minorVersion:0});
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
contx.getExtension('NV_depth_nonlinear');
contx.disable(gl.DITHER);
contx.enable(gl.CULL_FACE);
contx.enable(gl.DEPTH_TEST);
contx.disable(gl.BLEND);
contx.disable(gl.STENCIL_TEST);
contx.disable(gl.SCISSOR_TEST);
const g=new GPU({canvas:bcanvas,webGl:contx});
const g2=new GPU();
const glslAve=`float Ave(float a,float b,float c) {return (a+b+c)/3.0;}`;
/// const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((g+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/4.0);}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return((f+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/4.0);}`;
const glslAveg=`float Aveg(float a,float b){return(0.999999-(((a)-(b))*((a)*(0.999999/(0.999999-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setOutput([sz]);
const t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
// }).setTactic("precision").setPrecision('single').setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
}).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
// }).setTactic("precision").setPipeline(true).setPrecision('unsigned').setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
const r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
// var $fmax=this.constants.fmax;
// var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
// var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
/// var Min=(4.0*(($fmax-($aavg-$fmin))/2.0));
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
// var Min=(4.0*(($fmax-(p[3]-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
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
};
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
  
for (i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);$"+j+".set($$1);");
};

let d=S();if(d)d();d=S();function S(){
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
};
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
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
eval("if ($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");}");
eval("if ($F=="+i+"){var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
};
if($F%4==0){
let $bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
};
setTimeout(function(){
M();
},16.66);
};
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
};
});

SDL_AudioDeviceID dev;
struct{Uint8* snd;int pos;Uint32 slen;SDL_AudioSpec spec;}wave;

void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
return;
}};

void qu(int rc){
SDL_Quit();
return;
};

void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
};
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
};

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
};
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
};

void plt(){
char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
};
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
};
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
return;
};

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
};
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
};
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}};
return 0;
};

void uni(float xx,float yy,GLfloat time,EGLint fram){
GLfloat mX,mY;
if(ms_l==true){
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clk_l=false;
};
GLfloat mm=S*xx;
GLfloat nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
};
glUniform1f(uni_tme,time);
glUniform1i(uni_frm,fram);
return;
};

void renderFrame(){
glClear(GL_STENCIL_BUFFER_BIT);
t3=t2;
EMSCRIPTEN_RESULT ret;
t2=steady_clock::now();
duration<double>time_spanb=duration_cast<duration<double>>(t2-t3);
TtimeDelta=time_spanb.count();
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
glClear(GL_COLOR_BUFFER_BIT);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,indc);
 glClear(GL_DEPTH_BUFFER_BIT);

// glFlush();
// nanosleep(&req,&rem);
iFrame++;
// glFinish();
return;
};

static const char8_t *read_file(const char *filename){
char8_t *result=NULL;
long length=0;
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
};
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
};
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
} ;
fclose(file);
return result;
};
return nullptr;
};

GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;i++){
srclens[i]=(GLsizei)strlen(sources[i]);
};
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
};

void strt(){
// emscripten_cancel_main_loop();
nanosleep(&req,&rem);
const char *fileloc="/shader/shader1.toy";
EGLint v0=0,v3=3;
GLfloat gF=F;
GLfloat gF0=F0;
GLfloat gFm1=Fm1;

// typedef struct{GLfloat XYZW[4];}Vertex;
typedef struct{std::vector<GLfloat>XYZW;}Vertex;
 
// std::vector<GLfloat>aA={gFm1,gFm1,gF,gF};
// std::vector<GLfloat>bB={gF,gFm1,gF,gF};
// std::vector<GLfloat>cC={gF,gF,gF,gF};
// std::vector<GLfloat>dD={gFm1,gF,gF,gF};
// std::vector<GLfloat>eE={gFm1,gFm1,gFm1,gF};
// std::vector<GLfloat>fF={gF,gFm1,gFm1,gF};
// std::vector<GLfloat>gG={gF,gF,gFm1,gF};
// std::vector<GLfloat>hH={gFm1,gF,gF,gF};

const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
// const Vertex vertices[]={{aA},{bB},{cC},{dD},{eE},{fF},{gG},{hH}};

const char common_shader_header_gles3[]=
"#version 300 es \n"
"#undef HW_PERFORMANCE \n"
"#define HW_PERFORMANCE 0 \n"
"precision highp float;precision mediump int;precision mediump sampler3D;precision mediump sampler2D;\n";
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
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
EGL_CONFORMANT,EGL_OPENGL_BIT,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,0,
EGL_BUFFER_SIZE,32,
EGL_SAMPLE_BUFFERS,32,
EGL_SAMPLES,32,
EGL_NONE
};
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_FALSE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
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
emscripten_webgl_enable_extension(ctx,"NV_depth_nonlinear");
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
nanosleep(&req,&rem);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
nanosleep(&req,&rem);
static const char* default_fragment_shader=(char*)read_file(fileloc);
nanosleep(&req,&rem);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
nanosleep(&req,&rem);
shd_prg=glCreateProgram();
nanosleep(&req,&rem);
glAttachShader(shd_prg,vtx);
nanosleep(&req,&rem);
glAttachShader(shd_prg,frag);
nanosleep(&req,&rem);
atb_pos=0;
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
nanosleep(&req,&rem);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
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
glUniform3f(uni_res,S,S,1.0f);
glUniform3f(smp_chn_res,S,S,1.0f);
glClearColor(gF0,gF0,gF0,0.7f);
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
glDisable(GL_BLEND);
glDisable(GL_STENCIL_TEST);
glDisable(GL_SCISSOR_TEST);
glDepthFunc(GL_LESS);
glFrontFace(GL_CW);
// glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
// glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_DITHER);
t1=steady_clock::now();
// glViewport(0,0,GLint(Size),GLint(Size));
emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
};

extern "C" {

void str(){
strt();
return;
};

void pl(){
plt();
return;
};

void b3(){
ma();
return;
};

}

int main(){
EM_ASM({
"use strict";
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
