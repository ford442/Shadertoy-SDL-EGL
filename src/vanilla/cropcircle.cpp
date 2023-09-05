#include "../../include/vanilla/cropcircle.hpp"

boost::function<void(short int,int,float *,float *)>avgFrm=[](int Fnum,int leng,float *ptr,float *aptr){
max=0.0;
min=1.0;
sum=0.0;
avgSum=0.0;
minSum=0.0;
maxSum=0.0;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
}
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
}
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
}
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
}
aptr[200]=maxSum/32;
return;
};

extern "C" {

void nano(short int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
}

}

EM_JS(void, ma, (), {
let winSize=parseInt(window.innerHeight,10);
const scanvas=document.createElement('canvas');
scanvas.id='zimag';
scanvas.imageRendering='auto';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='none';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='1';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(0,0,0,0)';
document.getElementById("cp").appendChild(scanvas);
let c = document.getElementById("imag");

const contxVars={
// colorType:'float32',
// precision:'highp',
// preferLowPowerToHighPerformance:false,
alpha:true,
depth:true,
stencil:true,
preserveDrawingBuffer:true,
premultipliedAlpha:false,
imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:true,
powerPreference:'high-performance',
antialias:false
};

const ctx = scanvas.getContext('2d',contxVars);
const gpu = new GPUX({mode:'gpu', canvas:scanvas, webGl:ctx });
let dis = set();
if (dis) dis();dis = set();
var $, $r, z, w, R, h, ww, o, l, r, m, rotm, rotmb, rottm, kna, knab, knb, knbb, knc, kncb, knd, kndb, rott, rottb, rottc;
function set() {
ww = document.getElementById("iwid").innerHTML;
h = document.getElementById("ihig").innerHTML;
ow = document.getElementById("wid").innerHTML;
oh = document.getElementById("hig").innerHTML;
let cnP = document.getElementById("cp");
let flP = document.getElementById("flip");
let vd = document.getElementById("myvideo");
  //  var c = document.getElementById("zimag");
  //  var ctx = c.getContext("2d");
ctx.drawImage(vd, 0, 0, ww, h);
var imgData = ctx.getImageData(0, 0, ww, h);
var rgbdat = ctx.createImageData(ww, h);
var rgbd = rgbdat.data;
var imgg = imgData.data;


  
var i;
// let $H=Module.HEAPF32.buffer;
let la=h*ww*4;
var pointa=2*la;
// var agav=new Float32Array($H,pointa,1);
//   var rgbd = new Uint32Array(imgData.data);
// Module.HEAPF32.set(rgbd);

for (i = 0; i < (ww * h * 4); i = i + 4) {
var rgb = (imgg[i] * 0.2126) + (imgg[i + 1] * 0.7152) + (imgg[i + 2] * 0.0722);
var rgbm=128-rgb;
if (rgb > 126) {
if (rgb > 209) {    // orange
rgbd[i] = 255;
rgbd[i + 1] = 128;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255-(rgb-209)*16;
}
else if(rgb > 193){   // red
rgbd[i] = 255;
rgbd[i + 1] = 0;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255-(rgb-193)*16;
}else if(rgb > 177){   // light blue
rgbd[i] = 0;
rgbd[i + 1] = 255;
rgbd[i + 2] = 255;
rgbd[i + 3] =255- (rgb-177)*16;
}  else if(rgb > 161){  //  blue
rgbd[i] = 0;
rgbd[i + 1] = 0;
rgbd[i + 2] = 255;
rgbd[i + 3] =255- (rgb-161)*16;
}  else if(rgb > 145){  // green
rgbd[i] = 0;
rgbd[i + 1] = 255;
rgbd[i + 2] = 0;
rgbd[i + 3] =255- (rgb-145)*16;
} else if(rgb > 128){  // yellow
rgbd[i] =255;
rgbd[i + 1] = 255;
rgbd[i + 2] = 0;
rgbd[i + 3] =255- (rgb-128)*16;
}
} else {
rgbd[i] = 255;
rgbd[i + 1] = 255;
rgbd[i + 2] = 255;
rgbd[i + 3] =255- (rgb-128)*16;
}
}
ctx.putImageData(rgbdat, 0, 0);
function Ra() {
flP.setAttribute("style", "transform: scaleX(1);");
cnP.setAttribute("style", "transform: scaleY(1);");
}
function Rb() {
flP.setAttribute("style", "transform: scaleX(-1);");
cnP.setAttribute("style", "transform: scaleY(-1);");
}
knb = document.getElementById("rra");
kna = document.getElementById("mainr");
knc = document.getElementById("rrb");
knd = document.getElementById("rrc");
knbb = document.getElementById("rrab");
kncb = document.getElementById("rrbb");
kndb = document.getElementById("rrcb");
rate = (kna.innerHTML);
rott = 0;
rottb = 0;
rottc = 0;
let dur = document.getElementById("temptime").innerHTML / 10;
let dsd = false;
function $rn() {
if (dsd) {
return;
}
function rrra(rta) {
cnP.setAttribute("style", "transform: rotate(" + rta + "deg);");
}
function rrrb(rtb) {
cnP.setAttribute("style", "transform:rotate(" + rtb + "deg);");
}
function rrrc(rtc) {
cnP.setAttribute("style", "transform: rotate(" + rtc + "deg);");
}
if ((rott - knd.innerHTML) < 0) {
rott = (rott + 360 - knd.innerHTML);
} else {
rott = rott - knd.innerHTML;
}
rrra(rott);
if ((rottb - knc.innerHTML) < 0) {
rottb = (rottb + 360 - knc.innerHTML);
} else {
rottb = (rottb - knc.innerHTML);
}
setTimeout(function() {
Rb();
rrrb(rottb);
}, rate);
if ((rottc + knb.innerHTML) > 360) {
rottc = ((rottc + knb.innerHTML) - 360);
} else {
rottc = (rottc + knb.innerHTML);
}
setTimeout(function() {
Ra();
rrrc(rottc);
}, rate);
setTimeout(function() {
$rn();
}, rate);
}
$rn();
document.getElementById("di").onclick = function() {
dsd = true;
set();
};
return () => {
dsd = true;
};
}
});

int main() {
ma();
return 1;
}
