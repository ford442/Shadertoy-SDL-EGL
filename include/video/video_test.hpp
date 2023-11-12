#include <emscripten.h>
#include <emscripten/html5.h>

#include <functional>

#include <boost/function.hpp>

EMSCRIPTEN_RESULT ret;

EGLDisplay display;
EGLContext contextegl;
EGLSurface surface;
EGLint config_size,major,minor;

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;
