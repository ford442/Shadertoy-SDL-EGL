#include "../include/b3ogl.hpp"

void egla(){ 
eglconfig_fjs=NULL;
// emscripten_get_element_css_size("canvas",&wi_fjs,&hi_fjs);
// Size_fjs=(GLsizei)hi_fjs;
emscripten_webgl_init_context_attributes(&attr_fjs);
attr_fjs.alpha=EM_TRUE;
attr_fjs.stencil=EM_TRUE;
attr_fjs.depth=EM_TRUE;
attr_fjs.antialias=EM_TRUE;
attr_fjs.premultipliedAlpha=EM_FALSE;
attr_fjs.preserveDrawingBuffer=EM_TRUE;
attr_fjs.enableExtensionsByDefault=EM_TRUE;
attr_fjs.renderViaOffscreenBackBuffer=EM_FALSE;
attr_fjs.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_fjs.failIfMajorPerformanceCaveat=EM_FALSE;
attr_fjs.majorVersion=2;
attr_fjs.minorVersion=0;
ctx_fjs=emscripten_webgl_create_context("#acanvas",&attr_fjs);
// eglBindAPI(EGL_OPENGL_API);
eglBindAPI(EGL_OPENGL_ES_API);
display_fjs=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_fjs,&major_fjs,&minor_fjs);
eglChooseConfig(display_fjs,attribute_list_fjs,&eglconfig_fjs,(EGLint)1,&config_size_fjs);
contextegl_fjs=eglCreateContext(display_fjs,eglconfig_fjs,EGL_NO_CONTEXT,anEglCtxAttribs2_fjs);
surface_fjs=eglCreateWindowSurface(display_fjs,eglconfig_fjs,(NativeWindowType)0,attribut_list_fjs);
eglMakeCurrent(display_fjs,surface_fjs,surface_fjs,contextegl_fjs);
emscripten_webgl_make_context_current(ctx_fjs);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx_fjs,"OES_texture_float_linear");
// emscripten_webgl_enable_extension(ctx_fjs,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx_fjs,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx_fjs,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx_fjs,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx_fjs,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx_fjs,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx_fjs,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_single_precision");
// emscripten_webgl_enable_extension(ctx_fjs,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx_fjs,"OES_float_blend");
emscripten_webgl_enable_extension(ctx_fjs,"OES_frag_depth");
emscripten_webgl_enable_extension(ctx_fjs,"OES_shader_texture_lod");
emscripten_webgl_enable_extension(ctx_fjs,"OES_sRGB");
emscripten_webgl_enable_extension(ctx_fjs,"OES_depth32");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_disjoint_timer_query");
//  emscripten_webgl_enable_extension(ctx_fjs,"EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx_fjs,"GL_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx_fjs,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_fjs,"KHR_parallel_shader_compile");
// emscripten_webgl_enable_extension(ctx_fjs,"EXT_texture_shadow_lod");
// emscripten_webgl_enable_extension(ctx_fjs,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx_fjs,"EGL_NV_context_priority_realtime");
// emscripten_webgl_enable_extension(ctx_fjs,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_fjs,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_fjs,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx_fjs,"ARB_multisample");
emscripten_webgl_enable_extension(ctx_fjs,"ARB_robustness");
emscripten_webgl_enable_extension(ctx_fjs,"ARB_robust_buffer_access_behavior");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_gl_spirv");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_spirv_extensions");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_invalidate_subdata");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_texture_storage");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES2_compatibility");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES3_compatibility");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES3_1_compatibility");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES3_2_compatibility");
//emscripten_webgl_enable_extension(ctx_fjs,"EXT_gpu_shader5");
 // emscripten_webgl_enable_extension(ctx_fjs,"OES_gpu_shader5");
// glViewport((GLint)0,(GLint)0,(GLsizei)Size_fjs,(GLsizei)Size_fjs);
// glScissor((GLint)0,(GLint)0,(GLsizei)Size_fjs,(GLsizei)Size_fjs);
glDisable(GL_DITHER);
// glEnable(GL_SCISSOR_TEST);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
return; 
}

EM_BOOL mouse_call_click(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
};
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}};
return (EM_BOOL)1;
};

static EM_BOOL mouse_call_move(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}};
return (EM_BOOL)1;
};

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avrg=(((avr+(y1y-rlc))/2.0)+alc);
drk=y1y-(avr-0.5);
brt=((y1y-rlc)-(alc-0.5));
glBlendColor(avrg,avrg,avrg,y1y);
glClearColor(drk,drk,drk,brt);
return;
};

