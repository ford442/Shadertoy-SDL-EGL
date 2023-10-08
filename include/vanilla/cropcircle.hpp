#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgl.h>

// #include <webgl/webgl2.h>
#include <functional>
#include <chrono>
#include <ctime>

#define GL_FRAGMENT_PRECISION_HIGH 1

#define GL_CONTEXT_PROFILE_MASK 0x9126
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001

#define GL_GLES_PROTOTYPES 1
#define EGL_EGL_PROTOTYPES 1
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <KHR/khrplatform.h>

#include <GLES3/gl3.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

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

