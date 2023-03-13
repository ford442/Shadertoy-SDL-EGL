#include "../../include/combine/video.hpp"

void clrclr(GLclampf rlc,GLclampf alc,GLclampf avr){
avrg=(((avr+(1.0-rlc))/2.0)+alc);
drk=1.0-(avr-0.5);
brt=((1.0-rlc)-(alc-0.5));
glBlendColor(avrg,avrg,avrg,1.0);
glClearColor(drk,drk,drk,brt);
return;
}

extern "C" {

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
clrclr(cllr,alp,avr);
return;
}

}

void egl(){
eglconfig_js=NULL;
emscripten_get_element_css_size("canvas",&wi_js,&hi_js);
Size_js=(GLsizei)hi_js;
emscripten_webgl_init_context_attributes(&attr_js);
attr_js.alpha=EM_TRUE;
attr_js.stencil=EM_FALSE;
attr_js.depth=EM_TRUE;
attr_js.antialias=EM_TRUE;
attr_js.premultipliedAlpha=EM_FALSE;
attr_js.preserveDrawingBuffer=EM_FALSE;
attr_js.enableExtensionsByDefault=EM_TRUE;
attr_js.renderViaOffscreenBackBuffer=EM_FALSE;
attr_js.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_js.failIfMajorPerformanceCaveat=EM_FALSE;
attr_js.majorVersion=2;
attr_js.minorVersion=0;
ctx_js=emscripten_webgl_create_context("#bcanvas",&attr_js);
// eglBindAPI(EGL_OPENGL_API);
// eglBindAPI(EGL_OPENGL_ES_API);
display_js=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_js,&major_js,&minor_js);
eglChooseConfig(display_js,attribute_list_js,&eglconfig_js,(EGLint)1,&config_size_js);
contextegl_js=eglCreateContext(display_js,eglconfig_js,EGL_NO_CONTEXT,anEglCtxAttribs2_js);
surface_js=eglCreateWindowSurface(display_js,eglconfig_js,(NativeWindowType)0,attribut_list_js);
eglMakeCurrent(display_js,surface_js,surface_js,contextegl_js);
emscripten_webgl_make_context_current(ctx_js);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
glDisable(GL_DITHER);
glEnable(GL_SCISSOR_TEST);
emscripten_webgl_enable_extension(ctx_js,"EXT_pixel_format_float");  //  required for float/alpha   -- EGL --
emscripten_webgl_enable_extension(ctx_js,"EGL_IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"IMG_context_priority");     //     vv  required for realtime
emscripten_webgl_enable_extension(ctx_js,"NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_context_priority_realtime"); // ^^
emscripten_webgl_enable_extension(ctx_js,"NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_js,"HI_colorformats");
emscripten_webgl_enable_extension(ctx_js,"EGL_HI_colorformats");
// emscripten_webgl_enable_extension(ctx_js,"EXT_texture_filter_anisotropic");
// emscripten_webgl_enable_extension(ctx_js,"ARB_gl_spirv");
// emscripten_webgl_enable_extension(ctx_js,"ARB_spirv_extensions");
// emscripten_webgl_enable_extension(ctx_js,"ARB_invalidate_subdata");
// emscripten_webgl_enable_extension(ctx_js,"ARB_texture_storage ");
// emscripten_webgl_enable_extension(ctx_js,"ARB_ES2_compatibility");
// emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_compatibility ");
// emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_1_compatibility");
// emscripten_webgl_enable_extension(ctx_js,"ARB_ES3_2_compatibility");
// emscripten_webgl_enable_extension(ctx_js,"ARB_gpu_shader5");
emscripten_webgl_enable_extension(ctx_js,"KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"EGL_KHR_gl_colorspace");
emscripten_webgl_enable_extension(ctx_js,"EXT_gl_colorspace_scrgb_linear");
emscripten_webgl_enable_extension(ctx_js,"EGL_EXT_gl_colorspace_scrgb_linear");
glDisable(GL_STENCIL_TEST);
glDisable(GL_DEPTH_TEST);
glViewport((GLint)0,(GLint)0,Size_js,Size_js);
glScissor((GLint)0,(GLint)0,Size_js,Size_js);
return;
}

extern "C" {

void nano(short int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

void avgFrm(short int Fnum,int leng,float *ptr,float *aptr){
max=0.0;
min=1.0;
sum=0.0;
avgSum=0.0;
minSum=0.0;
maxSum=0.0;
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

EM_JS(void,vid,(),{

'use strict';

var vv=document.getElementById('mv');
var sh4d=false;
var stp,Lstp;
const stpInc=0.016;
var setTim;
// const timFrm=16.666;
const timFrm=10.42;
var lockVid;
var loopLoop;
var loopPart;
var mmvv;
var revv;
var $bb;
function forwardLoop(){
// setTim=mmvv.currentTime;
setTim+=stpInc;
if(setTim<stp){
mmvv.currentTime=setTim;
}else{
revv=true;
}
}
function reverseLoop(){
// setTim=mmvv.currentTime;
setTim-=stpInc;
if(setTim>=Lstp){
mmvv.currentTime=setTim;
}else{
revv=false;
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
loopPart=(stp+2.5)-(Math.floor(stp));
setTim=stp;
Lstp=stp-loopPart;
stp-=loopPart/2.0;
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
const $H=Module.HEAPF64.buffer;
const $H32=Module.HEAPF32.buffer;
var inh=window.innerHeight;
var s$=parseInt(inh,10);
var w$=parseInt(inh,10);
var h$=parseInt(inh,10);
var la=h$*w$*8;
var pointa=77*la;
var agav=new Float32Array($H32,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var blank$=Math.max((((w$-h$)*0.0)/8.0),0);
var nblank$=Math.max((((h$-w$)*0.0)/8.0),0);
let bCan=document.getElementById("bcanvas");
let gljs=bCan.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:false,
precision:'highp',
imageSmoothingEnabled:false,
imageSmoothingQuality:'medium',
preserveDrawingBuffer:false,
premultipliedAlpha:false,
desynchronized:false,
lowLatency:true,
powerPreference:'high-performance',
antialias:true,
willReadFrequently:false,
xrCompatible:false,
majorVersion:2,
minorVersion:0
});

gljs.getExtension('EXT_color_buffer_float');  //  required for float/alpha   -- WEBGL2 --
  /*
gl.getExtension('EGL_HI_colorformats');
gl.getExtension('EGL_KHR_gl_colorspace');
// gl.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_display_p3');
// gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
gl.getExtension('EXT_texture_filter_anisotropic');
*/
// gl.getExtension('ARB_blend_func_extended');
  
gljs.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gljs.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);

gljs.disable(gl.DITHER);
// gl.drawingBufferColorMetadata={mode:'extended'};
// gl.renderbufferStorage(gl.RENDERBUFFER,gl.RGBAF32,bCan.height,bCan.height);
gljs.blendColor(1.0,1.0,1.0,1.0);
gljs.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gljs.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
// gl.unpackColorSpace='display-p3';  // very slow
gljs.drawingBufferColorSpace='display-p3';
const g=new GPU({mode:'gpu',canvas:bcanvas,webGl:gljs});
const g2=new GPU({mode:'gpu'});
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(0.999-(((a)-(b))*((a)*(0.999/(0.999-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setOptimizeFloatMemory(true).setDynamicOutput(true).setOutput([sz]);
const t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
// var minuss=(av$-0.9)*(av$/(av$-0.9));
// av$=av$-(minuss*(av$*0.01));
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setPipeline(true).setOutput([s$,s$]);
//     }).setConstants({nblnk:nblank$,blnk:blank$}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput([h$,w$]);
const r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x];
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
//   var silvrr=Ave(p[0],p[1],p[2]);
// this.color(silvrr,silvrr,p[2],aveg);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setGraphical(true).setOutput([h$,w$]);
// }).setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]}).setTactic("precision").setGraphical(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([$S,$S]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-s$)*1.0)/8.0),0);
var nblank$=Math.max((((s$-w$)*1.0)/8.0),0);
la=h$*w$*8;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float32Array($H32,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
};
var pointb=77*la;
var $B=new Float32Array($H32,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
// eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);var $$1=0.0;$"+j+".fill($$1);");
};
var d=S();if(d)d();d=S();function S(){
vv=document.getElementById("mv");
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-s$)*1.0)/8.0),0);
var nblank$=Math.max((((s$-w$)*1.0)/8.0),0);
s$=parseInt(window.innerHeight,10);
la=h$*w$*8;
sz=(h$*w$)/8;
var pointa=77*la;
var agav=new Float32Array($H32,pointa,300);  // has to var?
R.setOutput([sz]);
for(var i=0;i<65;i++){
j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
};
var pointb=66*la;
var $B=new Float32Array($H32,pointb,sz);  // has to var?
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
};
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;};
var locb=$Bu+1;
if(locb>64){locb=1;};
if($F==i){
eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
};};
$bb=R(vv);
$B.set($bb,0,sz);
var pointb=66*la;  // has to revar?
if(sh4d==1){
Module.ccall("frm",null,[],[]);
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
Module.ccall("clr",null,["Number","Number","Number"],[agav[200],agav[100],agav[0]]);
};
setTimeout(function(){
M();
if(loopLoop==true){
if(revv==true){
reverseLoop();
}else{
forwardLoop();
};
};
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

extern "C" {

void b3_egl(){
void(*b3e)(){&egl};
b3e();
return;
}
  
void b3(){
void(*B3)(){&vid};
B3();
return;
}

}
