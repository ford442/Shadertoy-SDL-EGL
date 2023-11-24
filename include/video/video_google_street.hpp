#pragma once

// #pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include "../../include/video/defs.hpp"
#include "../../include/video/intrins.hpp"

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

#include <unistd.h>

#include <emscripten.h>

#include <emscripten/html5.h>

#include "../../include/video/egl.hpp"

void avgFrm(int,int,float *,float *);

extern "C"{

void b3();

void nano(int,int,float *,float *);

}

void uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

char32_t * read_file(const GLchar *);

void renderFrame();

EM_BOOL mouse_call_click(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL mouse_call_move(int,const EmscriptenMouseEvent *,void *);

void clrclr(GLfloat,GLfloat,GLfloat);

extern "C"{

void clr(GLfloat,GLfloat,GLfloat);

void str();

}
