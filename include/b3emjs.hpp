#include <emscripten.h>
#include <emscripten/html5.h>
void avgFrm(short int Fnum,int leng,float *ptr,float *aptr);
EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);
extern "C"{
void b3();
void nano(short int Fnum,int leng,float *ptr,float *aptr);
void clr(GLclampf cllr,GLclampf alp);
};
