#pragma once
#include "../../include/shader/boost_defs.h"

#include <boost/compute/core.hpp>
#include <boost/compute/interop/opengl.hpp>

// #define GL_SILENCE_DEPRECATION

#ifndef GL_FRAGMENT_PRECISION_HIGH
#define GL_FRAGMENT_PRECISION_HIGH 1
#endif

// #include <GL/gl3w.h>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/gl.h>
#include <GL/glext.h>


// #define GLFW_INCLUDE_GLEXT 1
// #include <GLFW/glfw3.h>
