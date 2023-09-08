#include "../../include/vanilla/cropcircle.hpp"

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
for(int y=0;y<hig;y++){
for(int x=0;x<wid;x++){
int index=4*(y*hig+x);
unsigned char red=Fptr[index];
unsigned char green=Fptr[index+1];
unsigned char blue=Fptr[index+2];
int newX=x*cos(angle)-y*sin(angle);
int newY=x*sin(angle)+y*cos(angle);
if (newX>=0&&newX<hig&&newY>=0&&newY<wid){
int newIndex=4*(newY*wid+newX);
NFptr[newIndex]=red;
NFptr[newIndex+1]=green;
NFptr[newIndex+2]=blue;
NFptr[newIndex+3]=255;
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

void emsc(){

EGLConfig eglconfig=NULL;
EGLDisplay display;
EGLContext contextegl;
EGLSurface surface;
EGLint config_size,major,minor;

const EGLint anEglCtxAttribs2[]={
EGL_CONTEXT_CLIENT_VERSION,3,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT, 
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
//   EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR,
EGL_NONE,EGL_NONE
};

static const EGLint attribut_list[]={
EGL_GL_COLORSPACE_KHR,EGL_GL_COLORSPACE_SCRGB_EXT,
EGL_NONE,EGL_NONE
};

static const EGLint attribute_list[]={
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
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

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
emscripten_get_element_css_size("zimag",&wi,&hi);
Size=(int)hi;
S=(GLfloat)Size;
eglBindAPI(EGL_OPENGL_API);
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_FALSE;
attr.premultipliedAlpha=EM_FALSE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
ctx=emscripten_webgl_create_context("#zimag",&attr);
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display,&major,&minor);
eglChooseConfig(display,attribute_list,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,anEglCtxAttribs2);
surface=eglCreateWindowSurface(display,eglconfig,0,attribut_list);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_webgl_make_context_current(ctx);
// emscripten_webgl_enable_extension(ctx,"GL_ALL_EXTENSIONS");
// emscripten_webgl_enable_extension(ctx,"EGL_EXT_gl_colorspace_scrgb");
 // glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
// glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
// glDisable(GL_DITHER);
// glViewport(0,0,GLint(Size),GLint(Size));
}

}

EM_JS(void,ma,(),{
"use strict";
let winSize=parseInt(window.innerHeight,10);
const scanvas1=document.createElement('canvas');
scanvas1.id='zimag1';
scanvas1.imageRendering='pixelated';
scanvas1.width=winSize;
scanvas1.height=winSize;
scanvas1.zoom=1;
scanvas1.scale=1;
scanvas1.style.pointerEvents='none';
scanvas1.style.display='block';
scanvas1.style.position='absolute';
scanvas1.style.zIndex='999991';
scanvas1.style.top='0';
scanvas1.style.height='100vh';
scanvas1.style.width='100vh';
scanvas1.style.backgroundColor='rgba(0,0,0,0)';
document.getElementById("cp1").appendChild(scanvas1);
const scanvas2=document.createElement('canvas');
scanvas2.id='zimag2';
scanvas2.imageRendering='pixelated';
scanvas2.width=winSize;
scanvas2.height=winSize;
scanvas2.zoom=1;
scanvas2.scale=1;
scanvas2.style.pointerEvents='none';
scanvas2.style.display='block';
scanvas2.style.position='absolute';
scanvas2.style.zIndex='999994';
scanvas2.style.top='0';
scanvas2.style.height='100vh';
scanvas2.style.width='100vh';
scanvas2.style.backgroundColor='rgba(0,0,0,0)';
document.getElementById("cp2").appendChild(scanvas2);
const scanvas3=document.createElement('canvas');
scanvas3.id='zimag3';
scanvas3.imageRendering='pixelated';
scanvas3.width=winSize;
scanvas3.height=winSize;
scanvas3.zoom=1;
scanvas3.scale=1;
scanvas3.style.pointerEvents='none';
scanvas3.style.display='block';
scanvas3.style.position='absolute';
scanvas3.style.zIndex='999993';
scanvas3.style.top='0';
scanvas3.style.height='100vh';
scanvas3.style.width='100vh';
scanvas3.style.backgroundColor='rgba(0,0,0,0)';
document.getElementById("cp3").appendChild(scanvas3);
const scanvas4=document.createElement('canvas');
scanvas4.id='zimag4';
scanvas4.imageRendering='pixelated';
scanvas4.width=winSize;
scanvas4.height=winSize;
scanvas4.zoom=1;
scanvas4.scale=1;
scanvas4.style.pointerEvents='none';
scanvas4.style.display='block';
scanvas4.style.position='absolute';
scanvas4.style.zIndex='999992';
scanvas4.style.top='0';
scanvas4.style.height='100vh';
scanvas4.style.width='100vh';
scanvas4.style.backgroundColor='rgba(0,0,0,0)';
document.getElementById("cp4").appendChild(scanvas4);

const contxVars={
// colorType:'float32',
// precision:'highp',
// preferLowPowerToHighPerformance:false,
alpha:true,
depth:false,
stencil:false,
// preserveDrawingBuffer:false,
// premultipliedAlpha:false,
// imageSmoothingEnabled:false,
willReadFrequently:true,
// lowLatency:true,
// powerPreference:'high-performance',
// antialias:false
};
const ctx1=scanvas1.getContext('2d',contxVars);
const ctx2=scanvas2.getContext('2d',contxVars);
const ctx3=scanvas3.getContext('2d',contxVars);
const ctx4=scanvas4.getContext('2d',contxVars);
// const ctxB=zcanvas.getContext('2d',contxVars);
const gpu1=new GPUX({mode:'gpu',canvas:scanvas1,webGl:ctx1 });
const gpu2=new GPUX({mode:'gpu',canvas:scanvas2,webGl:ctx2 });
const gpu3=new GPUX({mode:'gpu',canvas:scanvas3,webGl:ctx3 });
const gpu4=new GPUX({mode:'gpu',canvas:scanvas4,webGl:ctx4 });
// const gpuB=new GPUX({mode:'gpu',canvas:zcanvas,webGl:ctxB });
let dis=set();
if(dis){dis();}
dis=set();
var $,$r,z,w,R,h,ww,o,l,r,m,rotm,rotmb,rottm,kna,knab,knb,knbb,knc,kncb,knd,kndb,rott,rottb,rottc;
function set(){
ww=document.getElementById("iwid").innerHTML;
h=document.getElementById("ihig").innerHTML;
ow=document.getElementById("wid").innerHTML;
oh=document.getElementById("hig").innerHTML;
let cnP1=document.getElementById("cp1");
let cnP2=document.getElementById("cp2");
let cnP3=document.getElementById("cp3");
let cnP4=document.getElementById("cp4");
let cnPB=document.getElementById("cpB");
let flP=document.getElementById("flip");
let vd=document.getElementById("myvideo");
ctx1.drawImage(vd,0,0,ww,h);
ctx2.drawImage(vd,0,0,ww,h);
ctx3.drawImage(vd,0,0,ww,h);
ctx4.drawImage(vd,0,0,ww,h);
var imgData1=ctx1.getImageData(0,0,ww,h);
var imgData2=ctx2.getImageData(0,0,ww,h);
var imgData3=ctx3.getImageData(0,0,ww,h);
var imgData4=ctx4.getImageData(0,0,ww,h);
var rgbdat1=ctx1.createImageData(ww,h);
var rgbdat2=ctx2.createImageData(ww,h);
var rgbdat3=ctx3.createImageData(ww,h);
var rgbdat4=ctx4.createImageData(ww,h);
var rgbd1=rgbdat1.data;
var rgbd2=rgbdat2.data;
var rgbd3=rgbdat3.data;
var rgbd4=rgbdat4.data;
var imgg=imgData1.data;
var i;
let l=h*ww;
let la=h*ww*4;
var pointa=la*2.0;
var pointb=la*3.0;
var pointc=la*4.0;
let $H=Module.HEAPF32.buffer;
var agavF=new Float32Array($H,pointa,la);
var agavNF=new Float32Array($H,pointb,la);
agavF.set(imgData1.data);
Module.ccall("nano",null,["Number","Number","Number"],[la,pointa,pointc]);
var agav=new Float32Array($H,pointc,1);
console.log(agav[0]);
var rgb=(imgg[i]*0.2126)+(imgg[i+1]*0.7152)+(imgg[i+2]*0.0722);
var lightDark=128+((Math.abs(agav[0]-128))/2);
var diff=(agav[0]/255)*16;
// rgb=rgb+lightDark/2;
 
 //  but run past a lighter pixel if the avg is darker 
 //  i.e.  pixel is 110/255 or 0.431  ->  avg is 77/255 or 0.302
 //  so the pixel that should be checked would be darker by an amount 0.302 < 0.500
 //  |0|-|64|-|128|-|192|-|255|
 //  
 //  or pixel is 110/255 or 0.431  ->  avg is 177/255 or 0.695
 //  so the pixel that should be checked would be lighter  0.500 < 0.695   
 //
 //  0.302 < 0.500 is 40% of total B->W range
 //  0.302 < 0.500 is 20% of possible B->W difference
//
 // perhaps 0-32 difference possible +/-
 // perhaps half 0-16 difference possible +/-
 //
 //  new idea - have the average have effect on each color's gradient 
 //  range to the next color giving further color depth as well as 
 // keeping a darker range from having few different colors of gradient
 //
 

                      //  circle 1
                      //  non-rotating 
                       //  bottom zindex
                    // black / white
for(i=0;i<(ww*h*4);i=i+4){
if(rgb>126){
if(rgb>209){    // orange
rgbd1[i]=255;
rgbd1[i+1]=128+diff;
rgbd1[i+2]=0;
rgbd1[i+3]=0;
}
else if(rgb>193){   // red
rgbd1[i]=255-diff;
rgbd1[i+1]=0;
rgbd1[i+2]=0;
rgbd1[i+3]=0;
}else if(rgb>177){   // light blue
rgbd1[i]=0;
rgbd1[i+1]=255-diff;
rgbd1[i+2]=255;
rgbd1[i+3]=0;
}else if(rgb>161){  //  blue
rgbd1[i]=0;
rgbd1[i+1]=0;
rgbd1[i+2]=255-diff;
rgbd1[i+3]=0;
}else if(rgb>145){  // green
rgbd1[i]=0;
rgbd1[i+1]=255-diff;
rgbd1[i+2]=0;
rgbd1[i+3]=0;
}else if(rgb>128){  // yellow
rgbd1[i]=255;
rgbd1[i+1]=255-diff;
rgbd1[i+2]=0;
rgbd1[i+3]=0;
}
}else{
rgbd1[i]=255;
rgbd1[i+1]=255;
rgbd1[i+2]=255;
rgbd1[i+3]=255-((rgb-128)*diff);
}
}
ctx1.putImageData(rgbdat1,0,0);

              //        circle 2
             //    speed 1
             //    topmost
             //    yellow/green
for(i=0;i<(ww*h*4);i=i+4){
if(rgb>126){
if(rgb>209){    // orange
rgbd3[i]=255;
rgbd3[i+1]=128+diff;
rgbd3[i+2]=0;
rgbd3[i+3]=0;
}
else if(rgb>193){   // red
rgbd3[i]=255-diff;
rgbd3[i+1]=0;
rgbd3[i+2]=0;
rgbd3[i+3]=0;
}else if(rgb>177){   // light blue
rgbd3[i]=0;
rgbd3[i+1]=255-diff;
rgbd3[i+2]=255;
rgbd3[i+3]=0;
}else if(rgb>145){  // green
rgbd2[i]=0;
rgbd2[i+1]=255-diff;
rgbd2[i+2]=0;
rgbd2[i+3]=255-((rgb-145)*diff);
}else if(rgb>128){  // yellow
rgbd2[i]=255;
rgbd2[i+1]=255-diff;
rgbd2[i+2]=0;
rgbd2[i+3]=255-((rgb-128)*diff);
}
}else{
rgbd2[i]=0+diff;
rgbd2[i+1]=0+diff;
rgbd2[i+2]=0+diff;
rgbd2[i+3]=0;
}
}
ctx2.putImageData(rgbdat2,0,0);
 
         //        circle 3
             //    speed 2
             //    middle zindex
             //    orange/red
for(i=0;i<(ww*h*4);i=i+4){
if(rgb>126){
if(rgb>209){    // orange
rgbd3[i]=255;
rgbd3[i+1]=128+diff;
rgbd3[i+2]=0;
rgbd3[i+3]=255-((rgb-209)*diff);
}
else if(rgb>193){   // red
rgbd3[i]=255-diff;
rgbd3[i+1]=0;
rgbd3[i+2]=0;
rgbd3[i+3]=255-((rgb-193)*diff);
}else if(rgb>177){   // light blue
rgbd3[i]=0;
rgbd3[i+1]=255-diff;
rgbd3[i+2]=255;
rgbd3[i+3]=0;
}else if(rgb>161){  //  blue
rgbd3[i]=0;
rgbd3[i+1]=0;
rgbd3[i+2]=255-diff;
rgbd3[i+3]=0;
}else if(rgb>145){  // green
rgbd3[i]=0;
rgbd3[i+1]=255-diff;
rgbd3[i+2]=0;
rgbd3[i+3]=0;
}else if(rgb>128){  // yellow
rgbd3[i]=255;
rgbd3[i+1]=255-diff;
rgbd3[i+2]=0;
rgbd3[i+3]=0;
}
}else{
rgbd3[i]=0+diff;
rgbd3[i+1]=0+diff;
rgbd3[i+2]=0+diff;
rgbd3[i+3]=0;
}
}
// agavF.set(rgbdat3.data);
var ang=45;
// Module.ccall("rotat",null,["Number","Number","Number","Number","Number"],[ang,ww,h,pointa,pointb]);
ctx3.putImageData(rgbdat3,0,0);
for(i=0;i<(ww*h*4);i=i+4){

        //        circle 4
             //    speed 3
             //    bottom zindex
             //    blue/light blue
if(rgb>126){
if(rgb>209){    // orange
rgbd4[i]=255;
rgbd4[i+1]=128+diff;
rgbd4[i+2]=0;
rgbd4[i+3]=0;
}
else if(rgb>193){   // red
rgbd4[i]=255-diff;
rgbd4[i+1]=0;
rgbd4[i+2]=0;
rgbd4[i+3]=0;
}else if(rgb>177){   // light blue
rgbd4[i]=0;
rgbd4[i+1]=255-diff;
rgbd4[i+2]=255;
rgbd4[i+3]=255-((rgb-177)*diff);
}else if(rgb>161){  //  blue
rgbd4[i]=0;
rgbd4[i+1]=0;
rgbd4[i+2]=255-diff;
rgbd4[i+3]=255-((rgb-161)*diff);
}else if(rgb>145){  // green
rgbd4[i]=0;
rgbd4[i+1]=255-diff;
rgbd4[i+2]=0;
rgbd4[i+3]=0;
}else if(rgb>128){  // yellow
rgbd4[i]=255;
rgbd4[i+1]=255-diff;
rgbd4[i+2]=0;
rgbd4[i+3]=0;
}
}else{
rgbd4[i]=0+diff;
rgbd4[i+1]=0+diff;
rgbd4[i+2]=0+diff;
rgbd4[i+3]=0;
}
}
ctx4.putImageData(rgbdat4,0,0);

function Ra(){
flP.setAttribute("style","transform:scaleX(1)");
flP.setAttribute("style","transform:scaleY(1)");
}
function Rb(){
flP.setAttribute("style","transform: scaleX(-1)");
flP.setAttribute("style","transform: scaleY(-1)");
}
function rrra(rta){
cnP2.setAttribute("style","transform: rotate("+rta+"deg)");
}
function rrrb(rtb){
cnP3.setAttribute("style","transform: rotate("+rtb+"deg)");
}
function rrrc(rtc){
cnP4.setAttribute("style","transform: rotate("+rtc+"deg)");
}

knb=document.getElementById("rra");
kna=document.getElementById("mainr");
knc=document.getElementById("rrb");
knd=document.getElementById("rrc");
knbb=document.getElementById("rrab");
kncb=document.getElementById("rrbb");
kndb=document.getElementById("rrcb");
rate=(kna.innerHTML);
rott=0;
rottb=0;
rottc=0;
let dur=document.getElementById("temptime").innerHTML/10;
let dsd=false;
function $rn(){
if(dsd){
return;
}
// Ra();
if((rott-knd.innerHTML)<0){
rott=(rott+360-knd.innerHTML);
}else{
rott=rott-knd.innerHTML;
}
rrra(rott);
if((rottb-knc.innerHTML)<0){
rottb=(rottb+360-knc.innerHTML);
}else{
rottb=(rottb-knc.innerHTML);
}
setTimeout(function(){
setTimeout(function(){
setTimeout(function(){
// Rb();
rrrb(rottb);
},rate*2);
if((rottc+knb.innerHTML)>360){
rottc=((rottc+knb.innerHTML)-360);
}else{
rottc=(rottc+knb.innerHTML);
}
rrrc(rottc);
},rate*3);
$rn();
},rate*4);
}
$rn();
document.getElementById("di").onclick=function(){
dsd=true;
set();
};
return()=>{
dsd=true;
}
}
});

int main(){

ma();
emsc();
 
return 1;
}
