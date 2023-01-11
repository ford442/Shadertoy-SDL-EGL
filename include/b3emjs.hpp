
#include <emscripten.h>
#include <emscripten/html5.h>

extern "C"{
void b3();
void nano(short int,int,float *,float *);
};

void avgFrm(short int,int,float *,float *);

#define GL3_PROTOTYPES 1
#define GL4_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1

#include <GL/gl.h>
#include <GL/glext.h>

#include <webgl/webgl2.h>
