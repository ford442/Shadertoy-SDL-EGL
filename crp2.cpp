#include <emscripten.h>

extern "C" {

EM_JS(void,ma,(),{
  
let dis=set();if(dis)dis();dis=set();
var h,ww,kna,knb,knbb,knc,kncb,knd,kndb,rott,rottb,rottc;
function set(){ww=document.getElementById("iwid").innerHTML;h=document.getElementById("ihig").innerHTML;
ow=document.getElementById("wid").innerHTML;oh=document.getElementById("hig").innerHTML;
let cnP=document.getElementById("cp");let flP=document.getElementById("flip");let vd=document.getElementById("mv");
var ac=document.getElementById("imag");var actx=ac.getContext("2d",{alpha:true,desynchronized:false,premultipliedAlpha:false});
actx.drawImage(vd,0,0,ww,h);var imgData=actx.getImageData(0,0,ww,h);var rgbdat=actx.createImageData(ww,h);var rgbd=rgbdat.data;
var imgg=imgData.data;var i;
for(i=0;i<ww*h*4;i=i+4){
var rgb=imgg[i]*.2126+imgg[i+1]*.7152+imgg[i+2]*.0722;
var rgbb=Math.floor((imgg[i]+imgg[i+1]+imgg[i+2])/6);
var rgbc=Math.floor((imgg[i]+imgg[i+1]+imgg[i+2])/3);
if(rgb>126){
if(rgb>209){rgbd[i]=255;rgbd[i+1]=128;rgbd[i+2]=0;rgbd[i+3]=255;}
else if(rgb>193){rgbd[i]=255;rgbd[i+1]=0;rgbd[i+2]=0;rgbd[i+3]=128;}
else if(rgb>177){rgbd[i]=0;rgbd[i+1]=255;rgbd[i+2]=255;rgbd[i+3]=255;}
else if(rgb>161){rgbd[i]=0;rgbd[i+1]=0;rgbd[i+2]=255;rgbd[i+3]=128;}
else if(rgb>145){rgbd[i]=0;rgbd[i+1]=255;rgbd[i+2]=0;rgbd[i+3]=255;}
else if(rgb>128){rgbd[i]=255;rgbd[i+1]=255;rgbd[i+2]=0;rgbd[i+3]=128;}}
else{rgbd[i]=110;rgbd[i+1]=110;rgbd[i+2]=110;rgbd[i+3]=0;}}
ctx.putImageData(rgbdat,0,0);function Ra(){flP.setAttribute("style","transform: scaleX(1);");cnP.setAttribute("style","transform: scaleY(1);")}
function Rb(){flP.setAttribute("style","transform: scaleX(-1);");cnP.setAttribute("style","transform: scaleY(-1);")}
knb=document.getElementById("rra");kna=document.getElementById("mainr");knc=document.getElementById("rrb");knd=document.getElementById("rrc");
knbb=document.getElementById("rrab");kncb=document.getElementById("rrbb");kndb=document.getElementById("rrcb");
rate=kna.innerHTML;rott=0;rottb=0;rottc=0;let dur=document.getElementById("temptime").innerHTML/10;let dsd=false;
function $rn(){if(dsd){return}function rrra(rta){cnP.setAttribute("style","transform: rotate("+rta+"deg);")}
function rrrb(rtb){cnP.setAttribute("style","transform:rotate("+rtb+"deg);")}
function rrrc(rtc){cnP.setAttribute("style","transform: rotate("+rtc+"deg);")}
if(rott-knd.innerHTML<0){rott=rott+360-knd.innerHTML}else{rott=rott-knd.innerHTML}
rrra(rott);if(rottb-knc.innerHTML<0){rottb=rottb+360-knc.innerHTML}else{rottb=rottb-knc.innerHTML}setTimeout(function(){Rb();
rrrb(rottb)},rate);if(rottc+knb.innerHTML>360){rottc=rottc+knb.innerHTML-360}else{rottc=rottc+knb.innerHTML}setTimeout(
function(){Ra();rrrc(rottc)},rate);setTimeout(function(){$rn()},rate)}$rn();document.getElementById("di").onclick=function(){dsd=true;set()};return()=>{dsd=true}}
});

}

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

extern "C" {

#include <unistd.h>
#include <SDL2/SDL.h>
SDL_AudioDeviceID dev;
struct{Uint8* snd;int pos;Uint32 slen;SDL_AudioSpec spec;}wave;

void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
return;
}}

