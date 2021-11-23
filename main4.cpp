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
" \n #define specular \n"
" \n #define border \n "
" \n #define specrot \n "
" \n #define pi 3.14159265359 \n "
" \n #ifdef captmode  \n "
"const float KEY_1= 97.5/256.0; const float KEY_2= 98.5/256.0; const float KEY_3= 99.5/256.0; const float KEY_4= 100.5/256.0; const float KEY_5= 101.5/256.0; const float KEY_6= 102.5/256.0; const float KEY_7= 103.5/256.0; const float KEY_8= 104.5/256.0; const float KEY_9= 105.5/256.0;"
" \n #endif \n "
"const float aawidth=0.9; const int aasamples=2; const vec3 ambientColor=vec3(0.8, 0.9, 1.); const float ambientint=0.07; const float specint=0.74; const float specshin=45.; const float normdelta=0.01; const float maxdist=2500.; const float bg_height=0.04; const float hex_height=0.12; const float bg_width0=0.08; const float gap_width=0.055; const float borderpos=0.22; const float borderwidth=0.07; const float borderheight=0.2; const float gen_scale=0.15; const float gamma=1.4; const vec3 sky_color=vec3(0.); const vec3 background_color=vec3(0.3, 0.35, 0.5); vec3 campos=vec3(0., 0., 10.); vec3 camtarget=vec3(0., 0., 0.); vec3 camdir=vec3(0., 0., 0.); float fov=2.; struct DirLamp { vec3 direction; vec3 color; float intensity; }; struct RenderData { vec3 col; vec3 pos; vec3 norm; int objnr; }; vec3 colors[3];"
" \n #define SKY_OBJ 0 \n "
" \n #define BACKGROUND_OBJ  1 \n "
" \n #define HEXAGONS_OBJ2 \n "
"DirLamp lamps[3]; int aai; int aaj; float bg_width; float curtime;"
" \n #ifdef captmode \n "
"int num_key; int isKeyPressed(float key) { return texture(iChannel0, vec2(key, 0.25) ).x > .0?1:0; }"
" \n #endif \n "
"void init() {lamps[0]=DirLamp(vec3(-2.5, 1., -4.), vec3(1., .95, .55), 1.4); lamps[1]=DirLamp(vec3(2., 3., -4.), vec3(1., 1., 1.), 1.3); lamps[2]=DirLamp(vec3(2., -1., 4.), vec3(0.65, 0.72, 1.), 1.2);"
" \n #ifdef captmode \n "
"num_key=isKeyPressed(KEY_1) + 2*isKeyPressed(KEY_2) + 3*isKeyPressed(KEY_3); num_key+= 4*isKeyPressed(KEY_4) + 5*isKeyPressed(KEY_5) + 6*isKeyPressed(KEY_6); num_key+= 7*isKeyPressed(KEY_7) + 8*isKeyPressed(KEY_8) + 9*isKeyPressed(KEY_9); curtime=14.; "
" \n #else \n "
"curtime=iTime;"
" \n #endif \n "
"} vec2 opU(vec2 d1, vec2 d2) { return (d1.x<d2.x) ? d1 : d2; } vec2 rotateVec(vec2 vect, float angle) { vec2 rv; rv.x=vect.x*cos(angle) - vect.y*sin(angle); rv.y=vect.x*sin(angle) + vect.y*cos(angle); return rv; } vec4 hexagon(vec2 p) { vec2 q=vec2(p.x*2.0*0.5773503, p.y + p.x*0.5773503); vec2 ppi=floor(q); vec2 pf=fract(q); float v=mod(ppi.x + ppi.y, 3.0); float ca=step(1.0,v); float cb=step(2.0,v); vec2  ma=step(pf.xy,pf.yx); float e=dot( ma, 1.0-pf.yx + ca*(pf.x+pf.y-1.0) + cb*(pf.yx-2.0*pf.xy) ); p=vec2( q.x + floor(0.5+p.y/1.5), 4.0*p.y/3.0 )*0.5 + 0.5; float f=length( (fract(p) - 0.5)*vec2(1.0,0.85) );return vec4(ppi + ca - cb*ma, e, f); } float getAngle(vec4 h) { int colnr=int(mod(h.x, 3.)); float angle; if (colnr==0) angle=curtime*0.8*(1. + 0.12*sin(curtime*0.4 + h.x*0.04)) + sin(h.x*0.052 + h.y*0.012 + 4.*cos(h.x*0.008 + h.y*0.011)) - cos(h.x*0.015 + h.y*0.032); if (colnr==1) angle=curtime*0.9*(1. + 0.09*sin(curtime*0.3 + h.y*0.05)) + sin(h.x*0.047 + h.y*0.009) + 3.*cos(h.x*0.006 - h.y*0.007) - cos(h.x*0.013 + h.y*0.043); if (colnr==2) angle=curtime*1.05*(1. + 0.15*sin(curtime*0.5 + h.y*0.02)) + sin(h.x*0.056 + h.y*0.016) + 5.*cos(h.x*0.007 + h.y*0.009) - cos(h.x*0.018 + h.y*0.019); return angle*smoothstep(2., 9., curtime); } float map_background(vec3 pos) { vec4 h=hexagon(pos.xz); return max(h.z - bg_width/2., abs(pos.y) - bg_height/2.); } float map_hexagons(vec3 pos) { vec4 h0=hexagon(pos.xz);"
" \n #ifdef specrot \n "
"float colnr=mod(h0.x, 3.); pos.xz=rotateVec(pos.xz, colnr*pi/3.); vec4 h=hexagon(pos.xz);"
" \n #else \n "
"vec4 h=h0;"
" \n #endif \n "
"float lpx=pos.x - h.x*0.866025; float lpz=pos.z - h.y*1.5; vec3 pos2=vec3(lpx, pos.y, lpz); float angle=getAngle(h0); pos2.xy=rotateVec(pos2.xy, angle); vec4 h2=hexagon(vec2(pos2.x, pos.z - h.x*1.5));"
" \n #ifdef border \n "
"float borderhf=(1. - borderheight*smoothstep(borderpos, borderpos + borderwidth, h2.z))*(1. - 1.2*smoothstep(0.14, 0.115, h2.z)); "
" \n #else \n "
"float borderhf=1.;"
" \n #endif  \n "
"float hex=max(-h2.z + bg_width/2. + gap_width, abs(pos2.y) - hex_height/2.*borderhf); return h2.x==0.?hex:1000.; } vec2 map(vec3 pos) { bg_width=bg_width0*(1. + 15.*smoothstep(0.5, 1.0, sin(0.008*pos.x*gen_scale + 1.1)*sin(0.008*pos.z*gen_scale - 3.45))); float background=map_background(gen_scale*pos); vec2 res=vec2(background, BACKGROUND_OBJ); float hexagons=map_hexagons(gen_scale*pos); res=opU(res, vec2(hexagons, HEXAGONS_OBJ)); return res; } vec2 trace(vec3 cam, vec3 ray, float maxdist) { float t=campos.y - 5.; float objnr=0.; vec3 pos; float dist; for (int i=0; i < 180; ++i) { pos=ray*t + cam; vec2 res=map(pos); dist=res.x; if (dist>maxdist || abs(dist)<0.005 || cam.y<2.) break; t+= dist*1.3; objnr=abs(res.y); } return vec2(t, objnr); } vec3 getNormal(vec3 pos, float e) {  vec3 n=vec3(0.0); for( int i=0; i<4; i++ ) { vec3 e2=0.5773*(2.0*vec3((((i+3)>>1)&1),((i>>1)&1),(i&1))-1.0); n += e2*map(pos + e*e2).x; } return normalize(n); } vec3 getSkyColor(vec3 ray) { return sky_color; } vec3 getHexagonColor(vec4 h, vec3 pos) { colors[0]=vec3(1., 0., 0.); colors[1]=vec3(0., 1., 0.); colors[2]=vec3(0., 0., 1.); int colnr=int(mod(h.x, 3.)); vec4 h0=h;"
" \n #ifdef specrot \n "
"pos.xz=rotateVec(pos.xz, float(colnr)*pi/3.); h=hexagon(pos.xz);"
" \n #endif \n "
"float lpx=pos.x - h.x*0.866025; float lpz=pos.z - h.x*1.5; vec2 pos2=vec2(lpx, pos.y); float angle=getAngle(h0); pos2=rotateVec(pos2, angle); return pos2.y>0.?colors[colnr]:1.-colors[colnr]; } vec3 getColor(vec3 norm, vec3 pos, int objnr, vec3 ray) { if (objnr==BACKGROUND_OBJ) { vec3 col=background_color; col.r+= 0.4*smoothstep(0.92, 1.0, sin(0.008*pos.x*gen_scale + 1.1)*sin(0.008*pos.z*gen_scale - 3.45)); col.g+= 0.5*smoothstep(0.85, 1.0, sin(0.008*pos.x*gen_scale + 1.1)*sin(0.008*pos.z*gen_scale - 3.45)); col.b+= 0.6*smoothstep(0.75, 1.0, sin(0.008*pos.x*gen_scale + 1.1)*sin(0.008*pos.z*gen_scale - 3.45)); return col; } else if (objnr==HEXAGONS_OBJ) { vec4 hex=hexagon(gen_scale*pos.xz); return getHexagonColor(hex, gen_scale*pos); } else return getSkyColor(ray); } vec3 lampShading(DirLamp lamp, vec3 norm, vec3 pos, vec3 ocol, int objnr, int lampnr) { vec3 pl=normalize(lamp.direction); vec3 col=ocol*lamp.color*lamp.intensity*clamp(dot(norm, pl), 0., 1.);"
" \n #ifdef specular \n "
"if (dot(norm, lamp.direction) > 0.0)col+= lamp.color*lamp.intensity*specint*pow(max(0.0, dot(reflect(pl, norm), normalize(pos - campos))), specshin);"
" \n #endif \n "
"return col; } vec3 lampsShading(vec3 norm, vec3 pos, vec3 ocol, int objnr) { vec3 col=vec3(0.); for (int l=0; l<3; l++) col+= lampShading(lamps[l], norm, pos, ocol, objnr, l); return col; } vec3 GetCameraRayDir(vec2 vWindow, vec3 vCameraDir, float fov) { vec3 vForward=normalize(vCameraDir); vec3 vRight=normalize(cross(vec3(0.0, 1.0, 0.0), vForward)); vec3 vUp=normalize(cross(vForward, vRight)); vec3 vDir=normalize(vWindow.x * vRight + vWindow.y * vUp + vForward * fov); return vDir; } void setCamera() { vec2 "iMouse2;"
" \n #ifdef captmode \n "
"iMouse2=vec2(0.5, 0.05);"
" \n #else \n "
"if (iMouse.x==0. && iMouse.y==0.) iMouse2=vec2(0.5, 0.05); else iMouse2=iMouse.xy/iResolution.xy;"
" \n #endif \n "
"float cc=pow(1. - sin(0.12*curtime), 1.35); campos=vec3(0., 2.5 + 85.*pow(1. - cos(0.12*curtime), 2.2),  -43.*curtime - 270.*cc - 20.*pow(curtime*0.2, 1.3))/gen_scale; camdir=vec3(3.6*iMouse2.x - 1.75, -3.5*iMouse2.y - 0.6, -1.);} RenderData trace0(vec3 tpos, vec3 ray, float maxdist) { vec2 tr=trace(tpos, ray, maxdist); float tx=tr.x; int objnr=int(tr.y); vec3 col; vec3 pos=tpos + tx*ray; vec3 norm; if (tx<maxdist) { norm=getNormal(pos, normdelta); col=getColor(norm, pos, objnr, ray); col=col*ambientColor*ambientint + lampsShading(norm, pos, col, objnr); } else { objnr=SKY_OBJ; col=getSkyColor(ray); } col*= pow(smoothstep(maxdist, maxdist*0.3, tx), 0.5); return RenderData(col, pos, norm, objnr); } vec4 render(vec2 fragCoord) {vec2 uv=fragCoord.xy / iResolution.xy; uv=uv*2.0 - 1.0; uv.x*= iResolution.x / iResolution.y; float fov2=fov;"
" \n #ifdef captmode \n "
"if (num_key>0) { fov2*= 3.; uv.x+= 2.*(iResolution.x / iResolution.y)*(mod(float(num_key - 1), 3.) - 1.); uv.y+= 2.*(float((num_key - 1)/3) - 1.); }"
" \n #endif \n "
"vec3 ray=GetCameraRayDir(uv, camdir, fov2); RenderData traceinf=trace0(campos, ray, maxdist/gen_scale); vec3 col=traceinf.col; return vec4(pow(col, vec3(gamma)), 1.0); } void mainImage(out vec4 fragColor, in vec2 fragCoord) {init(); setCamera();"
" \n #ifdef antialias \n "
"vec4 vs=vec4(0.); for (aaj=0;aaj<aasamples ;aaj++) { float oy=float(aaj)*aawidth/max(float(aasamples-1), 1.); for (aai=0;aai<aasamples ;aai++) { float ox=float(aai)*aawidth/max(float(aasamples-1), 1.); vs+= render(fragCoord + vec2(ox, oy)); } } fragColor=vs/vec4(aasamples*aasamples);"
" \n #else \n "
"fragColor=vec4(render(fragCoord));"
" \n #endif \n "
"}";
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
