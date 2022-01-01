#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>
#include <ctime>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point t1,t2;
GLuint EBO,FBO,tex2d[4],shader_program,shader,frame,attrib_position,sampler_channel[4];
GLuint VBO,VAO,vtx,frag,uniform_frame,uniform_time,uniform_res,uniform_mouse;
long double Ttime;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
GLsizei nsources,i,S;
GLsizei s4=4;
EGLint config_size,major,minor;
EGLConfig eglconfig=NULL;
char8_t program_source;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
GLint v0=0,v1=1,v2=2,v4=4,v6=6;
struct timespec rem;
struct timespec req={0,4000000};
static const GLenum attt[]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3};
const char8_t common_shader_header_gles3[]=u8"#version 300 es \n precision highp float;precision highp sampler3D;precision highp sampler2D;precision highp int;\n";
const char8_t vertex_shader_body_gles3[]=u8"layout(location=0)in highp vec4 iPosition;void main(){gl_Position=iPosition;}\n";
const char8_t fragment_shader_header_gles3[]=u8"uniform vec3 iResolution;uniform float iTime;uniform vec4 iMouse;uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;out highp vec4 fragColor;\n";
const char8_t fragment_shader_footer_gles3[]=u8"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\n";
const char8_t* common_shader_header=common_shader_header_gles3;
const char8_t* vertex_shader_body=vertex_shader_body_gles3;
const char8_t* fragment_shader_header=fragment_shader_header_gles3;
const char8_t* fragment_shader_footer=fragment_shader_footer_gles3;
const EGLint attribut_list[]={EGL_NONE};
EGLint anEglCtxAttribs2[]={EGL_CONTEXT_CLIENT_VERSION,3,EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,EGL_NONE};
const EGLint attribute_list[]={EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,EGL_RED_SIZE,32,EGL_GREEN_SIZE,32,EGL_BLUE_SIZE,32,EGL_ALPHA_SIZE,32,EGL_DEPTH_SIZE,32,EGL_STENCIL_SIZE,32,EGL_BUFFER_SIZE,32,EGL_NONE};
typedef struct{GLfloat XYZW[4];}Vertex;
Vertex vertices[]={{-1.0,-1.0,0.0,1.0},{-1.0,1.0,0.0,1.0},{1.0,-1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
GLubyte Indices[]={0,1,2,2,1,3};
const size_t BufferSize=sizeof(vertices);
const size_t VertexSize=sizeof(vertices[0]);
char8_t fileloc[20]=u8"/shader/shader1.toy";
char8_t *sources[4];
char8_t *result=NULL;
long length=0;

static char8_t read_file(const char *filename){
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){fclose(file);return NULL;}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){fclose(file);return NULL;}
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){size_t actual_length=fread(result,sizeof(char8_t),length,file);result[actual_length++]={'\0'};}fclose(file);return result;}
return NULL;
}

static GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar *sources){
GLsizei srclens[nsources];
for(i=0;i<nsources;++i){srclens[i]=(GLsizei)sizeof(sources[i]);}
shader=glCreateShader(type);
glShaderSource(shader,nsources,&sources,srclens);
glCompileShader(shader);
return shader;
}

static void renderFrame(){
t2=high_resolution_clock::now();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
duration<long double>time_spana=duration_cast<duration<long double>>(t2-t1);
Ttime=time_spana.count();
glUniform1f(uniform_time,Ttime);
glUniform1i(uniform_frame,frame);
glDrawElements(GL_TRIANGLES,v6,GL_UNSIGNED_BYTE,Indices);
eglSwapBuffers(display,surface);
frame++;
nanosleep(&req,&rem);
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
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
ctx=emscripten_webgl_create_context("#canvas",&attr);
eglInitialize(display,&major,&minor);
if(eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size)==EGL_TRUE && eglconfig!=NULL){
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
program_source=read_file("/shader/shader1.toy");
const char8_t* default_fragment_shader=program_source.c_str();
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
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
glUseProgram(shader_program);
glGenBuffers(v1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_DRAW);
glGenVertexArrays(v1,&VAO);
glBindVertexArray(VAO);
glGenBuffers(v1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glVertexAttribPointer(attrib_position,v4,GL_FLOAT,GL_TRUE,VertexSize,GL_FALSE);
glEnableVertexAttribArray(attrib_position);
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
glUniform1i(sampler_channel[0],v0);
glUniform1i(sampler_channel[1],v0);
glUniform1i(sampler_channel[2],v0);
glUniform1i(sampler_channel[3],v0);
glEnable(GL_BLEND);
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
glDisable(GL_DITHER);
glDepthMask(GL_FALSE);
glDisable(GL_DEPTH_TEST);
glEnable(GL_SCISSOR_TEST);
glScissor(0,0,S,S);
glDisable(GL_SCISSOR_TEST);
glDisable(GL_STENCIL_TEST);
glBlendEquationSeparate(GL_FUNC_ADD,GL_MIN);
glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
glViewport(v0,v0,S,S);
glClearColor(0.0f,1.0f,0.0f,1.0f);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
t1=high_resolution_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
}

extern "C" {
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
FS.mkdir("/shader");
});
return 1;
}
