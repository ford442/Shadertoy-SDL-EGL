#include "../../include/vanilla/cropcircle.hpp"

const EGLint attribut_list[]={ 
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB_KHR,
EGL_NONE};
  
const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
  EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,

// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE};


static const EGLint attribut_list[]={
// EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SRGB,
EGL_NONE
};

static const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV,
// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE,
EGL_RED_SIZE,32,
EGL_GREEN_SIZE,32,
EGL_BLUE_SIZE,32,
EGL_ALPHA_SIZE,32,
EGL_DEPTH_SIZE,32,
EGL_STENCIL_SIZE,32,
EGL_BUFFER_SIZE,32,
EGL_NONE,EGL_NONE
};

boost::function<void(int,float *,float *)>avgFrm=[](int leng,float *ptr,float *aptr){
max=0.0f;
min=255.0f;
sum=0.0f;
avgSum=0.0f;
minSum=0.0f;
maxSum=0.0f;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
}
sum=sum/leng;
aptr[0]=sum;
aptr[1]=min;
aptr[2]=max;
return;
};

boost::function<void(int,int,int,float *,float *)>rotateFrame=[](int angle,int wid,int hig,float *Fptr,float *NFptr){
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;
emscripten_get_element_css_size("zimag",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
// eglBindAPI(EGL_OPENGL_API);
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
ctx=emscripten_webgl_create_context("#zimag",&attr);
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx,"EXT_float_blend");
emscripten_webgl_enable_extension(ctx,"EXT_frag_depth");
emscripten_webgl_enable_extension(ctx,"EXT_shader_texture_lod");
emscripten_webgl_enable_extension(ctx,"EXT_sRGB");
emscripten_webgl_enable_extension(ctx,"EXT_blend_minmax");
emscripten_webgl_enable_extension(ctx,"ANGLE_instanced_arrays");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query");
emscripten_webgl_enable_extension(ctx,"EXT_clip_cull_distance");
emscripten_webgl_enable_extension(ctx,"EXT_disjoint_timer_query_webgl2");
emscripten_webgl_enable_extension(ctx,"KHR_parallel_shader_compile");
emscripten_webgl_enable_extension(ctx,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx,"WEBGL_blend_equation_advanced_coherent");
emscripten_webgl_enable_extension(ctx,"WEBGL_depth_texture");
emscripten_webgl_enable_extension(ctx,"WEBGL_draw_buffers");
emscripten_webgl_enable_extension(ctx,"WEBGL_provoking_vertex");
emscripten_webgl_enable_extension(ctx,"EXT_framebuffer_sRGB");
emscripten_webgl_enable_extension(ctx,"OES_depth32");
emscripten_webgl_enable_extension(ctx,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx,"OES_shader_multisample_interpolation");
emscripten_webgl_enable_extension(ctx,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx,"OES_single_precision");
emscripten_webgl_enable_extension(ctx,"GL_EXT_texture_shadow_lod");
emscripten_webgl_enable_extension(ctx,"GL_NV_memory_attachment");
// display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
// eglInitialize(display,&v3,&v0);
// eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
// contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
// surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
// eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glDisable(GL_DITHER);
glViewport(0,0,GLint(Size),GLint(Size));

for (int y = 0; y < hig; y++) {
for (int x = 0; x < wid; x++) {
int index = 4 * (y * hig + x);
unsigned char red = Fptr[index];
unsigned char green = Fptr[index + 1];
unsigned char blue = Fptr[index + 2];
int newX = x * cos(angle) - y * sin(angle);
int newY = x * sin(angle) + y * cos(angle);
if (newX >= 0 && newX < hig && newY >= 0 && newY < wid) {
int newIndex = 4 * (newY * wid + newX);
NFptr[newIndex]=red;
NFptr[newIndex + 1]=green;
NFptr[newIndex + 2]=blue;
NFptr[newIndex + 3]=255;
}
}
}
 
return;
};

