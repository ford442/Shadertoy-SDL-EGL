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

EM_BOOL avgFrm(int,int,float *,float *);

extern "C"{

EM_BOOL b3();

EM_BOOL nano(int,int,float *,float *);

}

EM_BOOL uni(GLfloat,GLfloat,GLfloat,GLint,GLfloat);

GLuint compile_shader(GLenum,GLsizei,const GLchar **);

char32_t * read_file(const GLchar *);

EM_BOOL renderFrame();

EM_BOOL mouse_call_click(int,const EmscriptenMouseEvent *,void *);

static EM_BOOL mouse_call_move(int,const EmscriptenMouseEvent *,void *);

EM_BOOL clrclr(GLfloat,GLfloat,GLfloat);

extern "C"{

EM_BOOL clr(GLfloat,GLfloat,GLfloat);

EM_BOOL str();

}
