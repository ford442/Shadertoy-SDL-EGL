#include <emscripten.h>

int main(){

EM_ASM({

let cnv1=document.querySelector('#scanvas');
let base64Strings=[];
let currentApngFrame=0;

function AddPNGs_ctx() {
let apngCtx=cnv1.getContext('2d');
imageStrings[currentApngFrame]=apngCtx.getImageData(0, 0, cnv1.height, cnv1.height);
currentApngFrame++;
if(currentApngFrame<10){
setTimeout(function(){
AddPNGs();
},200);
}else{
const pngCanvas=createElement('canvas');
const pngCtx=pngCanvas.getContext('2d');
pngCanvas.height=cnv1.height;
pngCanvas.width=cnv1.height;
for (var i=0;i<10;i++){
pngCtx.putImageData(imageStrings[i]);
base64Strings[i]=pngCtx.toDataURL().split(',')[1];
}
MakeAPNG();
}
}

function AddPNGs() {
base64Strings[currentApngFrame]=cnv1.toDataURL().split(',')[1];;
currentApngFrame++;
if(currentApngFrame<10){
setTimeout(function(){
AddPNGs();
},200);
}else{
MakeAPNG();
}
}

function AddPNGsThreeJS() {
let cnv2=document.querySelector('canvas.#mvi');
base64Strings[currentApngFrame]=cnv2.toDataURL().split(',')[1];;
currentApngFrame++;
if(currentApngFrame<10){
setTimeout(function(){
AddPNGs();
},200);
}else{
MakeAPNG();
}
}

async function MakeAPNG() {
// console.log(base64Strings);
let pyodide = await loadPyodide();
// pyodide.globals.set("base64Strings", base64Strings);
const globals = pyodide.toPy({ imgStrings: base64Strings });
await pyodide.loadPackage("micropip");
await pyodide.runPythonAsync(`
import micropip
await micropip.install('numpy')
await micropip.install('cython')
await micropip.install('apng')
await micropip.install('pillow')
import os
import js
import base64
import pyodide
from PIL import Image
import io
import numpy as np
from apng import APNG, PNG
frames_data = []
apng_animation = APNG()

for base64_string in imgStrings:
        img_data = base64.b64decode(base64_string)
        img = Image.open(io.BytesIO(img_data))
        img_array = np.array(img)
        frames_data.append(img_array)

for frame_data in frames_data:
        img = Image.fromarray(frame_data)
        with io.BytesIO() as output:
            img.save(output, format="PNG")
            png_bytes = output.getvalue()
        png_image = PNG.from_bytes(png_bytes)
        apng_animation.append(png_image, delay=200, delay_den=1000)

apng_bytes = apng_animation.to_bytes()
apng_base64 = base64.b64encode(apng_bytes).decode('ascii')
apng_base64`,{globals}).then(result => {

    const apngDataURL = "data:image/apng;base64," + result;
    const img = document.createElement('img');
    img.src = apngDataURL;
    document.body.appendChild(img);

    const a = document.createElement('a');
    a.href = apngDataURL;
    a.download = 'animation.apng';
    a.click();
})
.catch(error => {
    console.error("Error in Pyodide:", error);
});

}

document.getElementById("apngBtn").addEventListener('click',function(){
AddPNGs();
});

document.getElementById("apngBtn2").addEventListener('click',function(){
AddPNGsThreeJS();
});

});

return 0;
}