void resizeShader(GLsizei szi){
glViewport((GLint)0,(GLint)0,szi,szi);
glScissor((GLint)0,(GLint)0,szi,szi);
// glUniform3f(uni_res,(double)szi,(double)szi,(GLfloat)1.0);
// glUniform3f(smp_chn_res,(double)szi,(double)szi,(GLfloat)1.0);
return;
};

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
};
mm=S*xx;
nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
};
glUniform1f(uni_tme,stime);
glUniform1f(uni_tme_dlt,delt);
glUniform1f(uni_fps,iFps);
glUniform1i(uni_frm,fram);
return;
};

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
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
// glFinish();
// nanosleep(&req,&rem);
return;
};

char32_t * read_file(const GLchar * filename){
char32_t * result=NULL;
long length=0;
FILE * file=fopen(filename,"r");
if(file){
short int status=fseek(file,(long int)0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
};
length=ftell(file);
status=fseek(file,(long int)0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
};
result=static_cast<char32_t *>(malloc((length+1)*sizeof(char32_t)));
if(result){
size_t actual_length=fread(result,sizeof(char32_t),length,file);
result[actual_length++]={'\0'};
};
fclose(file);
return result;
};
return nullptr;
};

GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar ** dsources){
GLsizei srclens[nsources];
for(i=0;i<nsources;i++){
srclens[i]=(GLsizei)strlen(sources[i]);
};
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
};

void strt(){
eglconfig=NULL;
iFrame=0;
clk_l=true;
retSa=emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(GLsizei)hi;
S=(GLfloat)hi;
mX=0.5*S;
mY=0.5*S;
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_TRUE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
// eglBindAPI(EGL_OPENGL_API);
eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,(EGLint)1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
// emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx,"OES_single_precision");
// emscripten_webgl_enable_extension(ctx,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"OES_float_blend");
emscripten_webgl_enable_extension(ctx,"OES_frag_depth");
emscripten_webgl_enable_extension(ctx,"OES_shader_texture_lod");
//  emscripten_webgl_enable_extension(ctx,"OES_sRGB");
emscripten_webgl_enable_extension(ctx,"OES_depth32");
// emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx,"GL_disjoint_timer_query");
// emscripten_webgl_enable_extension(ctx,"EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx,"GL_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx,"GL_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx,"EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx,"ARB_multisample");
emscripten_webgl_enable_extension(ctx,"ARB_robustness");
emscripten_webgl_enable_extension(ctx,"ARB_robust_buffer_access_behavior");
// emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
// emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
// emscripten_webgl_enable_extension(ctx,"ARB_invalidate_subdata");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_storage ");
// emscripten_webgl_enable_extension(ctx,"ARB_ES2_compatibility");
// emscripten_webgl_enable_extension(ctx,"ARB_ES3_compatibility ");
// emscripten_webgl_enable_extension(ctx,"ARB_ES3_1_compatibility");
// emscripten_webgl_enable_extension(ctx,"ARB_ES3_2_compatibility");
// emscripten_webgl_enable_extension(ctx,"EXT_gpu_shader5");
// emscripten_webgl_enable_extension(ctx,"OES_gpu_shader5");
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STREAM_DRAW);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STREAM_DRAW);
GLchar * default_fragment_shader=(GLchar *)read_file(fileloc);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,(GLsizei)2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,(GLsizei)4,sources);
shd_prg=glCreateProgram();
glAttachShader(shd_prg,frag);
glAttachShader(shd_prg,vtx);
atb_pos=0;
glBindAttribLocation(shd_prg,(GLuint)0,"iPosition");
glLinkProgram(shd_prg);
glGenVertexArrays((GLsizei)1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,(GLint)4,GL_FLOAT,GL_TRUE,(GLsizei)0,(GLvoid *)0);
  // glDisable(GL_STENCIL_TEST);
glEnable(GL_SCISSOR_TEST);
glDisable(GL_DITHER);
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearDepth(D);
glEnable(GL_BLEND);
glBlendFuncSeparate(GL_SRC_COLOR,GL_ONE_MINUS_DST_COLOR,GL_DST_COLOR,GL_SRC_ALPHA);
glBlendEquationSeparate(GL_FUNC_SUBTRACT,GL_MIN);
glUseProgram(shd_prg);
glViewport((GLint)0,(GLint)0,(GLsizei)Size,(GLsizei)Size);  //  viewport/scissor after UsePrg runs at full resolution
glScissor((GLint)0,(GLint)0,(GLsizei)Size,(GLsizei)Size);
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
glUniform1f(uni_srate,(GLfloat)44100.0);
glUniform3f(uni_res,S,S,(GLfloat)1.0);
glUniform3f(smp_chn_res,S,S,(GLfloat)1.0);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
auto t1=std::chrono::steady_clock::now();
return;
};

extern "C" {

void str(){
strt();
return;
};

void frm(){
renderFrame();
return;
};
  
void szz(GLsizei szi){
resizeShader(szi);
return;
};

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
clrclr(cllr,alp,avr);
return;
};

void fire_egl(){
egla();
return;
};

};
