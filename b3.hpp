#pragma once

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cfloat>
#include <climits>

#include <wasm_simd128.h>
#include <xmmintrin.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#undef main
#include "SDL_config.h"

#include <emscripten.h>
#include <emscripten/html5.h>

#define GL_GLEXT_PROTOTYPES 1
#define EGL_EGLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1
#define GL4_PROTOTYPES 1 //maybe??

#include <GL/gl.h>
#include <GL/glext.h>

#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <webgl/webgl2.h>

void avgFrm(short int Fnum,int leng,float *ptr,float *aptr);

static const char8_t *read_file(const GLchar *filename);

GLfloat x;
GLfloat y;
EM_BOOL ms_l;

void uni(float xx,float yy,GLfloat time,short int fram);

GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar **dsources);

using namespace std;
using namespace std::chrono;

steady_clock::time_point t1;
steady_clock::time_point t2;
steady_clock::time_point t3;
// high_resolution_clock::time_point t1;
// high_resolution_clock::time_point t2;
// high_resolution_clock::time_point t3;
// system_clock::time_point t1;
// system_clock::time_point t2;
// system_clock::time_point t3;

GLuint uni_mse;
GLuint uni_frm;
GLuint uni_tme;
GLuint uni_tme_dlt;
GLuint uni_res;
GLuint uni_srate;
GLuint shader;
float Ttime,TtimeDelta;
short int iFrame,iFps;
GLsizei s4=4;
// int a,b;
float F=1.0f;
float F0=0.0f;
float Fm1=-1.0f;
float D=1.0;
float D0=0.0;
float Dm1=-1.0;
float mouseX;
float mouseY;
float cMouseX;
float cMouseY;
short int Size;
GLfloat S;
EM_BOOL clk_l;
GLsizei i;
struct timespec rem;
struct timespec req={0,16660000};
const GLchar *sources[4];
GLubyte gu0=0,gu1=1,gu2=2,gu3=3,gu4=4,gu5=5,gu6=6,gu7=7,gu8=8,gu9=9;
GLubyte indc[]={gu3,gu0,gu1,gu1,gu2,gu3,gu4,gu0,gu3,gu3,gu7,gu4,gu1,gu5,gu6,gu6,gu2,gu1,gu4,gu7,gu6,gu6,gu5,gu4,gu2,gu6,gu6,gu7,gu3,gu0,gu4,gu1,gu1,gu4,gu5};

void renderFrame();

GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar **dsources);

extern "C"{
  
void strt();
void str();
void pl();
void b3();
void nano(short int Fnum,int leng,float *ptr,float *aptr);
EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);

};