void qu(int rc){
SDL_Quit();
return;
}

void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
}

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
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
}

void plt(){
char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
return;
}

}

extern "C" {

#include <emscripten/html5.h>

}

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

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1

}


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
return 0;
}

using namespace std;
using namespace std::chrono;

steady_clock::time_point t1,t2;
GLuint uni_frm,uni_tme,uni_res,shader;
double Ttime;
EGLint iFrame;
GLsizei s4=4;
int v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v10=10,v16=16,v24=24,v32=32;
int a,b;
float F=1.0f;
float F0=0.0f;
float Fm1=-1.0f;
float mouseX;
float mouseY;
float cMouseX;
float cMouseY;
int Size;
GLfloat S;
EM_BOOL clk_l;

GLsizei i;
float fps;
float timeSpeed;
struct timespec rem;
struct timespec req={0,10000000};

GLuint uni_mse;

void uni(float xx,float yy,GLfloat time,EGLint fram){
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
return;
}

const char *fileloc="/shader/shader1.toy";
const char *sources[4];
char8_t *result=NULL;
long length=0;

GLubyte indc[]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};

void renderFrame(){
EMSCRIPTEN_RESULT ret;
t2=steady_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,indc);
glFlush();
nanosleep(&req,&rem);
iFrame++;
glFinish();
return;
}

static const char8_t *read_file(const char *filename){
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

void strt(){
emscripten_cancel_main_loop();
nanosleep(&req,&rem);
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{Fm1,Fm1,F,F},{F,Fm1,F,F},{F,F,F,F},{Fm1,F,F,F},{Fm1,Fm1,Fm1,F},{F,Fm1,Fm1,F},{F,F,Fm1,F},{Fm1,F,F,F}};
const char common_shader_header_gles3[]=
"#version 300 es \n precision highp float;precision highp int;precision highp sampler3D;precision highp sampler2D;";
const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";
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
Size=EM_ASM_INT({return parseInt(window.innerHeight);});
S=(GLfloat)Size;
// eglBindAPI(EGL_OPENGL_ES_API);
eglBindAPI(EGL_OPENGL_API);
const EGLint attribut_list[]={ 
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,v3,
EGL_CONTEXT_MINOR_VERSION_KHR,v0,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,v8,
EGL_GREEN_SIZE,v8,
EGL_BLUE_SIZE,v8,
EGL_ALPHA_SIZE,v8,
EGL_DEPTH_SIZE,v24,
EGL_STENCIL_SIZE,v8,
EGL_BUFFER_SIZE,v32,
EGL_SAMPLE_BUFFERS,v4,
EGL_SAMPLES,v32,
EGL_NONE
};
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=v2;
attr.minorVersion=v0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"EXT_texture_float_linear");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glGenBuffers(v1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STREAM_DRAW);
nanosleep(&req,&rem);
glGenVertexArrays(v1,&VCO);
glBindVertexArray(VCO);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STREAM_DRAW);
nanosleep(&req,&rem);
static const char* default_fragment_shader=(char*)read_file(fileloc);
nanosleep(&req,&rem);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,v2,sources);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,v4,sources);
nanosleep(&req,&rem);
shd_prg=glCreateProgram();
nanosleep(&req,&rem);
glAttachShader(shd_prg,vtx);
nanosleep(&req,&rem);
glAttachShader(shd_prg,frag);
nanosleep(&req,&rem);
atb_pos=v0;
glBindAttribLocation(shd_prg,v0,"iPosition");
glLinkProgram(shd_prg);
nanosleep(&req,&rem);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,v4,GL_FLOAT,GL_TRUE,0,(GLvoid*)0);
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
glUniform3f(uni_res,S,S,1.0);
glUniform3f(smp_chn_res,S,S,1.0);
glClearColor(F0,F0,F0,0.5);
// glDisable(GL_BLEND);
// glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
glDisable(GL_SCISSOR_TEST);
glDepthFunc(GL_LESS);
glFrontFace(GL_CW);
glEnable(GL_BLEND);
glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
// glDisable(GL_CULL_FACE);
glDisable(GL_DITHER);
t1=steady_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
}

extern "C" {

void str(){
strt();
return;
}

void pl(){
plt();
return;
}

void b3(){
ma();
return;
}

}

int main(){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
