document.getElementById('btn2').addEventListener('click',function(){
let pth=document.getElementById('path').innerHTML;
let ff=new XMLHttpRequest();
ff.open("GET",pth,true);
ff.responseType="arraybuffer";
ff.onload=function(oEvent){
var arrayBuffer=ff.response;
if(arrayBuffer){
var fil=new Uint8ClampedArray(arrayBuffer);
FS.writeFile('/shader/shader1.toy',fil);
}}
ff.send(null);
console.log('Wrote 1 shader to filesystem.');
}}
ff4.send(null);
});
