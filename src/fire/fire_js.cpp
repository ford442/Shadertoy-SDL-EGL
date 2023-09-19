#include "../../include/fire/fire.hpp"

EM_JS(void,fl,(),{
});

boost::function<EM_BOOL()>em_ctx=[](){
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=3;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#acanvas",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
// emscripten_webgl_make_context_current(ctx);
//   emscripten_get_canvas_element_size("#zcanvas",&css.csswi,&css.csshi);
double sz;
double wd;
emscripten_get_element_css_size("canvas",&wd,&sz);
emscripten_set_element_css_size("acanvas",sz,sz);
int Size=(short int)sz;
// eglMakeCurrent(display,surface,surface,cntx.at(0,0));
emscripten_webgl_make_context_current(ctx);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(0);
///glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx,"GL_ALL_EXTENSIONS");
emscripten_webgl_enable_extension(ctx,"GL_KHR_no_error");
emscripten_webgl_enable_extension(ctx,"GL_REGAL_enable");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_platform_angle");
emscripten_webgl_enable_extension(ctx,"GL_ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_sample_shading");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_object");
emscripten_webgl_enable_extension(ctx,"ARB_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"NV_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_fragment_program");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program_option");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program");
emscripten_webgl_enable_extension(ctx,"NV_fragment_program2");
emscripten_webgl_enable_extension(ctx,"NV_float_buffer");
emscripten_webgl_enable_extension(ctx,"ARB_sample_shading");
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(ctx,"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(ctx,"NV_depth_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_float");
emscripten_webgl_enable_extension(ctx,"ARB_texture_half_float");
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_create_context");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx,"EXT_create_context_robustness");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"NV_gpu_shader4");
emscripten_webgl_enable_extension(ctx,"NV_gpu_shader5");
emscripten_webgl_enable_extension(ctx,"NV_vertex_buffer_unified_memory");
emscripten_webgl_enable_extension(ctx,"NV_gpu_program5");
emscripten_webgl_enable_extension(ctx,"NV_vertex_attrib_integer_64bit");
emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB_write_control");
emscripten_webgl_enable_extension(ctx,"OES_sample_shading");
emscripten_webgl_enable_extension(ctx,"EXT_multisample_compatibility");
emscripten_webgl_enable_extension(ctx,"OES_vertex_half_float");
emscripten_webgl_enable_extension(ctx,"NV_framebuffer_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_enhanced_layouts");
emscripten_webgl_enable_extension(ctx,"ARB_shading_language_420pack");
emscripten_webgl_enable_extension(ctx,"ARB_get_program_binary");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"EXT_bindable_uniform");
emscripten_webgl_enable_extension(ctx,"GL_EXT_geometry_shader4");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_direct_state_access");
emscripten_webgl_enable_extension(ctx,"ARB_multitexture");
emscripten_webgl_enable_extension(ctx,"GL_KHR_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"GL_EXT_texture_norm16");
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"GL_EXT_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_d3d_texture_client_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_direct3d_display");
emscripten_webgl_enable_extension(ctx,"EGL_ANGLE_robust_resource_initialization");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_device_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_output_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_platform_base");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_platform_device");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_swap_buffers_with_damage");
emscripten_webgl_enable_extension(ctx,"EGL_NV_cuda_event");
emscripten_webgl_enable_extension(ctx,"EGL_NV_device_cuda");
emscripten_webgl_enable_extension(ctx,"EGL_NV_robustness_video_memory_purge");
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglChooseConfig(display,att_lst,&eglconfig,1,&config_size);
eglInitialize(display,&major,&minor);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
eglMakeCurrent(display,surface,surface,ctxegl);
// glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
// glDepthMask(GL_TRUE);
// glEnable(GL_DEPTH_TEST);
// glEnable(GL_STENCIL_TEST);
// glFrontFace(GL_CW);
// glViewport(0,0,8192,8192);  //  viewport/scissor after UsePrg runs at full resolution
// glViewport(0,0,i_size.at(0,0),i_size.at(0,0));  //  viewport/scissor after UsePrg runs at full resolution
// glEnable(GL_SCISSOR_TEST);
// glScissor(0,0,i_size.at(0,0),i_size.at(0,0));
return EM_TRUE;
};

EM_JS(void,fi,(),{
document.getElementById('acanvas').style.zIndex=3100;
});

extern "C" {

void str(){
fl();
fi();
em_ctx();
return;
}

}
