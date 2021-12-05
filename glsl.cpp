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
typedef khronos_utime_nanoseconds_t EGLTime;
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
"#version 300 es\n"
"precision highp float;\n"
"precision highp int;\n";

static const char vertex_shader_body_gles3[]=
"layout (location = 0) in vec3 aPos;"
"layout (location = 1) in vec3 aColor;"
"out vec3 ourColor;"
"void main()"
"{"
"gl_Position = vec4(aPos, 1.0);"
"ourColor = aColor;"
"}\n\0";

static const char fragment_shader_header_gles3[]=
"in vec3 ourColor;\n"
"out vec4 FragColor;\n";

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

static GLfloat ink[]={1.0f,0.0f,0.0f,1.0f};
/* static GLfloat vertices[]={
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   
         0.1f, -0.1f, 0.1f,  1.0f, 0.0f, 1.0f,
        -0.23f, -0.27f, 0.2f,  0.0f, 1.0f, 0.3f,
         0.73f,  0.77f, 0.0f,  0.4f, 0.0f, 1.0f,
         0.13f, -0.17f, 0.1f,  1.0f, 0.0f, 1.0f,
        -0.2f, -0.9f, 0.2f,  0.0f, 1.0f, 0.3f,
         0.7f,  0.9f, 0.0f,  0.9f, 0.0f, 1.0f,
         0.7f,  0.7f, 0.9f,  0.4f, 0.9f, 1.0f
};
*/
static GLfloat vertices[2160]={};

static void renderFrame(){
GLuint VBO,VAO;
double white;
int x,y;
double siz;
int a;
float b;
Uint32 buttons;
glClear(GL_COLOR_BUFFER_BIT);
siz=0.42;

SDL_PumpEvents();
double abstime=SDL_GetTicks();
buttons=SDL_GetMouseState(&x, &y);
mouseX=x/viewportSizeX;
mouseY=y/viewportSizeY;
ink[0]=mouseX/2;
ink[1]=mouseY;
white=abstime-(round(abstime/1000)*1000);
white=1000/white;
if((buttons & SDL_BUTTON_LMASK)!=0){

mouseLPressed=1.0f;
ink[2]=white;
siz=0.77;
vertices[7]=1.0f-mouseX;
vertices[1]=1.0f-mouseY;
vertices[13]=1.0f-mouseX;
vertices[10]=0.0f-white;
vertices[11]=1.0f-mouseY;
vertices[2]=white;
vertices[8]=vertices[11];
vertices[32]=white/1.2f;
vertices[38]=white/1.1f;
vertices[0]=vertices[32]-white;
vertices[3]=vertices[1]-white;
vertices[2]=vertices[2]-white;
}else{
for(a=0;a<361;a++){
b=(float)a/360;
vertices[a*6]=siz*cos(a);
vertices[(a*6)+1]=siz*sin(a);
vertices[(a*6)+2]=b;
vertices[(a*6)+3]=1.0f;
vertices[(a*6)+4]=0.0f;
vertices[(a*6)+5]=1.0f-b;
};
mouseLPressed=0.0f;
vertices[7]=-0.5f;
vertices[1]=-0.5f;
vertices[13]=0.5f;
vertices[10]=1.0f-white;
vertices[11]=0.0f;
vertices[3]=1.0f;
vertices[0]=0.5f;
vertices[1]=-0.5f;
vertices[2]=0.0f;
ink[2]=0.0f;
ink[0]=white/100;
}

glClearColor(ink[0],ink[1],ink[2],ink[3]);
glGenVertexArrays(1,&VAO);
glGenBuffers(1,&VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
glEnableVertexAttribArray(1);
glUseProgram(shader_program);
glDrawArrays(GL_TRIANGLE_STRIP,0,360);
eglSwapBuffers(display,surface);      
}

static const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE
};

static const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RED_SIZE,16,
EGL_GREEN_SIZE,16,
EGL_BLUE_SIZE,16,
EGL_ALPHA_SIZE,16,
EGL_STENCIL_SIZE,16,
EGL_DEPTH_SIZE,16,
EGL_BUFFER_SIZE,32,
EGL_NONE
};

static void strt(){
EGLTime startTime;

int ii;
for(ii=0;ii<2161;ii++){
vertices[ii]=0.0f;
}
GLuint vtx,frag;
char *fileloc="/shader/shader1.glsl";
string program_source=read_file_into_str(fileloc);
const char* default_fragment_shader=program_source.c_str();
const char *sources[4];
SDL_GL_SetAttribute(SDL_GL_RED_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,16);
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
viewportSizeX=w;
viewportSizeY=h;
glClearColor(0.0f,1.0f,0.0f,1.0f);
SDL_Log("SDL_Time: %s",SDL_GetTicks());
SDL_Log("EGL_Time: %s",startTime);
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
