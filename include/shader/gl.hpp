#pragma once

// #define GL_SILENCE_DEPRECATION

#ifndef GL_FRAGMENT_PRECISION_HIGH
#define GL_FRAGMENT_PRECISION_HIGH
#endif

#include <GL/gl.h>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif

#include <GL/glext.h>

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
