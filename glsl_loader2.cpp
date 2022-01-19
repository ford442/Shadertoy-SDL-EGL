#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>
#include <ctime>
#include <GLES3/gl3.h>
#define __gl2_h_
#include <GLES2/gl2ext.h>
#include </usr/include/glm/glm.hpp>
#include <EGL/egl.h>
#include <EGL/eglext.h>

using namespace std;
using namespace std::chrono;
static GLuint DBO,EBO,VBO,CBO,tex2d[4],shader_program,shader,attrib_position,sampler_channel[4];
static GLuint VCO,ECO,CCO,vtx,frag;
static long double Ttime,Dtime;
static EGLDisplay display;
static EGLSurface surface;
static EGLContext contextegl;
static GLsizei nsources,i,S;
static GLsizei s4=4;
static EGLint config_size,major,minor;
static EGLConfig eglconfig=NULL;
static EmscriptenWebGLContextAttributes attr;
static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
static EGLint v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v8=8,v32=32,a,b;
struct timespec rem;
struct timespec req={0,150000000};
static GLfloat F=1.0f;
static GLfloat F0=0.0f;
static GLfloat Fm1=-1.0f;
typedef struct{GLfloat XYZW[4];}Vertex;
static Vertex vertices[]={{Fm1,Fm1,Fm1,F},{F,Fm1,Fm1,F},{F,F,Fm1,F},{Fm1,F,Fm1,F},{Fm1,Fm1,F,F},{F,Fm1,F,F},{F,F,F,F},{Fm1,F,F,F}};
// static Vertex colors[]={{F0,F0,F0,F},{F0,F0,F0,F},{F0,F0,F0,F},{F0,F0,F0,F},{F0,F0,F0,F},{F0,F0,F0,F},{F0,F0,F0,F},{F0,F0,F0,F}};
static GLubyte Indices[]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};
static const char *filelocf="/shader/shader.frag";
static const char *filelocv="/shader/shader.vert";
static const char *sources[4];
static char8_t *result=NULL;
static long length=0;
static const char common_shader_header_gles3[]=
"#version 300 es\n precision highp float;\n";
static const char fragment_shader_header_gles3[]=
"uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;out vec4 fragColor;\n";
static const char fragment_shader_footer_gles3[]=
"\n\0";
static const char* common_shader_header=common_shader_header_gles3;
static const char* fragment_shader_header=fragment_shader_header_gles3;
static const char* fragment_shader_footer=fragment_shader_footer_gles3;
static const char8_t *read_file(const char *filename){
static FILE *file=fopen(filename,"r");
if(file){
static int status=fseek(file,0,SEEK_END);
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
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
static size_t actual_length=fread(result,sizeof(char8_t),length,file);
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
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,Indices);
eglSwapBuffers(display,surface);
}
static void strt(){
eglBindAPI(EGL_OPENGL_ES_API);
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
static const EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
static const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_NONE};
static const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,8,
EGL_GREEN_SIZE,8,
EGL_BLUE_SIZE,8,
EGL_ALPHA_SIZE,8,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,8,
EGL_BUFFER_SIZE,32,
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
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=v2;
attr.minorVersion=v0;
ctx=emscripten_webgl_create_context("#canvas",&attr);
// emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
static const char* default_fragment_shader=(char*)read_file(filelocf);
nanosleep(&req,&rem);
static const char* vertex_shader_body=(char*)read_file(filelocv);
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
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
nanosleep(&req,&rem);
glUseProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenBuffers(v1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_DYNAMIC_READ);
glGenVertexArrays(v1,&VCO);
glBindVertexArray(VCO);
glEnableVertexAttribArray(0);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_COPY);
glVertexAttribPointer(0,v4,GL_FLOAT,GL_TRUE,0,(void*)0);
glEnable(GL_DITHER);
glEnable(GL_BLEND);
glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
glDepthFunc(GL_LESS);
glDepthMask(F);
glClearDepthf(F);
glClearColor(F0,F0,F0,F);
glViewport(0,0,S,S);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
emscripten_set_main_loop((void(*)())renderFrame,0,0);
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
