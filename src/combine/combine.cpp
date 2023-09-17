#include "../../include/combine/combine.hpp"

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
// glClear(GL_COLOR_BUFFER_BIT);
// glClear(GL_DEPTH_BUFFER_BIT);
// glClear(GL_STENCIL_BUFFER_BIT);
// glDrawElements(GL_TRIANGLES,(GLsizei)36,GL_UNSIGNED_BYTE,indc);
// glFlush();
// nanosleep(&req,&rem);
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
eglconfig=NULL;
iFrame=0;
clk_l=true;
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
eglBindAPI(EGL_OPENGL_ES_API);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,(EGLint)1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,attribut_list);
eglBindAPI(EGL_OPENGL_API);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
emscripten_get_element_css_size("canvas",&wi,&hi);
sSize=static_cast<int>(hi);
S=static_cast<GLfloat>(sSize);
mX=0.5*S;
mY=0.5*S;
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx, "EGL_KHR_create_context");
emscripten_webgl_enable_extension(ctx, "EGL_EXT_pixel_format_float");  //  required for float/alpha   -- EGL --
emscripten_webgl_enable_extension(ctx, "EGL_IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx, "EGL_NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx, "EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx, "EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx, "EGL_EXT_create_context_robustness");
emscripten_webgl_enable_extension(ctx, "EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_display_p3");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_bt2020_pq");
// emscripten_webgl_enable_extension(ctx, "EGL_EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(ctx, "EXT_texture_filter_anisotropic");
emscripten_webgl_enable_extension(ctx, "EXT_float_blend");
emscripten_webgl_enable_extension(ctx, "EXT_blend_func_separate");
emscripten_webgl_enable_extension(ctx, "EXT_blend_func_extended");
emscripten_webgl_enable_extension(ctx, "NV_depth_buffer_float");
emscripten_webgl_enable_extension(ctx, "NV_blend_equation_advanced");
emscripten_webgl_enable_extension(ctx, "NV_blend_equation_advanced_coherent");
emscripten_webgl_enable_extension(ctx, "ARB_gl_spirv");
emscripten_webgl_enable_extension(ctx, "ARB_spirv_extensions");
emscripten_webgl_enable_extension(ctx, "ARB_invalidate_subdata");
emscripten_webgl_enable_extension(ctx, "ARB_texture_storage ");
emscripten_webgl_enable_extension(ctx, "ARB_ES2_compatibility");
emscripten_webgl_enable_extension(ctx, "ARB_ES3_compatibility ");
emscripten_webgl_enable_extension(ctx, "ARB_ES3_1_compatibility");
emscripten_webgl_enable_extension(ctx, "ARB_ES3_2_compatibility");
emscripten_webgl_enable_extension(ctx, "ARB_gpu_shader5");
emscripten_webgl_enable_extension(ctx, "ARB_blend_func_extended");

// glEnable(GL_LINE_SMOOTH);
glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
glDepthMask(GL_TRUE);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
// glDepthFunc(GL_LESS);
glClearDepth(D);
// glEnable(GL_POLYGON_OFFSET_FILL);
// glPolygonOffset((GLfloat)1.0f,(GLfloat)1.0f);
glEnable(GL_STENCIL_TEST);
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
 // glDisable(GL_DITHER);
glEnable(GL_CULL_FACE);
glFrontFace(GL_CW);
 // glEnable(GL_BLEND);
// glEnable(GL_COLOR_LOGIC_OP); // invald capa
// glDisable(GL_BLEND);
// glBlendEquationSeparate(GL_MAX,GL_FUNC_ADD);
 
