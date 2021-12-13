#include <algorithm>
#include <string>
#include <cstdarg>
#include <cmath>
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
using std::string;
Uint8 *stm;
struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;

steady_clock::time_point t1;
SDL_AudioDeviceID dev;
GLuint shader_program;
GLint attrib_position;
GLint sampler_channel[4];
GLfloat uniform_time;
GLint uniform_frame;
GLfloat uniform_res;
GLfloat uniform_mouse;
GLfloat viewportSizeX=0.0f;
GLfloat viewportSizeY=0.0f;
Uint32 buttons;
long double outTimeA;
GLfloat mouseX=0.0f;
GLfloat mouseY=0.0f;
GLfloat mouseLPressed=0.0f;
GLfloat mouseRPressed=0.0f;
GLint x,y;
static int frame;
EGLDisplay display;
EGLSurface surface;

GLuint VBO,VAO,EBO,vtx,frag;
EGLContext contextegl;
SDL_Window *win;
SDL_GLContext *glCtx;
const char common_shader_header_gles3[]=
"#version 300 es \n"
"precision highp float; \n"
"precision highp int; \n";

const char vertex_shader_body_gles3[]=
"layout(location=0) in vec4 iPosition;"
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
"\n void main(){mainImage(fragColor, gl_FragCoord.xy);} \n";

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
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_BUFFER_SIZE,32,
EGL_NONE
};



typedef struct{GLfloat XYZW[4];}Vertex;

Vertex vertices[]={
{-1.0,-1.0,0.0,1.0},
{-1.0,1.0,0.0,1.0},
{1.0,-1.0,1.0,1.0}, 
{1.0,1.0,1.0,1.0}
};

GLubyte Indices[]={
0,1,2,2,1,3
};

static const char *read_file(const char *filename){
char *result=NULL;
long length=0;
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
GLuint shader;
GLsizei i,srclens[nsources];
for (i=0;i<nsources;++i){
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
mouseY=viewportSizeY-(float)y;
if((buttons & SDL_BUTTON_LMASK)!=0){
mouseLPressed=1.0f;
const float cMouseX=mouseX;
const float cMouseY=mouseY;
glUniform4f(uniform_mouse,mouseX,mouseY,cMouseX,cMouseY);
}else{
mouseLPressed=0.0f;
}
steady_clock::time_point t2=steady_clock::now();
duration<long double>time_spana=duration_cast<duration<long double>>(t2-t1);
outTimeA=time_spana.count();
glUniform1f(uniform_time,(float)outTimeA);
glUniform1i(uniform_frame,frame);
glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,Indices);
eglSwapBuffers(display,surface);
frame++;
}

static void strt(){
int h,w;
h=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
w=h;
EmscriptenWebGLContextAttributes attr;
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=true;
attr.stencil=true;
attr.depth=true;
attr.antialias=false;
attr.premultipliedAlpha=false;
attr.preserveDrawingBuffer=false;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
  
const size_t BufferSize=sizeof(vertices);
const size_t VertexSize=sizeof(vertices[0]);

char *fileloc="/shader/shader1.toy";
string program_source=read_file(fileloc);
const char* default_fragment_shader=program_source.c_str();
const char *sources[4];
const char* texture_files[4];
for (int i=0;i<4;++i) {
texture_files[i]=NULL;
}
SDL_GL_SetAttribute(SDL_GL_RED_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,1);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
  
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=emscripten_webgl_create_context("#canvas",&attr);
EGLConfig eglconfig=NULL;
EGLint config_size,major,minor;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
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
emscripten_webgl_make_context_current(ctx);
win=SDL_CreateWindow("Shadertoy",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,0);
glCtx=&contextegl;
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glUseProgram(shader_program);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_DYNAMIC_DRAW);
glGenVertexArrays(1,&VAO);
glBindVertexArray(VAO);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glVertexAttribPointer(0,4,GL_FLOAT,GL_TRUE,VertexSize,0);
glEnableVertexAttribArray(0);
attrib_position=glGetAttribLocation(shader_program,"iPosition");
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
viewportSizeX=(float)w;
viewportSizeY=(float)h;
glUniform3f(uniform_res,viewportSizeX,viewportSizeY,1.0f);
glViewport(0,0,viewportSizeX,viewportSizeY);
glEnable(GL_DEPTH_TEST);  
glDepthMask(GL_FALSE);
glDepthFunc(GL_LESS);
glEnable(GL_BLEND);
SDL_SetWindowTitle(win,"1ink.us - Shadertoy");
SDL_Log("GL_VERSION: %s",glGetString(GL_VERSION));
SDL_Log("GLSL_VERSION: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
SDL_Init(SDL_INIT_EVENTS);
t1=steady_clock::now();
glClearColor(0.0f,1.0f,0.0f,1.0f);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
emscripten_set_main_loop((void (*)())renderFrame,0,0);
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
Uint8 *wptr;
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
}
static void plt(){
char flnm[16];
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
}}
int main(){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
