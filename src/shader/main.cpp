#include "../../include/shader/main.h"

EM_JS(void,js_main,(),{
 
FS.mkdir('/shader');

window.scroll(0,0);

let $tim=document.getElementById('tim');
let $itim=document.getElementById('itim');
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;

var $shds=[];

function normalResStart(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
setTimeout(function(){
document.getElementById('stat').innerHTML='Sending Start';
document.getElementById('stat').style.backgroundColor='green';
Module.ccall('str');
},100);
document.getElementById('bcanvas').width=window.innerHeight;
document.getElementById('bcanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('acanvas').width=window.innerHeight;
document.getElementById('acanvas').height=window.innerHeight;
document.getElementById('di').click();
}

function shds(xml){
const sparser=new DOMParser();
let htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
let preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxts=txxts.replace(Self,"");
var x=document.getElementById("sh1");
var option=document.createElement("option");
option.text=txxts;
$shds[i+1]='https://glsl.1ink.us/shaders/'+txxts;
option.value=txxts;
x.add(option);
}
}
 
function rrun(){
let shadesNum=$shds[0];
if(shadesNum>0){
var randShade=Module.ccall('r4nd','Number',['Number'],[shadesNum])+5;
};
let shdMenu=document.getElementById('sh1');
var path;
if(shdMenu.value!='Default'){
if(shdMenu.value=='Random'){
document.getElementById('path').innerHTML=$shds[randShade];
}else{
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+shdMenu.value;
}
}else{
var fle=document.getElementById('path').innerHTML;
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+fle;
}
var pth=document.getElementById('path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.getElementById('stat').innerHTML='Downloading Shader';
document.getElementById('stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader.glsl',sfil);
document.getElementById('stat').innerHTML='Downloaded Shader';
document.getElementById('stat').style.backgroundColor='blue';
//setTimeout(function(){
normalResStart();
//},350);
}
});
ff.send(null);
}

function scanShaders(){
const dxhttp=new XMLHttpRequest();
// dxhttp.withCredentials=false;
dxhttp.addEventListener("load",function(){
shds(this);
});
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
}

let tem=document.getElementById('tim');
let ban=document.getElementById('menuBtn');
let sfr=document.getElementById('slideframe');
var $lt;
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
let slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();var slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
let tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
var $ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){slt=tem.innerHTML;},8);},16);});
const pnnl=document.body;

document.getElementById('startBtn2').addEventListener('click',function(){
Module.ccall('swp');
rrun();
});

document.getElementById('uniDown').addEventListener('click',function(){
Module.ccall('ud');
});

document.getElementById('viewDown').addEventListener('click',function(){
Module.ccall('vd');
});

document.getElementById('uniUp').addEventListener('click',function(){
Module.ccall('uu');
});

document.getElementById('viewUp').addEventListener('click',function(){
Module.ccall('vu');
});

document.getElementById('moveUp').addEventListener('click',function(){
Module.ccall('mu');

});document.getElementById('moveDown').addEventListener('click',function(){
Module.ccall('md');

});document.getElementById('moveLeft').addEventListener('click',function(){
Module.ccall('ml');

});document.getElementById('moveRight').addEventListener('click',function(){
Module.ccall('mr');
});

document.getElementById('sizeUp').addEventListener('click',function(){
document.getElementById('scanvas').style.width=window.innerHeight*1.01;
document.getElementById('scanvas').style.height=window.innerHeight*1.01;
// document.getElementById('scanvas').width=window.innerHeight*1.01;
//document.getElementById('scanvas').height=window.innerHeight*1.01;
// Module.ccall('vu');
setTimeout(function(){
Module.ccall('uu');
},100);
setTimeout(function(){
document.getElementById('scanvas').style.width=window.innerHeight;
document.getElementById('scanvas').style.height=window.innerHeight;
// document.getElementById('scanvas').width=window.innerHeight;
//document.getElementById('scanvas').height=window.innerHeight;
},200);
// Module.ccall('vd');
});
 
document.getElementById('sizeDown').addEventListener('click',function(){
document.getElementById('scanvas').style.width=window.innerHeight*0.99;
document.getElementById('scanvas').style.height=window.innerHeight*0.99;
// document.getElementById('scanvas').width=window.innerHeight*0.99;
//document.getElementById('scanvas').height=window.innerHeight*0.99;
// Module.ccall('vd');
setTimeout(function(){
Module.ccall('ud');
},100);
setTimeout(function(){
document.getElementById('scanvas').style.width=window.innerHeight;
document.getElementById('scanvas').style.height=window.innerHeight;
// document.getElementById('scanvas').width=window.innerHeight;
//document.getElementById('scanvas').height=window.innerHeight;
},200);
// Module.ccall('vu');
});

document.getElementById('startBtn').addEventListener('click',function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
document.getElementById('stat').innerHTML='Scanning Shaders';
document.getElementById('stat').style.backgroundColor='yellow';
rrun();
});

scanShaders();

setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},100);

function Key(e){
if(e.code=='KeyQ'){document.getElementById('startBtn').click();};
if(e.code=='KeyE'){document.getElementById('startBtn2').click();};
if(e.code=='KeyD'){document.getElementById('uniUp').click();};
if(e.code=='KeyA'){document.getElementById('uniDown').click();};
if(e.code=='KeyW'){document.getElementById('viewUp').click();};
if(e.code=='KeyS'){document.getElementById('viewDown').click();};
if(e.code=='KeyJ'){document.getElementById('moveLeft').click();};
if(e.code=='KeyK'){document.getElementById('moveRight').click();};
if(e.code=='KeyI'){document.getElementById('moveDown').click();};
if(e.code=='KeyM'){document.getElementById('moveUp').click();};
if(e.code=='Digit1'){document.getElementById('sizeDown').click();};
if(e.code=='Digit3'){document.getElementById('sizeUp').click();};
}
pnnl.addEventListener('keydown',Key);

});

js JS;

extern"C"{
 
int32_t r4nd(int32_t tH){
Rg=JS.rNd(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}

}
 
static inline void(*jss)(){&js_main};

int main(void){
jss();
// tie(JS.Th,JS.rD,JS.Dr);
return 1;
}
