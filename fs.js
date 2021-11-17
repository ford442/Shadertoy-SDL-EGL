
document.getElementById('cue').addEventListener('onchange',function(event){
let input=event.target;
let reader=new FileReader();
reader.onload=function(){
let arrayBuffer=reader.result;
let fil=new Uint8ClampedArray(arrayBuffer);
let filnm="/shader1.glsl";
FS.writeFile(filnm,fil);
console.log('File: '+input.files[0].name);
};
reader.readAsArrayBuffer(input.files[0]);
};
