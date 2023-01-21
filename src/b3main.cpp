#include "../include/b3main.hpp"

void avgFrm(short int Fnum,int leng,float * ptr,float * aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
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

extern "C" {

void nano(short int Fnum,int leng,float * ptr,float * aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,b3_main,(),{

"use strict";
var lvv=document.getElementById("ldv");
var vv=document.getElementById("mv");
var intervalLoop=null;
var f;
var loopLoop;
var sh4d=true;
var a,b;
var stp=document.getElementById("mv").currentTime;
var loopPart=(stp-(Math.floor(stp))+1.0)*2;
var mmvv=document.getElementById("mv");
var paus;
function stpBackForth(){
loopLoop=false;
}

function doKey(e){
if(e.code=='Space'){
e.preventDefault();
if(paus==true){
paus=false;
};
if(paus==false){
paus=true;
};
};
if (e.code=='KeyZ'){
mmvv=document.getElementById("mv");
mmvv.pause();
stp=document.getElementById("mv").currentTime;
loopPart=(stp-(Math.floor(stp))+1.0)*2;
// console.log(stp);
loopLoop=true;
f=false;
// backForth(stp);
};
if(e.code=='KeyX'){
loopLoop=false;
// stpBackForth();
vv.play();
};
if(e.code=='KeyA'){
sh4d=true;
};
if(e.code=='KeyS'){
sh4d=false;
};
}

const pnnl=document.body;
pnnl.addEventListener('keydown',doKey);
// var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
// var h$=vv.videoHeight;
var w$=vv.videoWidth;
const $H=Module.HEAPF64.buffer;
var la=h$*h$*8;
var pointa=77*la;
var agav=new Float64Array($H,pointa,300);
var sz=(h$*w$)/8;
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var bcanvas=document.getElementById("bcanvas");
var gl=bcanvas.getContext("webgl2",{
colorType:'float64',
preferLowPowerToHighPerformance:false,
precision:'highp',
logarithmicDepthBuffer:true,
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
imageSmoothingEnabled:true,
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

const g=new GPU({mode:'webgl2',canvas:bcanvas,webGl:gl});
const g2=new GPU({mode:'webgl2'});  //  A / B    'webgl2' / 'gpu' / 'cpu'
const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((g-f)*((g)*(g-f)))))))/3.0);}`;
const glslAveg=`float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}`;
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
const Pa=tv[this.thread.y][this.thread.x*4];
return Ave(Pa[0]*0.8,Pa[1],Pa[2]*1.2);
}).setTactic("speed").setDynamicOutput(true).setOutput([sz]);
const t=g.createKernel(function(v){
const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
const av$=Ave(P[0]*0.8,P[1],P[2]*1.2);
return[P[0],P[1],P[2],av$];
}).setTactic("precision").setPipeline(true).setPrecision("single").setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
const r=g.createKernel(function(f){
const p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
const $amax=this.constants.amax;
const $amin=this.constants.amin;
const $aavg=this.constants.aavg;
const alph=Alphe($amax,$amin,$aavg,p[3]);
const Min=(4.0*(($amax-($aavg-$amin))/2.0));
const ouT=Math.max(Min,alph);
const aveg=Aveg(p[3],ouT);
this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setOutput([w$,h$]);
gl.getExtension('WEBGL_color_buffer_float');
gl.getExtension('WEBGL_color_buffer_half_float');
gl.getExtension('GL_OES_texture_float_linear');
gl.getExtension('GL_OES_texture_half_float_linear');
gl.getExtension('GL_EXT_float_blend');
gl.getExtension('GL_EXT_frag_depth');
gl.getExtension('GL_EXT_shader_texture_lod');
gl.getExtension('GL_EXT_sRGB');
gl.getExtension('GL_EXT_blend_minmax');
gl.getExtension('ANGLE_instanced_arrays');
// gl.getExtension('EXT_disjoint_timer_query');
gl.getExtension('GL_EXT_clip_cull_distance');
// gl.getExtension('EXT_disjoint_timer_query_webgl2');
gl.getExtension('KHR_parallel_shader_compile');
gl.getExtension('GL_OES_draw_buffers_indexed');
gl.getExtension('GL_OES_element_index_uint');
gl.getExtension('GL_OES_fbo_render_mipmap');
gl.getExtension('GL_OES_standard_derivatives');
gl.getExtension('GL_OES_vertex_array_object');
gl.getExtension('WEBGL_blend_equation_advanced_coherent');
gl.getExtension('WEBGL_depth_texture');
gl.getExtension('WEBGL_draw_buffers');
gl.getExtension('WEBGL_provoking_vertex');
gl.getExtension('EXT_framebuffer_sRGB');
gl.getExtension('OES_depth32');
gl.getExtension('GL_OES_fixed_point');
gl.getExtension('GL_OES_shader_multisample_interpolation');
gl.getExtension('WEBGL_webcodecs_video_frame');
gl.getExtension('GL_OES_single_precision');
// gl.getExtension('GL_EXT_texture_shadow_lod');
gl.getExtension('EGL_NV_memory_attachment');
gl.getExtension('EGL_NV_depth_nonlinear');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3');
gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
gl.getExtension('GL_ARB_multisample');

// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
gl.blendColor(1.0,1.0,1.0,1.0);
gl.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gl.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gl.unpackColorSpace='display-p3';  // very slow
 
 gl.drawingBufferColorSpace='display-p3';
gl.disable(gl.DITHER);

// w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
// var h$=vv.videoHeight;
var w$=vv.videoWidth;
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
var pointb=77*la;
var $B=new Float64Array($H,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);$"+j+".set($$1,0,la);");
}
var d=S();if(d)d();d=S();function S(){
    
gl.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gl.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
 
// w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
// var h$=vv.videoHeight;
var w$=vv.videoWidth;
var blank$=Math.max((((w$-h$)*0)/2.0),0);
var nblank$=Math.max((((h$-w$)*0)/2.0),0);
la=h$*h$*8;
sz=(h$*w$)/8;
pointa=77*la;
var agav=new Float64Array($H,pointa,300);
R.setOutput([sz]);
for(var i=0;i<65;i++){
var j=i+1;
eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H,point"+j+",la);");
}
pointb=66*la;
var $B=new Float64Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.getElementById("mv");
lvv=document.getElementById("ldv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]});
if(T){
return;
};
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
eval("if($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";}");
}
pointb=66*la;
setTimeout(function(){
M();
if(loopLoop==true){
if(f==true){
if(document.getElementById("mv").currentTime>(stp-loopPart)){
mmvv.currentTime-=0.013333;
}else{
f=false;
if(document.getElementById("mv").currentTime<(stp)){
document.getElementById("mv").currentTime+=0.013333;
}else{
f=true;
}}} /*
if(f==false){
if(document.getElementById("mv").currentTime<(stp)){
document.getElementById("mv").currentTime+=0.013333;
}else{
f=true;
if(document.getElementById("mv").currentTime>(stp-loopPart)){
document.getElementById("mv").currentTime-=0.013333;
}else{
f=false;
}}
} */
}else{
// if($F%4!=0){
var $bb=R(vv);$B.set($bb,0,sz);
Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
// };
// };
Module.ccall("clr",null,["Number","Number","Number"],[agav[201],agav[101],agav[1]]);
// if($F%2==0){
};
if(sh4d==true){
Module.ccall("frm");
};
},13.333333)}
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

EM_JS(void,js_main,(),{

"use strict";

function highResStart(){
document.getElementById('scanvas').height=window.innerHeight*2;
document.getElementById('scanvas').width=window.innerHeight*2;
document.getElementById('scanvas').style.height=(window.innerHeight*2)+'px';
document.getElementById('scanvas').style.width=(window.innerHeight*2)+'px';
document.getElementById('pmhig').innerHTML=window.innerHeight*2;
setTimeout(function(){
Module.ccall('b3_egl');
},350);
setTimeout(function(){
Module.ccall('str');
},650);
setTimeout(function(){
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').style.height=window.innerHeight+'px';
document.getElementById('scanvas').style.width=window.innerHeight+'px';
document.getElementById('pmhig').innerHTML=window.innerHeight;
},850);
setTimeout(function(){
Module.ccall('b3');
},1250);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
// const bz=new BroadcastChannel('bez');
// bz.postMessage({data:222});
},1550);
}

function normalResStart(){
setTimeout(function(){
Module.ccall('b3_egl');
},250);
setTimeout(function(){
Module.ccall('b3');
},450);
setTimeout(function(){
Module.ccall('str');
},750);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
// const bz=new BroadcastChannel('bez');
// bz.postMessage({data:222});
},950);
}
  
const fll=new BroadcastChannel('file');
const shutDown=new BroadcastChannel('shutDown');

fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
Module.ccall('pl');
setTimeout(function(){
shutDown.postMessage({data:222});
},450);
});

var $sngs=[];
var $vids=[];
var $shds=[];

function sngs(xml){
const nparser=new DOMParser();
const htmlDocs=nparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocs.getElementsByTagName('pre')[0].getElementsByTagName('a');
$sngs[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$sngs[i]=Self+'songs/'+txxt;
}}

function vids(xml){
const vparser=new DOMParser();
const htmlDocv=vparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocv.getElementsByTagName('pre')[0].getElementsByTagName('a');
$vids[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$vids[i]=Self+'video/'+txxt;
}}

function shds(xml){
const sparser=new DOMParser();
const htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$shds[i+1]='https://glsl.1ink.us/shaders/'+txxt;
};
var randShade=Math.random();
randShade=Math.floor($shds[0]*randShade)+5;
document.getElementById('path').innerHTML=$shds[randShade];
var pth=document.getElementById('path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
ff.onload=function(oEvent){
const sarrayBuffer=ff.response;
if(sarrayBuffer){
const sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader1.toy',sfil);
setTimeout(function(){
  
  normalResStart();
  
},150);
};};
ff.send(null);
}

function scanSongs(){
const nxhttp=new XMLHttpRequest();
nxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
sngs(this);
}};
nxhttp.open('GET','songs/',true);
nxhttp.send();
}

function scanVideos(){
const fxhttp=new XMLHttpRequest();
fxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
vids(this);
}};
fxhttp.open('GET','video/',true);
fxhttp.send();
}

function scanShaders(){
const dxhttp=new XMLHttpRequest();
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
shds(this);
}};
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
}

scanVideos();
scanShaders();
scanSongs();

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
document.getElementById('acanvas').height=parseInt(window.innerHeight,10);
document.getElementById('acanvas').width=parseInt(window.innerHeight,10);
document.getElementById('bcanvas').height=parseInt(window.innerHeight,10);
document.getElementById('bcanvas').width=parseInt(window.innerHeight,10);


function snd(){
const randSong=Math.floor(($sngs[0]-5)*Math.random());
const songSrc=$sngs[randSong+5];
document.getElementById('track').src=songSrc;
const sng=new BroadcastChannel('sng');
sng.postMessage({data:songSrc});
}

document.getElementById('musicBtn').addEventListener('click',function(){
window.open('./flac');
setTimeout(function(){
snd();
},1650);
});
  
});

EM_JS(void,js_page,(),{

var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;
 
var $iwid=document.getElementById('iwid');

const mV=document.getElementById('mv');
const loadV=document.getElementById('ldv');

mV.load();
loadV.load();

const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:16.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){slt=tem.innerHTML;},8);},13);});
var adr='./intro.mp4';
wi=1920;
he=1080;
var hii=window.innerHeight;
document.getElementById('ihid').innerHTML=hii;
r$=hii/he;
$w=wi*r$;
let $ihigB=document.getElementById('ihid');
let $ihig=document.getElementById('ihig');
$hg=hii+'px';
$ihig.innerHTML=parseInt(window.innerHeight,10);
$iwid.innerHTML=parseInt($w,10);
document.getElementById('wrap').style.lineheight=$hg;
document.getElementById('wrap').style.pointerEvents='auto';
document.getElementById('isrc').innerHTML=adr;

mV.play();
var lockVid=0;

function spKey(e){
if(e.code=='Space'){
e.preventDefault();
if(lockVid==0){lockVid=1;};
if(lockVid==1){lockVid=0;};
};
if(e.code=='KeyZ'){lockVid=1;};
if(e.code=='KeyX'){lockVid=0;};
}

let pnnl=document.body;
pnnl.addEventListener('keydown',spKey);

function loada(){
if(lockVid!=1){
  
// document.getElementById('wid').innerHTML=1920;
// document.getElementById('hig').innerHTML=1080;
  
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);

document.getElementById('ldv').addEventListener('canplay',function(){
document.getElementById('ldv').width=document.getElementById('ldv').videoWidth;
document.getElementById('ldv').height=document.getElementById('ldv').videoHeight;
document.getElementById('wid').innerHTML=document.getElementById('ldv').videoWidth;
document.getElementById('hig').innerHTML=document.getElementById('ldv').videoHeight;
  
var $sc=this.duration;
var mic=Math.round($sc*1000000);
$pt=Math.random()*mic;
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.getElementById('idur').innerHTML=mic/1000000;
document.getElementById('itim').innerHTML=$pt;
});
var vide=document.querySelectorAll('video');
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
hii=window.innerHeight;
document.getElementById('ihid').innerHTML=hii;
$lt=Math.round(tem.innerHTML);
var $ldt=document.getElementById('tim').innerHTML;
$ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var rnum=Math.floor((Math.random()*($vids[0]-5))+5);
document.getElementById('isrc').innerHTML=$vids[rnum];
$h=window.innerHeight;
he=document.getElementById('hig').innerHTML;
wi=document.getElementById('wid').innerHTML;
r$=he/$h;
$w=wi/r$;
hii=$ihigB.innerHTML;
var $hi=$h-hii;
if($hi>1){$h=$ihigB.innerHTML;$ihig.innerHTML=$h;$r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;};
$hg=$h+'px';
window.scroll(0,0);
mv=vide[0].id;
lo=vide[1].id;
vide[0].id=lo;
vide[1].id=mv;
document.getElementById('mv').play();
$iwid.innerHTML=parseInt($w,10);
$ihig.innerHTML=parseInt(window.innerHeight,10);
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('circle').height=parseInt(window.innerHeight,10);
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('ldv').src=document.getElementById('isrc').innerHTML;
document.getElementById('ldv').load();
document.getElementById('ldv').currentTime=document.getElementById('itim').innerHTML;
// document.getElementById('ldv').height=document.innerHeight;
// document.getElementById('wid').innerHTML=document.getElementById('mv').videoWidth;
// document.getElementById('hig').innerHTML=document.getElementById('mv').videoHeight;
document.getElementById('di').click();
};
setTimeout(function(){
loada();
},$ldt);
}
loada();
  
});

extern "C" {
 
void b3(){
b3_main();
return;
}

}
   
int main(){
  
EM_ASM({
"use strict";
FS.mkdir("/snd");
FS.mkdir("/shader");
});

js_main();
js_page();

return 1;

}
