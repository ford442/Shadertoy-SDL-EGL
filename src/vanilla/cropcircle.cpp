#include "../../include/vanilla/cropcircle.hpp"

EM_JS(void, ma, (), {
let winSize=parseInt(window.innerHeight,10);
const scanvas=document.createElement('canvas');
scanvas.id='zimag';
scanvas.imageRendering='auto';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='auto';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='1';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(255,255,255,0)';
document.getElementById("cp").appendChild(scanvas);
let c = document.getElementById("imag");

const contxVars={
// colorType:'float32',
// precision:'highp',
// preferLowPowerToHighPerformance:false,
alpha:true,
depth:false,
stencil:false,
preserveDrawingBuffer:false,
premultipliedAlpha:true,
imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:true,
powerPreference:'high-performance',
antialias:false
};

const ctx = scanvas.getContext('2d',contxVars);
// ctx.getExtension('GL_ALL_EXTENSIONS');
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

for (i = 0; i < (ww * h * 4); i = i + 4) {
var rgb = (imgg[i] * 0.2126) + (imgg[i + 1] * 0.7152) + (imgg[i + 2] * 0.0722);
if (rgb > 126) {
if (rgb > 209) {
rgbd[i] = 255;
rgbd[i + 1] = 128;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255;
}
else if(rgb > 193){
rgbd[i] = 255;
rgbd[i + 1] = 0;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255;
}else if(rgb > 177){
rgbd[i] = 0;
rgbd[i + 1] = 255;
rgbd[i + 2] = 255;
rgbd[i + 3] = 255;
}  else if(rgb > 161){
rgbd[i] = 0;
rgbd[i + 1] = 0;
rgbd[i + 2] = 255;
rgbd[i + 3] = 255;
}  else if(rgb > 145){
rgbd[i] = 0;
rgbd[i + 1] = 255;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255;
} else if(rgb > 128){
rgbd[i] =255;
rgbd[i + 1] = 255;
rgbd[i + 2] = 0;
rgbd[i + 3] = 128;
}
} else {
rgbd[i] = 0;
rgbd[i + 1] = 0;
rgbd[i + 2] = 0;
rgbd[i + 3] = 255;
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
