#include "../../include/vanilla/main_gpujs.hpp"

extern "C"{

}

EM_JS(void,js_main,(),{
// FS.mkdir('/video');

"use strict";

function normalResStart(){
window.scroll(0,0);
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
const scanvas=document.createElement('canvas');
scanvas.id='zcanvas';
scanvas.imageRendering='auto';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='auto';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='3300';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(7,233,7,255)';
document.getElementById("contain1").appendChild(scanvas);
/*
  const contxVars={preferLowPowerToHighPerformance:false,logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:true,stencil:true,preserveDrawingBuffer:true,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',antialias:false};
const context = scanvas.getContext('webgl2',contxVars);
context.getExtension('GL_ALL_EXTENSIONS');
context.getExtension('GL_KHR_no_error');
context.getExtension('GL_REGAL_enable');
context.getExtension('GL_ARB_spirv_extensions');
context.getExtension('GL_ARB_ES2_compatibility');
context.getExtension('GL_ARB_direct_state_access');
*/
var vv=document.getElementById("mv");
document.getElementById("wid").innerHTML=winSize;
document.getElementById("hig").innerHTML=winSize;
var w$=parseInt(document.getElementById("wid").innerHTML,10);
var h$=parseInt(document.getElementById("hig").innerHTML,10);
const $H=Module.HEAPF32.buffer;
var la=h$*h$;
const bcanvas=document.getElementById("zcanvas");
const gl=bcanvas.getContext("webgl2",{colorType:'float32',preferLowPowerToHighPerformance:false,precision:'highp',logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:false,stencil:true,imageSmoothingEnabled:true,preserveDrawingBuffer:true,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true,willReadFrequently:true,majorVersion:2,minorVersion:0});
const g=new GPUX({canvas:bcanvas,webGl:gl});
const t=g.createKernel(function(v){
const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
return[P[0],P[1],P[2],P[3]];
}).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
const r=g.createKernel(function(f){
const p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
this.color(p[0],p[1],p[2],p[3]);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blank$=Math.max((((w$-h$)*1)/2),0);
var nblank$=Math.max((((h$-w$)*1)/2),0);
// la=h$*h$;
for(var i=0;i<65;i++){
var j=i+1;
var mem=(Math.floor((j*la)/65536)+1)*65536;
eval("var point"+j+"=mem;var $"+j+"=new Float32Array($H,point"+j+",la);");
};
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$});
t.setConstants({nblnk:nblank$,blnk:blank$});
var $$1=t(vv);
for (i=0;i<65;i++){
var j=i+1;
var mem=(Math.floor((j*la)/65536)+1)*65536;
eval("var point"+j+"=mem;var $"+j+"=new Float32Array($H,point"+j+",la);$"+j+".set($$1);");
};
var d=S();if(d)d();d=S();function S(){
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var blank$=Math.max((((w$-h$)*0)/2),0);
var nblank$=Math.max((((h$-w$)*0)/2),0);
// la=h$*h$;
for(var i=0;i<65;i++){
var j=i+1;
var mem=(Math.floor((j*la)/65536)+1)*65536;
eval("var point"+j+"=mem;var $"+j+"=new Float32Array($H,point"+j+",la);");
};
pointb=66*la;
var $B=new Float32Array($H,pointb,sz);
r.setConstants({nblnk:nblank$,blnk:blank$});
t.setConstants({nblnk:nblank$,blnk:blank$});
var T=false;
function M(){
vv=document.getElementById("mv");
t.setConstants({nblnk:nblank$,blnk:blank$});
r.setConstants({nblnk:nblank$,blnk:blank$});
if(T){return;}
for(var i=64;i>0;i--){
var loca=$F+1;
if(loca>64){loca=1;}
var locb=$Bu+1;
if(locb>64){locb=1;}
eval("if ($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");}");
eval("if ($F=="+i+"){var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
};
if($F%4==0){
var $bb=R(vv);
};
setTimeout(function(){
M();
if(loopLoop==true){
if(f==true){
if(vv.currentTime>a){
vv.currentTime-=0.016;
}else{
f=false;
if(vv.currentTime<b){
vv.currentTime+=0.016;
}else{
f=true;
}}};
if(f==false){
if(vv.currentTime<b){
vv.currentTime+=0.016;
}else{
f=true;
if(vv.currentTime>a){
vv.currentTime-=0.016;
}else{
f=false;
}}}};
},16.66)};
M();
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
}};
}
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt=tem.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16)
;});
document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});
setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);

});

int main(void){
js_main();
return 0;
}
