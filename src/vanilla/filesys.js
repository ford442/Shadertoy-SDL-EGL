function rrr(){
var pth='https://wasm.noahcohn.com/b3hd/model.onnx';
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
ff.onload=function(oEvent){
const sarrayBuffer=ff.response;
if(sarrayBuffer){
const sfil=new Uint8ClampedArray(sarrayBuffer);
setTimeout(function(){
FS.writeFile('/model.onnx',sfil);
console.log("Got ONNX model.");
},1150);
}};
}

document.getElementById('startBtn3').addEventListener('click',function(){
rrr();
});
