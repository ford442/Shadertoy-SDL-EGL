EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');
let running=0;
let vv=document.querySelector('#mv');
let vvi=document.querySelector('#mvi');

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}
}
  
function flipImageData(imageData) {
const width = imageData.width;
const height = imageData.height;
const data = imageData.data;
for (let y = 0; y < height / 2; y++) {
for (let x = 0; x < width; x++) {
const topIndex = (y * width + x) * 4;
const bottomIndex = ((height - 1 - y) * width + x) * 4;
for (let c = 0; c < 4; c++) {
[data[topIndex + c], data[bottomIndex + c]] = [data[bottomIndex + c], data[topIndex + c]];
}
}
}
return imageData;
}

function videoFrames(){
let vw$=parseInt(document.querySelector("#mvi").videoWidth);
let vh$=parseInt(document.querySelector("#mvi").videoHeight);
let SiZ=window.innerHeight;
vvi.height=SiZ;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
  
let tstSiZ=h$;
if(running==0){
// Module.ccall("frm",null,['Number'],['Number'],h$,h$);
setTimeout(function(){
Module.ccall("startWebGPU");
console.log('Starting..');
running=1;
},500);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=SiZ;
cnvb.height=SiZ;
cnv.width=SiZ;
cnvb.width=SiZ;
var ratio=SiZ/h$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
const gl2=cnv.getContext('2d',{colorType:'float32',willReadFrequently:false,alpha:true}); // 
gl2.drawImage(vvi,offS,0,SiZ,SiZ,0,0,SiZ,SiZ);
let image=gl2.getImageData(0,0,SiZ,SiZ);
// let mageData=flipImageData(image);
let imageData=image.data;
let pixelData=new Float32Array(imageData);
FS.writeFile('/video/frame.gl',pixelData);
setInterval(function(){
gl2.drawImage(vvi,offS,0,SiZ,SiZ,0,0,SiZ,SiZ);
image=gl2.getImageData(0,0,SiZ,SiZ);
imageData=image.data;
// pixelData=new Uint8ClampedArray(imageData,0,imageData.size);
pixelData=new Float32Array(imageData,0,imageData.size);
FS.writeFile('/video/frame.gl',pixelData);
},16.6);
}

function normalResStart(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#canvas').height=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#canvas').width=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#di').click();
videoFrames();
},1500);
document.querySelector('#status').style.backgroundColor="green";
}
document.querySelector('#status').height=20;
document.querySelector('#status').width=parseInt(window.innerHeight,10);
const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');
var $lt=tem.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.querySelector('#panel'),'menu':document.querySelector('#menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
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
document.querySelector('#menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16);
});
  
document.querySelector('#startBtn').addEventListener('click',function(){
// var pth="https://glsl.1ink.us/wgsl/plasma.wgslc";
var pth=document.querySelector('#path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader.wgsl',sfil);
document.querySelector('#stat').innerHTML='Downloaded Shader';
document.querySelector('#stat').style.backgroundColor='blue';
normalResStart();
}
});
ff.send(null);
});
  
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});
