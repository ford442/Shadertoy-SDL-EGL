EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');
let running=0;

function flipImageData(imageData){
const width=imageData.width;
const height=imageData.height;
const data=imageData.data;
for(let y=0;y<height/2;y++){
for(let x=0;x<width;x++){
const topIndex=(y*width+x)*4;
const bottomIndex=((height-1-y)*width+x)*4;
for(let c=0;c<4;c++){
[data[topIndex+c],data[bottomIndex+c]]=[data[bottomIndex+c],data[topIndex+c]];
}}}
return imageData;
}

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}}

let pause='ready';

function canvasStart(){
const vvic=document.querySelector('#mvi');
const srsiz=document.querySelector('#srsiz').innerHTML;
const vsiz=document.querySelector('#vsiz').innerHTML;
const SiZ=window.innerHeight;
const w$=parseInt(vsiz,10);
vvic.width=SiZ;
const h$=parseInt(vsiz,10);
vvic.height=SiZ;
console.log("canvas size: ",h$,", ",w$);
const cnvb=new OffscreenCanvas(h$,w$); 
// document.querySelector('#contain2').appendChild(cnvb);
const cnv=document.querySelector('#scanvas');
const cnvc=document.querySelector('#bcanvas');
cnv.height=SiZ;
cnvb.height=vsiz;
cnvc.height=vsiz;
cnvc.style.height=vsiz+'px';
cnv.width=SiZ;
cnvb.width=vsiz;
cnvc.width=vsiz;
cnvc.style.width=vsiz+'px';
const gl3=cnvb.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
gl3.imageSmoothingEnabled=false;
const fileStream=FS.open('/video/frame.gl','w');
function drawFrame() {
if (pause === 'ready') {
gl3.clearRect(0, 0, w$, h$);
gl3.drawImage(vvic, 0, 0, SiZ, SiZ, 0, 0, w$, h$);
}
const image = gl3.getImageData(0, 0, w$, h$);
const imageData = image.data;
const pixelData = new Float64Array(imageData);
FS.write(fileStream, pixelData, 0, pixelData.length, 0);
Module.ccall("frmOn");
}
if (running == 0) {
setTimeout(() => {
Module.ccall("startWebGPUC", null,"Number",[vsiz,srsiz]);
running = 1;
setInterval(drawFrame, 16.6); 
}, 250);
} else {
setInterval(drawFrame, 16.6);
}
}
 
function videoStart(){
const vvi=document.querySelector('#mvi');
let vw$=vvi.videoWidth;
let vh$=vvi.videoHeight;
let SiZ=window.innerHeight;
vvi.height=vh$;
vvi.width=vw$;
let w$=parseInt(document.querySelector("#mvi").width);
let h$=parseInt(document.querySelector("#mvi").height);
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
if(running==0){
setTimeout(function(){
Module.ccall("startWebGPUi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
Module.ccall("startWebGPUbi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
const cnvb=new OffscreenCanvas(h$,w$); 
// document.querySelector('#contain2').appendChild(cnvb);
const cnv=document.querySelector('#scanvas');
const cnvc=document.querySelector('#bcanvas');
cnv.height=SiZ;
cnvb.height=vsiz;
cnvc.height=vsiz;
cnvc.style.height=vsiz+'px';
cnv.width=SiZ;
cnvb.width=vsiz;
cnvc.width=vsiz;
cnvc.style.width=vsiz+'px';
const gl3=cnvb.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// var image=flipImageData(gl3.getImageData(0,0,w$,h$));
var image=gl3.getImageData(0,0,w$,h$);
var imageData=image.data;
// let pixelData=new Uint8ClampedArray(imageData);
var pixelData=new Float64Array(imageData);
// var pixelData=new Float64Array(imageData,0,la);
let fileStream=FS.open('/video/frame.gl','w');
FS.write(fileStream,pixelData,0,pixelData.length,0);
Module.ccall("frmOn");
setInterval(function(){
gl3.clearRect(0,0,w$,h$);  
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// image=flipImageData(gl3.getImageData(0,0,w$,h$));
image=gl3.getImageData(0,0,w$,h$);
imageData=image.data;
// pixelData=new Uint8ClampedArray(imageData);
pixelData=new Float64Array(imageData);
 // pixelData=new Float64Array(imageData);
 //  const externalTexture = gpuDevice.createTexture({size: [imageWidth, imageHeight, 1],format: 'rgba8unorm',usage: GPUTextureUsage.TEXTURE_BINDING | GPUTextureUsage.COPY_DST });
// gpuQueue.writeTexture({ texture }, pixelData, { bytesPerRow }, { width: w$, height: h$ } );
// pixelData=new Float64Array(imageData,0,la);  // causes sub-array data array-reforming (slower)
FS.write(fileStream,pixelData,0,pixelData.length,0);
Module.ccall("frmOn");
},16.666);
}

function imageStart(){
var vvi=document.querySelector('#ivi');
let SiZ=window.innerHeight;
let w$=parseInt(document.querySelector("#ivi").width);
let h$=parseInt(document.querySelector("#ivi").height);
if(running==0){
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#scanvas');
var offsetX=Math.floor((w$-h$)/2);
var offsetY=Math.floor((h$-w$)/2);
cnvb.height=SiZ;
cnv.height=h$-offsetY;
cnvb.width=SiZ;
cnv.width=w$-offsetX;
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
// const gl3=cnvb.getContext('2d',{colorType:'float64',alpha:true}); // 
const gl3=cnv.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
}); // 
gl3.drawImage(vvi,0,0,w$-offsetX,h$-offsetY,0,0,w$-offsetX,h$-offsetY);
// let image=flipImageData(gl3.getImageData(0,0,w$,h$));
var image=gl3.getImageData(0,0,w$-offsetX,h$-offsetY);
var imageData=image.data;
let pixelData=new Uint8ClampedArray(imageData);
// var pixelData=new Float64Array(imageData);
// var pixelData=new Float64Array(imageData,0,la);
var fileStream=FS.open('/video/frame.gl','w');
FS.write(fileStream,pixelData,0,pixelData.length,0);
Module.ccall("frmOn");
setInterval(function(){
gl3.clearRect(0,0,w$,h$);  
gl3.drawImage(vvi,0,0,w$-offsetX,h$-offsetY,0,0,w$-offsetX,h$-offsetY);
// let image=flipImageData(gl3.getImageData(0,0,w$,h$));
var image=gl3.getImageData(0,0,w$-offsetX,h$-offsetY);
var imageData=image.data;
var pixelData=new Float64Array(imageData);
FS.write(fileStream,pixelData,0,pixelData.length,0);
Module.ccall("frmOn");
},16.666);
}

function imageStartSR(){
let vvi=document.querySelector('#ivi');
let SiZ=window.innerHeight;
let w$=parseInt(document.querySelector("#ivi").width);
let h$=parseInt(document.querySelector("#ivi").height);
if(running==0){
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
running=1;
},250);
}else{
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
},250);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#scanvas');
cnv.height=SiZ;
cnvb.height=h$;
cnv.width=SiZ;
cnvb.width=w$;
let offS=Math.floor((w$-h$)/2);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
// const gl3=cnvb.getContext('2d',{colorType:'float64',alpha:true}); // 
const gl3=cnvb.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
// colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
}); // 
 const gl4=cnv.getContext('2d',{
colorType:'float64',
alpha:true,
willReadFrequently:false,
stencil:false,
depth:false,
// colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
}); // 
gl3.drawImage(vvi,0,0,w$,h$,0,0,w$,h$);
// let image=flipImageData(gl3.getImageData(0,0,w$,h$));
let image=gl3.getImageData(0,0,w$,h$);
let imageData=image.data;
// let pixelData=new Uint8ClampedArray(imageData);
let pixelData=new Float64Array(imageData);
// var pixelData=new Float64Array(imageData,0,la);
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
setInterval(function(){
image=gl4.getImageData(0,0,SiZ,SiZ);
gl3.drawImage(image,0,offS,h$,h$,0,0,h$,h$);
let image=gl3.getImageData(0,0,w$,h$);
imageData=image.data;
pixelData=new Float64Array(imageData);
FS.writeFile('/video/frame.gl',pixelData);
Module.ccall("frmOn");
},16.666);
}

