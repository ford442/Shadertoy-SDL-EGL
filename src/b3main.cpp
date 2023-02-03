#include "../include/b3main.hpp"

EM_JS(void,js_main,(),{

"use strict";

window.scroll(0,0);

const fll=new BroadcastChannel('file');
const shutDown=new BroadcastChannel('shutDown');

function pll(){
Module.ccall('pl');
}

fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
setTimeout(function(){
pll();
},1500);
setTimeout(function(){
shutDown.postMessage({data:222});
},2000);
});

var vide=document.querySelectorAll('video');
var mV=document.getElementById('mv');
var loadV=document.getElementById('ldv');
var $tim=document.getElementById('tim');
var $itim=document.getElementById('itim');
var $high=document.getElementById('canvasSize');
var winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
document.getElementById('circle').height=winSize;
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('di').click();
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

const pnnl=document.body;
pnnl.addEventListener('keydown',spKey);

var $sngs=[];
var $vids=[];
var $shds=[];

function sngs(xml){
const nparser=new DOMParser();
const htmlDocs=nparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocs.getElementsByTagName('pre')[0].getElementsByTagName('a');
$sngs[0]=preList.length;
for(var i=1;i<preList.length;i++){
var stxxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
stxxt=stxxt.replace(Self,"");
$sngs[i]=Self+'songs/'+stxxt;
};
}

function scanSongs(){
const nxhttp=new XMLHttpRequest();
nxhttp.withCredentials=false;
nxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
sngs(this);
};};
nxhttp.open('GET','songs/',true);
nxhttp.send();
}

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
},550);
});

function vids(xml){
const vparser=new DOMParser();
const htmlDocv=vparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocv.getElementsByTagName('pre')[0].getElementsByTagName('a');
$vids[0]=preList.length;
for(var i=1;i<preList.length;i++){
var vtxxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
vtxxt=vtxxt.replace(Self,"");
const vidMenu1=document.getElementById('vi1').value;
var ar1=vidMenu1+'video/'+vtxxt;
var ar2=Self+'video/'+vtxxt;
if(vidMenu1!='Default'){
$vids[i]=ar1;
}else{
$vids[i]=ar2;
};
};
}

function scanVideos(){
const fxhttp=new XMLHttpRequest();
fxhttp.withCredentials=false;
fxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
vids(this);
};};
const vidMenu1=document.getElementById('vi1').value;
if(vidMenu1!='Default'){
var looc=vidMenu1+'video/';
}else{
var looc='video/';
};
fxhttp.open('GET',looc,true);
fxhttp.send();
}

function shds(xml){
const sparser=new DOMParser();
const htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxts=txxts.replace(Self,"");
$shds[i+1]='https://glsl.1ink.us/shaders/'+txxts;
};
var randShade=Math.random();
randShade=Math.floor($shds[0]*randShade)+5;
const shdMenu=document.getElementById('sh1');
if(shdMenu.value!='Default'){
if(shdMenu.value=='Random'){
document.getElementById('path').innerHTML=$shds[randShade];
}else{
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+shdMenu.value;
};
}else{
var fle=document.getElementById('path').innerHTML;
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+fle;
};
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
},450);
};};
ff.send(null);
}

function scanShaders(){
const dxhttp=new XMLHttpRequest();
dxhttp.withCredentials=false;
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
shds(this);
};};
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
}

/*
function highResStart(){
document.getElementById('scanvas').height=window.innerHeight*2;
document.getElementById('scanvas').width=window.innerHeight*2;
document.getElementById('scanvas').style.height=(window.innerHeight*2)+'px';
document.getElementById('scanvas').style.width=(window.innerHeight*2)+'px';
$high.innerHTML=window.innerHeight*2;
setTimeout(function(){
Module.ccall('b3_egl');
},450);
setTimeout(function(){
Module.ccall('b3');
},550);
setTimeout(function(){
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').style.height=window.innerHeight+'px';
document.getElementById('scanvas').style.width=window.innerHeight+'px';
$high.innerHTML=window.innerHeight;
},750);
setTimeout(function(){
Module.ccall('str');
},850);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
// const bz=new BroadcastChannel('bez');
// bz.postMessage({data:222});
},1250);
}
*/
  
function normalResStart(){

document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;

document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').height=window.innerHeight;

document.getElementById('bcanvas').width=window.innerHeight;
document.getElementById('bcanvas').height=window.innerHeight;

document.getElementById('acanvas').width=window.innerHeight;
document.getElementById('acanvas').height=window.innerHeight;

setTimeout(function(){
// Module.ccall('fire_egl');
},150);
setTimeout(function(){
// Module.ccall('b3_egl');
},350);
setTimeout(function(){
Module.ccall('b3');
},550);
setTimeout(function(){
Module.ccall('str');
},750);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},950);
}
  
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt;
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();var slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
var $ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});setTimeout(function(){slt=tem.innerHTML;},8);},16);});

function loada(){
var mv,lo;
if(lockVid!=1){
winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
document.getElementById('circle').height=winSize;
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('ldv').addEventListener('canplay',function(){
document.getElementById('ldv').height=winSize;
// loadV.width=this.videoWidth;
document.getElementById('wid').innerHTML=parseInt(this.videoWidth,10);
document.getElementById('hig').innerHTML=parseInt(this.videoHeight,10);
var $sc=this.duration;
var mic=Math.round($sc*1000000);
var $pt=Math.random()*mic;
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.getElementById('idur').innerHTML=mic/1000000;
document.getElementById('itim').innerHTML=$pt;
});
winSize=parseInt(window.innerHeight,10);
$lt=Math.round(tem.innerHTML);
var $ldt=$tim.innerHTML;
var $ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var rnum=Math.floor((Math.random()*($vids[0]-5))+5);
var vidSrc=$vids[rnum];
var $h=window.innerHeight;
var he=document.getElementById('hig').innerHTML;
var wi=document.getElementById('wid').innerHTML;
var r$=he/$h;
var $w=wi/r$;
var $hi=he-winSize;
if($hi>1){$h=winSize;var $r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;};
var $hg=$h+'px';
mv=vide[0].id;
lo=vide[1].id;
vide[0].id=lo;
vide[1].id=mv;
document.getElementById('mv').play();
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("wrap").style.pointerEvents="auto";
document.getElementById('ldv').src=vidSrc;
document.getElementById('ldv').currentTime=$itim.innerHTML;
document.getElementById('ldv').load();
document.getElementById('di').click();
};
setTimeout(function(){
loada();
},$ldt);
}
   
document.getElementById('startBtn').addEventListener('click',function(){
scanSongs();
scanVideos();
loada();
scanShaders();
});

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