extern "C" {

void nano(int leng,float *ptr,float *aptr){
avgFrm(leng,ptr,aptr);
}

void rotat(int angle,int wd,int hi,float *Fptr,float *NFptr){
rotateFrame(angle,wd,hi,Fptr,NFptr);
}

}

EM_JS(void, ma, (), {
let winSize=parseInt(window.innerHeight,10);
const scanvas=document.createElement('canvas');
scanvas.id='zimag';
scanvas.imageRendering='pixelated';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='none';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='999995';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(0,0,0,128)';
document.getElementById("cp").appendChild(scanvas);

/*
const zcanvas=document.createElement('canvas');
zcanvas.id='jimag';
zcanvas.imageRendering='pixelated';
zcanvas.width=winSize;
zcanvas.height=winSize;
zcanvas.zoom=1;
zcanvas.scale=1;
zcanvas.style.pointerEvents='none';
zcanvas.style.display='block';
zcanvas.style.position='absolute';
zcanvas.style.zIndex='999994';
zcanvas.style.top='0';
zcanvas.style.height='100vh';
zcanvas.style.width='100vh';
zcanvas.style.backgroundColor='rgba(0,0,0,128)';
// document.getElementById("cpB").appendChild(zcanvas);
  */
// let c = document.getElementById("imag");

const contxVars={
// colorType:'float32',
// precision:'highp',
// preferLowPowerToHighPerformance:false,
alpha:true,
depth:true,
stencil:true,
preserveDrawingBuffer:false,
premultipliedAlpha:true,
imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:true,
powerPreference:'high-performance',
antialias:false
};
const ctx = scanvas.getContext('2d',contxVars);
// const ctxB = zcanvas.getContext('2d',contxVars);
const gpu = new GPUX({mode:'gpu', canvas:scanvas, webGl:ctx });
// const gpuB = new GPUX({mode:'gpu', canvas:zcanvas, webGl:ctxB });
let dis = set();
if (dis) dis();dis = set();
var $, $r, z, w, R, h, ww, o, l, r, m, rotm, rotmb, rottm, kna, knab, knb, knbb, knc, kncb, knd, kndb, rott, rottb, rottc;
function set() {
ww = document.getElementById("iwid").innerHTML;
h = document.getElementById("ihig").innerHTML;
ow = document.getElementById("wid").innerHTML;
oh = document.getElementById("hig").innerHTML;
let cnP = document.getElementById("cp");
let cnPB = document.getElementById("cpB");
let flP = document.getElementById("flip");
let vd = document.getElementById("myvideo");
  //  var c = document.getElementById("zimag");
  //  var ctx = c.getContext("2d");
ctx.drawImage(vd, 0, 0, ww, h);
var imgData = ctx.getImageData(0, 0, ww, h);
var rgbdat = ctx.createImageData(ww, h);
var rgbd = rgbdat.data;
var imgg = imgData.data;
var pointb=0.0;
var i;
 
let l=h*ww;
let la=h*ww*4;
var pointa=la*2.0;
var pointb=la*3.0;
var pointc=la*4.0;
let $H=Module.HEAPF32.buffer;
// var rgbd = new Uint32Array(imgData.data);
var agavF=new Float32Array($H,pointa,la);
var agavNF=new Float32Array($H,pointb,la);
agavF.set(imgData.data);
// Module.HEAPF32.set(imgData.data);
Module.ccall("nano",null,["Number","Number","Number"],[la,pointa,pointc]);
var agav=new Float32Array($H,pointc,1);
console.log(agav[0]);
for (i = 0; i < (ww * h * 4); i = i + 4) {
var rgb = (imgg[i] * 0.2126) + (imgg[i + 1] * 0.7152) + (imgg[i + 2] * 0.0722);
var rgbm=128-rgb;
if (rgb > 126) {
if (rgb > 209) {    // orange
rgbd[i] = 255;
rgbd[i + 1] = 128;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255-(rgb-209)*16;
}
else if(rgb > 193){   // red
rgbd[i] = 255;
rgbd[i + 1] = 0;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255-(rgb-193)*16;
}else if(rgb > 177){   // light blue
rgbd[i] = 0;
rgbd[i + 1] = 255;
rgbd[i + 2] = 255;
rgbd[i + 3] =255- (rgb-177)*16;
}  else if(rgb > 161){  //  blue
rgbd[i] = 0;
rgbd[i + 1] = 0;
rgbd[i + 2] = 255;
rgbd[i + 3] =255- (rgb-161)*16;
}  else if(rgb > 145){  // green
rgbd[i] = 0;
rgbd[i + 1] = 255;
rgbd[i + 2] = 0;
rgbd[i + 3] =255- (rgb-145)*16;
} else if(rgb > 128){  // yellow
rgbd[i] =255;
rgbd[i + 1] = 255;
rgbd[i + 2] = 0;
rgbd[i + 3] =255- (rgb-128)*16;
}
} else {
rgbd[i] = 0;
rgbd[i + 1] = 0;
rgbd[i + 2] = 0;
rgbd[i + 3] =255- (rgb-128)*16;
}
}
// Module.HEAPF32.set(rgbdat.data);
agavF.set(rgbdat.data);
var ang=45;
Module.ccall("rotat",null,["Number","Number","Number","Number","Number"],[ang,ww,h,pointa,pointb]);
// var rtt =ctx.createImageData(ww,h);
// rtt.data=agavNF;
ctx.putImageData(rgbdat,0,0);

function Ra() {
flP.setAttribute("style", "transform: scaleX(1);");
cnP.setAttribute("style", "transform: scaleY(1);");
// cnPB.setAttribute("style", "transform: scaleY(-1);");
}
function Rb() {
flP.setAttribute("style", "transform: scaleX(-1);");
cnP.setAttribute("style", "transform: scaleY(-1);");
// cnPB.setAttribute("style", "transform: scaleY(1);");
}
knb = document.getElementById("rra");
kna = document.getElementById("mainr");
knc = document.getElementById("rrb");
knd = document.getElementById("rrc");
knbb = document.getElementById("rrab");
kncb = document.getElementById("rrbb");
kndb = document.getElementById("rrcb");
rate = (kna.innerHTML);
rott = 0;
rottb = 0;
rottc = 0;
let dur = document.getElementById("temptime").innerHTML / 10;
let dsd = false;

function $rn() {
if (dsd) {
return;
}
function rrra(rta) {
cnP.setAttribute("style", "transform: rotate(" + rta + "deg);");
// cnPB.setAttribute("style", "transform: rotate(" + rta + "deg);");
}
function rrrb(rtb) {
cnP.setAttribute("style", "transform:rotate(" + rtb + "deg);");
// cnPB.setAttribute("style", "transform:rotate(" + rtb + "deg);");
}
function rrrc(rtc) {
cnP.setAttribute("style", "transform: rotate(" + rtc + "deg);");
// cnPB.setAttribute("style", "transform: rotate(" + rtc + "deg);");
}
if ((rott - knd.innerHTML) < 0) {
rott = (rott + 360 - knd.innerHTML);
} else {
rott = rott - knd.innerHTML;
}
rrra(rott);
if ((rottb - knc.innerHTML) < 0) {
rottb = (rottb + 360 - knc.innerHTML);
} else {
rottb = (rottb - knc.innerHTML);
}
setTimeout(function() {
Rb();
rrrb(rottb);
}, rate);
if ((rottc + knb.innerHTML) > 360) {
rottc = ((rottc + knb.innerHTML) - 360);
} else {
rottc = (rottc + knb.innerHTML);
}
setTimeout(function() {
Ra();
rrrc(rottc);
}, rate);
setTimeout(function() {
$rn();
}, rate);
}
$rn();

document.getElementById("di").onclick = function() {
dsd = true;
set();
};
return () => {
dsd = true;
};


}
});

int main() {
ma();
return 1;
}
