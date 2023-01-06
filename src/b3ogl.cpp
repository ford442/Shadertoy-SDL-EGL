#include "../include/b3ogl.hpp"

EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 1;
}

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avrg){
glBlendColor(y1y,y1y,y1y,alc);
glClearColor(rlc,rlc,rlc,avrg);
return;
}

void uni(float xx,float yy,GLfloat time,short int fram){
GLclampf mX,mY;
if(ms_l==true){
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clk_l=false;
}
GLclampf mm=S*xx;
GLclampf nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,time);
glUniform1i(uni_frm,fram);
return;
}

void renderFrame(){
auto t3=t2;
auto t2=std::chrono::high_resolution_clock::now();
std::chrono::duration<float>time_spanb=duration_cast<std::chrono::duration<float>>(t2-t3);
TtimeDelta=time_spanb.count();
std::chrono::duration<float>time_spana=duration_cast<std::chrono::duration<float>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)1,mouse_call);
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
iFrame++;
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
// glFlush();
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
// glFinish();
// nanosleep(&req,&rem);
return;
}

static const char8_t * read_file(const GLchar * filename){
char8_t * result=NULL;
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
result=static_cast<char8_t *>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
return result;
}
return nullptr;
}

GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar ** dsources){
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
// emscripten_cancel_main_loop();
eglconfig=NULL;
iFrame=0;
clk_l=true;
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
// eglBindAPI(EGL_OPENGL_ES_API);
eglBindAPI(EGL_OPENGL_API);
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_TRUE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&v3,&v0);
eglChooseConfig(display,attribute_list,&eglconfig,(EGLint)1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"OES_depth32");
emscripten_webgl_enable_extension(ctx,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"OES_single_precision");
emscripten_webgl_enable_extension(ctx,"EXT_float_blend");
emscripten_webgl_enable_extension(ctx,"EXT_frag_depth");
emscripten_webgl_enable_extension(ctx,"EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB");
emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx,"EXT_clip_cull_distance");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx,"GL_EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx,"GL_NV_memory_attachment");
emscripten_webgl_enable_extension(ctx,"GL_ARB_multisample");
emscripten_webgl_enable_extension(ctx,"NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robust_buffer_access_behavior");
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"GL_ARB_spirv_extensions");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx,"EXT_gpu_shader4");
emscripten_webgl_enable_extension(ctx,"EXT_gpu_shader5");
// glDisable(GL_STENCIL_TEST);

glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearDepth(D);
 //  swap alpha to use one_minus_alpha for 'source'
glEnable(GL_BLEND);
glBlendFuncSeparate(GL_SRC_COLOR,GL_SRC_ALPHA,GL_DST_COLOR,GL_SRC_ALPHA);
glBlendEquationSeparate(GL_MIN,GL_MAX);
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,(GLsizei)Size,(GLsizei)Size);
// glDisable(GL_DITHER);
glViewport((GLint)0,(GLint)0,GLsizei(Size),GLsizei(Size));
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
static const GLchar * default_fragment_shader=(GLchar *)read_file(fileloc);
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
glUseProgram(shd_prg);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,(GLint)4,GL_FLOAT,GL_TRUE,(GLsizei)0,(GLvoid *)0);
// smp_chn_res=glGetUniformLocation(shd_prg,"iChannelResolution");
// smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
// smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
// smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
// smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
uni_tme=glGetUniformLocation(shd_prg,"iTime");
uni_frm=glGetUniformLocation(shd_prg,"iFrame");
uni_res=glGetUniformLocation(shd_prg,"iResolution");
uni_mse=glGetUniformLocation(shd_prg,"iMouse");
uni_srate=glGetUniformLocation(shd_prg,"iSampleRate");
glUniform1f(uni_srate,(GLfloat)44100.0);
glUniform3f(uni_res,S,S,g1g);
glUniform3f(smp_chn_res,S,S,g1g);
 // glFinish();
auto t1=std::chrono::high_resolution_clock::now();
// nanosleep(&req,&rem);
// emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
}

extern "C" {

void str(){
strt();
return;
}

void frm(){
renderFrame();
return;
}

void clr(GLclampf cllr,GLclampf alp,GLclampf avrg){
clrclr(cllr,alp,avrg);
return;
}

}
