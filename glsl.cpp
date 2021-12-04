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
"#version 300 es\n";

static const char vertex_shader_body_gles3[]=
"layout (location = 0) in vec3 aPos;"
"layout (location = 1) in vec3 aColor;"
"out vec3 ourColor;"
"void main()"
"{"
"gl_Position = vec4(aPos, 1.0);"
"ourColor = aColor;"
"}                              \n\0";

static const char fragment_shader_header_gles3[]=
"precision mediump float;        \n"
"in vec3 ourColor;                  \n"
"out vec4 FragColor;              \n";

static const char fragment_shader_footer_gles3[]=
"\n\0";

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
static GLuint shader_program;
static GLfloat mouseX=0.0f;
static GLfloat mouseY=0.0f;
static GLfloat mouseLPressed=0.0f;
static GLfloat mouseRPressed=0.0f;
static GLfloat viewportSizeX=0.0f;
static GLfloat viewportSizeY=0.0f;

// static const GLfloat vertices[]={-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f};

static GLuint compile_shader(GLenum type,GLsizei nsources,const char **sources){
static GLuint shader;
GLsizei i,srclens[nsources];
for (i=0;i<nsources;++i){
SDL_Log("GL Shader: %s",sources[i]);
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

static GLfloat vertices[] = {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};
static GLfloat ink[]={1.0f,0.0f,0.0f,1.0f};

static void renderFrame(){
GLuint VBO, VAO;
int x, y;
Uint32 buttons;
SDL_PumpEvents();
glClear(GL_COLOR_BUFFER_BIT);
buttons=SDL_GetMouseState(&x, &y);
ink[1]=(float)ink[1]-x;
if((buttons & SDL_BUTTON_LMASK)!=0){
mouseLPressed=1.0f;
ink[2]=1.0f;
vertices[7] =-0.25f;
vertices[10] =0.0f;
vertices[11] =1.0f;
}else{
mouseLPressed=0.0f;
vertices[7] =-0.5f;
vertices[10] =1.0f;
vertices[11] =0.0f;
ink[2]=0.0f;
}
glClearColor(ink[0],ink[1],ink[2],ink[3]);
float abstime=(float)(round(SDL_GetTicks()/100));
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
glEnableVertexAttribArray(1);
glUseProgram(shader_program);
glDrawArrays(GL_TRIANGLES,0,3);
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
attr.stencil=1;
attr.depth=1;
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
glClearColor(0.0f,1.0f,0.0f,1.0f);
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
