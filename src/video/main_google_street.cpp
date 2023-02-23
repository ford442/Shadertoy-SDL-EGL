#include "../../include/video/main.hpp"

EM_JS(void,js_main,(),{

"use strict";

const bezl=document.getElementById('circle');
window.scroll(0,0);
const switchy=document.getElementById('di');
var mV=document.getElementById('mv');
let $tim=document.getElementById('tim');
let $itim=document.getElementById('itim');
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
bezl.height=winSize;
bezl.width=parseInt(window.innerWidth,10);
switchy.click();

var $vids=[];

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
Module.ccall('b3');
},750);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
bezl.width=window.innerWidth;
bezl.height=window.innerHeight;
switchy.click();
},950);
}
  
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt;

function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){
slo.toggle();
sfr.innerHTML="";
setTimeout(function(){
grab$lt();
var slt=$lt/1000;
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
var $ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
});setTimeout(function(){slt=tem.innerHTML;},8);},16);});

document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});

});

int main(){

js_main();
return 0;

}
