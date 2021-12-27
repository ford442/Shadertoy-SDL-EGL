// #include <algorithm>
#include <cstring>
#include <cstdarg>
// #include <cmath>
#include <cstdio>
#include <cstdlib>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>

using namespace std;
using namespace std::chrono;

char flnm[16];
struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
high_resolution_clock::time_point t1,t2;
SDL_AudioDeviceID dev;
GLuint FBO,tex2d[4],shader_program,shader,frame,attrib_position,sampler_channel[4],VBO,VAO,EBO,vtx,frag,uniform_frame,uniform_time,uniform_res,uniform_mouse;
GLint x,y;
GLfloat mouseX,mouseY,mouseLPressed,mouseRPressed;
Uint32 buttons;
long double Ttime;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
SDL_Window *win;
SDL_GLContext *glCtx;
int lft;
Uint8 *wptr;
GLsizei nsources,i,S;
EGLint config_size,major,minor;
EGLConfig eglconfig=NULL;
string program_source;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
GLint v0=0,v1=1,v2=2,v4=4,v6=6;

static const GLenum attt[]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3};

const char common_shader_header_gles3[]=
"#version 300 es \n"
"precision highp float;"
"precision highp sampler3D;"
"precision highp sampler2D;"
"precision highp int; \n";
const char vertex_shader_body_gles3[]=
"layout(location=0)in highp vec4 iPosition;"
"void main(){"
"gl_Position=iPosition;"
"} \n";
const char fragment_shader_header_gles3[]=
"uniform vec3 iResolution;"
"uniform float iTime;"
"uniform vec4 iMouse;"
"uniform sampler2D iChannel0;"
"uniform sampler2D iChannel1;"
"uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
"out highp vec4 fragColor; \n";
const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);} \n";

const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;

const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE
};

EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_NONE};

const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_RED_SIZE,8,
EGL_GREEN_SIZE,8,
EGL_BLUE_SIZE,8,
EGL_ALPHA_SIZE,8,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,8,
EGL_BUFFER_SIZE,32,
EGL_NONE
};

typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{-1.0,-1.0,0.0,1.0},{-1.0,1.0,0.0,1.0},{1.0,-1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
GLubyte Indices[]={0,1,2,2,1,3};
const size_t BufferSize=sizeof(vertices);
const size_t VertexSize=sizeof(vertices[0]);
char *fileloc="/shader/shader1.toy";
const char *sources[4];
// const char *texture_files[4];
char *result=NULL;
long length=0;

static const char *read_file(const char *filename){
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return NULL;
}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return NULL;
}
result=static_cast<char*>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return NULL;
}

static GLuint compile_shader(GLenum type,GLsizei nsources,const char **sources){
GLsizei srclens[nsources];
for(i=0;i<nsources;++i){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

static void renderFrame(){
buttons=SDL_GetMouseState(&x,&y);
mouseX=(float)x;
mouseY=(float)S-(float)y;
if((buttons & SDL_BUTTON_LMASK)!=0){
mouseLPressed=1.0f;
const float cMouseX=mouseX;
const float cMouseY=mouseY;
glUniform4f(uniform_mouse,mouseX,mouseY,cMouseX,cMouseY);
}else{
mouseLPressed=0.0f;
}
t2=high_resolution_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glDrawBuffers(v4,attt);
duration<long double>time_spana=duration_cast<duration<long double>>(t2-t1);
Ttime=time_spana.count();
glUniform1f(uniform_time,Ttime);
glUniform1i(uniform_frame,frame);
glDrawElements(GL_TRIANGLES,v6,GL_UNSIGNED_BYTE,Indices);
eglSwapBuffers(display,surface);
frame++;
}

static void gets(){
}

static void comp(){
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
// SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_ES);
SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,1);
SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
ctx=emscripten_webgl_create_context("#canvas",&attr);
eglInitialize(display,&major,&minor);
if(eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size)==EGL_TRUE && eglconfig!=NULL){
if(eglBindAPI(EGL_OPENGL_ES_API)!=EGL_TRUE){
}
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
if(contextegl==EGL_NO_CONTEXT){
}
else{
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}}
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_make_context_current(ctx);
glCtx=&contextegl;
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
program_source=read_file(fileloc);
const char* default_fragment_shader=program_source.c_str();
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
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
}

static void strt(){
// for (int i=0;i<4;++i) {texture_files[i]=NULL;}
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
win=SDL_CreateWindow("Shadertoy",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,S,S,SDL_WINDOW_FOREIGN|SDL_WINDOW_BORDERLESS|SDL_WINDOW_OPENGL);
glUseProgram(shader_program);
glGenBuffers(v1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_DRAW);
glGenVertexArrays(v1,&VAO);
glBindVertexArray(VAO);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glEnableVertexAttribArray(attrib_position);
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_TRUE,VertexSize,GL_FALSE);
glGenTextures(v4,tex2d);
glBindTexture(GL_TEXTURE_2D,tex2d[0]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glBindTexture(GL_TEXTURE_2D,tex2d[1]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glBindTexture(GL_TEXTURE_2D,tex2d[2]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glBindTexture(GL_TEXTURE_2D,tex2d[3]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glBindTexture(GL_TEXTURE_2D,v0);
glGenFramebuffers(v1, &FBO);
glBindFramebuffer(GL_FRAMEBUFFER,FBO);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tex2d[0],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,tex2d[1],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D,tex2d[2],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT3,GL_TEXTURE_2D,tex2d[3],v0);
glBindFramebuffer(GL_FRAMEBUFFER,v0);
attrib_position=glGetAttribLocation(shader_program,"iPosition");
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
glUniform3f(uniform_res,(float)S,(float)S,(float)S);
glUniform1i(sampler_channel[0],tex2d[0]);
glUniform1i(sampler_channel[1],tex2d[1]);
glUniform1i(sampler_channel[2],tex2d[2]);
glUniform1i(sampler_channel[3],tex2d[3]);
glEnable(GL_BLEND);
glEnable(GL_CULL_FACE); 
glFrontFace(GL_CW);
glDisable(GL_DITHER); 
glDepthMask(GL_FALSE);
glDisable(GL_DEPTH_TEST); 
glBlendEquationSeparate(GL_FUNC_ADD,GL_FUNC_ADD);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glViewport(v0,v0,S,S);
glActiveTexture(GL_TEXTURE0);
SDL_SetWindowTitle(win,"1ink.us - Shadertoy");
SDL_Log("GL_VERSION: %s",glGetString(GL_VERSION));
SDL_Log("GLSL_VERSION: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
SDL_Init(SDL_INIT_EVENTS);
glClearColor(0.0f,1.0f,0.0f,1.0f);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
t1=high_resolution_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
}
static void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
}}
static void qu(int rc){
SDL_Quit();
exit(rc);
}
static void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
qu(2);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
}
static void SDLCALL bfr(void *unused,Uint8 *stm,int len){
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
static void plt(){
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
SDL_Log("SDL failed to init.");
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
}
extern "C" {
void pl(){
plt();
}
void str(){
strt();
}
void compile(){
comp();
}
void getShader(){
gets();
}}

int main(){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
