#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <SDL2/SDL.h>

using namespace std;

//  SDL
SDL_AudioDeviceID dev;
struct{SDL_AudioSpec spec;Uint8* snd;Uint32 slen;int pos;}wave;
static GLfloat mouseX;
static GLfloat mouseY;
static GLfloat cMouseX;
static GLfloat cMouseY;
static GLfloat x;
static GLfloat y;
static EM_BOOL mouseLPressed;
static GLfloat Size;
static EM_BOOL clickLoc;
static GLfloat mX,mY;
static GLsizei i;
static GLfloat fps;
static GLfloat timeSpeed;
static EGLint config_size,major,minor,attrib_position;
EGLConfig eglconfig=NULL;
static EmscriptenWebGLContextAttributes attr;
static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
static EMSCRIPTEN_RESULT ret;

long length=0;

static EM_BOOL mouse_callback(int eventType,const EmscriptenMouseEvent *e,void *userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
mouseLPressed=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
mouseLPressed=false;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return 0;
}

void avgFrm(int F,int leng,float *dat,float *aLoc){
static float max=0.0;
static float min=1.0;
static float sum=0.0;
static float avgSum=0.0;
static float minSum=0.0;
static float maxSum=0.0;
for (int i=0;i<leng;i++){
sum+=dat[i];
if(max<dat[i]){max=dat[i];}
if(min>dat[i]&&dat[i]>0){min=dat[i];}
}
sum=sum/leng;
aLoc[F]=sum;
aLoc[F+100]=min;
aLoc[F+200]=max;
for(int i=33;i<65;i++){
avgSum+=aLoc[i];
}
aLoc[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aLoc[i+100];
}
aLoc[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aLoc[i+200];
}
aLoc[200]=maxSum/32;
}

void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
}}
void qu(int rc){
SDL_Quit();
exit(rc);
}
void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);
if(!dev){
SDL_FreeWAV(wave.snd);
qu(2);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
}
Uint8* wptr;
int lft;
void SDLCALL bfr(void *unused,Uint8* stm,int len){
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
void plt(){
cls_aud();
char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_Quit();
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu(1);
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){
qu(1);
}
wave.pos=0;
wave.spec.callback=bfr;
opn_aud();
}

EM_JS(void,ma,(),{
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
vv=document.getElementById("mv");
let $H=Module.HEAPF32.buffer;
var la=h$*h$*4;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
var sz=(h$*h$)/8;
var avag=0.750;
var min=1.0;
var max=0.0;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var bcanvas=document.getElementById("bcanvas");
var contx=bcanvas.getContext('webgl2',{antialias:false,alpha:true,imageSmoothingEnabled:false,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
var g=new GPU({canvas:bcanvas,webGl:contx});
var g2=new GPU();
const glslAve=`float Ave(float a,float b,float c) {return (a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g) {return (1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25)));}`;
const glslAveg=`float Aveg(float a,float b) {return (1.0-(((a)-(b))*((a)*(1.0/(1.0-b))))) ;}`;

g.addNativeFunction('Ave', glslAve, { returnType: 'Number' });
g.addNativeFunction('Alphe', glslAlphe, { returnType: 'Number' });
g.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Aveg', glslAveg, { returnType: 'Number' });
g2.addNativeFunction('Ave', glslAve, { returnType: 'Number' });

var R=g2.createKernel(function(tv){
var Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setDynamicOutput(true).setArgumentTypes(['HTMLVideo']).setFixIntegerDivisionAccuracy(false).setOutput([sz]);

var t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
var av$=Ave(P[0],P[1],P[2]);
return[P[0],P[1],P[2],1.0];
}).setTactic("precision").setPipeline(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setFixIntegerDivisionAccuracy(false).setOutput([w$,h$]);

var r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
var $fmax=this.constants.fmax;
var $fmin=this.constants.fmin;
var $amax=this.constants.amax;
var $amin=this.constants.amin;
var $favg=this.constants.favg;
var $aavg=this.constants.aavg;
var alph=Alphe($amax,$amin,$fmax,$fmin,$favg,$aavg,p[3]);
var Min=(4.0*(($amax-($aavg-$amin))/2.0));

// var Min=(4.0*(($amax-$aavg)/2.0))+(($fmin+$amin)/2.0);
// var Min=(4.0*(($amax-$amin-$aavg)/2.0));
var ouT=Math.max(Min,alph);
var aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],1.0);
}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setFixIntegerDivisionAccuracy(false).setOutput([w$,h$]);

var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);

R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float32Array($H,pointb,sz);
let $F=1;
let $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});

var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
eval("$"+j+".set($$1);");
}

let d=S();if(d)d();d=S();function S(){
var w$=parseInt(document.getElementById('wid').innerHTML,10);
var h$=parseInt(document.getElementById('hig').innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
var l=w$*h$*16;
var la=h$*h$*4;
var al=w$*h$*8;
var sz=(h$*h$)/8;
var pointa=77*la;
var agav=new Float32Array($H,pointa,300);
R.setOutput([sz]);

for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
}
var pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;

function M(){
var vv=document.getElementById("mv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){return;}
for(i=64;i>0;i--){
var loca=$F+1;if(loca>64){loca=1;}
var locb=$Bu+1;if(locb>64){locb=1;}
eval("if ($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
}
var $bb=R(vv);
$B.set($bb,0,sz);
setTimeout(function(){
var pointb=66*la;
Module.ccall('nano',null,['Number'],['Number'],['Number'],['Number'],[$F],[sz],[pointb],[pointa]);
M();
},16.6);
}
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};
}
})

extern "C" {

void pl(){
plt();
}

void b3(){
ma();
}

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}

}

int main(){
EM_ASM({
FS.mkdir('/snd');
FS.mkdir('/shader');
});
return 1;
}
