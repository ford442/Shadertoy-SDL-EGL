#include <emscripten.h>
#include <emscripten/html5.h>

#include <webgl/webgl2.h>

void avgFrm(int Fnum,int leng,float *ptr,float *aptr);

void clrclr(GLfloat rlc,GLfloat alc,GLfloat avr);

// void uni(float xx,float yy,GLfloat time,EGLint fram);

// GLuint compile_shader(GLenum type,GLsizei nsources,const char **dsources);

void renderFrame();

void strt();

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);

// void SDLCALL bfr(void *unused,Uint8* stm,int len);

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData);

static const char8_t *read_file(const char *filename);
static const char *read_file_c(const char *filename);
