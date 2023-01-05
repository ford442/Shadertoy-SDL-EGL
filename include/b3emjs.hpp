#include <emscripten.h>
#include <emscripten/html5.h>
#include <webgl/webgl2.h>
#include <GL/gl.h>
void avgFrm(short int,int,float *,float *);
EM_BOOL mouse_call(int,const EmscriptenMouseEvent *,void *);
extern "C"{
void b3();
void nano(short int,int,float *,float *);
};
