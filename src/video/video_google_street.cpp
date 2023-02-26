#include "../../include/video/video_google_street.hpp"

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avrg=(((avr+(y1y-rlc))/2.0)+alc);
drk=y1y-(avr-0.5);
brt=((y1y-rlc)-(alc-0.5));
glBlendColor(avrg,avrg,avrg,y1y);
glClearColor(drk,drk,drk,brt);
return;
}

extern "C" {

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
clrclr(cllr,alp,avr);
return;
}

}

EM_BOOL mouse_call_click(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

static EM_BOOL mouse_call_move(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return (EM_BOOL)1;
}

void uni(GLfloat xx,GLfloat yy,GLfloat stime,GLint fram,GLfloat delt){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
iFps=60.0/delt;
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_move);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=1.0-(xxx*Size);
mY=1.0-(yyy*Size);
clk_l=false;
}
mm=S*xx;
nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,stime);
glUniform1f(uni_tme_dlt,delt);
glUniform1f(uni_fps,iFps);
glUniform1i(uni_frm,fram);
return;
}

void renderFrame(){
auto t3=t2;
auto t2=std::chrono::steady_clock::now();
std::chrono::duration<float>time_spanb=duration_cast<std::chrono::duration<float>>(t2-t3);
TtimeDelta=time_spanb.count();
std::chrono::duration<float>time_spana=duration_cast<std::chrono::duration<float>>(t2-t1);
Ttime=time_spana.count();
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame,TtimeDelta);
iFrame++;
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
// glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
// glFlush();
// nanosleep(&req,&rem);
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
glFinish();
return;
}

char32_t * read_file(const GLchar * filename){
char32_t * result=NULL;
long length=0;
FILE * file=fopen(filename,"r");
if(file){
short int status=fseek(file,(long int)0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
status=fseek(file,(long int)0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
}
result=static_cast<char32_t *>(malloc((length+1)*sizeof(char32_t)));
if(result){
size_t actual_length=fread(result,sizeof(char32_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
return result;
}
return nullptr;
}

GLuint compile_shader(GLenum type,GLsizei nsources,GLchar ** dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;i++){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}

void strt(){
eglconfig=NULL;
iFrame=0;
clk_l=true;
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
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,(EGLint)1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
// retSa=emscripten_get_element_css_size("canvas",&wi,&hi);
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(float)Size;
mX=0.5*S;
mY=0.5*S;
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"EXT_color_buffer_float");
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
// emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
// emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
// emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
// emscripten_webgl_enable_extension(ctx,"GL_OES_draw_buffers_indexed");
// emscripten_webgl_enable_extension(ctx,"OES_fixed_point");  // webgl 1
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx,"OES_single_precision");  // webgl 1
// emscripten_webgl_enable_extension(ctx,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"EXT_float_blend");
// emscripten_webgl_enable_extension(ctx,"EXT_frag_depth");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_shader_texture_lod");
// emscripten_webgl_enable_extension(ctx,"GL_OES_sRGB");
// emscripten_webgl_enable_extension(ctx,"GL_OES_depth32");
// emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx,"GL_disjoint_timer_query");
// emscripten_webgl_enable_extension(ctx,"GL_EXT_clip_cull_distance");
emscripten_webgl_enable_extension(ctx,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx,"GL_disjoint_timer_query_webgl2");
// emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_sRGB"); //  ES 2
// emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
// emscripten_webgl_enable_extension(ctx,"GL_EXT_texture_shadow_lod");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_framebuffer_object");
emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
// emscripten_webgl_enable_extension(ctx,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
/// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
/// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb_linear");
/// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
/// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
/// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_multisample");
// emscripten_webgl_enable_extension(ctx,"ARB_robustness");
// emscripten_webgl_enable_extension(ctx,"ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx,"ARB_texture_storage");
emscripten_webgl_enable_extension(ctx,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx,"ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx,"ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx,"ARB_ES3_2_compatibility");
// emscripten_webgl_enable_extension(ctx,"EXT_gpu_shader4");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_gpu_shader5");
// emscripten_webgl_enable_extension(ctx,"GL_AMD_pinned_memory");
// emscripten_webgl_enable_extension(ctx,"ARB_blend_func_extended");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_buffer_storage");
// emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float");
// emscripten_webgl_enable_extension(ctx,"ARB_compatibility");
emscripten_webgl_enable_extension(ctx,"ARB_compute_shader");
emscripten_webgl_enable_extension(ctx,"ARB_enhanced_layouts");
// emscripten_webgl_enable_extension(ctx,"ARB_shadow");
// emscripten_webgl_enable_extension(ctx,"ARB_sync");
emscripten_webgl_enable_extension(ctx,"ARB_tessellation_shader");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_texture_float");
// emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_multisample");
emscripten_webgl_enable_extension(ctx,"EXT_geometry_shader");
// emscripten_webgl_enable_extension(ctx,"GL_MESA_shader_integer_functions");
// emscripten_webgl_enable_extension(ctx,"OES_geometry_shader");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_stencil8");
emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_draw_buffers_blend");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_cull_distance");
// emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
// emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearDepth(D);
glEnable(GL_POLYGON_OFFSET_FILL);
glPolygonOffset((GLfloat)0.5f,(GLfloat)500.0f);
// glDisable(GL_STENCIL_TEST);
glDisable(GL_DITHER);
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
//glEnable(GL_BLEND);
glDisable(GL_BLEND);
// glBlendFuncSeparate(GL_SRC_COLOR,GL_ONE_MINUS_DST_COLOR,GL_DST_COLOR,GL_SRC_ALPHA);
// glBlendEquationSeparate(GL_FUNC_SUBTRACT,GL_MIN);
// glClearColor((GLclampf)gF,(GLclampf)gF,(GLclampf)gF,(GLclampf)gF);
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
nanosleep(&req,&rem);
GLchar * default_fragment_shader=(GLchar *)read_file(fileloc);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
nanosleep(&req,&rem);
shd_prg=glCreateProgram();
glAttachShader(shd_prg,frag);
glAttachShader(shd_prg,vtx);
atb_pos=0;
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_tme_dlt=glGetUniformLocation(shd_prg,"iTimeDelta");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_fps=glGetUniformLocation(shd_prg,"iFrameRate");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
uni_srate=glGetUniformLocation(shd_prg,"iSampleRate");
smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
// smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
// smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
// smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
// smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
glUniform1f(uni_srate,44100.0f);
glUniform3f(uni_res,S,S,gF);
glUniform3f(smp_chn_res,S,S,gF);
glViewport((GLint)0,(GLint)0,Size,Size);  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES,GL_NICEST);
glScissor((GLint)0,(GLint)0,Size,Size);

auto t1=std::chrono::steady_clock::now();
emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
}

