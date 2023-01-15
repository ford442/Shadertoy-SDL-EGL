#include "../include/b3main.hpp"

EM_JS(void,js_main,(),{
  
 "use strict";
  
function highResStart(){
document.getElementById('scanvas').height=window.innerHeight*4;
document.getElementById('scanvas').width=window.innerHeight*4;
document.getElementById('pmhig').innerHTML=window.innerHeight*4;
setTimeout(function(){
Module.ccall('str');
},350);
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
setTimeout(function(){
Module.ccall('b3');
},750);
setTimeout(function(){
const bz=new BroadcastChannel('bez');
bz.postMessage({data:222});},350);
}

function normalResStart(){
var vvc=document.getElementsByClassName('mapsConsumerUiSceneInternalCoreScene__canvas widget-scene-canvas');
var vve=vvc[0];
vve.id='mcanvas';
setTimeout(function(){
Module.ccall('b3');
},550);
setTimeout(function(){
const bz=new BroadcastChannel('bez');
bz.postMessage({data:222});
},650);
setTimeout(function(){
Module.ccall('str');
},850);
}

function pll(){
Module.ccall('pl');
}

const fll=new BroadcastChannel('file');

fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
setTimeout(function(){pll();},500);
const shutDown=new BroadcastChannel('shutDown');
shutDown.postMessage({data:222});
});

var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

var $iwid=document.getElementById('iwid');
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
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;

function snd(){
const randSong=Math.floor(($sngs[0]-5)*Math.random());
const songSrc=$sngs[randSong+5];
document.getElementById('track').src=songSrc;
const sng=new BroadcastChannel('sng');
sng.postMessage({data:songSrc});
}

document.getElementById('musicBtn').addEventListener('click',function(){
window.open('./flac');
setTimeout(function(){snd();},1550);
});

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
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){slt=tem.innerHTML;},8);},16);});
var adr='./intro.mp4';
wi=1920;
he=1080;
var hii=window.innerHeight;
document.getElementById('ihid').innerHTML=hii;
r$=hii/he;
$w=wi*r$;
const $ihigB=document.getElementById('ihid');
const $ihig=document.getElementById('ihig');
$hg=hii+'px';
$ihig.innerHTML=parseInt(window.innerHeight,10);
$iwid.innerHTML=parseInt($w,10);
document.getElementById('wrap').style.lineheight=$hg;
document.getElementById('wrap').style.pointerEvents='auto';
document.getElementById('wid').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('hig').innerHTML=parseInt(window.innerHeight,10);
var vide=document.querySelectorAll('video');
hii=window.innerHeight;
document.getElementById('ihid').innerHTML=hii;
window.scroll(0,0);
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('circle').height=window.innerHeight;
document.getElementById('circle').width=window.innerHeight;
document.getElementById('di').click();
  
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
