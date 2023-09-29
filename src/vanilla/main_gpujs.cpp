#include "../../include/vanilla/main_gpujs.hpp"

EM_JS(void,setup_js,(),{
  
"use strict";

window.scroll(0,0);
let Shigh=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
Shigh.innerHTML=winSize;
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
scanvas.style.zIndex='3100';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(7,233,7,255)';
document.getElementById("contain1").appendChild(scanvas);
var vv=document.getElementById("mv");
document.getElementById("wid").innerHTML=winSize;
document.getElementById("hig").innerHTML=winSize;
var wS=parseInt(document.getElementById("wid").innerHTML,10);
var hS=parseInt(document.getElementById("hig").innerHTML,10);
const SzH=Module.HEAPU8.buffer;
var la=hS*hS;
const bcanvas=document.getElementById("zcanvas");
const gl=bcanvas.getContext("webgl2",{preferLowPowerToHighPerformance:false,precision:'highp',logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:false,stencil:true,imageSmoothingEnabled:true,preserveDrawingBuffer:true,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true,willReadFrequently:true,majorVersion:2,minorVersion:0});
const g=new GPUX({canvas:bcanvas,webGl:gl});
const t=g.createKernel(function(v){
const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
return[P[0],P[1],P[2],P[3]];
}).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([wS,hS]);
const r=g.createKernel(function(f){
const p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
this.color(p[0],p[1],p[2],p[3]);
}).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([wS,hS]);
wS=parseInt(document.getElementById("wid").innerHTML,10);
hS=parseInt(document.getElementById("hig").innerHTML,10);
vv=document.getElementById("mv");
var blankS=Math.max((((wS-hS)*1)/2),0);
var nblankS=Math.max((((hS-wS)*1)/2),0);
la=hS*hS;
for(var i=0;i<33;i++){
var j=i+1;
var memr=(Math.floor((i*la)/65536)+1)*65536;
var mem=((Math.floor(memr/4))+1)*4;
eval("var point"+j+"=mem;let bfS"+j+"=new Uint8Array(SzH,point"+j+",memr);");  //
};
var SF=1;
var SBu=17;
r.setConstants({nblnk:nblankS,blnk:blankS});
t.setConstants({nblnk:nblankS,blnk:blankS});
  
var d=S();if(d)d();d=S();function S(){
document.getElementById("mv").play();
var SS1=t(vv);
for (i=0;i<33;i++){
var j=i+1;
var memr=(Math.floor((j*la)/65536)+1)*65536;
var mem=((Math.floor(memr/4))+1)*4;
eval("var point"+j+"=mem;bfS"+j+"=new Uint8Array(SzH,point"+j+",memr);bfS"+j+".set(SS1);");
};
wS=parseInt(document.getElementById("wid").innerHTML,10);
hS=parseInt(document.getElementById("hig").innerHTML,10);
var blankS=Math.max((((wS-hS)*0)/2),0);
var nblankS=Math.max((((hS-wS)*0)/2),0);
// la=hS*hS;
for(var i=0;i<33;i++){
var j=i+1;
var memr=(Math.floor((j*la)/65536)+1)*65536;
var mem=((Math.floor(memr/4))+1)*4;
eval("var point"+j+"=mem;bfS"+j+"=new Uint8Array(SzH,point"+j+",memr);");  //
};
r.setConstants({nblnk:nblankS,blnk:blankS});
t.setConstants({nblnk:nblankS,blnk:blankS});
var T=false;
  
function M(){
vv=document.getElementById("mv");
t.setConstants({nblnk:nblankS,blnk:blankS});
r.setConstants({nblnk:nblankS,blnk:blankS});
if(T){return;}
for(var i=32;i>0;i--){
var loca=SF+1;
if(loca>32){loca=0;}
var locb=SBu+1;
if(locb>32){locb=0;}
eval("if (SF=="+i+"){var Sr"+i+"=t(bfS"+i+");r(Sr"+i+");}");
eval("if (SF=="+i+"){var SS"+SBu+"=t(vv);bfS"+SBu+".set(SS"+SBu+");SF="+loca+";SBu="+locb+";}");
};
setTimeout(function(){
M();
},16.66)}
  
M();
  
document.getElementById("di").onclick=function(){
T=true;
S();
};
return()=>{
T=true;
};}

});

extern "C"{

void gpu_js{
setup_js();
}

}

EM_JS(void,js_main,(),{
// FS.mkdir('/video');

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var Llt=tem.innerHTML;
function grabLlt(){
Llt=Math.round(Llt);
}
Llt=tem.innerHTML;
grabLlt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grabLlt();
slt=Llt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grabLlt();
slt=(Llt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
Sll=tsl.getValue();
Sll=Sll*100;
Sll=Math.round(Sll);
Sll=Sll/100;Sll=(Sll*1000);
tem.innerHTML=Sll;
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