void egl(){
eglconfig_js=NULL;
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=(GLsizei)hi_js;
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_TRUE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_TRUE;
attr_js.preserveDrawingBuffer=EM_FALSE;
attr_js.enableExtensionsByDefault=EM_FALSE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
// eglSurfaceAttrib(display_js,surface_js,EGL_MIPMAP_LEVEL,(EGLint)1);
emscripten_webgl_make_context_current(ctx_js);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glDisable(GL_DITHER);
glEnable(GL_SCISSOR_TEST);
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_webcodecs_video_frame");
// emscripten_webgl_enable_extension(ctx_js,"OES_texture_float_linear");
// emscripten_webgl_enable_extension(ctx_js,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx_js,"OES_element_index_uint");
// emscripten_webgl_enable_extension(ctx_js,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx_js,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx_js,"OES_draw_buffers_indexed");
// emscripten_webgl_enable_extension(ctx_js,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx_js,"OES_single_precision");
// emscripten_webgl_enable_extension(ctx_js,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx_js,"OES_float_blend");
// emscripten_webgl_enable_extension(ctx_js,"OES_frag_depth");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shader_texture_lod");
// emscripten_webgl_enable_extension(ctx_js,"OES_sRGB");
// emscripten_webgl_enable_extension(ctx_js,"OES_depth32");
// emscripten_webgl_enable_extension(ctx_js,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_js,"GL_disjoint_timer_query");
// emscripten_webgl_enable_extension(ctx_js,"EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx_js,"GL_disjoint_timer_query_webgl2");
// emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx_js,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_js,"KHR_parallel_shader_compile");
// emscripten_webgl_enable_extension(ctx_js,"EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
// emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_pixel_format_float");  //  required for float/alpha (must be 'EXT_pixel_format_float' not 'EGL_EXT_pixel_format_float')
emscripten_webgl_enable_extension(ctx_js,"EGL_KHR_gl_colorspace");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_multisample");
// emscripten_webgl_enable_extension(ctx_js,"ARB_robustness");
// emscripten_webgl_enable_extension(ctx_js,"ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx_js,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"EXT_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"OES_gpu_shader5");
// emscripten_webgl_enable_extension(ctx_js,"EXT_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"AMD_pinned_memory");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_blend_func_extended");
// emscripten_webgl_enable_extension(ctx_js,"ARB_buffer_storage");
// emscripten_webgl_enable_extension(ctx_js,"ARB_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"ARB_compatibility");
// emscripten_webgl_enable_extension(ctx_js,"ARB_compute_shader");
// emscripten_webgl_enable_extension(ctx_js,"ARB_enhanced_layouts");
// emscripten_webgl_enable_extension(ctx_js,"ARB_shadow");
// emscripten_webgl_enable_extension(ctx_js,"ARB_sync");
// emscripten_webgl_enable_extension(ctx_js,"ARB_tessellation_shader");
// emscripten_webgl_enable_extension(ctx_js,"ARB_texture_float");
// emscripten_webgl_enable_extension(ctx_js,"EXT_framebuffer_multisample");
// emscripten_webgl_enable_extension(ctx_js,"EXT_geometry_shader");
// emscripten_webgl_enable_extension(ctx_js,"MESA_shader_integer_functions");
// emscripten_webgl_enable_extension(ctx_js,"OES_geometry_shader");
// emscripten_webgl_enable_extension(ctx_js,"ARB_texture_stencil8");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_draw_buffers_blend");
// emscripten_webgl_enable_extension(ctx_js,"ARB_cull_distance");
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
// glViewport((GLint)0,(GLint)0,Size_js,Size_js);
glScissor((GLint)0,(GLint)0,Size_js,Size_js);
return;
}