glBlendFuncSeparate(GL_DST_COLOR,GL_SRC_COLOR,GL_DST_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBlendEquationSeparate(GL_FUNC_ADD,GL_MAX);
 
// glBlendEquationSeparate(GL_MAX,GL_MAX);
// glBlendEquation(GL_EXCLUSION_NV);   
// glBlendFuncSeparate(GL_SRC_COLOR,GL_ONE_MINUS_DST_COLOR,GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
// 	glBlendFunc(GL_ONE, GL_ZERO);
 // glBlendEquation(GL_LIGHTEN_NV);
// glBlendEquation(GL_MAX);                             
// glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glClearColor((GLclampf)gF0,(GLclampf)gF0,(GLclampf)gF0,(GLclampf)gF);
glClear(GL_COLOR_BUFFER_BIT);
// glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
glBlendColor((GLclampf)gF,(GLclampf)gF,(GLclampf)gF,(GLclampf)gF);
glGenBuffers((GLsizei)1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
nanosleep(&req,&rem);
glGenBuffers((GLsizei)1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indc),indc,GL_STATIC_DRAW);
nanosleep(&req,&rem);
GLchar * default_fragment_shader=(GLchar *)rd_fl(Fnm);
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
auto t1=std::chrono::steady_clock::now();
// emscripten_set_main_loop((void(*)())renderFrame,0,0);
return;
}

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avrg=(((avr+(1.0-rlc))/2.0)+alc);
drk=1.0-(avr-0.5);
brt=1.0-(((1.0-rlc)-(alc-0.5)));
glBlendColor(avrg,avrg,avrg,1.0);
glClearColor(drk,drk,drk,brt);
return;
}

