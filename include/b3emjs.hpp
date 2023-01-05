#include <emscripten.h>
#include <emscripten/html5.h>
#include <webgl/webgl2.h>
#include <GL/gl.h>
void avgFrm(short int Fnum,int leng,float *ptr,float *aptr);
EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);
extern "C"{
void b3();
void nano(short int Fnum,int leng,float *ptr,float *aptr);
};
