#pragma once

#include "../../include/combine/intrins.hpp"

#include <webgl/webgl2.h>

#ifndef GL_GLES_PROTOTYPES
#define GL_GLES_PROTOTYPES
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>
#ifndef EGL_EGL_PROTOTYPES 
#define EGL_EGL_PROTOTYPES
#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#ifndef EGL_NO_PLATFORM_SPECIFIC_TYPES
#define EGL_NO_PLATFORM_SPECIFIC_TYPES
#ifndef EGLAPI
#define EGLAPI

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

// #include <emscripten/html5_webgl.h>
