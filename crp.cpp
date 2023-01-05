#include <emscripten.h>
#include <emscripten/html5.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#define __gl2_h_
#include <GLES2/gl2ext.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <SDL2/SDL.h>

using namespace std;
using namespace std::chrono;

//  SDL
SDL_AudioDeviceID dev;
struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;

high_resolution_clock::time_point t1,t2,t3;
GLuint DBO,EBO,VBO,CBO,shader_program,shader,frame,sampler_channel[4],sampler_channel_res,TEX;
GLuint uniform_dtime,uniform_fps,uniform_date,VCO,ECO,CCO,vtx,frag,uniform_frame,uniform_time,uniform_res,uniform_mouse;
long double Ttime,Dtime;
EGLint iFrame;
static GLsizei s4=4;
static EGLint v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v24,v32=32,a,b;
static GLfloat F=1.0f;
static GLfloat F0=0.0f;
static GLfloat Fm1=-1.0f;
static GLfloat mouseX;
static GLfloat mouseY;
static GLfloat cMouseX;
static GLfloat cMouseY;
static GLfloat x;
static GLfloat y;
static EM_BOOL mouseLPressed;
static int S;
static GLfloat Size;
static EM_BOOL clickLoc;
static GLfloat mX,mY;

EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
GLsizei i;
GLfloat fps;
GLfloat timeSpeed;
EGLint config_size,major,minor,attrib_position;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
struct timespec rem;
struct timespec req={0,8333333};
EMSCRIPTEN_RESULT ret;
typedef struct{GLfloat XYZW[4];}Vertex;
static Vertex vertices[]={{Fm1,Fm1,F,F},{F,Fm1,F,F},{F,F,F,F},{Fm1,F,F,F},{Fm1,Fm1,Fm1,F},{F,Fm1,Fm1,F},{F,F,Fm1,F},{Fm1,F,F,F}};
static GLubyte Indices[]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};
static const char *fileloc="/shader/shader1.toy";
const char *sources[4];
char8_t *result=NULL;
long length=0;
// const GLenum attt[]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3};
static const char common_shader_header_gles3[]=
"#version 300 es \n precision highp float;precision highp int;precision lowp sampler3D;precision highp sampler2D;";
static const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";
static const char fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution;uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;"
"uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"out vec4 fragColor;\n";
static const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\n\0";
static const char* common_shader_header=common_shader_header_gles3;
static const char* vertex_shader_body=vertex_shader_body_gles3;
static const char* fragment_shader_header=fragment_shader_header_gles3;
static const char* fragment_shader_footer=fragment_shader_footer_gles3;

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
static GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;++i){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

static EM_BOOL mouse_callback(int eventType,const EmscriptenMouseEvent *e,void *userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
mouseLPressed=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
mouseLPressed=false;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 0;
}

static void uniforms(GLfloat xx,GLfloat yy,GLfloat time,EGLint fram){
if(mouseLPressed==true){
if(clickLoc==true){
const GLfloat xxx=xx;
const GLfloat yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clickLoc=false;
}
glUniform4f(uniform_mouse,(Size*xx),(Size*yy),mX,mY);
}else{
clickLoc=true;
}
glUniform1f(uniform_time,time);
glUniform1i(uniform_frame,fram);
}

static void renderFrame(){
eglSwapBuffers(display,surface);
t2=high_resolution_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<double>time_spana=duration_cast<duration<double>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_callback);
mouseX=x/Size;
mouseY=(Size-y)/Size;
uniforms(mouseX,mouseY,Ttime,iFrame);
 
// glUniform1i(sampler_channel[3],GL_TEXTURE0);

emscripten_webgl_make_context_current(ctx);
glBindTexture(GL_TEXTURE_2D,TEX);

glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,Indices);
glFinish();
// nanosleep(&req,&rem);
iFrame++;
}

void avgFrm(int F,int leng,float *dat,float *aLoc){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for (int i=4;i<leng;i=i){
sum+=dat[i];
if(max<dat[i]){max=dat[i];}
if(min>dat[i]&&dat[i]>0){min=dat[i];}
}
sum=sum/leng;
aLoc[F]=sum;
aLoc[F+100]=min;
aLoc[F+200]=max;
for(int i=1;i<65;i++){
avgSum+=aLoc[i];
}
aLoc[0]=avgSum;
for(int i=1;i<65;i++){
minSum+=aLoc[i+100];
}
aLoc[100]=minSum;
for(int i=1;i<65;i++){
maxSum+=aLoc[i+200];
}
aLoc[200]=maxSum;
}

