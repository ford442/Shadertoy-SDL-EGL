#include "../../include/shader/main.hpp"

EM_JS(void,js_main,(),{

"use strict";

window.scroll(0,0);

let $tim=document.getElementById('tim');
let $itim=document.getElementById('itim');
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
document.getElementById('circle').height=winSize;
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('di').click();

var $shds=[];

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
Module.ccall('str');
},550);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},950);
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
// dxhttp.withCredentials=false;
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
shds(this);
};};
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
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
});
setTimeout(function(){slt=tem.innerHTML;},8);},16);});
document.getElementById('startBtn').addEventListener('click',function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
scanShaders();
});
setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},150);

});

int main(){

"use strict";

EM_ASM({
FS.mkdir("/shader");
});

js_main();

return 0;

}
