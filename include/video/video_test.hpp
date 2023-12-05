#include <emscripten.h>
#include <emscripten/html5.h>

#include <GL/gl.h>
#include <GL/glext.h>
// #include <GLES3/gl32.h>
#include <GLES3/gl31.h>
// #include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
// #include <GLES/gl.h>
// #include <GLES/glext.h>
#include <GLES3/gl3platform.h>
#include <emscripten/html5_webgl.h>
// #define GLFW_INCLUDE_GLEXT 1
// #define GLFW_INCLUDE_ES3
// #include <GLFW/glfw3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
// #include <EGL/eglplatform.h>  included by egl.h
// #include <KHR/khrplatform.h>  included by egl.h

#include <functional>

#include <boost/function.hpp>

EM_BOOL mouse_call(int,const EmscriptenMouseEvent *,void *);
static const char8_t *read_file(const char *);
GLuint compile_shader(GLenum,GLsizei,const char **);

#include "../../include/video/common.hpp"
