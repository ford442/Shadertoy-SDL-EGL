#include <float.h>
#include <vector>
#include <algorithm>
#include <string>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
using std::string;

static const char *read_file_into_str(const char *filename){
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

static const char common_shader_header_gles3[]=
"/n #version 300 es \n";

static const char vertex_shader_body_gles3[]=
"/n void main(){"
"gl_Position=iPosition;"
"} \n";

static const char fragment_shader_header_gles3[]=
"/n in vec4 color;"
"out vec4 fragColor; \n";

static const char fragment_shader_footer_gles3[]=
" \n";

static SDL_AudioDeviceID dev;
static EGLDisplay display;
static EGLContext contextegl;
static EGLSurface surface;
static EmscriptenWebGLContextAttributes attr;
static struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
SDL_Window *win;
SDL_GLContext *glCtx;
static const char* common_shader_header=common_shader_header_gles3;
static const char* vertex_shader_body=vertex_shader_body_gles3;
static const char* fragment_shader_header=fragment_shader_header_gles3;
static const char* fragment_shader_footer=fragment_shader_footer_gles3;
GLuint shader_program;

static const GLfloat vertices[]={
-1.0f,-1.0f,
1.0f,-1.0f,
-1.0f,1.0f,
1.0f,1.0f
};

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
int x, y;
GLuint vbo,vbu;
Uint32 buttons;
SDL_PumpEvents();
glClear(GL_COLOR_BUFFER_BIT);
buttons=SDL_GetMouseState(&x, &y);
if((buttons & SDL_BUTTON_LMASK)!=0){
// mouseLPressed=1.0f;
}else{
// mouseLPressed=0.0f;
}
float abstime=(float)(round(SDL_GetTicks()/100));
glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glGenVertexArrays(1,&vbu);
glBindVertexArray(vbu);
glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
glEnableVertexAttribArray(0);
glUseProgram(shader_program);
glDrawArrays(GL_TRIANGLE_STRIP,0,4);
eglSwapBuffers(display,surface);
}

static const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE
};

static const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_BUFFER_SIZE,64,
EGL_NONE
};

static void strt(){
GLuint vtx,frag;
char *fileloc="/shader/shader1.glsl";
string program_source=read_file_into_str(fileloc);
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
SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
attr.alpha=1;
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
EGL_NONE};
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
if(contextegl==EGL_NO_CONTEXT){
}
else{
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}}
emscripten_webgl_make_context_current(ctx);
int h=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
int w=h;
win=SDL_CreateWindow("Shader",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,0);
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
SDL_SetWindowTitle(win,"1ink.us - GLSL 300 es");
SDL_Log("GL_VERSION: %s",glGetString(GL_VERSION));
SDL_Log("GLSL_VERSION: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
SDL_Init(SDL_INIT_TIMER|SDL_INIT_EVENTS);
glViewport(0,0,w,h);
glClearColor(0.0f,0.0f,0.0f,1.0f);
emscripten_set_main_loop((void (*)())renderFrame,0,0);
}

extern "C" {
void str(){
strt();
}}
int main(){
EM_ASM({
FS.mkdir("/shader");
});
return 1;
}
