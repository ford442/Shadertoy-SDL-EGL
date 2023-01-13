extern "C"{
void str();
};

float Ttime,TtimeDelta,cMouseY,cMouseX,mouseY,mouseX,Dm1=-1.0,D0=0.0,D=1.0,F=1.0f,Fm1=-1.0f,F0=0.0f;
short int iFrame,iFps,Size;
double wi,hi;
const char * fileloc="/shader/shader1.toy";

void renderFrame();

#include <iostream>
#include <ctime>
#include <chrono>

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::high_resolution_clock::time_point t3;

struct timespec rem;
struct timespec req={0,16600000};

#include "../include/b3gl.hpp"

extern "C"{
  
void clr(GLclampf,GLclampf,GLclampf);
  
};

GLclampf x,y,gF=F,gF0=F0,gFm1=Fm1,y1y=1.0;
GLfloat g1g=1.0,S;
GLsizei s4=4,i;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res,VCO,ECO,vtx,frag,uni_mse,shader,uni_srate,uni_res,uni_tme_dlt,uni_tme,uni_frm;
GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9,indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};
typedef struct{GLclampf XYZW[4];}Vertex;
const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLchar * sources[4];

const GLchar common_shader_header_gles3[]=
"#version 300 es\n"
"\n #undef HW_PERFORMANCE\n"
"\n #define HW_PERFORMANCE 0\n"
"\n precision highp float;precision highp int;precision lowp sampler3D;precision lowp sampler2D;\n";

const GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";

const GLchar fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"\n uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"\n uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"\n out vec4 fragColor;\n";

const GLchar fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);}\0";

const GLchar * common_shader_header=common_shader_header_gles3;
const GLchar * vertex_shader_body=vertex_shader_body_gles3;
const GLchar * fragment_shader_header=fragment_shader_header_gles3;
const GLchar * fragment_shader_footer=fragment_shader_footer_gles3;

void uni(float,float,GLfloat,short int);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

void clrclr(GLclampf,GLclampf,GLclampf);

static const char8_t * read_file(const GLchar *);

#include "../include/b3egl.hpp"

EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig;
EGLint config_size,major,minor,atb_pos;

#include <emscripten.h>

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EMSCRIPTEN_RESULT ret;
EM_BOOL ms_l,clk_l;

EM_BOOL mouse_call(int,const EmscriptenMouseEvent *,void *);


#include <wasm_simd128.h>
#include <xmmintrin.h>
#include <unistd.h>
