#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstdbool>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>
#include <ctime>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point t1,t2,t3;
GLuint VBO,EBO,CBO,NBO,tex2d[4],shader_program,shader,frame;
GLuint attribute_position,sampler_channel[4],shader_color,shader_normals,shader_indice;
GLuint VCO,CCO,ECO,NCO,vtx,frag,uniform_frame,uniform_time;
GLuint uniform_dtime,uniform_fps,uniform_res,uniform_mouse;
long double Ttime,Dtime;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
GLsizei nsources,i,S;
GLsizei s4=4;
EGLint config_size,major,minor;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EGLint v0=0,v1=1,v2=2,v3=3,v4=4,v6=6,v32=32;
struct timespec rem;
struct timespec req={0,25000000};
GLfloat F=1.0f;
GLfloat F0=0.0f;
GLfloat fps;
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{-1.0,-1.0,0.0,1.0},{-1.0,1.0,0.0,1.0},{1.0,-1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
Vertex colors[]={{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0}};
Vertex normals[]={{0.0,0.0,1.0},{0.0,0.0,1.0},{0.0,0.0,1.0},{0.0,0.0,1.0}};
GLuint Indices[]={0,1,2,2,1,3};
const size_t BufferSize=sizeof(vertices);
const size_t ColorsSize=sizeof(colors);
const size_t NormalsSize=sizeof(normals);
const size_t IndicesSize=sizeof(Indices);
const size_t VertexSize=sizeof(vertices[0]);
const size_t ColorSize=sizeof(colors[0]);
const size_t NormalSize=sizeof(normals[0]);
const size_t IndexSize=sizeof(Indices[0]);
char *fileloc="/shader/shader1.toy";
const char *sources[4];
char8_t *result=NULL;
long length=0;
static const GLenum attt[]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3};
const char common_shader_header_gles3[]=
"#version 300 es \n"
"precision highp float;"
"precision highp sampler3D;"
"precision highp sampler2D;"
"precision highp int;\n";
const char vertex_shader_body_gles3[]=
"layout(location=0)in highp vec4 iPosition;"
"void main(){"
"gl_Position=iPosition;"
"} \n";
const char fragment_shader_header_gles3[]=
"uniform vec3 iResolution;"
"uniform float iTime;"
"uniform float iTimeDelta;"
"uniform float iFrameRate;"
"uniform vec4 iMouse;"
"uniform sampler2D iChannel0;"
"uniform sampler2D iChannel1;"
"uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
"out highp vec4 fragColor;\n";
const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);} \n";
const char* common_shader_header=common_shader_header_gles3;
const char* vertex_shader_body=vertex_shader_body_gles3;
const char* fragment_shader_header=fragment_shader_header_gles3;
const char* fragment_shader_footer=fragment_shader_footer_gles3;

static const char8_t *read_file(const char *filename){
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
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
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
t3=t2;
t2=high_resolution_clock::now();
duration<long double>time_spanb=duration_cast<duration<long double>>(t2-t3);
duration<long double>time_spana=duration_cast<duration<long double>>(t2-t1);
Ttime=time_spana.count();
Dtime=time_spanb.count();
fps=1.0f/Dtime;
glUniform1f(uniform_time,Ttime);
glUniform1i(uniform_frame,frame);
glUniform1f(uniform_dtime,Dtime);
glUniform1f(uniform_fps,fps);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
glDrawElements(GL_TRIANGLES,v6,GL_UNSIGNED_INT,Indices);
eglSwapBuffers(display,surface);
frame++;
// nanosleep(&req,&rem);
}

