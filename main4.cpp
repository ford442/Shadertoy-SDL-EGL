#include <string>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "SDL2/SDL_config.h"
#include <SDL2/SDL.h>
#include "config.h"
static SDL_AudioDeviceID dev;
static EGLDisplay display;
static EGLContext contextegl;
static EGLSurface surface;
static EmscriptenWebGLContextAttributes attr;
static struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
SDL_Window *win;
SDL_GLContext *glCtx;
static const char* common_shader_header = common_shader_header_gles3;
static const char* vertex_shader_body = vertex_shader_body_gles3;
static const char* fragment_shader_header = fragment_shader_header_gles3;
static const char* fragment_shader_footer = fragment_shader_footer_gles3;
static GLuint shader_program;
static GLint attrib_position;
static GLint sampler_channel[4];
static GLint uniform_cres;
static GLint uniform_ctime;
static GLint uniform_date;
static GLint uniform_gtime;
static GLint uniform_time;
static GLint uniform_mouse;
static GLint uniform_res;
static GLint uniform_srate;
static void select_gles3() {
common_shader_header = common_shader_header_gles3;
vertex_shader_body = vertex_shader_body_gles3;
fragment_shader_header = fragment_shader_header_gles3;
fragment_shader_footer = fragment_shader_footer_gles3;
}
static GLuint compile_shader(GLenum type, GLsizei nsources, const char **sources){
GLuint shader;
GLint success, len;
GLsizei i, srclens[nsources];
char *log;
for (i = 0; i < nsources; ++i){
srclens[i] = (GLsizei)strlen(sources[i]);
}
shader = glCreateShader(type);
glShaderSource(shader, nsources, sources, srclens);
glCompileShader(shader);
glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
return shader;
}
float abstime;
static void renderFrame(){
abstime = SDL_GetTicks() / 1000;
static const GLfloat vertices[] = {
-1.0f, -1.0f,
1.0f, -1.0f,
-1.0f, 1.0f,
1.0f, 1.0f,
};
if(uniform_gtime >= 0)
glUniform1f(uniform_gtime, abstime);
if(uniform_time >= 0)
glUniform1f(uniform_time, abstime);
glClearColor(0.0f, 0.0f, 0.0f, 1.0);
glClear(GL_COLOR_BUFFER_BIT);
glEnableVertexAttribArray(attrib_position);
glVertexAttribPointer(attrib_position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
static char* read_file_into_str(const char *filename) {
char *result = NULL;
long length = 0;
FILE *file = fopen(filename, "r");
if(file) {
int status = fseek(file, 0, SEEK_END);
if(status != 0) {
fclose(file);
return NULL;
}
length = ftell(file);
status = fseek(file, 0, SEEK_SET);
if(status != 0) {
fclose(file);
return NULL;
}
result = static_cast<char*>(malloc((length+1) * sizeof(char)));
if(result) {
size_t actual_length = fread(result, sizeof(char), length , file);
result[actual_length++] = '\0';
} 
fclose(file);
return result;
}
return NULL;
}

static void shdd(){
EM_ASM({
console.log("fileReader init.");
var openFile=function(event){
var input=event.target;
var reader=new FileReader();
reader.onload=function(){
var arrayBuffer=reader.result;
var fil=new Uint8ClampedArray(arrayBuffer);
var filnm="/"+input.files[0].name;
FS.writeFile(filnm,fil);
console.log('File: '+input.files[0].name);
};
reader.readAsArrayBuffer(input.files[0]);
};
});
}

static void strt(){
GLuint vtx, frag;
const char *sources[4];
const char *log;
GLint success, len;

int temp_val = 0;
const char* texture_files[4];
for (int i=0; i<4; ++i) {
texture_files[i] = NULL;
}
const char* ssrc = "/shader1.glsl";
char *program_source = NULL;
int selected_option = -1;
int selected_index = 0;
program_source = read_file_into_str(ssrc);
default_fragment_shader = program_source;
select_gles3();
static const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE
};
static const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_RED_SIZE,8,
EGL_GREEN_SIZE,8,
EGL_BLUE_SIZE,8,
EGL_ALPHA_SIZE,8,
EGL_STENCIL_SIZE,8,
EGL_DEPTH_SIZE,24,
EGL_NONE
};
SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,8);
SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,24);
SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);
attr.alpha=0;
attr.stencil=0;
attr.depth=0;
attr.antialias=0;
attr.premultipliedAlpha=0;
attr.preserveDrawingBuffer=0;
emscripten_webgl_init_context_attributes(&attr);
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=emscripten_webgl_create_context("#canvas",&attr);
EGLConfig eglconfig=NULL;
EGLint config_size,major,minor;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
if(eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size)==EGL_TRUE && eglconfig!=NULL){
if(eglBindAPI(EGL_OPENGL_ES_API)!=EGL_TRUE){
}
EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_NONE};
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
if(contextegl==EGL_NO_CONTEXT){
}
else{
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
glClearColor(0.0,1.0,0.0,1.0);
glClear(GL_COLOR_BUFFER_BIT);
}}
emscripten_webgl_make_context_current(ctx);
int width=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
int height=width;
win=SDL_CreateWindow("pm",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_OPENGL);
glCtx=&contextegl;
sources[0] = common_shader_header;
sources[1] = vertex_shader_body;
vtx = compile_shader(GL_VERTEX_SHADER, 2, sources);
sources[0] = common_shader_header;
sources[1] = fragment_shader_header;
sources[2] = default_fragment_shader;
sources[3] = fragment_shader_footer;
frag = compile_shader(GL_FRAGMENT_SHADER, 4, sources);
shader_program = glCreateProgram();
glAttachShader(shader_program, vtx);
glAttachShader(shader_program, frag);
glLinkProgram(shader_program);
glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glUseProgram(shader_program);
glValidateProgram(shader_program);
attrib_position = glGetAttribLocation(shader_program, "iPosition");
sampler_channel[0] = glGetUniformLocation(shader_program, "iChannel0");
sampler_channel[1] = glGetUniformLocation(shader_program, "iChannel1");
sampler_channel[2] = glGetUniformLocation(shader_program, "iChannel2");
sampler_channel[3] = glGetUniformLocation(shader_program, "iChannel3");
uniform_cres = glGetUniformLocation(shader_program, "iChannelResolution");
uniform_ctime = glGetUniformLocation(shader_program, "iChannelTime");
uniform_date = glGetUniformLocation(shader_program, "iDate");
uniform_gtime = glGetUniformLocation(shader_program, "iGlobalTime");
uniform_time = glGetUniformLocation(shader_program, "iTime");
uniform_res = glGetUniformLocation(shader_program, "iResolution");
SDL_SetWindowTitle(win,"1ink.us - Shadertoy");
SDL_Log("GL_VERSION: %s",glGetString(GL_VERSION));
SDL_Log("GLSL_VERSION: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
SDL_Init(SDL_INIT_TIMER);
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
static void SDLCALL bfr(void *unused,Uint8* stm,int len){
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
}
static void plt(){
char flnm[1024];
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
void shdr(){
shdd();
}
void str(){
strt();
}}
int main(){
EM_ASM({
FS.mkdir('/');
FS.mkdir('/snd');
shdd();
});
return 1;
}