function regularStart(){
let SiZ=window.innerHeight;
let cnvb=document.querySelector('#scanvas');
cnvb.height=SiZ;
cnvb.width=SiZ;
if(running==0){
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
running=1;
},50);
}else{
setTimeout(function(){
let srsiz=document.querySelector('#srsiz').innerHTML;let vsiz=document.querySelector('#vsiz').innerHTML;
Module.ccall("startWebGPUbi",null,"Number",[vsiz,srsiz]);
console.log('Starting..');
},50);
}
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

function getModel(pth,fname){
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading ONNX Model';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/model/'+fname,sfil);
document.querySelector('#stat').innerHTML='Downloaded ONNX Model';
document.querySelector('#stat').style.backgroundColor='blue';
}
});
ff.send(null);
}
  
let codeMessage=new BroadcastChannel('codeMessage');
let codeMessageV=new BroadcastChannel('codeMessageV');

codeMessage.addEventListener('message',event=>{
var pth2=document.querySelector('#computePathNovid').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
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
regularStart();
},50);
});

codeMessageV.addEventListener('message',event=>{
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
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
regularStart();
// imageStart();
// videoStart();
},50);
});

const vsiz=document.querySelector('#vsiz');
let menuSz=parseInt(window.innerWidth*.5,10);

document.querySelector('#startBtn').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
videoStart();
});

document.querySelector('#startBtn2').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
var pth5=document.querySelector('#onnxPath').innerHTML;
getModel(pth5,'model.onnx');
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePathNovid').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
regularStart();
});

document.querySelector('#startBtnC').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
setTimeout(function(){
canvasStart();
},3000);
});

document.querySelector('#startBtnI').addEventListener('click',function(){
var pth=document.querySelector('#path').innerHTML;
getShader(pth,'shader.wgsl');
var pth2=document.querySelector('#computePath').innerHTML;
var pth3=document.querySelector('#fragPath').innerHTML;
var pth4=document.querySelector('#vertPath').innerHTML;
getShader(pth2,'compute.wgsl');
getShader(pth3,'frag2.wgsl');
getShader(pth4,'vert.wgsl');
setTimeout(function(){
imageStart();
},1000);
});

document.querySelector('#moveFwd').addEventListener('click',function(){
Module.ccall("frmsOff");
pause='loading'; // Toggle pause on/off
setTimeout(function(){
pause='ready'; // Toggle pause on/off
Module.ccall("frmsOn");
},1900);
});

document.querySelector('#sizeUp').addEventListener('click',function(){
Module.ccall("zoomIn");
});

document.querySelector('#sizeDown').addEventListener('click',function(){
Module.ccall("zoomOut");
});

document.querySelector('#moveDown').addEventListener('click',function(){
Module.ccall("panDown");
});

document.querySelector('#moveUp').addEventListener('click',function(){
Module.ccall("panUp");
});

document.querySelector('#moveRight').addEventListener('click',function(){
Module.ccall("panRight");
});

document.querySelector('#moveLeft').addEventListener('click',function(){
Module.ccall("panLeft");
});

setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});
