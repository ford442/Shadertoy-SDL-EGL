#include "../../include/vanilla/cropcircle.hpp"

boost::function<void(int,float *,float *)>avgFrm=[](int leng,float *ptr,float *aptr){
max=0.0f;
min=255.0f;
sum=0.0f;
avgSum=0.0f;
minSum=0.0f;
maxSum=0.0f;
for (int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];}
}
sum=sum/leng;
aptr[0]=sum;
aptr[1]=min;
aptr[2]=max;
return;
};

boost::function<void(int,int,float *)>rotateFrame=[](int angle,int leng,float *Fptr){
for (int y = 0; y < leng; y++) {
for (int x = 0; x < leng; x++) {
int index = 4 * (y * leng + x);
unsigned char red = Fptr[index];
unsigned char green = Fptr[index + 1];
unsigned char blue = Fptr[index + 2];
int new_x = x - (leng / 2) * tan(angle / 2);
int new_y = y - (leng / 2);
int new_index = 4 * (new_y * leng + new_x);
Fptr[new_index] = red;
Fptr[new_index + 1] = green;
Fptr[new_index + 2] = blue;
}
}
return;
};

extern "C" {

void nano(int leng,float *ptr,float *aptr){
avgFrm(leng,ptr,aptr);
}

void rotat(int angle,int leng,float *Fptr){
rotateFrame(angle,leng,Fptr);
}

}

EM_JS(void, ma, (), {
let winSize=parseInt(window.innerHeight,10);
const scanvas=document.createElement('canvas');
scanvas.id='zimag';
scanvas.imageRendering='pixelated';
scanvas.width=winSize;
scanvas.height=winSize;
scanvas.zoom=1;
scanvas.scale=1;
scanvas.style.pointerEvents='none';
scanvas.style.display='block';
scanvas.style.position='absolute';
scanvas.style.zIndex='999995';
scanvas.style.top='0';
scanvas.style.height='100vh';
scanvas.style.width='100vh';
scanvas.style.backgroundColor='rgba(0,0,0,128)';
document.getElementById("cp").appendChild(scanvas);

/*
const zcanvas=document.createElement('canvas');
zcanvas.id='jimag';
zcanvas.imageRendering='pixelated';
zcanvas.width=winSize;
zcanvas.height=winSize;
zcanvas.zoom=1;
zcanvas.scale=1;
zcanvas.style.pointerEvents='none';
zcanvas.style.display='block';
zcanvas.style.position='absolute';
zcanvas.style.zIndex='999994';
zcanvas.style.top='0';
zcanvas.style.height='100vh';
zcanvas.style.width='100vh';
zcanvas.style.backgroundColor='rgba(0,0,0,128)';
// document.getElementById("cpB").appendChild(zcanvas);
  */
// let c = document.getElementById("imag");

const contxVars={
// colorType:'float32',
// precision:'highp',
// preferLowPowerToHighPerformance:false,
alpha:true,
depth:true,
stencil:true,
preserveDrawingBuffer:false,
premultipliedAlpha:true,
imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:true,
powerPreference:'high-performance',
antialias:false
};
const ctx = scanvas.getContext('2d',contxVars);
// const ctxB = zcanvas.getContext('2d',contxVars);
const gpu = new GPUX({mode:'gpu', canvas:scanvas, webGl:ctx });
// const gpuB = new GPUX({mode:'gpu', canvas:zcanvas, webGl:ctxB });
let dis = set();
if (dis) dis();dis = set();
var $, $r, z, w, R, h, ww, o, l, r, m, rotm, rotmb, rottm, kna, knab, knb, knbb, knc, kncb, knd, kndb, rott, rottb, rottc;
function set() {
ww = document.getElementById("iwid").innerHTML;
h = document.getElementById("ihig").innerHTML;
ow = document.getElementById("wid").innerHTML;
oh = document.getElementById("hig").innerHTML;
let cnP = document.getElementById("cp");
let cnPB = document.getElementById("cpB");
let flP = document.getElementById("flip");
let vd = document.getElementById("myvideo");
  //  var c = document.getElementById("zimag");
  //  var ctx = c.getContext("2d");
ctx.drawImage(vd, 0, 0, ww, h);
var imgData = ctx.getImageData(0, 0, ww, h);
var rgbdat = ctx.createImageData(ww, h);
var rgbd = rgbdat.data;
var imgg = imgData.data;
var pointb=0.0;
var i;
let la=h*ww*4;
var pointa=la*2.0;
var pointb=la*1.0;
let $H=Module.HEAPF32.buffer;
//   var agav=new Float32Array($H,la,1);
// var rgbd = new Uint32Array(imgData.data);
var agavF=new Float32Array($H,pointb,la);
agavF.set(imgData.data);
// Module.HEAPF32.set(imgData.data);
Module.ccall("nano",null,["Number","Number","Number"],[la,pointb,pointa]);

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
rgbd[i] = 0;
rgbd[i + 1] = 0;
rgbd[i + 2] = 0;
rgbd[i + 3] =255- (rgb-128)*16;
}
}
// Module.HEAPF32.set(rgbdat.data);
agavF.set(rgbdat.data);
Module.ccall("rotat",null,["Number","Number"],[ang,la,pointb]);

rgbdat.data=new Float32Array($H,pointb,la);
ctx.putImageData(rgbdat, 0, 0);

function Ra() {
flP.setAttribute("style", "transform: scaleX(1);");
cnP.setAttribute("style", "transform: scaleY(1);");
// cnPB.setAttribute("style", "transform: scaleY(-1);");
}
function Rb() {
flP.setAttribute("style", "transform: scaleX(-1);");
cnP.setAttribute("style", "transform: scaleY(-1);");
// cnPB.setAttribute("style", "transform: scaleY(1);");
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
// cnPB.setAttribute("style", "transform: rotate(" + rta + "deg);");
}
function rrrb(rtb) {
cnP.setAttribute("style", "transform:rotate(" + rtb + "deg);");
// cnPB.setAttribute("style", "transform:rotate(" + rtb + "deg);");
}
function rrrc(rtc) {
cnP.setAttribute("style", "transform: rotate(" + rtc + "deg);");
// cnPB.setAttribute("style", "transform: rotate(" + rtc + "deg);");
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
