#include <string>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
static const char *read_file_into_str(const char *filename){
char *result=NULL;
long length=0;
FILE *file=fopen(filename,"r");
if(file){
int status=fseek(file,0,SEEK_END);
if(status!=0){
fclose(file);
return NULL;
}
length=ftell(file);
status=fseek(file,0,SEEK_SET);
if(status!=0){
fclose(file);
return NULL;
}
result=static_cast<char*>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
} 
fclose(file);
return result;
}
return NULL;
}
static const char common_shader_header_gles3[]=
"#version 300 es \n"
"precision highp float; \n";
static const char vertex_shader_body_gles3[]=
"layout(location=0) in vec4 iPosition;"
"void main(){"
"gl_Position=iPosition;"
"} \n";
static const char fragment_shader_header_gles3[]=
"uniform vec3 iResolution;"
"uniform float iTime;"
"uniform float iChannelTime[4];"
"uniform vec4 iMouse;"
"uniform vec4 iDate;"
"uniform vec3 iChannelResolution[4];"
"uniform sampler2D iChannel0;"
"uniform sampler2D iChannel1;"
"uniform sampler2D iChannel2;"
"uniform sampler2D iChannel3;"
"out vec4 fragColor; \n";
static const char fragment_shader_footer_gles3[]=
"\n void main(){mainImage(fragColor, gl_FragCoord.xy);} \n";
static SDL_AudioDeviceID dev;
static EGLDisplay display;
static EGLContext contextegl;
static EGLSurface surface;
static EmscriptenWebGLContextAttributes attr;
static struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
SDL_Window *win;
SDL_GLContext *glCtx;
static const char* common_shader_header=common_shader_header_gles3;
static const char* vertex_shader_body=vertex_shader_body_gles3;
static const char* fragment_shader_header=fragment_shader_header_gles3;
static const char* fragment_shader_footer=fragment_shader_footer_gles3;
static GLuint shader_program;
static GLint attrib_position;
static GLint sampler_channel[4];
static GLint uniform_cres;
static GLint uniform_ctime;
static GLint uniform_date;
static GLint uniform_gtime;
static GLint uniform_time;
static GLint uniform_res;
static GLfloat viewportSizeX=0.0;
static GLfloat viewportSizeY=0.0;
static const GLfloat vertices[]={
-1.0f,-1.0f,
1.0f,-1.0f,
-1.0f,1.0f,
1.0f,1.0f
};
static GLuint compile_shader(GLenum type,GLsizei nsources,const char **sources){
static GLuint shader;
GLsizei i,srclens[nsources];
for (i=0;i<nsources;++i){
srclens[i]=(GLsizei)strlen(sources[i]);
}
shader=glCreateShader(type);
glShaderSource(shader,nsources,sources,srclens);
glCompileShader(shader);
return shader;
}
GLuint vbo,vbu;
static void renderFrame(){
double abstime=(double)SDL_GetTicks()/1000;
glClearColor(0.0f, 0.0f, 0.0f, 1.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glGenVertexArrays(1,&vbu);
glBindVertexArray(vbu);
glVertexAttribPointer(attrib_position,2,GL_FLOAT,GL_FALSE,0,0);
glEnableVertexAttribArray(attrib_position);
glUseProgram(shader_program);
glUniform1f(uniform_time,abstime);
glUniform1f(uniform_gtime,abstime);
glDrawArrays(GL_TRIANGLE_STRIP,0,4);
eglSwapBuffers(display,surface);
}
static const EGLint attribut_list[]={
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE
};
static const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RED_SIZE,8,
EGL_GREEN_SIZE,8,
EGL_BLUE_SIZE,8,
EGL_ALPHA_SIZE,8,
EGL_STENCIL_SIZE,8,
EGL_DEPTH_SIZE,24,
EGL_BUFFER_SIZE,32,
EGL_NONE
};
static void strt(){
static const char *default_fragment_shader=
"vec2 sim2d( in vec2 p, in float s) { vec2 ret=p; ret=p+s/2.0; ret=fract(ret/s)*s-s/2.0; return ret; } vec3 stepspace( in vec3 p, in float s) { return p-mod(p-s/2.0,s); } float obj(in vec3 p) { vec3 fp=stepspace(p,2.0);; float d=sin(fp.x*0.3+iTime*4.0)+cos(fp.z*0.3+iTime*2.0); p.y=p.y+d; p.xz=sim2d(p.xz,2.0); float c1=length(max(abs(p)-vec3(0.6,0.6,0.6),0.0))-0.35; float c2=length(p)-1.0; float cf=sin(iTime)*0.5+0.5; return mix(c1,c2,cf); } vec3 obj_c(vec3 p) { vec2 fp=sim2d(p.xz-1.0,4.0); if (fp.y>0.0) fp.x=-fp.x; if (fp.x>0.0) return vec3(0.0,0.0,0.0); else return vec3(1.0,1.0,1.0);   } float PI=3.14159265; vec3 phong( in vec3 pt, in vec3 prp, in vec3 normal, in vec3 light, in vec3 color, in float spec, in vec3 ambLight) { vec3 lightv=normalize(light-pt); float diffuse=dot(normal,lightv); vec3 refl=-reflect(lightv,normal); vec3 viewv=normalize(prp-pt); float specular=pow(max(dot(refl,viewv),0.0),spec); return (max(diffuse,0.0)+ambLight)*color+specular; } float raymarching( in vec3 prp, in vec3 scp, in int maxite, in float precis, in float startf, in float maxd, out int objfound) { const vec3 e=vec3(0.1,0,0.0); float s=startf; vec3 c,p,n; float f=startf; objfound=1; for(int i=0;i<256;i++){ if (abs(s)<precis||f>maxd||i>maxite) break; f+=s; p=prp+scp*f; s=obj(p); } if (f>maxd) objfound=-1; return f; } vec3 camera( in vec3 prp, in vec3 vrp, in vec3 vuv, in float vpd, in vec2 fragCoord) { vec2 vPos=-1.0+2.0*fragCoord.xy/iResolution.xy; vec3 vpn=normalize(vrp-prp); vec3 u=normalize(cross(vuv,vpn)); vec3 v=cross(vpn,u); vec3 scrCoord=prp+vpn*vpd+vPos.x*u*iResolution.x/iResolution.y+vPos.y*v; return normalize(scrCoord-prp); } vec3 normal(in vec3 p) { const float n_er=0.01; float v1=obj(vec3(p.x+n_er,p.y-n_er,p.z-n_er)); float v2=obj(vec3(p.x-n_er,p.y-n_er,p.z+n_er)); float v3=obj(vec3(p.x-n_er,p.y+n_er,p.z-n_er)); float v4=obj(vec3(p.x+n_er,p.y+n_er,p.z+n_er)); return normalize(vec3(v4+v1-v3-v2,v3+v4-v1-v2,v2+v4-v3-v1)); } vec3 render( in vec3 prp, in vec3 scp, in int maxite, in float precis, in float startf, in float maxd, in vec3 background, in vec3 light, in float spec, in vec3 ambLight, out vec3 n, out vec3 p, out float f, out int objfound) { objfound=-1; f=raymarching(prp,scp,maxite,precis,startf,maxd,objfound); if (objfound>0){ p=prp+scp*f; vec3 c=obj_c(p); n=normal(p); vec3 cf=phong(p,prp,n,light,c,spec,ambLight); return vec3(cf); } f=maxd; return vec3(background); } void mainImage( out vec4 fragColor, in vec2 fragCoord ){ vec3 vuv=vec3(0,1,0); vec3 vrp=vec3(iTime*4.0,0.0,0.0); float mx=iMouse.x/iResolution.x*PI*2.0; float my=iMouse.y/iResolution.y*PI/2.01; if ((iMouse.x<=0.0)||(iMouse.y<=0.0)){mx=1.0,my=0.5;}; vec3 prp=vrp+vec3(cos(my)*cos(mx),sin(my),cos(my)*sin(mx))*12.0; float vpd=1.5; vec3 light=prp+vec3(5.0,0,5.0); vec3 scp=camera(prp,vrp,vuv,vpd,fragCoord); vec3 n,p; float f; int o; const float maxe=0.01; const float startf=0.1; const vec3 backc=vec3(0.0,0.0,0.0); const float spec=8.0; const vec3 ambi=vec3(0.1,0.1,0.1); vec3 c1=render(prp,scp,256,maxe,startf,60.0,backc,light,spec,ambi,n,p,f,o); c1=c1*max(1.0-f*.015,0.0); vec3 c2=backc; if (o>0){ scp=reflect(scp,n); c2=render(p+scp*0.05,scp,32,maxe,startf,10.0,backc,light,spec,ambi,n,p,f,o); } c2=c2*max(1.0-f*.1,0.0); fragColor=vec4(c1.xyz*0.75+c2.xyz*0.25,1.0); }";
  char const *program_source=NULL;
char *fileloc="/shader/shader1.toy";
program_source=read_file_into_str(fileloc);
// default_fragment_shader=program_source;
SDL_Log("Got Shader: %s",fileloc);
SDL_Log("Shader: %s",default_fragment_shader);
GLuint vtx,frag,vbo;
const char *sources[4];
// const char *log;
// GLint success,len;
// int temp_val=0;
const char* texture_files[4];
for (int i=0;i<4;++i) {
texture_files[i]=NULL;
}
SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
attr.alpha=1;
attr.stencil=1;
attr.depth=1;
attr.antialias=0;
attr.premultipliedAlpha=0;
attr.preserveDrawingBuffer=0;
emscripten_webgl_init_context_attributes(&attr);
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=emscripten_webgl_create_context("#canvas",&attr);
EGLConfig eglconfig=NULL;
EGLint config_size,major,minor;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
if(eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size)==EGL_TRUE && eglconfig!=NULL){
if(eglBindAPI(EGL_OPENGL_ES_API)!=EGL_TRUE){
}
EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_NONE};
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
if(contextegl==EGL_NO_CONTEXT){
}
else{
surface=eglCreateWindowSurface(display,eglconfig,NULL,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
}}
emscripten_webgl_make_context_current(ctx);
int h=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
int w=h;
win=SDL_CreateWindow("pm",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,0);
glCtx=&contextegl;
sources[0]=common_shader_header;
sources[1]=vertex_shader_body;
vtx=compile_shader(GL_VERTEX_SHADER,2,sources);
sources[0]=common_shader_header;
sources[1]=fragment_shader_header;
sources[2]=default_fragment_shader;
sources[3]=fragment_shader_footer;
glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER,0);
glGenVertexArrays(1,&vbo);
frag=compile_shader(GL_FRAGMENT_SHADER,4,sources);
shader_program=glCreateProgram();
glAttachShader(shader_program,vtx);
glAttachShader(shader_program,frag);
glLinkProgram(shader_program);
glDeleteShader(vtx);
glDeleteShader(frag);
glReleaseShaderCompiler();
glUseProgram(shader_program);
glValidateProgram(shader_program);
attrib_position=glGetAttribLocation(shader_program,"iPosition");
sampler_channel[0]=glGetUniformLocation(shader_program,"iChannel0");
sampler_channel[1]=glGetUniformLocation(shader_program,"iChannel1");
sampler_channel[2]=glGetUniformLocation(shader_program,"iChannel2");
sampler_channel[3]=glGetUniformLocation(shader_program,"iChannel3");
uniform_cres=glGetUniformLocation(shader_program,"iChannelResolution");
uniform_ctime=glGetUniformLocation(shader_program,"iChannelTime");
uniform_date=glGetUniformLocation(shader_program,"iDate");
uniform_gtime=glGetUniformLocation(shader_program,"iGlobalTime");
uniform_time=glGetUniformLocation(shader_program,"iTime");
uniform_res=glGetUniformLocation(shader_program,"iResolution");
glUniform3f(uniform_res,(float)w,(float)h,0.0f);
SDL_SetWindowTitle(win,"1ink.us - Shadertoy");
SDL_Log("GL_VERSION: %s",glGetString(GL_VERSION));
SDL_Log("GLSL_VERSION: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
SDL_Init(SDL_INIT_TIMER);
// glViewport(0,0,w,h);
// viewportSizeX=w;
// viewportSizeY=h;
// glActiveTexture(GL_TEXTURE0);
emscripten_set_main_loop((void (*)())renderFrame,0,0);
}
static void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
}}
static void qu(int rc){
SDL_Quit();
exit(rc);
}
static void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
qu(2);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
}
static void SDLCALL bfr(void *unused,Uint8 * stm,int len){
Uint8* wptr;
int lft;
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while (lft<=len){
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
}
static void plt(){
char flnm[1024];
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
SDL_Log("SDL failed to init.");
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
}
extern "C" {
void pl(){
plt();
}
void str(){
strt();
}}
int main(){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 1;
}