static void strt(){
iFrame=0;
clickLoc=true;
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
Size=(float)S;
eglBindAPI(EGL_OPENGL_ES_API);
static const EGLint attribut_list[]={ 
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
static const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,v3,
EGL_CONTEXT_MINOR_VERSION_KHR,v0,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
static const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
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
EGL_NONE
};
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
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
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_DRAW);
glGenVertexArrays(v1,&VCO);
glBindVertexArray(VCO);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
static const char* default_fragment_shader=(char*)read_file(fileloc);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,v2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,v4,sources);
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
attrib_position=v0;
glBindAttribLocation(shader_program,v0,"iPosition");
glUseProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
attrib_position=glGetAttribLocation(shader_program,"iPosition");
glEnableVertexAttribArray(attrib_position);
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_TRUE,0,(GLvoid*)0);
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel_res=glGetUniformLocation(shader_program,"iChannelResolution");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
glUniform3f(uniform_res,Size,Size,1.0);
glUniform3f(sampler_channel_res,Size,Size,1.0);
glClearColor(F0,F0,F0,F0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glEnable(GL_BLEND);
glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);

GLfloat greenPixel[4]={0.0f,0.7f,0.21f,0.5f};
glGenTextures(1,&TEX);
glBindTexture(GL_TEXTURE_2D,TEX);
glActiveTexture(GL_TEXTURE0);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_FLOAT,&greenPixel);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glUniform1i(sampler_channel[3],GL_TEXTURE0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

t1=high_resolution_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
}
void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
}}
void qu(int rc){
SDL_Quit();
exit(rc);
}
void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
qu(2);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
}
static Uint8* wptr;
static int lft;
void SDLCALL bfr(void *unused,Uint8* stm,int len){
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
}
void plt(){
cls_aud();
static char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_Quit();
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
}

