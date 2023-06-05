#pragma once
#include <boost/cstdfloat.hpp>  // must be first include
#include "../../include/combine/defs.h"
#include "../../include/combine/boost_defs.h"
#include "../../include/combine/intrins.h"
#include "../../include/combine/gl.h"
#include "../../include/combine/egl.h"
#include <algorithm>
#include <string.h>
#include <time.h>
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
#include <float.h>
#include <math.h>
#include <new>
#include <boost/integer.hpp>
#include <boost/atomic.hpp>
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <emscripten.h>
#include <emscripten/html5.h>

using avg_tensor=boost::numeric::ublas::tensor<float>;
static avg_tensor avRg=avg_tensor{3,3};
EmscriptenWebGLContextAttributes attr_js=nullptr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx_js=0;
EGLConfig eglconfig_js=nullptr;
double hi_js=0.0,wi_js=0.0,Size_js=0.0;
EGLint config_size_js=0,major_js=0,minor_js=0;
EGLDisplay display_js=nullptr;
EGLSurface surface_js=nullptr;
EGLContext ctxegl_js=nullptr;

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
eglChooseConfig(display_js,att_lst_js,&eglconfig_js,(EGLint)1,&config_size_js);
ctxegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,ctx_att_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,att_lst2_js);
eglBindAPI(EGL_OPENGL_API);
eglMakeCurrent(display_js,surface_js,surface_js,ctxegl_js);
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
glViewport(0,0,Size_js,Size_js);
// glScissor((GLint)0,(GLint)0,Size_js,Size_js);
return;
}
  
};
