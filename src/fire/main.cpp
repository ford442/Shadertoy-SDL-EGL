#include "../../include/fire/main.hpp"

EM_JS(void,fl,(),{
window.scroll(0,0);
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
const scanvas=document.createElement('canvas');
scanvas.id='acanvas';
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
scanvas.style.backgroundColor='rgba(255,255,255,0)';
document.getElementById("contain1").appendChild(scanvas);
const contxVars={colorType:'float64',precision:'highp',preferLowPowerToHighPerformance:false,logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:true,stencil:true,preserveDrawingBuffer:true,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',antialias:false};
const context=scanvas.getContext('webgl2',contxVars);
context.getExtension('GL_ALL_EXTENSIONS');
context.getExtension('GL_KHR_no_error');
context.getExtension('GL_REGAL_enable');
context.getExtension('GL_ARB_spirv_extensions');
context.getExtension('GL_ARB_ES2_compatibility');
context.getExtension('GL_ARB_direct_state_access');
// context.disable(gl.DITHER);
// context.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
// context.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
const gpu=new GPUX({mode:'gpu',webGl:context });
});

EM_JS(void,js_main,(),{

"use strict";

function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall('str');
},950);
}
  
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var  $lt=tem.innerHTML;

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
},550);
});
  
int main(){
fl();
EM_ASM({
"use strict";
console.log('fire.. heh heh..');});
js_main();
return 0;
}