void egl(){
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
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
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

void(*FrM)(){&renderFrame};

extern "C" {

void nano(short int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
clrclr(cllr,alp,avr);
return;
}

void frm(){
FrM();
return;
}

}

EM_JS(void,vid,(),{

"use strict";

var vv=document.getElementById('mv');
var sh4d=false;
var stp,Lstp;
var stpInc=0.016;
var setTim;
var timFrm=16.66;
var lockVid;
var loopLoop;
var mmvv;
let revv;
var $bb;
  
function reverseLoopB(){
if(setTim>Lstp){
setTim-=stpInc;
mmvv.currentTime=setTim;
}else{
revv=false;
forwardLoop();
}
}
  
function forwardLoop(){
if(setTim<=stp){
setTim+=stpInc;
mmvv.currentTime=setTim;
}else{
revv=true;
reverseLoopB();
}
}

function reverseLoop(){
if(setTim>Lstp){
setTim-=stpInc;
mmvv.currentTime=setTim;
}else{
revv=false;
forwardLoop();
}
}

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
}
if (e.code=='KeyZ'){
mmvv=document.getElementById('mv');
mmvv.pause();
stp=document.getElementById('mv').currentTime;
stp=Math.ceil(stp);
setTim=stp;
Lstp=stp-2.0;
loopLoop=true;
revv=true;
}
if(e.code=='KeyX'){
loopLoop=false;
vv.play();
}
if(e.code=='KeyA'){
sh4d=true;
}
if(e.code=='KeyS'){
sh4d=false;
}
}

const pnnl=document.body;
pnnl.addEventListener('keydown',doKey);
let $H64=Module.HEAPF64.buffer;
var inh=parseInt(window.innerHeight,10);
var s$=parseInt(inh,10);
var w$=parseInt(inh,10);
var h$=parseInt(inh,10);
  // w$=parseInt(document.getElementById("wid").innerHTML,10);
// h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=Math.ceil(h$*w$*8);
var pointa=Math.ceil(77*la);
var agav=new Float64Array($H64,pointa,304);
var sz=Math.ceil((h$*w$)/8);
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var blank$=Math.max((((w$-h$)*1.0)/8.0),0.0);
var nblank$=Math.max((((h$-w$)*1.0)/8.0),0.0);
let bCan=document.getElementById("bcanvas");
let gljs=bCan.getContext("webgl2",{
colorType:'float64',
precision:'highp',
preferLowPowerToHighPerformance:false,
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:true,
preserveDrawingBuffer:false,
premultipliedAlpha:false,
desynchronized:false,
lowLatency:false,
powerPreference:'high-performance',
antialias:false,
willReadFrequently:false,
xrCompatible:false,
majorVersion:2,
minorVersion:0
});

gljs.getExtension('OES_texture_float_linear');
gljs.getExtension('OES_texture_half_float_linear');
gljs.getExtension('EGL_EXT_pixel_format_float');  //  required for float/alpha   -- WEBGL2 --
gljs.getExtension('EXT_color_buffer_float');  //  required for float/alpha   -- WEBGL2 --
gljs.getExtension('EXT_color_buffer_half_float');
gljs.getExtension("EXT_float_blend");
gljs.getExtension("EXT_blend_minmax");
// gljs.getExtension('EGL_HI_colorformats');
// gljs.getExtension('EGL_EXT_gl_colorspace_display_p3');
  /*
gljs.getExtension("WEBGL_color_buffer_float");
gljs.getExtension("OES_texture_float_linear");
gljs.getExtension("OES_single_precision");
gl.getExtension("WEBGL_color_buffer_half_float");
gl.getExtension("OES_texture_half_float_linear");
gl.getExtension("EXT_sRGB");
gl.getExtension("OES_fbo_render_mipmap");
gl.getExtension("WEBGL_blend_equation_advanced_coherent");
gl.getExtension("EXT_framebuffer_sRGB");
gl.getExtension("OES_depth32");
gl.getExtension("OES_fixed_point");
gl.getExtension("OES_shader_multisample_interpolation");
gl.getExtension("WEBGL_webcodecs_video_frame");
gl.getExtension("GL_NV_memory_attachment");
gl.getExtension("NV_depth_nonlinear");
gl.getExtension("EXT_gl_colorspace_display_p3");
// gl.getExtension('EGL_KHR_gl_colorspace');
// gl.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
*/
gljs.getExtension("ARB_multisample");
gljs.getExtension('EXT_texture_filter_anisotropic');
gljs.getExtension('ARB_blend_func_extended');
// gljs.getExtension('EXT_framebuffer_sRGB');
gljs.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gljs.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gljs.enable(gl.FRAMEBUFFER_SRGB_EXT); 
// gljs.disable(gl.DITHER);
gljs.drawingBufferColorMetadata={mode:'extended'};
// gljs.renderbufferStorage(gl.RENDERBUFFER,gl.RGBAF64,bCan.height,bCan.height);
// gljs.blendColor(1.0,1.0,1.0,1.0);
// gljs.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
 gljs.blendEquationSeparate(gl.FUNC_ADD,gl.MAX);
// gljs.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.FUNC_ADD);
// gljs.blendEquation(gl.MAX);
// gljs.blendFunc(gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gljs.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
// gljs.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.ONE,gl.ONE_MINUS_SRC_ALPHA);
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
// gl.unpackColorSpace='display-p3';  // very slow
gljs.drawingBufferColorSpace='display-p3';
let g=new GPU({mode:"gpu",canvas:bcanvas,webGl:gljs});
let g2=new GPU({mode:"gpu"});
const glslSilver=`float Silver(float a){return((a+0.75+0.75+((a+0.75)/2.0))/4.0);}`;
const glslGoldR=`float GoldR(float a){return((a+0.831+0.831+0.831+((a+0.831)/2.0))/5.0);}`;
const glslGoldG=`float GoldG(float a){return((a+0.686+0.686+0.686+((a+0.686)/2.0))/5.0);}`;
const glslGoldB=`float GoldB(float a){return((a+0.215+0.215+0.215+((a+0.215)/2.0))/5.0);}`;
const glslRoseR=`float RoseR(float a){return((a+0.86+0.86+0.86+((a+0.86)/2.0))/5.0);}`;
const glslRoseG=`float RoseG(float a){return((a+0.13+0.13+0.13+((a+0.13)/2.0))/5.0);}`;
const glslRoseB=`float RoseB(float a){return((a+0.86+0.86+0.86+((a+0.86)/2.0))/5.0);}`;
const glslGreenR=`float GreenR(float a){return((a+0.11+0.11+0.11+((a+0.11)/2.0))/5.0);}`;
const glslGreenG=`float GreenG(float a){return((a+0.73+0.73+0.73+((a+0.73)/2.0))/5.0);}`;
const glslGreenB=`float GreenB(float a){return((a+0.14+0.14+0.14+((a+0.14)/2.0))/5.0);}`;
let glslAve="float Ave(float a,float b,float c){return(a+b+c)/3.0;}";
// const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float f,float g) {return (1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25)));}`;
let glslAveg="float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}";
// const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*(f-g))))))+0.777777)/4.0);}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(c)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*(f-g))))))+(a+0.75))/5.0);}`;
// // let glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return ((1.4+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/5.0);}`;
// let glslAlphe="float Alphe(float a,float b,float c,float d,float e,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((g-f)*((g)*(g-f))))))+0.777777)/4.0);}";
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g.addNativeFunction('GreenR',glslGreenR,{returnType:'Number'});
g.addNativeFunction('GreenG',glslGreenG,{returnType:'Number'});
g.addNativeFunction('GreenB',glslGreenB,{returnType:'Number'});
g.addNativeFunction('RoseR',glslRoseR,{returnType:'Number'});
g.addNativeFunction('RoseG',glslRoseG,{returnType:'Number'});
g.addNativeFunction('RoseB',glslRoseB,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setPrecision('single').optimizeFloatMemory(true).setDynamicOutput(true).setOutput([sz]);
const t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blnk-this.constants.nblnk];
var av$=Ave(0.8*P[0],P[1],1.2*P[2]);
// var minuss=(av$-0.5)*(av$/(av$-0.5));
// av$=av$+(minuss*(av$*0.033));
return[0.8*P[0],P[1],1.2*P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setPipeline(true).setOutput([s$,s$]);
//     }).setConstants({nblnk:nblank$,blnk:blank$}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput([s$,s$]);
const r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
 
var alph=Alphe($fmax,$amin,$fmax,$amin,$aavg,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
  /*
//  // 
var rr;
var gg;
var bb;
var der=p[0];
var neerg=p[1];
var eulb=p[2];
// if(der>0.333){
 rr=GreenR(der);
// }else{
// rr=RoseR(der);
// }
// if(neerg>0.4){
gg=GreenG(neerg);
// }else{
// gg=RoseG(neerg);
// }
// if(eulb>0.5){
bb=GreenB(eulb);
// }else{
// bb=RoseB(eulb);
// }//   
 */
// this.color(GreenR(p[0]),GreenG(p[1]),GreenB(p[2]),aveg);
// this.color(rr,gg,bb,aveg);
// 
//   var silvrr=Ave(p[0],p[1],p[2]);
// this.color(silvrr,silvrr,p[2],aveg);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setGraphical(true).setOutput([h$,w$]);
// }).setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]}).setTactic("precision").setGraphical(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([s$,s$]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var inh=parseInt(window.innerHeight,10);
var s$=parseInt(inh,10);
vv=document.getElementById("mv");
blank$=Math.max((((w$-s$)*1.0)/8.0),0.0);
nblank$=Math.max((((s$-w$)*1.0)/8.0),0.0);
la=Math.ceil(h$*w$*8);
pointa=Math.ceil(77*la);
agav=new Float64Array($H64,pointa,304);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H64,point"+j+",la);");
};
var pointb=Math.ceil(66*la);
var $B=new Float64Array($H64,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H64,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
// eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H64,point"+j+",la);var $$1=0.0;$"+j+".fill($$1);");
};
var d=S();if(d){d()};d=S();function S(){
vv=document.getElementById("mv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var inh=parseInt(window.innerHeight,10);
var s$=parseInt(inh,10);
blank$=Math.max((((w$-s$)*1.0)/8.0),0.0);
nblank$=Math.max((((s$-w$)*1.0)/8.0),0.0);
s$=parseInt(window.innerHeight,10);
la=Math.ceil(h$*w$*8);
pointa=Math.ceil(77*la);
var agav=new Float64Array($H64,pointa,304);  // has to var?
R.setOutput([sz]);
for(var i=0;i<65;i++){
j=i+1;
eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H64,point"+j+",la);");
};
pointb=Math.ceil(66*la);
var $B=new Float64Array($H64,pointb,sz);  // has to var?
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
}
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
if($F==i){
eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
}};
$bb=R(vv);
$B.set($bb,0,sz);
pointb=Math.ceil(66*la);  // has to revar?
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
if(sh4d==1){
Module.ccall("clr",null,["Number","Number","Number"],[agav[200],agav[100],agav[0]]);
Module.ccall("frm",null,[],[]);
}
setTimeout(function(){
M();
if(loopLoop==true){
timFrm=8.33;
if(revv==true){
reverseLoop();
}else{
timFrm=16.66;
forwardLoop();
}
}
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

void(*sTr)(){&strt};
void(*B3)(){&vid};
void(*b3e)(){&egl};

extern "C" {

void b3_egl(){
b3e();
return;
}

void b3(){
B3();
return;
}

void str(){
sTr();
return;
}

}
