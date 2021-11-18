
document.getElementById('btn').addEventListener('click',function(){
Module.ccall('str');
});

document.getElementById('btn7').addEventListener('click',function(){
document.getElementById("contain2").height=1440;
document.getElementById("contain2").width=1440;
document.getElementById("canvas").height=1440;
document.getElementById("canvas").width=1440;
document.getElementById('btn4').style="background-color:grey;position:absolute;display:block;left:3%;top:33%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn5').style="background-color:pink;position:absolute;display:block;left:3%;top:43%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn3').style="background-color:red;position:absolute;display:block;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn6').style="background-color:yellow;position:absolute;display:block;left:3%;top:53%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn').style="background-color:red;position:absolute;display:block;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn7').style="background-color:red;position:absolute;display:block;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('shut').innerHTML=2;
document.getElementById('di').click();
Module.ccall("str");
});


document.getElementById('cue').addEventListener('onchange',function(event){
let input=event.target;
let reader=new FileReader();
reader.onload=function(){
let arrayBuffer=reader.result;
let fil=new Uint8ClampedArray(arrayBuffer);
let filnm="/shader1.glsl";
FS.writeFile(filnm,fil);
console.log('File: '+input.files[0].name);
}
reader.readAsArrayBuffer(input.files[0]);
}
