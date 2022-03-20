document.getElementById('btn2').addEventListener('click',function(){
let pth=document.getElementById('path').innerHTML;
let ff=new XMLHttpRequest();
ff.open("GET",pth,true);
ff.responseType="arraybuffer";
ff.onload=function(oEvent){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader1.toy',sfil);
}}
ff.send(null);
console.log('Wrote 1 shader to filesystem: \n -> ',pth);
});
