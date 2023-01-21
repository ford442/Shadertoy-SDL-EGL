#include "../include/b3main.hpp"

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
  
function pll(){
Module.ccall('pl');
}
  
const fll=new BroadcastChannel('file');
const shutDown=new BroadcastChannel('shutDown');

fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
pll();
setTimeout(function(){
shutDown.postMessage({data:222});
},450);
});

var $iwid=document.getElementById('iwid');
var mV=document.getElementById('mv');
var loadV=document.getElementById('ldv');
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
  
mV.load();
loadV.load();

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

var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

let tem=document.getElementById('tim');
let ban=document.getElementById('menuBtn');
let sfr=document.getElementById('slideframe');
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;
grab$lt();
let slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
let tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:16.00},
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

loadV.addEventListener('canplay',function(){
  
  
loadV.width=this.videoWidth;
loadV.height=this.videoHeight;
document.getElementById('wid').innerHTML=this.videoWidth;
document.getElementById('hig').innerHTML=this.videoHeight;
  
  
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
  
int main(){
  
EM_ASM({
"use strict";
FS.mkdir("/snd");
FS.mkdir("/shader");
});

js_main();
return 0;

}
