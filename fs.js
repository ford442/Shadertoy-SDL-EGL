
document.getElementById('cue').addEventListener('onchange',function(event){
var input=event.target;
var reader=new FileReader();
reader.onload=function(){
var arrayBuffer=reader.result;
var fil=new Uint8ClampedArray(arrayBuffer);
var filnm="/shader1.glsl";
console.log("Wrote: /shader1.glsl");
FS.writeFile(filnm,fil);
console.log('File: '+input.files[0].name);
};
reader.readAsArrayBuffer(input.files[0]);
});
