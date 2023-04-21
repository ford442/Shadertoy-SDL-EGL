#include "../../include/shader/shader_speed.hpp"

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

static inline void uni(GLfloat xx,GLfloat yy,GLfloat Tm,GLint fram,GLfloat delt){
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
iFps=60.0/delt;
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const GLfloat xxx=xx;
const GLfloat yyy=yy;
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
glUniform1f(uni_tme,Tm);
glUniform1f(uni_tme_dlt,delt);
glUniform1f(uni_fps,iFps);
glUniform1i(uni_frm,fram);
return;
}

void(*un)(GLfloat,GLfloat,GLfloat,GLint,GLfloat){&uni};

static inline void Rend(){
t3=t2;
t2=std::chrono::steady_clock::now();
std::chrono::duration<float, std::chrono::seconds::period> time_spanb=std::chrono::duration<float,std::chrono::seconds::period>(t2-t3);
Tdlt=time_spanb.count();
std::chrono::duration<double, std::chrono::seconds::period>time_spana=std::chrono::duration<double,std::chrono::seconds::period>(t2-t1);
Ttime=time_spana.count();
mouseX=x/S;
mouseY=(S-y)/S;
un(mouseX,mouseY,Ttime,iFrame,Tdlt);
iFrame++;
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glClear(GL_STENCIL_BUFFER_BIT);
// glFlush();
glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
// glFinish();
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
const GLuint shader=glCreateShader(type);
glShaderSource(shader,nsrc,src,srclens);
glCompileShader(shader);
return shader;
}

GLuint(* cs)(GLenum,GLsizei,const GLchar **){&cmpl_shd};

static inline void strt(){
tie(F,Fm1,F0);
tie(gF,gFm1,gF0);
tie(D,Dm1,D0);
tie(gD,gDm1,gD0);
tie(iFrame,iFps);
tie(mouseY,mouseX,x,y);
tie(gu0,gu1,gu2,gu3);
tie(gu4,gu5,gu6,gu7);
tie(gu8,gu9);
tie(Tdlt,mouseY,mouseX);
tie(hi,wi,S);
tie(mX,mY,mm,nn);
tie(s4,i);
tie(t1,t2,t3);
tie(EBO,VBO);
tie(VCO,ECO);
tie(config_size,major,minor);
tie(display,surface,ctxegl,eglconfig);
tie(attr,surface,ctx);
tie(uni_mse,uni_srate,uni_res);
tie(uni_tme,uni_frm,uni_fps);
tie(smp_chn_res,smp_chn,uni_tme_dlt);
tie(cm_hdr_src,vrt_bdy_src,frg_hdr_src,frg_ftr_src);
tie(vrt,indc);
eglconfig=NULL;
iFrame=0;
clk_l=true;
GLchar * frag_body=rd_fl(Fnm);
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
eglBindAPI(EGL_OPENGL_API);
//   eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,att_lst,&eglconfig,(EGLint)1,&config_size);
ctxegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
eglMakeCurrent(display,surface,surface,ctxegl);
emscripten_webgl_make_context_current(ctx);
glUseProgram(0);
emscripten_get_element_css_size("canvas",&wi,&hi);
Size=static_cast<int_fast32_t>(hi);
// S=static_cast<GLfloat>(wi);
S=Size;
mX=0.5*S;
mY=0.5*S;
emscripten_webgl_enable_extension(ctx,"ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx,"ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx,"EXT_polygon_offset_clamp");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counters");
emscripten_webgl_enable_extension(ctx,"ARB_shader_atomic_counter_ops");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample_resolve");
emscripten_webgl_enable_extension(ctx,"EGL_NV_quadruple_buffer");
emscripten_webgl_enable_extension(ctx,"EGL_NV_coverage_sample");
emscripten_webgl_enable_extension(ctx,"EGL_IMG_context_priority");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_sample_variables");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx,"EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx,"EGL_NV_context_priority_realtime");
emscripten_webgl_enable_extension(ctx,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx,"EGL_HI_colorformats");
// emscripten_webgl_enable_extension(ctx,"EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_KHR_create_context");
emscripten_webgl_enable_extension(ctx,"GL_ARB_robustness");
emscripten_webgl_enable_extension(ctx,"EXT_create_context_robustness");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb_linear");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3_linear");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx,"ARB_gpu_shader_fp64");
emscripten_webgl_enable_extension(ctx,"EXT_vertex_attrib_64bit");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB_write_control");
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
glClearDepth(D);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
// glEnable(GL_DEPTH_TEST);
// glDepthFunc(GL_LESS);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
glDisable(GL_DITHER);
glFrontFace(GL_CW);
glEnable(GL_CULL_FACE);
// glDisable(GL_BLEND);
// glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_COLOR,GL_ONE_MINUS_SRC_ALPHA);
// glBlendEquationSeparate(GL_MIN,GL_MAX);
glClearColor((GLclampf)gF0,(GLclampf)gF0,(GLclampf)gF0,(GLclampf)gF);
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vrt),vrt,GL_STATIC_DRAW);
nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
nanosleep(&req,&rem);
src[0]=cm_hdr;
src[1]=vrt_bdy;
const GLuint vtx=cs(GL_VERTEX_SHADER,2,src);
src[0]=cm_hdr;
src[1]=frg_hdr;
// src[2]=frg_aa;
src[2]=frag_body;
src[3]=frg_ftr;
const GLuint frag=cs(GL_FRAGMENT_SHADER,4,src);
nanosleep(&req,&rem);
const GLuint shd_prg=glCreateProgram();
tie(shd_prg,frag,vtx);
glAttachShader(shd_prg,frag);
glAttachShader(shd_prg,vtx);
glBindAttribLocation(shd_prg,0,"iPosition");
glLinkProgram(shd_prg);
glUseProgram(shd_prg);
nanosleep(&req,&rem);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glGenVertexArrays((GLsizei)1,&VCO);
glBindVertexArray(VCO);
const GLuint atb_pos=glGetAttribLocation(shd_prg,"iPosition");
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
glViewport((GLint)0,(GLint)0,Size,Size);  //  viewport/scissor after UsePrg runs at full resolution
glEnable(GL_SCISSOR_TEST);
glScissor((GLint)0,(GLint)0,Size,Size);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_FASTEST);
t1=std::chrono::steady_clock::now();
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
