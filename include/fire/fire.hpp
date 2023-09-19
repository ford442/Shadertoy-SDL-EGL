#include <emscripten.h>
#include <emscripten/html5.h>

#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/function.hpp>

#ifndef OPENGL_CORE_PROFILE
#define OPENGL_CORE_PROFILE 1
#endif

#ifndef GL_CONTEXT_FLAG_NO_ERROR_BIT
#define GL_CONTEXT_FLAG_NO_ERROR_BIT 1
#endif

#define GL_RED_MIN 0.0
#define GL_RED_MAX 1.0
#define GL_GREEN_MIN 0.0
#define GL_GREEN_MAX 1.0
#define GL_BLUE_MIN 0.0
#define GL_BLUE_MAX 1.0
#define GL_ALPHA_MIN 0.0
#define GL_ALPHA_MAX 1.0
#define GL_INTENSITY_MIN 0.0
#define GL_INTENSITY_MAX 1.0
#define GL_LUMINANCE_MIN 0.0
#define GL_LUMINANCE_MAX 1.0

static constexpr EGLint numSamples=2;

// static constexpr float numSamplesf=float(numSamples);
static constexpr float numSamplesf=4.0f;

static constexpr EGLint att_lst2[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,

  // Google Colab
/*
If BT-2020 is set to linear, it will degrade the fidelity of image representation. 
This is because the BT.2020 color space is a non-linear color space, and when it is set to linear,
the values of the components are directly proportional to the perceived brightness or lightness of the color.
This means that the colors in the image will be misrepresented,
and the image will not be as accurate as it would be if it were in the original BT.2020 color space.
*/

// EGL_GL_COLORSPACE_LINEAR_KHR, 
// EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_SRGB,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// / EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_BACK_BUFFER,
EGL_NONE,EGL_NONE
};

static constexpr EGLint ctx_att[]={
// EGL_CONTEXT_MAJOR_VERSION_KHR,2,
// EGL_CONTEXT_MINOR_VERSION_KHR,0,
EGL_CONTEXT_MAJOR_VERSION_KHR,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};

static constexpr EGLint att_lst[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FIXED_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_BIT,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_TRIPLE_BUFFER_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
//   EGL_SURFACE_TYPE,EGL_MULTISAMPLE_RESOLVE_BOX_BIT,
//   EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY,EGL_NO_RESET_NOTIFICATION,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_COLOR_BUFFER_TYPE,EGL_RGB_BUFFER,
EGL_LUMINANCE_SIZE,32,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,64,
EGL_SAMPLE_BUFFERS,1,
EGL_COVERAGE_BUFFERS_NV,1,
EGL_COVERAGE_SAMPLES_NV,4,
EGL_SAMPLES,4,
EGL_NONE,EGL_NONE
};

boost::function<EM_BOOL(void)>em_ctx;

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;

EGLDisplay display=nullptr;
EGLSurface surface=nullptr;
EGLContext ctxegl=nullptr;
EGLConfig eglconfig=nullptr;
EGLint config_size,major,minor;
