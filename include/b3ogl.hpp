extern "C"{
void str();
};

float F=1.0f,cMouseY,cMouseX,mouseY,mouseX,Dm1=-1.0,D0=0.0,D=1.0,Fm1=-1.0f,F0=0.0f,Ttime,TtimeDelta;
short int iFrame,iFps,Size;
double wi,hi;
const char * fileloc="/shader/shader1.toy";

void renderFrame();

#include <iostream>
#include <ctime>
#include <chrono>

// steady_clock::time_point t1;
// steady_clock::time_point t2;
// steady_clock::time_point t3;
std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::high_resolution_clock::time_point t3;
struct timespec rem;
struct timespec req={0,15000000};

#define GL3_PROTOTYPES 1
#define GL_GLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#include <GL/gl.h>
#include <GL/glext.h>

extern "C"{
  
void clr(GLclampf,GLclampf);
  
};

GLclampf x,y,y1y=1.0,gF=F,gF0=F0,gFm1=Fm1;
GLfloat g1g=1.0,S;
GLsizei s4=4,i;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res,VCO,ECO,vtx,frag,uni_mse,shader,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm;
GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9,indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
typedef struct{GLclampf XYZW[4];}Vertex;
const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLchar * sources[4];

const GLchar common_shader_header_gles3[]=
"#version 300 es\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
"precision highp float;precision mediump int;precision mediump sampler3D;precision mediump sampler2D;\n";

const GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";

const GLchar fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"\n uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"\n uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"\n out vec4 fragColor;\n";

const GLchar fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);fragColor.a=1.0;}\0";

const GLchar * common_shader_header=common_shader_header_gles3;
const GLchar * vertex_shader_body=vertex_shader_body_gles3;
const GLchar * fragment_shader_header=fragment_shader_header_gles3;
const GLchar * fragment_shader_footer=fragment_shader_footer_gles3;

void uni(float,float,GLfloat,short int);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

void clrclr(GLclampf,GLclampf);

static const char8_t * read_file(const GLchar *);

#define EGL_EGLEXT_PROTOTYPES 1
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
EGLint v0=0,v3=3,config_size,major,minor,atb_pos;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig;

const EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE};

const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};

const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
//  EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
EGL_CONFORMANT,EGL_OPENGL_BIT,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
EGL_RED_SIZE,64,
EGL_GREEN_SIZE,64,
EGL_BLUE_SIZE,64,
EGL_ALPHA_SIZE,64,
EGL_DEPTH_SIZE,64,
EGL_STENCIL_SIZE,64,
EGL_BUFFER_SIZE,64,
EGL_SAMPLE_BUFFERS,256,
EGL_SAMPLES,128,
EGL_NONE
};

// #define GL4_PROTOTYPES 1 //maybe??

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#include <webgl/webgl2.h>

#include <emscripten.h>
#include <emscripten/html5.h>

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EMSCRIPTEN_RESULT ret;
EM_BOOL ms_l,clk_l;
EM_BOOL mouse_call(int,const EmscriptenMouseEvent *,void *);
