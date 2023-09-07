#include <emscripten.h>
#include <emscripten/html5.h>
// #include <webgl/webgl2.h>
#include <functional>
#include <chrono>

#define GL_FRAGMENT_PRECISION_HIGH 1

#include <GL/gl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/function.hpp>

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;

EGLDisplay display;
EGLContext contextegl;
EGLSurface surface;
EGLint config_size,major,minor;

double wi,hi;

int Size;
GLfloat S;

