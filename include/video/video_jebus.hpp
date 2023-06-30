#include <emscripten.h>
#include <emscripten/html5.h>

#include <webgl/webgl2.h>

void avgFrm(int Fnum,int leng,float *ptr,float *aptr);

void clrclr(GLfloat rlc,GLfloat alc,GLfloat avr);

void uni(float xx,float yy,GLfloat time,EGLint fram);

GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources);

void renderFrame();

void strt();

void plt();

void SDLCALL bfr(void *unused,Uint8* stm,int len);

void opn_aud();

void qu(int rc);

void cls_aud();

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);

static const char8_t *read_file(const char *filename);
