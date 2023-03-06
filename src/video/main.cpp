#include "../../include/video/main.hpp"

int rNd(int Th){
std::srand(std::time(nullptr));
int rD=std::rand()%Th;
return rD;
}

EM_JS(void,js_main,(),{

"use strict";

const bezl=document.getElementById('circle');
window.scroll(0,0);
const switchy=document.getElementById('di');
var vide=document.querySelectorAll('video');
let $tim=document.getElementById('tim');
let $itim=document.getElementById('itim');
document.getElementById('canvasSize').innerHTML=parseInt(window.innerHeight,10);
bezl.height=parseInt(window.innerHeight,10);
bezl.width=parseInt(window.innerWidth,10);
switchy.click();
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

var $vids=[];

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
let vidMenu1=document.getElementById('vi1').value;
let ar1=vidMenu1+'video/'+vtxxt;
let ar2=Self+'video/'+vtxxt;
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
dxhttp.addEventListener("load",function(){
vids(this);
});
let vidMenua1=document.getElementById('vi1').value;
if(vidMenua1!='Default'){
var looc=vidMenua1+'video/';
}else{
var looc='video/';
};
fxhttp.open('GET',looc,true);
fxhttp.send();
}

function normalResStart(){
bezl.width=window.innerWidth;
bezl.height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('bcanvas').width=window.innerHeight;
document.getElementById('bcanvas').height=window.innerHeight;
document.getElementById('acanvas').width=window.innerHeight;
document.getElementById('acanvas').height=window.innerHeight;
setTimeout(function(){
Module.ccall('b3_egl');
},250);
setTimeout(function(){
Module.ccall('b3');
},750);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
bezl.width=window.innerWidth;
bezl.height=window.innerHeight;
switchy.click();
},850);
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
// $high.innerHTML=parseInt(window.innerHeight,10);
bezl.height=parseInt(window.innerHeight,10);
bezl.width=parseInt(window.innerWidth,10);
document.getElementById('ldv').addEventListener('canplay',function(){
document.getElementById('ldv').height=parseInt(window.innerHeight,10);
// document.getElementById('ldv').width=this.videoWidth;
document.getElementById('wid').innerHTML=parseInt(this.videoWidth,10);
document.getElementById('hig').innerHTML=parseInt(this.videoHeight,10);
var $sc=this.duration;
var mic=Math.round($sc*1000000);
if(mic>0){
var $pt=Module.ccall('r4nd','Number',['Number'],[mic]);
};
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.getElementById('idur').innerHTML=mic/1000000;
document.getElementById('itim').innerHTML=$pt;
});
$lt=Math.round(tem.innerHTML);
var $ldt=$tim.innerHTML;
var $ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var vidNum=($vids[0]-5);
if(vidNum>0){
var rnum=Module.ccall('r4nd','Number',['Number'],[vidNum]);
};
let vidSrc=$vids[rnum+5];
var $h=window.innerHeight;
var he=document.getElementById('hig').innerHTML;
var wi=document.getElementById('wid').innerHTML;
var r$=he/$h;
var $w=wi/r$;
var $hi=he-parseInt(window.innerHeight,10);
if($hi>1){$h=parseInt(window.innerHeight,10);var $r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;}
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
switchy.click();
}
setTimeout(function(){
loada();
},$ldt);
}
  
scanVideos();
loada();
document.getElementById('startBtn').addEventListener('click',function(){

normalResStart();
});

});

extern"C"{
 
int r4nd(int tH){
int Rg=rNd(tH);
return Rg;
}
  
}

int main(void){

js_main();
return 0;

}