void avgFrm(short int Fnum,int leng,float *ptr,float *aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for(int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];
}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];
}
}
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
}
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
}
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
}
aptr[200]=maxSum/32;
return;
}

extern "C" {

void nano(short int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,vid,(),{

"use strict";

var vv=document.getElementById("mv");
var sh4d=true;
var stp,Lstp;
const stpInc=0.016;
var setTim;
const timFrm=16.666;
var loopLoop;
var loopPart;
var mmvv;
var revv;
var $bb;
const $H=Module.HEAPF64.buffer;
var $S=parseInt(window.innerHeight,10);
var w$=parseInt(window.innerHeight,10);
var h$=parseInt(window.innerHeight,10);
var la=h$*h$*8;
var pointa=77*la;
var agav=new Float64Array($H,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var blank$=Math.max((((w$-h$)*1.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*1.0)/8.0),0);
let bCan=document.getElementById("bcanvas");
let gl=bCan.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
precision:'highp',
imageSmoothingEnabled:true,
imageSmoothingQuality:'medium',
preserveDrawingBuffer:false,
premultipliedAlpha:true,
desynchronized:false,
lowLatency:true,
powerPreference:'high-performance',
antialias:true,
willReadFrequently:false,
xrCompatible:false,
majorVersion:2,
minorVersion:0
});
gl.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
gl.getExtension('EXT_color_buffer_float');
// gl.getExtension('WEBGL_color_buffer_float');
// gl.getExtension('WEBGL_color_buffer_half_float');
// gl.getExtension('OES_texture_float_linear');
// gl.getExtension('OES_texture_half_float_linear');
gl.getExtension('GL_EXT_float_blend');
// gl.getExtension('EXT_frag_depth');
// gl.getExtension('EXT_shader_texture_lod');
// gl.getExtension('EXT_sRGB');
// gl.getExtension('EXT_blend_minmax');
// gl.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
// gl.getExtension('EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
// gl.getExtension('KHR_parallel_shader_compile');
// gl.getExtension('OES_draw_buffers_indexed');
// gl.getExtension('GL_OES_element_index_uint');
// gl.getExtension('OES_fbo_render_mipmap');
// gl.getExtension('OES_standard_derivatives');
// gl.getExtension('OES_vertex_array_object');
// /gl.getExtension('WEBGL_blend_equation_advanced_coherent');
// gl.getExtension('WEBGL_depth_texture');
// gl.getExtension('WEBGL_draw_buffers');
// gl.getExtension('WEBGL_provoking_vertex');
// gl.getExtension('EXT_framebuffer_sRGB');
// gl.getExtension('OES_depth32');
// gl.getExtension('OES_fixed_point');
gl.getExtension('OES_shader_multisample_interpolation');
// gl.getExtension('WEBGL_webcodecs_video_frame');
// gl.getExtension('OES_single_precision');
// gl.getExtension('EXT_texture_shadow_lod');
gl.getExtension('EGL_NV_memory_attachment');
gl.getExtension('EGL_NV_depth_nonlinear');
// gl.getExtension('EXT_framebuffer_sRGB');
gl.getExtension('EGL_EXT_pixel_format_float');  //  required for float/alpha (must be 'EXT_pixel_format_float' not 'EGL_EXT_pixel_format_float')
gl.getExtension('EGL_KHR_gl_colorspace');
// gl.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3');
// gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
// emscripten_webgl_enable_extension(ctx,"ARB_robust_buffer_access_behavior");
gl.getExtension('ARB_gl_spirv');
gl.getExtension('ARB_spirv_extensions');
gl.getExtension('ARB_invalidate_subdata');
gl.getExtension('ARB_texture_storage');
gl.getExtension('ARB_ES2_compatibility');
gl.getExtension('ARB_ES3_compatibility');
gl.getExtension('ARB_ES3_1_compatibility');
gl.getExtension('ARB_ES3_2_compatibility');
gl.getExtension('GL_EXT_gpu_shader5');
// emscripten_webgl_enable_extension(ctx,"OES_gpu_shader5");
// gl.getExtension('AMD_pinned_memory');
gl.getExtension('ARB_blend_func_extended');
// gl.getExtension('ARB_buffer_storage');
// gl.getExtension('GL_ARB_color_buffer_float');
// gl.getExtension('ARB_compatibility');
// gl.getExtension('ARB_compute_shader');
// gl.getExtension('ARB_enhanced_layouts');
// gl.getExtension('ARB_shadow');
// gl.getExtension('ARB_sync');
// gl.getExtension('ARB_tessellation_shader');
// gl.getExtension('ARB_texture_float');
// gl.getExtension('EXT_framebuffer_multisample');
// gl.getExtension('EXT_geometry_shader');
// gl.getExtension('MESA_shader_integer_functions');
// gl.getExtension('OES_geometry_shader');
// gl.getExtension('ARB_texture_stencil8');
gl.getExtension('GL_OES_shader_multisample_interpolation');
gl.getExtension('GL_OES_draw_buffers_indexed');
gl.getExtension('GL_ARB_draw_buffers_blend');
gl.getExtension('GL_ARB_cull_distance');
gl.getExtension('ARB_gpu_shader_fp64');
gl.getExtension('EXT_vertex_attrib_64bit');
gl.disable(gl.DITHER);
// gl.renderbufferStorage(gl.RENDERBUFFER,gl.RGBAF32,bCan.height,bCan.height);
// gl.drawingBufferColorMetadata={mode:'extended'};
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
// gl.disable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl.blendColor(1.0,1.0,1.0,1.0);
gl.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
gl.drawingBufferColorSpace='display-p3';
const g=new GPU({mode:'gpu',canvas:bcanvas,webGl:gl});
const g2=new GPU();
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(0.999-(((a)-(b))*((a)*(0.999/(0.999-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
let R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setOptimizeFloatMemory(true).setDynamicOutput(true).setOutput([sz]);
let t=g.createKernel(function(v){
  
var P=v[this.thread.y][this.thread.x];
var av$=Ave(P[0],P[1],P[2]);
var minuss=(av$-0.9)*(av$/(av$-0.9));
av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
  
}).setTactic("precision").setPrecision('single').setDynamicOutput(true).setPipeline(true).setOutput([$S,$S]);
let r=g.createKernel(function(f){
  
var p=f[this.thread.y][this.thread.x];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);

var rr,gg,bb;
var der=p[0];
var neerg=p[1];
var eulb=p[2];
var rdS=(der+0.75)/2.0);
var grS=(der+0.831)/2.0);
var blS=(neerg+0.75)/2.0);
var rdG=(neerg+0.686)/2.0);
var grG=(eulb+0.75)/2.0);
var blG=(eulb+0.215)/2.0);

if(der>0.333){
rr=Ave(der,0.75,rdS);
}else{
rr=Ave(der,0.831,rdG);
};

if(neerg>0.4){
gg=Ave(neerg,0.75,grS);
}else{
gg=Ave(neerg,0.868,grG);
};

if(eulb>0.5){
bb=Ave(eulb,0.75,blS);
}else{
bb=Ave(eulb,0.215,blG);
};
  
this.color(rr,gg,bb,aveg);
// this.color(p[0],p[1],p[2],aveg);
  
}).setTactic("precision").setDynamicOutput(true).setGraphical(true).setOutput([$S,$S]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*1.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*1.0)/8.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
};
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
};
var d=S();if(d)d();d=S();function S(){
vv=document.getElementById("mv");

w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);

var blank$=Math.max((((w$-h$)*1.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*1.0)/8.0),0);
$S=parseInt(window.innerHeight,10);
// t.setOutput([$S,$S]);
// r.setOutput([$S,$S]);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float64Array($H,pointa,300);  // has to var?
R.setOutput([sz]);
for(var i=0;i<65;i++){
j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
};
pointb=66*la;
var $B=new Float64Array($H,pointb,sz);  // has to var?
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
};
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;};
var locb=$Bu+1;
if(locb>64){locb=1;};
if($F==i){
eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
};};
$bb=R(vv);
$B.set($bb,0,sz);
pointb=66*la;  // has to revar?
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
Module.ccall("clr",null,["Number","Number","Number"],[agav[201],agav[101],agav[1]]);
setTimeout(function(){
M();
if(loopLoop==true){
if(revv==true){
reverseLoop();
}else{
forwardLoop();
};
};
},timFrm)}
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}

});

extern "C" {

void str(){
strt();
return;
}

void b3(){
egl();
vid();
return;
}

}
