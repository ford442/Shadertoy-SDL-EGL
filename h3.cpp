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
GLuint DBO,EBO,VBO,CBO,tex2d[4],shader_program,shader,frame,sampler_channel[4];
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
struct timespec req={0,16666666};
// struct timespec req={0,33100000};
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
"#version 300 es \n precision highp float;precision highp int;precision highp sampler3D;precision highp sampler2D;\n";
static const char vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n\0";
static const char fragment_shader_header_gles3[]=
"\n uniform vec2 iResolution;uniform float iTime;uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;out vec4 fragColor;\n";
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
emscripten_webgl_make_context_current(ctx);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,Indices);
 glFinish();
 nanosleep(&req,&rem);
iFrame++;
}

void avgFrm(int F,int leng,float *dat,float *aLoc){
float max=0.0;
float min=1.0;
float sum=0.0;
for (int i=4;i<leng;i=i){
sum+=dat[i];
if(max<dat[i]){max=dat[i];}
if(min>dat[i]&&dat[i]>0){min=dat[i];}
}
sum=sum/leng;
aLoc[F]=sum;
aLoc[F+100]=min;
aLoc[F+200]=max;
aLoc[0]=(aLoc[1]+aLoc[2]+aLoc[3]+aLoc[4]+aLoc[5]+aLoc[6]+aLoc[7]+aLoc[8]+aLoc[9]+aLoc[10]+aLoc[11]+aLoc[12]+aLoc[13]+aLoc[14]+aLoc[15]+aLoc[16]+aLoc[17]+aLoc[18]+aLoc[19]+aLoc[20]+aLoc[21]+aLoc[22]+aLoc[23]+aLoc[24]+aLoc[25]+aLoc[26]+aLoc[27]+aLoc[28]+aLoc[29]+aLoc[30]+aLoc[31]+aLoc[32])/32;
aLoc[100]=(aLoc[101]+aLoc[102]+aLoc[103]+aLoc[104]+aLoc[105]+aLoc[106]+aLoc[107]+aLoc[108]+aLoc[109]+aLoc[110]+aLoc[111]+aLoc[112]+aLoc[113]+aLoc[114]+aLoc[115]+aLoc[116]+aLoc[117]+aLoc[118]+aLoc[119]+aLoc[120]+aLoc[121]+aLoc[122]+aLoc[123]+aLoc[124]+aLoc[125]+aLoc[126]+aLoc[127]+aLoc[128]+aLoc[129]+aLoc[130]+aLoc[131]+aLoc[132])/32;
aLoc[200]=(aLoc[201]+aLoc[202]+aLoc[203]+aLoc[204]+aLoc[205]+aLoc[206]+aLoc[207]+aLoc[208]+aLoc[209]+aLoc[210]+aLoc[211]+aLoc[212]+aLoc[213]+aLoc[214]+aLoc[215]+aLoc[216]+aLoc[217]+aLoc[218]+aLoc[219]+aLoc[220]+aLoc[221]+aLoc[222]+aLoc[223]+aLoc[224]+aLoc[225]+aLoc[226]+aLoc[227]+aLoc[228]+aLoc[229]+aLoc[230]+aLoc[231]+aLoc[232])/32;
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
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
static const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,v8,
EGL_GREEN_SIZE,v8,
EGL_BLUE_SIZE,v8,
EGL_ALPHA_SIZE,v8,
EGL_DEPTH_SIZE,v32,
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
attr.enableExtensionsByDefault=EM_TRUE;
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
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_TRUE,0,(void*)0);
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
glUniform2f(uniform_res,Size,Size);
glEnable(GL_BLEND);
glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearColor(F0,F0,F0,F);
glViewport(0,0,S,S);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
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
var pointa=33*la;
var agav=new Float32Array($H,pointa,300);
var sz=(h$*h$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
let bcanvas=document.getElementById("bcanvas");
let acanvas=document.getElementById("acanvas");
let contx=bcanvas.getContext('webgl2',{alpha:true,imageSmoothingEnabled:false,stencil:true,depth:true,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
let contx2=acanvas.getContext('webgl2',{alpha:true,imageSmoothingEnabled:false,stencil:true,depth:true,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
let g=new GPU({canvas:bcanvas,webGl:contx});
let g2=new GPU();
let g3=new GPU({canvas:acanvas,webGl:contx2});
const glslAve=`float Ave(float a,float b,float c) {return (a + b + c) / 3.0 ;}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g) {return (((((a - b) * 0.6) + b) + (((c - d) * 0.6) + d) + (((1.0 - (b / 2.0)) * 0.7) + (b/2.0)) + (((1.0 - (c)) * 0.7)) + ((0.7 - (0.7 * (e - f) / (c-f)))) + ((f + 0.7) / 2.0)) / 6.0) ;}`;
const glslAveg=`float Aveg(float a,float b) {return (1.0 - (((a) - (b)) * ((a) * (1.0 / (1.0 - b))))) ;}`;

g.addNativeFunction('Ave', glslAve, { returnType: 'Number' });
g.addNativeFunction('Alphe', glslAlphe, { returnType: 'Number' });
g.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Ave', glslAve, { returnType: 'Number' });

let R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setArgumentTypes(['HTMLVideo']).setOutput([sz]);

let t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);

let r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($fmax,$fmin,$amax,$amin,$favg,$aavg,p[3]);
var aveg=Aveg(p[3],alph);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("balanced").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);

let rA=g.createKernel(function(fa){
var pd=fa[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var avrg=(1.0-Ave(pd[0],pd[1],pd[2])-0.75)*(Ave(pd[0],pd[1],pd[2])*4.0);
this.color(pd[0],pd[1],pd[2],0.075);
}).setTactic("balanced").setGraphical(true).setDynamicOutput(true).setOutput([w$,h$]);

let d=S();if(d)d();d=S();function S(){
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=33*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);
var point1=0;
var $1=new Float32Array($H,point1,la);
var point2=1*la;
var $2=new Float32Array($H,point2,la);
var point3=2*la;
var $3=new Float32Array($H,point3,la);
var point4=3*la;
var $4=new Float32Array($H,point4,la);
var point5=4*la;
var $5=new Float32Array($H,point5,la);
var point6=5*la;
var $6=new Float32Array($H,point6,la);
var point7=6*la;
var $7=new Float32Array($H,point7,la);
var point8=7*la;
var $8=new Float32Array($H,point8,la);
var point9=8*la;
var $9=new Float32Array($H,point9,la);
var point10=9*la;
var $10=new Float32Array($H,point10,la);
var point11=10*la;
var $11=new Float32Array($H,point11,la);
var point12=11*la;
var $12=new Float32Array($H,point12,la);
var point13=12*la;
var $13=new Float32Array($H,point13,la);
var point14=13*la;
var $14=new Float32Array($H,point14,la);
var point15=14*la;
var $15=new Float32Array($H,point15,la);
var point16=15*la;
var $16=new Float32Array($H,point16,la);
var point17=16*la;
var $17=new Float32Array($H,point17,la);
var point18=17*la;
var $18=new Float32Array($H,point18,la);
var point19=18*la;
var $19=new Float32Array($H,point19,la);
var point20=19*la;
var $20=new Float32Array($H,point20,la);
var point21=20*la;
var $21=new Float32Array($H,point21,la);
var point22=21*la;
var $22=new Float32Array($H,point22,la);
var point23=22*la;
var $23=new Float32Array($H,point23,la);
var point24=23*la;
var $24=new Float32Array($H,point24,la);
var point25=24;
var $25=new Float32Array($H,point25,la);
var point26=25*la;
var $26=new Float32Array($H,point26,la);
var point27=26*la;
var $27=new Float32Array($H,point27,la);
var point28=27*la;
var $28=new Float32Array($H,point28,la);
var point29=28*la;
var $29=new Float32Array($H,point29,la);
var point30=29*la;
var $30=new Float32Array($H,point30,la);
var point31=30*la;
var $31=new Float32Array($H,point31,la);
var point32=31*la;
var $32=new Float32Array($H,point32,la);
var pointb=32*la;
var $B=new Float32Array($H,pointb,sz);
let $F=1;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
rA.setConstants({nblnk:nblank$,blnk:blank$});
/*
 var $$1=t(vv);
$1.set($$1);
$2.set($$1);
$3.set($$1);
$4.set($$1);
$5.set($$1);
$6.set($$1);
$7.set($$1);
$8.set($$1);
$9.set($$1);
$10.set($$1);
$11.set($$1);
$12.set($$1);
$13.set($$1);
$14.set($$1);
$15.set($$1);
$16.set($$1);
*/
var T=false;

function M(){
rA.setConstants({nblnk:nblank$,blnk:blank$});
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){return;}
if($F==32){
var $r32=t($32);
rA($r32);
r($r32);
var $$16=t(vv);
$16.set($$16);
$F=1;
}
if($F==31){
var $r31=t($31);
rA($r31);
r($r31);
var $$15=t(vv);
$15.set($$15);
$F=32;
}
if($F==30){
var $r30=t($30);
rA($r30);
r($r30);
var $$14=t(vv);
$14.set($$14);
$F=31;
}
if($F==29){
var $r29=t($29);
rA($r29);
r($r29);
var $$13=t(vv);
$13.set($$13);
$F=30;
}
if($F==28){
var $r28=t($28);
rA($r28);
r($r28);
var $$12=t(vv);
$12.set($$12);
$F=29;
}
if($F==27){
var $r27=t($27);
rA($r27);
r($r27);
var $$11=t(vv);
$11.set($$11);
$F=28;
}
if($F==26){
var $r26=t($26);
rA($r26);
r($r26);
var $$10=t(vv);
$10.set($$10);
$F=27;
}
if($F==25){
var $r25=t($25);
rA($r25);
r($r25);
var $$9=t(vv);
$9.set($$9);
$F=26;
}
if($F==24){
var $r24=t($24);
rA($r24);
r($r24);
var $$8=t(vv);
$8.set($$8);
$F=25;
}
if($F==23){
var $r23=t($23);
rA($r23);
r($r23);
var $$7=t(vv);
$7.set($$7);
$F=24;
}
if($F==22){
var $r22=t($22);
rA($r22);
r($r22);
var $$6=t(vv);
$6.set($$6);
$F=23;
}
if($F==21){
var $r21=t($21);
rA($r21);
r($r21);
var $$5=t(vv);
$5.set($$5);
$F=22;
}
if($F==20){
var $r20=t($20);
rA($r20);
r($r20);
var $$4=t(vv);
$4.set($$4);
$F=21;
}
if($F==19){
var $r19=t($19);
rA($r19);
r($r19);
var $$3=t(vv);
$3.set($$3);
$F=20;
}
if($F==18){
var $r18=t($18);
rA($r18);
r($r18);
var $$2=t(vv);
$2.set($$2);
$F=19;
}
if($F==17){
var $r17=t($17);
rA($r17);
r($r17);
var $$1=t(vv);
$1.set($$1);
$F=18;
}
if($F==16){
var $r16=t($16);
rA($r16);
r($r16);
var $$32=t(vv);
$32.set($$32);
$F=17;
}
if($F==15){
var $r15=t($15);
rA($r15);
r($r15);
var $$31=t(vv);
$31.set($$31);
$F=16;
}
if($F==14){
var $r14=t($14);
rA($r14);
r($r14);
var $$30=t(vv);
$30.set($$30);
$F=15;
}
if($F==13){
var $r13=t($13);
rA($r13);
r($r13);
var $$29=t(vv);
$29.set($$29);
$F=14;
}
if($F==12){
var $r12=t($12);
rA($r12);
r($r12);
var $$28=t(vv);
$28.set($$28);
$F=13;
}
if($F==11){
var $r11=t($11);
rA($r11);
r($r11);
var $$27=t(vv);
$27.set($$27);
$F=12;
}
if($F==10){
var $r10=t($10);
rA($r10);
r($r10);
var $$26=t(vv);
$26.set($$26);
$F=11;
}
if($F==9){
var $r9=t($9);
rA($r9);
r($r9);
var $$25=t(vv);
$25.set($$25);
$F=10;
}
if($F==8){
var $r8=t($8);
rA($r8);
r($r8);
var $$24=t(vv);
$24.set($$24);
$F=9;
}
if($F==7){
var $r7=t($7);
rA($r7);
r($r7);
var $$23=t(vv);
$23.set($$23);
$F=8;
}
if($F==6){
var $r6=t($6);
rA($r6);
r($r6);
var $$22=t(vv);
$22.set($$22);
$F=7;
}
if($F==5){
var $r5=t($5);
rA($r5);
r($r5);
var $$21=t(vv);
$21.set($$21);
$F=6;
}
if($F==4){
var $r4=t($4);
rA($r4);
r($r4);
var $$20=t(vv);
$20.set($$20);
$F=5;
}
if($F==3){
var $r3=t($3);
rA($r3);
r($r3);
var $$19=t(vv);
$19.set($$19);
$F=4;
}
if($F==2){
var $r2=t($2);
rA($r2);
r($r2);
var $$18=t(vv);
$18.set($$18);
$F=3;
}
if($F==1){
var $r1=t($1);
rA($r1);
r($r1);
var $$17=t(vv);
$17.set($$17);
$F=2;
}
var $bb=R(vv);
$B.set($bb,0,sz);
setTimeout(function(){
var pointb=32*la;
Module.ccall('nano',null,['Number'],['Number'],['Number'],['Number'],[$F],[sz],[pointb],[pointa]);
M();
},16.666);
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
