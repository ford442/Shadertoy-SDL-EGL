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
  
function videoFrames(){
let vw$=parseInt(document.querySelector("#mvi").videoWidth);
let vh$=parseInt(document.querySelector("#mvi").videoHeight);
let SiZ=window.innerHeight;
vvi.height=vh$;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
let tstSiZ=720;
if(running==0){
// Module.ccall("frm",null,['Number'],['Number'],h$,h$);
setTimeout(function(){
let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz]);
  console.log('Starting..');
running=1;
},500);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=h$;
cnvb.height=SiZ;
cnv.width=w$;
cnvb.width=w$;
var ratio=SiZ/h$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
const gl2=cnv.getContext('2d',{colorType:'float32',willReadFrequently:false,alpha:true}); // 
gl2.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
let image=gl2.getImageData(0,0,w$,h$);
let imageData=image.data;
let pixelData=new Float32Array(imageData);
FS.writeFile('/video/frame.gl',pixelData);
setInterval(function(){
gl2.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
image=gl2.getImageData(0,0,w$,h$);
imageData=image.data;
pixelData=new Float32Array(imageData,0,la);
FS.writeFile('/video/frame.gl',pixelData);
},16.6);
}
  
function getShader(pth,fname){
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/'+fname,sfil);
document.querySelector('#stat').innerHTML='Downloaded Shader';
document.querySelector('#stat').style.backgroundColor='blue';
}
});
ff.send(null);
}
  
let codeMessage=new BroadcastChannel('codeMessage');

codeMessage.addEventListener('message',event=>{
var pth2=document.querySelector('#computePath').innerHTML;
getShader(pth2,'compute.wgsl');
document.querySelector('#status').style.backgroundColor="blue";
let flDat=event.data.data;
var buffer = new ArrayBuffer(flDat.length*2);
var bufferView = new Uint16Array(buffer);
for (var i = 0; i < flDat.length; i++) {
bufferView[i] = flDat.charCodeAt(i);
}
// console.log(bufferView);
FS.writeFile('/shader/shader.wgsl',bufferView);
// document.querySelector('#startBtn').click();
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
document.querySelector('#status').style.backgroundColor="green";
normalResStart();
},1000);
});

const vsiz=document.querySelector('#vsiz');

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
// let vsz=vsiz.innerHTML;
// Module.ccall("startWebGPUi",null,"Number",[vsz]);
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
const tsl=new rSlider({target:'#timeslider',values:{min:0.05,max:2.50},
step:[0.05],labels:false,tooltip:true,scale:false,});
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
$ll=$ll/100;
$ll=($ll*1000);
tem.innerHTML=$ll;
vsiz.innerHTML=Math.round($ll/1000*window.innerHeight);
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16);
});



document.querySelector('#startBtn').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
getShader(pth2,'compute.wgsl');
normalResStart();
});

  
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});