EM_JS(void,ma,(),{
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
vv=document.getElementById("mv");
let $H=Module.HEAPF32.buffer;
var la=h$*h$*4;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
var sz=(h$*h$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var bcanvas1=document.getElementById("bcanvas1");
var bcanvas2=document.getElementById("bcanvas2");
var bcanvas3=document.getElementById("bcanvas3");

var c1=document.getElementById("c1");
var c2=document.getElementById("c2");
var c3=document.getElementById("c3");

var x1=document.getElementById("x1");
var x2=document.getElementById("x2");
var x3=document.getElementById("x3");

var y1=document.getElementById("y1");
var y2=document.getElementById("y2");
var y3=document.getElementById("y3");
var contx1=bcanvas1.getContext('webgl2',{antialias:false,alpha:true,imageSmoothingEnabled:false,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
var contx2=bcanvas2.getContext('webgl2',{antialias:false,alpha:true,imageSmoothingEnabled:false,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
var contx3=bcanvas3.getContext('webgl2',{antialias:false,alpha:true,imageSmoothingEnabled:false,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
var gA=new GPU({canvas:bcanvas1,webGl:contx1});
var gB=new GPU({canvas:bcanvas2,webGl:contx2});
var gC=new GPU({canvas:bcanvas3,webGl:contx3});
var g2=new GPU();
const glslAve=`float Ave(float a,float b,float c) {return (a + b + c) / 3.0 ;}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g) {return ((((1.0*floor(0.5/((a-b)*0.751)+b))*(((a-b)*g)+b))+(((1.0*(ceil(0.5/f)))*(1.0-(((a-e)*g)+e)))+((1.0*(ceil(0.5/f)))*(((a-d)*0.7511)+d)))+(((0.7501*(1.0-a))+(((1.0-b)*g)+b))/2.0)+(1.0-(f-g))+0.777)/5.0);}`;
const glslAveg=`float Aveg(float a,float b) {return (1.0 - (((a) - (b)) * ((a) * (1.0 / (1.0 - b))))) ;}`;

gA.addNativeFunction('Ave', glslAve, { returnType: 'Number' });
gA.addNativeFunction('Alphe', glslAlphe, { returnType: 'Number' });
gA.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
gB.addNativeFunction('Ave', glslAve, { returnType: 'Number' });
gB.addNativeFunction('Alphe', glslAlphe, { returnType: 'Number' });
gB.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
gC.addNativeFunction('Ave', glslAve, { returnType: 'Number' });
gC.addNativeFunction('Alphe', glslAlphe, { returnType: 'Number' });
gC.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Ave', glslAve, { returnType: 'Number' });

var R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setArgumentTypes(['HTMLImage']).setOutput([sz]);

var tA=gA.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(['HTMLImage']).setDynamicOutput(true).setOutput([w$,h$]);

var tB=gB.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(['HTMLImage']).setDynamicOutput(true).setOutput([w$,h$]);

var tC=gC.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(['HTMLImage']).setDynamicOutput(true).setOutput([w$,h$]);

var rA=gA.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$amax,$amin,$aavg,$aavg,p[3]);
var Min=(($amin*($fmax-$favg)/2.0)+(($amax-$aavg)/2.0)+$aavg);
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
 if (p[3]==1.0){
  aveg=0.0;
 }
this.color(p[3],0.0,0.0,aveg);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);

var rB=gB.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$amax,$amin,$aavg,$aavg,p[3]);
var Min=(($amin*($fmax-$favg)/2.0)+(($amax-$aavg)/2.0)+$aavg);
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
 if (p[3]==1.0){
  aveg=0.0;
 }
 this.color(0.0,p[3],0.0,aveg);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);

var rC=gC.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$amax,$amin,$aavg,$aavg,p[3]);
var Min=(($amin*($fmax-$favg)/2.0)+(($amax-$aavg)/2.0)+$aavg);
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
if (p[3]==1.0){
aveg=0.0;
}
this.color(0.0,0.0,p[3],aveg);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);

var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
let $F=1;
let $Bu=33;

let d=S();if(d)d();d=S();function S(){
var vv=document.getElementById("mv");
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
var pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
var T=false;
var $bb=R(vv);
$B.set($bb,0,sz);
var pointb=66*la;
Module.ccall('nano',null,['Number'],['Number'],['Number'],['Number'],[$F],[sz],[pointb],[pointa]);
rA.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
tA.setConstants({nblnk:nblank$,blnk:blank$});
rB.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
tB.setConstants({nblnk:nblank$,blnk:blank$});
rC.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
tC.setConstants({nblnk:nblank$,blnk:blank$});
var $$A=tA(vv);
var $$B=tB(vv);
var $$C=tC(vv);
rA($$A);
rB($$B);
rC($$C);
function Ra(){
y1.setAttribute("style","transform: scaleY(1);");
x1.setAttribute("style","transform: scaleX(1);");
y2.setAttribute("style","transform: scaleY(-1);");
x2.setAttribute("style","transform: scaleX(-1);");
y3.setAttribute("style","transform: scaleY(1);");
x3.setAttribute("style","transform: scaleX(1);");
}
function Rb(){
x1.setAttribute("style","transform: scaleX(-1);");
y1.setAttribute("style","transform: scaleY(-1);");
x2.setAttribute("style","transform: scaleX(1);");
y2.setAttribute("style","transform: scaleY(1);");
x3.setAttribute("style","transform: scaleX(-1);");
y3.setAttribute("style","transform: scaleY(-1);");
}
rott=0;
rottb=0;
rottc=0;
function M(){
if(T){return;}
knb=document.getElementById("rra").innerHTML;
kna=document.getElementById("mainr").innerHTML;
knc=document.getElementById("rrb").innerHTML;
knd=document.getElementById("rrc").innerHTML;
knbb=document.getElementById("rrab").innerHTML;
kncb=document.getElementById("rrbb").innerHTML;
kndb=document.getElementById("rrcb").innerHTML;
rate=kna;
function rrra(rta) {
c1.setAttribute("style","transform: rotate("+rta+"deg);");
}
function rrrb(rtb) {
c2.setAttribute("style","transform: rotate("+rtb+"deg);");
}
function rrrc(rtc) {
c3.setAttribute("style","transform: rotate("+rtc+"deg);");
}
if((rott-knd)<0){
rott=rott+360-knd;
}else{
rott=rott-knd;
}
rrra(rott);
if ((rottb-knc)<0){
rottb=rottb+360-knc;
}else{
rottb=rottb-knc;
}
setTimeout(function(){
Rb();
rrrb(rottb);
},rate);
if((rottc+knb)>360){
rottc=rottc+knb-360;
} else {
rottc=rottc+knb;
}
setTimeout(function(){
Ra();
rrrc(rottc);
},rate);
setTimeout(function(){
M();
},rate);
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

extern "C" {

void str(){
strt();
}

void pl(){
plt();
}

void b3(){
ma();
}

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}
}

int main(){
EM_ASM({
FS.mkdir('/snd');
FS.mkdir('/shader');
});
return 1;
}
