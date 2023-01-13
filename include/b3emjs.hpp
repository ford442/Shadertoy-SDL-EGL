
#include <emscripten.h>


extern "C"{
void b3();
void nano(short int,int,float *,float *);
};

void avgFrm(short int,int,float *,float *);



#include "../include/b3gl.hpp"
#include "../include/b3egl.hpp"

EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx_js;
EGLContext contextegl_js;
EmscriptenWebGLContextAttributes attr_js;

EGLDisplay display_js;
EGLSurface surface_js;
EGLConfig eglconfig_js;
EGLint config_size_js,major_js,minor_js;
