#include <emscripten.h>
#include <emscripten/bind.h>
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include <emscripten/em_types.h>
#include <emscripten/val.h>

int main(){

EM_ASM({

//  shutter / bezel

let rec;
let ccs;
let mw;
let tc;
let iww;
let img;
let imgb;
let hi;
let sht;
let lns;
let glas;
let rr;
let mdd;
let gtop;
let nw;
let nh;
let ndiff;
let bz;
let fbb;
let bctx;
let ttx;

function clo(sz){
bctx.globalCompositeOperation='source-over';
bctx.fillStyle='rgba(0,0,0,0.3)';
shtr(rr-2);
bctx.fillStyle='rgba(0,0,0,0.1)';
shtr(rr-1);
bctx.fillStyle='rgba(0,0,0,0.3)';
shtr(rr);
bctx.fillStyle='rgba(0,0,0,0.4)';
shtr(rr+1);
shtr(rr);
bctx.fillStyle='rgba(0,0,0,0.4)';
shtr(rr+2);
}

function shtr(sim){
if(ccs.getContext){
bctx.beginPath();
bctx.arc(mw,rr,sim,0,2*Math.PI,false);
bctx.fill();
};
}

function op(sz){
bctx.globalCompositeOperation='source-over';
bctx.fillStyle='rgba(168,168,168,1)';
shtr(rr);
bctx.globalCompositeOperation='destination-out';
shtr(sz);
}

ccs=document.querySelector('#circle');

tc=document.querySelector('#tcan');

const params={
colorType:'float32',
colorSpace:'display-p3',
alpha:true,
depth:true,
stencil:true,
preserveDrawingBuffer:true,
premultipliedAlpha:true,
desynchronized:false,
lowLatency:false,
powerPreference:'high-performance',
antialias:true,
willReadFrequently:false,
majorVersion:2,
minorVersion:0
};

bctx=ccs.getContext('2d',params);
ttx=tc.getContext('2d',params);

function draw(){
hi=parent.window.innerHeight;
rec=parent.window.innerWidth;
rec=Math.round(rec);
document.querySelector('#circle').width=rec;
document.querySelector('#circle').height=hi;
imgb=document.querySelector('#gl');
glas=Math.round(hi*1.133);
imgb.height=glas;
imgb.width=glas;
rr=hi/2;
rr=Math.round(rr);
mw=((rec-hi)/2)+rr;
mw=Math.round(mw);
tc.height=hi;
img=document.querySelector('#frm');
mdd=(rec-glas)/2;
gtop=Math.round((imgb.height-hi)/2);
mdd=Math.round(mdd);
imgb.style.cssText='position:absolute;left:'+mdd+'px;right:'+mdd+'px;z-index:555;top:-'+gtop+'px;';
nw=img.naturalWidth;
nh=img.naturalHeight;
iww=(hi/nh)*nw;
iww=Math.round(iww);
ndiff=(iww-rec)/2;
ndiff=(ndiff*(nh/hi));
tc.width=rec;
sht=parent.document.querySelector('#shut').innerHTML;
lns=document.querySelector('#lns').innerHTML;
if(ccs.getContext){
tc.style.cssText="image-rendering:'auto'";
ccs.style.cssText="image-rendering:'auto'";
bctx.globalCompositeOperation='source-over';
ttx.drawImage(img,ndiff,0,nw-(Math.round(nw*0.02)),nh-Math.round((nh*0.02)),0,0,iww,hi);
bctx.beginPath();
bctx.fillStyle='black';
bctx.fillRect(0,0,rec,parent.window.innerHeight);
bctx.fillStyle=bctx.createPattern(tc,'no-repeat');
bctx.beginPath();
bctx.fillRect(0,0,rec,hi);
bctx.globalCompositeOperation='destination-out';
shtr(rr);
bctx.globalCompositeOperation='source-over';
bctx.fillStyle='rgba(168,168,168,1)';
shtr(rr);
if(sht==2){
if(lns==1){
for(var sz=0;sz<rr;sz=sz+1){
setTimeout(function(){
op(sz);
},2);};
document.querySelector('#lns').innerHTML=2;
};
bctx.globalCompositeOperation='destination-out';
shtr(rr);
};
if(sht==1){
if(lns==2){
for(var sz=0;sz<rr;sz=sz+1){
setTimeout(function(){
clo(sz);
},2);};
document.querySelector('#lns').innerHTML=1;
};
bctx.globalCompositeOperation='source-over';
bctx.fillStyle='rgba(168,168,168,1)';
shtr(0);
};};
}

parent.document.querySelector('#di').addEventListener('click',function(){
draw();
});

setTimeout(function(){
document.querySelector('#splash2').style.zIndex=3000;
document.querySelector('#splash2').style.display='none';
},4200);
setTimeout(function(){
document.querySelector('#splash1').style.zIndex=3000;
document.querySelector('#splash1').style.display='none';
},4500);

setTimeout(function(){
document.querySelector('#vsiz').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
},500);

setTimeout(function(){
window.scrollTo({
top: 0,
left: 0,
behavior: "smooth",
});
},750);
var modu=document.querySelector('#modulePath').innerHTML;
const xhr=new XMLHttpRequest();
xhr.open('GET', modu, true); // Replace with your filename
xhr.responseType='arraybuffer'; // Get raw binary data
console.log('got loader run');
function decodeUTF32(uint8Array, isLittleEndian=true) {
const dataView=new DataView(uint8Array.buffer);
let result="";
for (let i=0; i < uint8Array.length; i += 4) {
let codePoint;
if (isLittleEndian) {
codePoint=dataView.getUint32(i, true);
} else {
codePoint=dataView.getUint32(i, false);
}
result += String.fromCodePoint(codePoint);
}
return result;
}
xhr.onload=function() {
console.log('got loader load');
if (xhr.status === 200) {
const utf32Data=xhr.response;
const jsCode=decodeUTF32(new Uint8Array(utf32Data), true);
const scr=document.createElement('script');
// scr.type='module';
scr.text=jsCode;
document.body.appendChild(scr);
setTimeout(function(){
var Module=lib1ink();
Module.onRuntimeInitialized=function(){
console.log('call mod main');
Module.callMain();
};
},2000);
}
};
xhr.send();
const vsiz=document.querySelector('#vsiz');
let menuSz=parseInt(window.innerWidth*.75,10);
let infoSz=parseInt(window.innerHeight*.25,10);

function normalResSetup(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#di').click();
},250);
document.querySelector('#status').style.backgroundColor="green";
}
document.querySelector('#status').height=20;
document.querySelector('#status').width=parseInt(window.innerHeight,10);
const infoBtn=document.querySelector('#infoBtn');
const srs=document.querySelector('#srsiz');
const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');
const sfr2=document.querySelector('#slideframe2');
var $lt=tem.innerHTML;
let $sr=srs.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({
'panel':document.querySelector('#panel'),
'menu':document.querySelector('#menu'),
'padding':menuSz,
'tolerance':70,
'easing':'cubic-bezier(.32,2,.55,.27)'
});
ban.addEventListener('click',function(){
slo.toggle();
sfr.innerHTML="";
sfr2.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
sfr2.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider2"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.025,max:2.00},
step:[0.005],labels:false,tooltip:true,scale:false,});
const srsl=new rSlider({target:'#timeslider2',values:{min:0.05,max:2.00},
step:[0.05],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(1.0);
srsl.setValues(1.0);
vsiz.innerHTML=Math.round(window.innerHeight);
document.querySelector('#menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;
$ll=($ll*1000);
tem.innerHTML=$ll;
var sr=Math.round(srsl.getValue()*1000);
srs.innerHTML=sr;
vsiz.innerHTML=Math.round($ll/1000*window.innerHeight);
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16);
});
const infoSlideout=new Slideout({
panel: document.querySelector('#info'),
menu: document.querySelector('#info'),
padding: infoSz,
tolerance: 70,
side: 'top',
easing: 'cubic-bezier(.32,2,.55,.27)' 
});
infoBtn.addEventListener('click', function() {
infoSlideout.toggle();
});
normalResSetup();
});
return 0;
}
