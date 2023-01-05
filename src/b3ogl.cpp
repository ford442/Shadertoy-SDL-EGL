#include "../include/b3ogl.h"
EM_BOOL mouse_call(int eventType,const EmscriptenMouseEvent *e,void *userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
};
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
};
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}};
return 0;
};

void clrclr(GLclampf rlc,GLclampf alc){
glBlendColor(1.0,1.0,1.0,1.0-alc);
glClearColor(rlc,rlc,rlc,1.0-rlc);
};

void uni(float xx,float yy,GLfloat time,short int fram){
GLclampf mX,mY;
if(ms_l==true){
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=xxx*Size;
mY=yyy*Size;
clk_l=false;
};
GLclampf mm=S*xx;
GLclampf nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
};
glUniform1f(uni_tme,time);
glUniform1i(uni_frm,fram);
return;
};

void renderFrame(){
auto t3=t2;
auto t2=high_resolution_clock::now();
duration<float>time_spanb=duration_cast<duration<float>>(t2-t3);
TtimeDelta=time_spanb.count();
duration<float>time_spana=duration_cast<duration<float>>(t2-t1);
Ttime=time_spana.count();
ret=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
ret=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,1,mouse_call);
mouseX=x/S;
mouseY=(S-y)/S;
uni(mouseX,mouseY,Ttime,iFrame);
iFrame++;
glClear(GL_DEPTH_BUFFER_BIT);
 glClear(GL_COLOR_BUFFER_BIT);
//  glClear(GL_STENCIL_BUFFER_BIT);
// glFlush();
glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,indc);
// nanosleep(&req,&rem);
// glFinish();
return;
};

static const char8_t *read_file(const GLchar *filename){
char8_t *result=NULL;
long length=0;
FILE *file=fopen(filename,"r");
if(file){
short int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return nullptr;
};
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return nullptr;
};
result=static_cast<char8_t*>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
};
fclose(file);
return result;
};
return nullptr;
};

GLuint compile_shader(GLenum type,GLsizei nsources,const GLchar **dsources){
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
emscripten_cancel_main_loop();
const char *fileloc="/shader/shader1.toy";
EGLint v0=0,v3=3;
GLclampf gF=F;
GLclampf gF0=F0;
GLclampf gFm1=Fm1;
typedef struct{GLclampf XYZW[4];}Vertex;
const Vertex vertices[]={{gFm1,gFm1,gF,gF},{gF,gFm1,gF,gF},{gF,gF,gF,gF},{gFm1,gF,gF,gF},{gFm1,gFm1,gFm1,gF},{gF,gFm1,gFm1,gF},{gF,gF,gFm1,gF},{gFm1,gF,gF,gF}};
const GLchar common_shader_header_gles3[]=
"#version 300 es\n"
"#undef HW_PERFORMANCE\n"
"#define HW_PERFORMANCE 0\n"
"precision mediump float;precision mediump int;precision lowp sampler3D;precision highp sampler2D;\n";
const GLchar vertex_shader_body_gles3[]=
"\n layout(location=0)in vec4 iPosition;void main(){gl_Position=iPosition;}\n";
const GLchar fragment_shader_header_gles3[]=
"\n uniform vec3 iChannelResolution[4];uniform vec3 iResolution;uniform vec4 iMouse;uniform float iSampleRate;"
"\n uniform float iTime;uniform float iTimeDelta;uniform float iFrameRate;uniform vec4 iDate;uniform float iChannelTime[4];"
"\n uniform sampler2D iChannel0;uniform sampler2D iChannel1;uniform sampler2D iChannel2;uniform sampler2D iChannel3;"
"\n out vec4 fragColor;\n";
const GLchar fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor,gl_FragCoord.xy);fragColor.a=1.0;}\0";
const GLchar* common_shader_header=common_shader_header_gles3;
const GLchar* vertex_shader_body=vertex_shader_body_gles3;
const GLchar* fragment_shader_header=fragment_shader_header_gles3;
const GLchar* fragment_shader_footer=fragment_shader_footer_gles3;
GLuint EBO,VBO,shd_prg,smp_chn[4],smp_chn_res;
GLuint VCO,ECO,vtx,frag;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig=NULL;
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
EGLint config_size,major,minor,atb_pos;
iFrame=0;
clk_l=true;
double wi,hi;
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
// eglBindAPI(EGL_OPENGL_ES_API);
eglBindAPI(EGL_OPENGL_API);
const EGLint attribut_list[]={ 
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_DISPLAY_P3_EXT,
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_BT2020_PQ_EXT,
EGL_NONE};
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};
const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
//  EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
EGL_CONFORMANT,EGL_OPENGL_BIT,
// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
// EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_COLOR_FORMAT_HI,EGL_COLOR_RGBA_HI,
EGL_RED_SIZE,64,
EGL_GREEN_SIZE,64,
EGL_BLUE_SIZE,64,
EGL_ALPHA_SIZE,64,
EGL_DEPTH_SIZE,64,
EGL_STENCIL_SIZE,64,
EGL_BUFFER_SIZE,64,
EGL_SAMPLE_BUFFERS,256,
EGL_SAMPLES,128,
EGL_NONE
};
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_FALSE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_FALSE;
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
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
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
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx,"GL_ARB_ES3_2_compatibility");
// glDisable(GL_STENCIL_TEST);
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
glFrontFace(GL_CW);
glDepthFunc(GL_LESS);
glClearDepth(D);
 //  swap alpha to use one_minus_alpha for 'source'
glEnable(GL_BLEND);
glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_ONE_MINUS_DST_COLOR,GL_SRC_ALPHA);
glBlendEquationSeparate(GL_MIN,GL_FUNC_ADD);
glBlendColor((GLclampf)1.0,(GLclampf)1.0,(GLclampf)1.0,(GLclampf)1.0);
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,(GLsizei)Size,(GLsizei)Size);
// glDisable(GL_DITHER);
glViewport((GLint)0,(GLint)0,GLsizei(Size),GLsizei(Size));
glClearColor((GLclampf)1.0,(GLclampf)1.0,(GLclampf)1.0,(GLclampf)1.0);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
nanosleep(&req,&rem);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
nanosleep(&req,&rem);
static const GLchar* default_fragment_shader=(GLchar*)read_file(fileloc);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
nanosleep(&req,&rem);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
nanosleep(&req,&rem);
shd_prg=glCreateProgram();
nanosleep(&req,&rem);
glAttachShader(shd_prg,frag);
nanosleep(&req,&rem);
glAttachShader(shd_prg,vtx);
nanosleep(&req,&rem);
atb_pos=0;
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
nanosleep(&req,&rem);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays(1,&VCO);
glBindVertexArray(VCO);
atb_pos=glGetAttribLocation(shd_prg,"iPosition");
glEnableVertexAttribArray(atb_pos);
glVertexAttribPointer(atb_pos,4,GL_FLOAT,GL_TRUE,0,(GLvoid*)0);
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
glUniform1f(uni_srate,44100.0);
glUniform3f(uni_res,S,S,1.0);
glUniform3f(smp_chn_res,S,S,1.0);
auto t1=steady_clock::now();
nanosleep(&req,&rem);
emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
};
extern "C" {
void str(){strt();return;};
void clr(GLclampf cllr,GLclampf alp){clrclr(cllr,alp);return;};
};
