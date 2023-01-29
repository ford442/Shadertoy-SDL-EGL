#include "../include/b3ogl.hpp"

EM_BOOL mouse_call_click(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
};
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
};};
return (EM_BOOL)1;
};

static EM_BOOL mouse_call_move(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
};};
return (EM_BOOL)1;
};

void egl(){
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_TRUE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_FALSE;
attr_js.preserveDrawingBuffer=EM_TRUE;
attr_js.enableExtensionsByDefault=EM_TRUE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
eglBindAPI(EGL_OPENGL_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
emscripten_webgl_make_context_current(ctx_js);
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=(int)hi_js;
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_js,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_element_index_uint");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_depth32");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_fixed_point");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_single_precision");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_float_blend");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_frag_depth");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_sRGB");
emscripten_webgl_enable_extension(ctx_js,"GL_OES_depth32");
// emscripten_webgl_enable_extension(ctx_js,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_js,"GL_EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_js,"GL_EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx_js,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_js,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx_js,"EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_multisample");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_gpu_shader4");
emscripten_webgl_enable_extension(ctx_js,"GL_EXT_gpu_shader5");
  glDisable(GL_DITHER);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
glViewport((GLint)0,(GLint)0,GLsizei(Size_js),GLsizei(Size_js));
glScissor((GLint)0,(GLint)0,(GLsizei)Size_js,(GLsizei)Size_js);


};

void avgFrm(int Fnum,int leng,float * ptr,float * aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];};
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];};
};
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
};
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
};
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
};
aptr[200]=maxSum/32;
};

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avrg=(((avr+(y1y-rlc))/2.0)+alc);
drk=y1y-(avr-0.5);
brt=((y1y-rlc)-(alc-0.5));
glBlendColor(avrg,avrg,avrg,y1y);
glClearColor(drk,drk,drk,brt);
};

void uni(GLfloat xx,GLfloat yy,GLfloat time,GLint fram,GLfloat delt){
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
iFps=60.0/delt;
if(ms_l==true){
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_move);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,mouse_call_click);
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
glUniform1f(uni_tme,time);
glUniform1f(uni_tme_dlt,delt);
glUniform1f(uni_fps,iFps);
glUniform1i(uni_frm,fram);
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
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
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
eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,(EGLint)1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
// glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
emscripten_webgl_make_context_current(ctx);
  
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
  
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
// emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
// emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx,"GL_OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"GL_OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx,"GL_OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"GL_OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"GL_OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"GL_OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"GL_OES_depth32");
emscripten_webgl_enable_extension(ctx,"GL_OES_fixed_point");
emscripten_webgl_enable_extension(ctx,"GL_OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"GL_OES_single_precision");
emscripten_webgl_enable_extension(ctx,"GL_OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"GL_EXT_float_blend");
emscripten_webgl_enable_extension(ctx,"GL_EXT_frag_depth");
emscripten_webgl_enable_extension(ctx,"GL_EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx,"GL_EXT_sRGB");
emscripten_webgl_enable_extension(ctx,"GL_OES_depth32");
// emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx,"GL_EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx,"GL_EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx,"GL_EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx,"GL_EXT_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx,"EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx,"EGL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx,"GL_ARB_multisample");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx,"GL_ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"GL_ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx,"ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx,"ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_EXT_gpu_shader4");
emscripten_webgl_enable_extension(ctx,"GL_EXT_gpu_shader5");
  
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearDepth(D);
glEnable(GL_BLEND);
glBlendFuncSeparate(GL_SRC_COLOR,GL_ONE_MINUS_DST_COLOR,GL_DST_COLOR,GL_SRC_ALPHA);
glBlendEquationSeparate(GL_FUNC_SUBTRACT,GL_MIN);
glDisable(GL_DITHER);

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
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_tme_dlt=glGetUniformLocation(shd_prg,"iTimeDelta");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_fps=glGetUniformLocation(shd_prg,"iFrameRate");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
uni_srate=glGetUniformLocation(shd_prg,"iSampleRate");
  
   glViewport((GLint)0,(GLint)0,GLsizei(Size),GLsizei(Size));
   glScissor((GLint)0,(GLint)0,(GLsizei)Size,(GLsizei)Size);
   glUseProgram(shd_prg);
  

// smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
// smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
// smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
// smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
// smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");

  
  
glUniform1f(uni_srate,(GLfloat)44100.0);
glUniform3f(uni_res,S,S,g1g);
glUniform3f(smp_chn_res,S,S,g1g);
  
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
  
  // glDisable(GL_STENCIL_TEST);
// glEnable(GL_SCISSOR_TEST);
auto t1=std::chrono::steady_clock::now();
};

extern "C" {

void str(){
strt();
};

void nano(int Fnum,int leng,float * ptr,float * aptr){
avgFrm(Fnum,leng,ptr,aptr);
};

void frm(){
renderFrame();
};
 
void b3_egl(){
egl();
};

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
clrclr(cllr,alp,avr);
};

};
