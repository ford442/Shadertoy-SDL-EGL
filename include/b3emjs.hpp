extern "C"{
void b3();
void nano(short int,int,float *,float *);
};

void avgFrm(short int,int,float *,float *);

#include <emscripten.h>
#include <emscripten/html5.h>

EM_BOOL mouse_call(int,const EmscriptenMouseEvent *,void *);

#define GL_GLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#include <GL/gl.h>
#include <GL/glext.h>

#include <webgl/webgl2.h>