static void strt(){
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
F=(float)S;
const EGLint attribut_list[]={EGL_NONE,EGL_NONE};
EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,v3,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_NONE,EGL_NONE};
const EGLint attribute_list[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
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
EGL_NONE,EGL_NONE
};
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=v2;
attr.minorVersion=v0;
ctx=emscripten_webgl_create_context("#canvas",&attr);
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,config_size,&v1);
eglBindAPI(EGL_OPENGL_ES_API);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
const char* default_fragment_shader=(char*)read_file(fileloc);
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
glUseProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays(v1,&VCO);
glGenVertexArrays(v1,&CCO);
glGenVertexArrays(v1,&ECO);
glGenVertexArrays(v1,&NCO);
glGenBuffers(v1,&VBO);
glGenBuffers(v1,&EBO);
glGenBuffers(v1,&CBO);
glGenBuffers(v1,&NBO);

glBindVertexArray(VCO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,BufferSize,vertices,GL_STATIC_DRAW);
glVertexAttribPointer(attribute_position,v4,GL_FLOAT,GL_FALSE,VertexSize,0);
glEnableVertexAttribArray(attribute_position);

glBindVertexArray(CCO);
glBindBuffer(GL_ARRAY_BUFFER,CBO);
glBufferData(GL_ARRAY_BUFFER,ColorsSize,colors,GL_STATIC_DRAW);
glVertexAttribPointer(shader_color,v4,GL_FLOAT,GL_FALSE,ColorSize,0);
glEnableVertexAttribArray(shader_color);
 
glBindVertexArray(NCO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,NBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,NormalsSize,normals,GL_STATIC_DRAW);
glVertexAttribPointer(shader_normals,v3,GL_FLOAT,GL_FALSE,NormalSize,0);
glEnableVertexAttribArray(shader_normals);

glBindVertexArray(ECO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,IndicesSize,Indices,GL_STATIC_DRAW);
glVertexAttribPointer(shader_indice,v1,GL_UNSIGNED_INT,GL_FALSE,IndexSize,0);
glEnableVertexAttribArray(shader_indice);

glBindVertexArray(v0);

/*
glGenTextures(v4,tex2d);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,tex2d[0]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glGenerateMipmap(GL_TEXTURE_2D);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D,tex2d[1]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glGenerateMipmap(GL_TEXTURE_2D);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D,tex2d[2]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glGenerateMipmap(GL_TEXTURE_2D);
glActiveTexture(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D,tex2d[3]);
glTexImage2D(GL_TEXTURE_2D,v0,GL_RGBA,S,S,v0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glGenerateMipmap(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,v0);
glGenFramebuffers(v1,&FBO);
glBindFramebuffer(GL_FRAMEBUFFER,FBO);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,tex2d[0],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,tex2d[1],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D,tex2d[2],v0);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT3,GL_TEXTURE_2D,tex2d[3],v0);
glBindFramebuffer(GL_FRAMEBUFFER,v0);
*/
attribute_position=glGetAttribLocation(shader_program,"iPosition");
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_dtime=glGetUniformLocation(shader_program,"iTimeDelta");
uniform_frame=glGetUniformLocation(shader_program,"iFrame");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
uniform_mouse=glGetUniformLocation(shader_program,"iMouse");
uniform_fps=glGetUniformLocation(shader_program,"iFrameRate");
shader_color=glGetUniformLocation(shader_program,"fragColor");
glUniform3f(uniform_res,F,F,F);
/*
glUniform1i(sampler_channel[0],v0);
glUniform1i(sampler_channel[1],v0);
glUniform1i(sampler_channel[2],v0);
glUniform1i(sampler_channel[3],v0);
*/
// glViewport(v0,v0,S,S);
glDisable(GL_BLEND);
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
glDisable(GL_DITHER);
// glEnable(GL_DEPTH_TEST);
 // glDepthFunc(GL_ALWAYS);
 //  glEnable(GL_SCISSOR_TEST);
// glScissor(v0,v0,S,S);
// glDisable(GL_SCISSOR_TEST);
// glEnable(GL_STENCIL_TEST);
glClearColor(F0,F0,F0,F);
glClearDepthf(F);
glClearStencil(F0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
t1=high_resolution_clock::now();
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
