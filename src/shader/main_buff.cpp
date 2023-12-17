#include "../../include/shader/main.hpp"

js JS;
extern int rD,Rg,nm;

int r4nd4(int tH){
Rg=JS.rNd(tH);
return Rg;
}

extern"C"{

int r4nd(int TH){
RG=r4nd4(TH);
return RG;
}

}

EM_JS(void,js_main,(),{
FS.mkdir('/shader');
window.scroll(0,0);
var $shds=[];

function highResStart(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#scanvas').width=window.innerWidth*2;
document.querySelector('#scanvas').height=window.innerHeight*2;
document.querySelector('#di').click();
setTimeout(function(){
document.querySelector('#stat').innerHTML='Sending Start';
document.querySelector('#stat').style.backgroundColor='green';
Module.ccall('str',{async:true});
},50);
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#scanvas').width=window.innerHeight;
document.querySelector('#scanvas').height=window.innerHeight;
document.querySelector('#di').click();
},50);
}

function normalResStart(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
setTimeout(function(){
document.querySelector('#stat').innerHTML='Sending Start';
document.querySelector('#stat').style.backgroundColor='green';
Module.ccall('str',{async:true});
},100);
document.querySelector('#scanvas').width=window.innerHeight;
document.querySelector('#scanvas').height=window.innerHeight;
document.querySelector('#di').click();
}

function shds(xml){
const sparser=new DOMParser();
let htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
let preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,'');
txxts=txxts.replace(Self,'');
var x=document.getElementById('sh1');
var option=document.createElement('option');
option.text=txxts;
$shds[i+1]='https://glsl.1ink.us/shaders/'+txxts;
option.value=txxts;
x.add(option);
}
}
 
function rrun(){
let shadesNum=$shds[0];
if(shadesNum>0){
var randShade=Module.ccall('r4nd','Number',['Number'],[shadesNum],{async:true})+5;
};
let shdMenu=document.querySelector('#sh1');
let highRes=document.querySelector('#resMode').value;
var path;

if(shdMenu.value=='Random'){
document.querySelector('#path').innerHTML=$shds[randShade];
}else{
document.querySelector('#path').innerHTML='https://glsl.1ink.us/shaders/'+shdMenu.value;
}
}else{
document.querySelector('#path').innerHTML='https://glsl.1ink.us/shaders/'+fle;
var fle=document.querySelector('#path').innerHTML;
}
var pth=document.querySelector('#path').innerHTML;
var pthA=pth+'A';
let ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/Image.glsl',sfil);
document.querySelector('#stat').innerHTML='Downloaded Image Shader';
}
});
ff.send(null);

ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/BufferA.glsl',sfil);
document.querySelector('#stat').innerHTML='Downloaded BufferA Shader';
}
});
ff.send(null);
document.querySelector('#stat').style.backgroundColor='blue';
setTimeout(function(){
if (highRes==true){
highResStart();
}else{
normalResStart();
}
},150);
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

let tem=document.querySelector('#tim');
let ban=document.querySelector('#menuBtn');
let sfr=document.querySelector('#slideframe');
var $lt;
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
let slo=new Slideout({'panel':document.querySelector('#panel'),'menu':document.querySelector('#menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";});
const pnnl=document.body;

document.querySelector('#startBtn2').addEventListener('click',function(){
Module.ccall('swp',{async:true});
rrun();
});

document.querySelector('#uniDown').addEventListener('click',function(){
Module.ccall('ud',{async:true});
});

document.querySelector('#viewDown').addEventListener('click',function(){
Module.ccall('vd',{async:true});
});

document.querySelector('#uniUp').addEventListener('click',function(){
Module.ccall('uu',{async:true});
});

document.querySelector('#viewUp').addEventListener('click',function(){
Module.ccall('vu',{async:true});
});

document.querySelector('#moveUp').addEventListener('click',function(){
Module.ccall('mu',{async:true});

});document.querySelector('#moveDown').addEventListener('click',function(){
Module.ccall('md',{async:true});

});document.querySelector('#moveLeft').addEventListener('click',function(){
Module.ccall('ml',{async:true});

});document.querySelector('#moveRight').addEventListener('click',function(){
Module.ccall('mr',{async:true});
});

document.querySelector('#sizeUp').addEventListener('click',function(){
// document.querySelector('#scanvas').style.width=window.innerHeight*1.01;
// document.querySelector('#scanvas').style.height=window.innerHeight*1.01;
// document.querySelector('#scanvas').width=window.innerHeight*1.01;
//document.querySelector('#scanvas').height=window.innerHeight*1.01;
// Module.ccall('vu');
setTimeout(function(){
Module.ccall('uu',{async:true});
},100);
setTimeout(function(){
// document.querySelector('#scanvas').style.width=window.innerHeight;
// document.querySelector('#scanvas').style.height=window.innerHeight;
// document.querySelector('#scanvas').width=window.innerHeight;
//document.querySelector('#scanvas').height=window.innerHeight;
},200);
// Module.ccall('vd');
});
 
document.querySelector('#sizeDown').addEventListener('click',function(){
// document.querySelector('#scanvas').style.width=window.innerHeight*0.99;
// document.querySelector('#scanvas').style.height=window.innerHeight*0.99;
// document.querySelector('#scanvas').width=window.innerHeight*0.99;
//document.querySelector('#scanvas').height=window.innerHeight*0.99;
// Module.ccall('vd');
setTimeout(function(){
Module.ccall('ud',{async:true});
},100);
setTimeout(function(){
// document.querySelector('#scanvas').style.width=window.innerHeight;
// document.querySelector('#scanvas').style.height=window.innerHeight;
// document.querySelector('#scanvas').width=window.innerHeight;
//document.querySelector('#scanvas').height=window.innerHeight;
},200);
// Module.ccall('vu',{async:true});
});

document.querySelector('#startBtn').addEventListener('click',function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
document.querySelector('#stat').innerHTML='Scanning Shaders';
document.querySelector('#stat').style.backgroundColor='yellow';
rrun();
});

scanShaders();

setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},100);

function Key(e){
if(e.code=='KeyQ'){document.querySelector('#startBtn').click();};
if(e.code=='KeyE'){document.querySelector('#startBtn2').click();};
if(e.code=='KeyD'){document.querySelector('#uniUp').click();};
if(e.code=='KeyA'){document.querySelector('#uniDown').click();};
if(e.code=='KeyW'){document.querySelector('#viewUp').click();};
if(e.code=='KeyS'){document.querySelector('#viewDown').click();};
if(e.code=='KeyJ'){document.querySelector('#moveLeft').click();};
if(e.code=='KeyK'){document.querySelector('#moveRight').click();};
if(e.code=='KeyI'){document.querySelector('#moveDown').click();};
if(e.code=='KeyM'){document.querySelector('#moveUp').click();};
if(e.code=='Digit1'){document.querySelector('#sizeDown').click();};
if(e.code=='Digit3'){document.querySelector('#sizeUp').click();};
}
pnnl.addEventListener('keydown',Key);

});

static inline boost::function<EM_BOOL()>jss=[](){
js_main();
return EM_TRUE;
};

int main(){
jss();
return 0;
}
