#include "../../include/shader/shader.hpp"

EM_BOOL ms_clk(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

static EM_BOOL ms_mv(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return (EM_BOOL)1;
}

void uni(GLfloat xx,GLfloat yy,GLfloat Tm,GLint fram,GLfloat delt){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
iFps=60.0/delt;
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const float xxx=xx;
const float yyy=yy;
mX=1.0-(xxx*sSize);
mY=1.0-(yyy*sSize);
clk_l=false;
}
mm=S*xx;
nn=S*yy;
glUniform4f(uni_mse,mm,nn,mX,mY);
}else{
clk_l=true;
}
glUniform1f(uni_tme,Tm);
glUniform1f(uni_tme_dlt,delt);
glUniform1f(uni_fps,iFps);
glUniform1i(uni_frm,fram);
return;
}

void Rend(){
auto t3=t2;
auto t2=std::chrono::steady_clock::now();
std::chrono::duration<float>time_spanb=duration_cast<std::chrono::duration<float>>(t2-t3);
Tdlt=time_spanb.count();
std::chrono::duration<float>time_spana=duration_cast<std::chrono::duration<float>>(t2-t1);
Ttime=time_spana.count();
mouseX=x/S;
mouseY=(S-y)/S;
void(*un)(GLfloat,GLfloat,GLfloat,GLint,GLfloat);
un=&uni;
un(mouseX,mouseY,Ttime,iFrame,Tdlt);
iFrame++;
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
glDisable(GL_BLEND);
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
return;
}

GLchar * rd_fl(const char * Fnm){
char8_t * result=NULL;
GLchar * results=NULL;
long int length=0;
FILE * file=fopen(Fnm,"r");
if(file){
int stat=fseek(file,(int)0,SEEK_END);
if(stat!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
stat=fseek(file,(int)0,SEEK_SET);
if(stat!=0){
fclose(file);
return nullptr;
}
result=static_cast<char8_t *>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
results=reinterpret_cast<GLchar *>(result);
return results;
}
return nullptr;
}

GLuint cmpl_shd(GLenum type,GLsizei nsrc,const GLchar ** src){
GLsizei srclens[nsrc];
for(i=0;i<nsrc;i++){
srclens[i]=static_cast<GLsizei>(strlen(src[i]));
}
shader=glCreateShader(type);
glShaderSource(shader,nsrc,src,srclens);
glCompileShader(shader);
return shader;
}

void strt(){
eglconfig=NULL;
iFrame=0;
clk_l=true;
GLchar * frag_body=rd_fl(Fnm);
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
// eglBindAPI(EGL_OPENGL_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,att_lst,&eglconfig,(EGLint)1,&config_size);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglMakeCurrent(display,surface,surface,ctxegl);
emscripten_webgl_make_context_current(ctx);
eglBindAPI(EGL_OPENGL_ES_API);
glUseProgram(0);
emscripten_get_element_css_size("canvas",&wi,&hi);
sSize=static_cast<GLint>(hi);
S=static_cast<GLfloat>(wi);
mX=0.5;
mY=0.5;
emscripten_webgl_enable_extension(ctx,"IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_float");
// emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
// emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
// emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
// emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"HI_colorformats");
// emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx,"EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EXT_create_context_robustness");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_scrgb");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_bt2020_linear");
// emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
// emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
// emscripten_webgl_enable_extension(ctx,"ARB_invalidate_subdata");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_storage");
// emscripten_webgl_enable_extension(ctx,"ARB_ES2_compatibility");
// emscripten_webgl_enable_extension(ctx,"ARB_ES3_compatibility ");
// emscripten_webgl_enable_extension(ctx,"ARB_ES3_1_compatibility");
// emscripten_webgl_enable_extension(ctx,"ARB_ES3_2_compatibility");
// emscripten_webgl_enable_extension(ctx,"EXT_gpu_shader4");
// emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader4");
// emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader5");
// emscripten_webgl_enable_extension(ctx,"ARB_blend_func_extended");
// emscripten_webgl_enable_extension(ctx,"ARB_color_buffer_float");
// emscripten_webgl_enable_extension(ctx,"ARB_compatibility");
// emscripten_webgl_enable_extension(ctx,"ARB_compute_shader");
// emscripten_webgl_enable_extension(ctx,"ARB_enhanced_layouts");
// emscripten_webgl_enable_extension(ctx,"ARB_tessellation_shader");
// emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_multisample");
// emscripten_webgl_enable_extension(ctx,"EXT_geometry_shader");
// emscripten_webgl_enable_extension(ctx,"MESA_shader_integer_functions");
// emscripten_webgl_enable_extension(ctx,"OES_geometry_shader");
// emscripten_webgl_enable_extension(ctx,"ARB_geometry_shader");
// emscripten_webgl_enable_extension(ctx,"ARB_texture_stencil8");
// emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
// emscripten_webgl_enable_extension(ctx,"GL_ARB_draw_buffers_blend");
// emscripten_webgl_enable_extension(ctx,"ARB_cull_distance");
emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB_write_control");
// glEnable(GL_LIGHTING);  //  LEGACY_GL
// glEnable(GL_FOG);  //  LEGACY_GL
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glClearDepth(D);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
// glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // invalid capa
// glEnable(GL_FOG);  // invalid capa
// glEnable(GL_POLYGON_OFFSET_POINT); // invalid capa
glEnable(GL_POLYGON_OFFSET_FILL);  // works
glPolygonOffset((GLfloat)0.0,(GLfloat)-0.0);
//  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //  undefined symbol
// glEnable(GL_POLYGON_SMOOTH); // invalid capa
//    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST); // invalid target
// glEnable(GL_PROGRAM_POINT_SIZE);  //  invalid capability
// glEnable(GL_POLYGON_OFFSET_LINE); // invalid capa
// glEnable(GL_LINE_SMOOTH); // invalid capa
//    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST); // invalid target
glDisable(GL_DITHER);
glFrontFace(GL_CW);
glEnable(GL_CULL_FACE);
//  glEnable(GL_FRAMEBUFFER_SRGB); //  invalid capa
// glDisable(GL_BLEND);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
glClearColor((GLclampf)gF0,(GLclampf)gF0,(GLclampf)gF0,(GLclampf)gF);
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_DYNAMIC_DRAW);
nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_DYNAMIC_DRAW);
nanosleep(&req,&rem);
src[0]=cm_hdr;
src[1]=vrt_bdy;
GLuint(* cs)(GLenum,GLsizei,const GLchar **){&cmpl_shd};
const GLuint vtx=cs(GL_VERTEX_SHADER,2,src);
src[0]=cm_hdr;
src[1]=frg_hdr;
// src[2]=frg_aa;
src[2]=frag_body;
src[3]=frg_ftr;
const GLuint frag=cs(GL_FRAGMENT_SHADER,4,src);
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
smp_chn[0]=glGetUniformLocation(shd_prg,"iChannel0");
smp_chn[1]=glGetUniformLocation(shd_prg,"iChannel1");
smp_chn[2]=glGetUniformLocation(shd_prg,"iChannel2");
smp_chn[3]=glGetUniformLocation(shd_prg,"iChannel3");
glUniform1f(uni_srate,44100.0f);
glUniform3f(uni_res,S,S,gF);
glUniform3f(smp_chn_res,S,S,gF);
glViewport((GLint)0,(GLint)0,sSize,sSize);  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,sSize,sSize);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
auto t1=std::chrono::steady_clock::now();
emscripten_set_main_loop((void(*)())Rend,0,0);
return;
}

void(*st)(){&strt};

extern "C" {

void str(){
st();
return;
}

}
