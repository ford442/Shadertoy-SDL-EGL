#include <emscripten.h>
#include <emscripten/html5.h>

#define GL_GLEXT_PROTOTYPES 1
#define GL_FRAGMENT_PRECISION_HIGH 1
#define GL3_PROTOTYPES 1

#include <GLES3/gl3.h>
// #include <GLES3/gl31.h>
// #include <GLES3/gl32.h>
// #include <GLES3/gl3platform.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
// #include <EGL/eglplatform.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include <functional>

#include <boost/function.hpp>
