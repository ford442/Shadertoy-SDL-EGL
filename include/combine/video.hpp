#pragma once
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#pragma pack(1)
#pragma fenv_access(on)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE OFF
#pragma STDC FP_CONTRACT ON
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1


#include <float.h>
#include <math.h>
#include <new>

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_USE_LONG_DOUBLE
#define BOOST_NO_EXCEPTIONS 

#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "../../include/combine/intrins.hpp"

#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>

#include <emscripten.h>
#include <algorithm>
#include <string.h>
// #include <locale> // utf-16
// #include <uchar.h> // utf-16
// #include <stdfloat>  //  c++23
#include <time.h>
// #include <chrono>
#include "../../include/shader/gl.h"
#include "../../include/shader/egl.h"
#include <emscripten/html5.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp.h"

#include <cfloat>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cfloat>
#include <climits>

EGLint att_lst2_js[1000]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT|EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT,
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT|EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT|EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
// EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_BT2020_LINEAR_EXT,
EGL_NONE,EGL_NONE
};

EGLint ctx_att_js[500]={
EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_CONTEXT_MAJOR_VERSION_KHR,(EGLint)3,
// EGL_CONTEXT_MINOR_VERSION_KHR,(EGLint)0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE,EGL_NONE
};

EGLint att_lst_js[1500]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_ES3_BIT,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_RED_SIZE,(EGLint)32,
EGL_GREEN_SIZE,(EGLint)32,
EGL_BLUE_SIZE,(EGLint)32,
EGL_ALPHA_SIZE,(EGLint)32,
EGL_DEPTH_SIZE,(EGLint)32,
EGL_STENCIL_SIZE,(EGLint)32,
EGL_BUFFER_SIZE,(EGLint)64,
EGL_SAMPLE_BUFFERS,EGL_TRUE,
// EGL_COVERAGE_BUFFERS_NV,(EGLint)1, // used to indicate, not set
//  EGL_COVERAGE_SAMPLES_NV,(EGLint)4, // used to indicate, not set
EGL_SAMPLES,32,
// EGL_MIPMAP_LEVEL,(EGLint)1, // used to indicate, not set
// EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX, // used to indicate, not set
EGL_NONE,EGL_NONE
};

using avg_tensor=boost::numeric::ublas::tensor<float>;

static avg_tensor avRg=avg_tensor{3,3};
EmscriptenWebGLContextAttributes attr_js;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx_js;
EGLConfig eglconfig_js;
double hi_js,wi_js,Size_js;
EGLint config_size_js,major_js,minor_js;
EGLDisplay display_js;
EGLSurface surface_js;

class Video{

private:

public:

union{

static void resetAvg(){
avRg.at(0,0)=0.0; // max
avRg.at(1,0)=1.0; // min
avRg.at(2,0)=0.0; // sum
avRg.at(0,1)=0.0; // avgsum
avRg.at(1,1)=0.0; // minsum
avRg.at(2,1)=0.0; // maxsum
avRg.at(0,2)=0.0; // brt
avRg.at(1,2)=0.0; // drk
avRg.at(2,2)=0.0; // avrg
}

static void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avRg.at(2,2)=(((avr+(1.0-rlc))/2.0)+alc);
avRg.at(1,2)=1.0-(avr-0.5);
avRg.at(0,2)=1.0-(((1.0-rlc)-(alc-0.5)));
glBlendColor(avRg.at(2,2),avRg.at(2,2),avRg.at(2,2),1.0f);
glClearColor(avRg.at(1,2),avRg.at(1,2),avRg.at(1,2),avRg.at(0,2));
return;
}

static void avgFrm(int Fnum,int leng,float *ptr,float *aptr){
for(int i=0;i<leng;i++){
avRg.at(2,0)+=ptr[i];
if(avRg.at(0,0)<ptr[i]){avRg.at(0,0)=ptr[i];
}
if(avRg.at(1,0)>ptr[i]&&ptr[i]>0){avRg.at(1,0)=ptr[i];
}
}
avRg.at(2,0)=avRg.at(2,0)/leng;
aptr[Fnum]=avRg.at(2,0);
aptr[Fnum+100]=avRg.at(1,0);
aptr[Fnum+200]=avRg.at(0,0);
for(int i=33;i<65;i++){
avRg.at(0,1)+=aptr[i];
}
aptr[0]=avRg.at(0,1)/32;
for(int i=33;i<65;i++){
avRg.at(1,1)+=aptr[i+100];
}
aptr[100]=avRg.at(1,1)/32;
for(int i=33;i<65;i++){
avRg.at(2,1)+=aptr[i+200];
}
aptr[200]=avRg.at(2,1)/32;
return;
}

}avgr;

static void egl(){
eglconfig_js=NULL;
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=static_cast<int>(hi_js);
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_TRUE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_FALSE;
attr_js.premultipliedAlpha=EM_FALSE;
attr_js.preserveDrawingBuffer=EM_FALSE;
attr_js.enableExtensionsByDefault=EM_TRUE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
eglBindAPI(EGL_OPENGL_ES_API);
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,att_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,ctx_att_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,att_lst2_js);
eglBindAPI(EGL_OPENGL_API);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
emscripten_webgl_make_context_current(ctx_js);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glEnable(GL_BLEND);
// glDisable(GL_DITHER);
 glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBlendEquationSeparate(GL_FUNC_ADD,GL_MAX);
// glEnable(GL_SCISSOR_TEST);
emscripten_webgl_enable_extension(ctx_js, "EGL_EXT_create_context_robustness");
emscripten_webgl_enable_extension(ctx_js, "EGL_EXT_pixel_format_float");  //  required for float/alpha   -- EGL --
emscripten_webgl_enable_extension(ctx_js, "EGL_IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js, "EGL_NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js, "EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js, "EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js, "EXT_color_buffer_float");
emscripten_webgl_enable_extension(ctx_js, "EXT_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx_js, "EXT_blend_minmax");
emscripten_webgl_enable_extension(ctx_js, "EXT_float_blend");
emscripten_webgl_enable_extension(ctx_js, "EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx_js, "ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js, "ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js, "ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js, "ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js, "ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js, "ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js, "ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js, "ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx_js, "ARB_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js, "EGL_KHR_gl_colorspace");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_scrgb_linear");
 // emscripten_webgl_enable_extension(ctx_js, "EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_display_p3");
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
// glDisable(GL_BLEND);
glViewport((GLint)0,(GLint)0,Size_js,Size_js);
// glScissor((GLint)0,(GLint)0,Size_js,Size_js);
return;
}
  
};
