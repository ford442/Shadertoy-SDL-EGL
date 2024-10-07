#include <emscripten.h>

int main(){

EM_ASM({

    // https://cdn.jsdelivr.net/pyodide/v0.24.1/full/pyodide.js
const pyChannel = new BroadcastChannel('py_channel');
const imageChannel = new BroadcastChannel('imageChannel');
const imgOut = document.getElementById('mvi');
const pyBtn3 = document.getElementById('pyBtn3');
const pyBtn4 = document.getElementById('pyBtn4');
const fileInput = document.getElementById('fileInput'); // Replace 'fileInput' with your input's ID
const fileInput2 = document.getElementById('fileInput2'); // Replace 'fileInput' with your input's ID

function getDepth(){
// window.open('./depth.1ink');
const xhr = new XMLHttpRequest();
xhr.open('GET', 'https://noahcohn.com/depth009.3ijs', true);
xhr.responseType = 'arraybuffer';
console.log('got run');
function decodeUTF32(uint8Array, isLittleEndian = true) {
const dataView = new DataView(uint8Array.buffer);
let result = "";
for (let i = 0; i < uint8Array.length; i += 4) {
let codePoint;
if (isLittleEndian) {
codePoint = dataView.getUint32(i, true); // Little-endian
} else {
codePoint = dataView.getUint32(i, false); // Big-endian
}
result += String.fromCodePoint(codePoint);
}
return result;
}
xhr.onload = function() {
if (xhr.status === 200) {
const utf32Data = xhr.response;
const jsCode = decodeUTF32(new Uint8Array(utf32Data), true); // Assuming little-endian
const scr = document.createElement('script');
scr.type = 'module';
scr.text = jsCode;
setTimeout(function(){
document.body.appendChild(scr);
},200);
}
};
xhr.send();
var imgChan=new BroadcastChannel('imageURL');
imgChan.addEventListener('message',event=>{
document.querySelector('#imagePath').innerHTML=event.data.data;
document.querySelector('#example').click();
});
const loaderChannel = new BroadcastChannel('loaderChannel');
document.querySelector('#loadGLTF').addEventListener('click',function(){
document.querySelector('#saveName').innerHTML=document.querySelector('#savedName').value;
var GLloc=document.querySelector('#saveName').innerHTML;
loaderChannel.postMessage({GLloc});
});
document.querySelector('#savegltf').addEventListener('click',function(){
document.querySelector('#saveName').innerHTML=document.querySelector('#savedName').value;
});
}

// Add event listener for file selection
fileInput.addEventListener('change', (event) => {
const file = event.target.files[0];
if (file) {
const reader = new FileReader();
reader.onload = (e) => {
const imageDataURL = e.target.result;
getDepth();
setTimeout(function(){
imageChannel.postMessage({ imageDataURL });
},3500);};
reader.readAsDataURL(file);
setTimeout(function(){
document.querySelector('#tvi').style.position='absolute';
document.querySelector('#tvi').style.zIndex=3100;
document.querySelector('#tvi').style.pointerEvents='auto';
},5500);
}
});

pyBtn4.onclick = () => {
const divElement = document.querySelector('#imagePath'); // Replace 'myDiv' with your div's ID
const mtext = navigator.clipboard.readText(); // Read text from clipboard
divElement.textContent = mtext; // Set the div's text content
document.getElementById("pyBtn").click();
}

pyBtn3.onclick = () => {
getDepth();
setTimeout(function () {
const canvas = document.createElement('canvas');
canvas.width = imgOut.width;
canvas.height = imgOut.height;
const ctx = canvas.getContext('2d');
ctx.drawImage(imgOut, 0, 0);
// window.open('./depth.1ink');
//window.open('./depth/index.html');
// const imageDataURL = canvas.toDataURL();
const imageDataURL = imgOut.src;
imageChannel.postMessage({imageDataURL});
}, 4500);
setTimeout(function(){
document.querySelector('#tvi').style.position='absolute';
document.querySelector('#tvi').style.zIndex=3300;
document.querySelector('#tvi').style.pointerEvents='auto';
},6500);
};

pyChannel.addEventListener('message', (event) => {
const message = event.data;
console.log('got postmessage');
});

document.getElementById("pyBtn").addEventListener('click', () => {
    const pth = document.querySelector('#imagePath').innerHTML;
    processImageFromURL(pth);
});

document.getElementById("pyBtn5").addEventListener('click', () => {
    getDepth();
    setTimeout(function () {
     //   const canvas = document.createElement('canvas');
     //   canvas.width = imgOut.width;
     //   canvas.height = imgOut.height;
    //    const ctx = canvas.getContext('2d');
     //   ctx.drawImage(imgOut, 0, 0);
// window.open('./depth.1ink');
//window.open('./depth/index.html');
// const imageDataURL = canvas.toDataURL();
        const imageDataURL = imgOut.src;
        imageChannel.postMessage({imageDataURL});
    }, 4500);
    setTimeout(function(){
        document.querySelector('#tvi').style.position='absolute';
        document.querySelector('#tvi').style.zIndex=3300;
        document.querySelector('#tvi').style.pointerEvents='auto';
    },6500);
});

// Add an event listener to your file input element
fileInput2.addEventListener('change', (event) => {
document.querySelector('#scanvas').style.transform='scaleY(-1.0)';
const file = event.target.files[0];
if (file) {
const reader = new FileReader();
reader.onload = (e) => {
const imageDataURL = e.target.result;
processImage(imageDataURL);
};
reader.readAsDataURL(file);
}
});

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
console.log(base64Strings);
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
await micropip.install('essentia')
import os
import js
import base64
import pyodide
from PIL import Image
import io
import numpy as np
from apng import APNG, PNG
frames_data = []  # List to store decoded frame data

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
apng_base64
`,{globals})
.then(result => {
    // Get the base64 data back in JavaScript
  //  const apngBase64 = pyodide.globals.get("apngBase64");

    // Create a data URL
    const apngDataURL = "data:image/apng;base64," + result;

    // Now you can use apngDataURL to display the animation or trigger a download

    // Example: Displaying the animation in an <img> tag
    const img = document.createElement('img');
    img.src = apngDataURL;
    document.body.appendChild(img);

    // Example: Triggering a download
    const a = document.createElement('a');
    a.href = apngDataURL;
    a.download = 'animation.apng';
    a.click();
})
.catch(error => {
    console.error("Error in Pyodide:", error);
});

}

async function processImage(imageDataURL) {
let result;
let base64String;
    const img = new Image();
    img.src = imageDataURL;
    const maxSize = 1024; // Set your desired maximum size for the square
        let newWidth, newHeight, cropX, cropY;

base64String = imageDataURL.split(',')[1];

    if (img.width > img.height) {
        newWidth = newHeight = img.height;
        cropX = (img.width - img.height) / 2;
        cropY = 0;
    } else if (img.height > img.width) {
       newHeight = newWidth = img.width;
        cropX = 0;
        cropY = (img.width - img.height) / 2;
    }
    if (newWidth > maxSize) {
        newWidth = newHeight = maxSize;
            const canvas = document.createElement('canvas');
        canvas.width = newWidth;
        canvas.height = newHeight;
        img.width = newWidth;
        img.height = newHeight;
  //   document.getElementById('vsiz').innerHTML=newHeight;
    const ctx = canvas.getContext('2d', { alpha: true });
 document.getElementById('vsiz').innerHTML=newHeight;
    ctx.drawImage(img, cropX, cropY, newWidth, newHeight, 0, 0, newWidth, newHeight);
        const newImageDataURL = canvas.toDataURL(); // Get the new data URL
        imageDataURL = newImageDataURL;
        img.src = imageDataURL;
    }

// async function main() {
let pyodide = await loadPyodide({ indexURL: "./py", TOTAL_MEMORY: 1 * 1024 * 1024 * 1024 }); // 2GB
pyodide.globals.set("imageDataPy", imageDataURL);
await pyodide.loadPackage("micropip");
await pyodide.runPythonAsync(`
import micropip
import os
await micropip.install('numpy')
await micropip.install('scikit-image')
await micropip.install('cython')
await micropip.install('opencv-python')
import cv2

import pyodide
import pyximport
pyximport.install()
import js
import io
import base64
from PIL import Image
from io import BytesIO
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from skimage import data, img_as_float
from skimage import exposure
from skimage.filters import unsharp_mask
from skimage import filters, transform
import skimage.color as color
matplotlib.rcParams['font.size'] = 8
img_data:bytes = base64.b64decode('${base64String}')
img: Image.Image = Image.open(io.BytesIO(img_data))
img_array: np.ndarray = np.array(img)
p2: float
p98: float
p2, p98 = np.percentile(img_array, (2, 98))
js.console.log('got image PIL')


original_height, original_width = img_array.shape[:2]

tile_height = img_array.shape[0] // 4  # Divide height into 4
tile_width = img_array.shape[1] // 2  # Divide width into 2

tile1 = img_array[:tile_height, :tile_width]
tile2 = img_array[:tile_height, tile_width:]
tile3 = img_array[tile_height:2*tile_height, :tile_width]
tile4 = img_array[tile_height:2*tile_height, tile_width:]
tile5 = img_array[2*tile_height:3*tile_height, :tile_width]
tile6 = img_array[2*tile_height:3*tile_height, tile_width:]
tile7 = img_array[3*tile_height:, :tile_width]
tile8 = img_array[3*tile_height:, tile_width:]

del img_array  # Release original image data
def process_tile(tile: np.ndarray):
   rows, cols = tile.shape[:2]
   input_pts:np.float32 = np.float32([[0,0], [cols-1,0], [0,rows-1]])
   output_pts:np.float32 = np.float32([[cols-1,0], [0,0], [cols-1,rows-1]])
   M= cv2.getAffineTransform(input_pts , output_pts)
   dst = cv2.warpAffine(tile, M, (cols,rows))
   img_eq: np.ndarray = exposure.equalize_hist(dst)
   del dst
   resize4x: np.ndarray = transform.rescale(tile, 2)
   del tile
   js.console.log('2x resize SKI')
   result_1: np.ndarray = unsharp_mask(resize4x, radius=1, amount=1)
   del resize4x
   js.console.log('unsharp mask SKI')
   processed_tile: np.ndarray = transform.pyramid_reduce(result_1,2)
   del result_1
   js.console.log('1x downscale SKI')
   return processed_tile
processed_tile1 = process_tile(tile1)
del tile1
processed_tile2 = process_tile(tile2)
del tile2
processed_tile3 = process_tile(tile3)
del tile3
processed_tile4 = process_tile(tile4)
del tile4
processed_tile5 = process_tile(tile5)
del tile5
processed_tile6 = process_tile(tile6)
del tile6
processed_tile7 = process_tile(tile7)
del tile7
processed_tile8 = process_tile(tile8)
del tile8
row1 = np.hstack((processed_tile1, processed_tile2))
row2 = np.hstack((processed_tile3, processed_tile4))
row3 = np.hstack((processed_tile5, processed_tile6))
row4 = np.hstack((processed_tile7, processed_tile8))

top_half = np.vstack((row1, row2))
bottom_half = np.vstack((row3, row4))

result_image = np.vstack((top_half, bottom_half))
final_image = cv2.resize(result_image, (original_width, original_height))

img_eq_pil: Image.Image = Image.fromarray((final_image * 255).astype(np.uint8))
del result_image
buf: io.BytesIO = io.BytesIO()
img_eq_pil.save(buf, format='JPEG')
buf.seek(0)
img_str:str = base64.b64encode(buf.read()).decode('utf-8')
buf.close()
del img_eq_pil
img_str
`).then(result => {
const imgElement = document.getElementById('mvi');
imgElement.src = "data:image/png;base64," + result;
imgElement.width=window.innerHeight;
imgElement.height=window.innerHeight;
const downloadButton = document.getElementById('downloadButton'); // Assuming you have a button with this ID
// document.querySelector('#scanvas').style.transform='scaleY(-1.0)';
// document.getElementById('vsiz').innerHTML=document.getElementById('mvi').height;
document.querySelector('#startBtnC').click();
setTimeout(function(){
// pyBtn3.click();
},3500);
downloadButton.addEventListener('click', () => {
downloadImage(result, 'histogram_eq_image.jpg');
});
});
// }
// main();
}

function _arrayBufferToBase64(buffer) {
let binary = '';
const bytes = new Uint8Array(buffer);
const len = bytes.byteLength;
for (let i = 0; i < len; i++) {
binary += String.fromCharCode(bytes[i]);
}
return window.btoa(binary);

}

function downloadImage(base64String, filename) {
const link = document.createElement('a');
link.href = "data:image/jpeg;base64," + base64String;
link.download = filename;
document.body.appendChild(link);
link.click();
document.body.removeChild(link);
}

function processImageFromURL(pth) {
const xhr = new XMLHttpRequest();
document.querySelector('#mvi').src = pth;
xhr.open('GET', pth, true);
xhr.responseType = 'arraybuffer';
console.log('got py image');
xhr.onload = function() {
const imageData = xhr.response;
processImage(imageData); // Reuse the processImage function
};
xhr.send();
}

document.getElementById("pyBtn2").addEventListener('click',function() {
document.querySelector('#scanvas').style.transform='scaleY(-1.0)';
const imageDataUrl = document.getElementById('scanvas').toDataURL('image/jpeg'); // You can change the format if needed
document.getElementById('mvi').src=imageDataUrl;
document.querySelector('#mvi').style.transform='scaleY(-1.0)';
document.querySelector('#mvi').style.transform='scaleX(-1.0)';

});

</script>

<script type="module">

document.getElementById("startBtn").addEventListener('click',function(){
document.getElementById('mvi').play();
});

document.getElementById("mviBtn").addEventListener('click',function(){
document.getElementById('mvi').play();
});

document.getElementById("apngBtn").addEventListener('click',function(){
AddPNGs();
});

document.getElementById("apngBtn2").addEventListener('click',function(){
AddPNGsThreeJS();
});

/*
document.getElementById("apngBtn2").addEventListener('click',function(){

const xhr = new XMLHttpRequest();
xhr.open('GET', 'https://wasm.noahcohn.com/b3hd/w0-017-apng.3ijs', true); // Replace with your filename
xhr.responseType = 'arraybuffer'; // Get raw binary data
console.log('got run');

function decodeUTF32(uint8Array, isLittleEndian = true) {
const dataView = new DataView(uint8Array.buffer);
let result = "";
for (let i = 0; i < uint8Array.length; i += 4) {
let codePoint;
if (isLittleEndian) {
codePoint = dataView.getUint32(i, true); // Little-endian
} else {
codePoint = dataView.getUint32(i, false); // Big-endian
}
result += String.fromCodePoint(codePoint);
}
return result;
}

xhr.onload = function() {
console.log('got load');
if (xhr.status === 200) {
console.log('got script');
const utf32Data = xhr.response;
//const decoder = new TextDecoder('utf-32'); // Or 'utf-32be'
const jsCode = decodeUTF32(new Uint8Array(utf32Data), true); // Assuming little-endian
const scr = document.createElement('script');
//scr.type = 'module';
scr.text = jsCode;
//scr.dataset.moduleUrl = 'https://wasm.noahcohn.com/b3hd/'; // Base URL for module's relative paths
document.body.appendChild(scr);
setTimeout(function(){
var Module = libapng();
Module.onRuntimeInitialized = function(){
Module.callMain();
console.log('call main');
};
},2500);
}
};
xhr.send();
});

*/

document.getElementById("startBtn5").addEventListener('click',function(){
const xhr = new XMLHttpRequest();
xhr.open('GET', 'https://wasm.noahcohn.com/b3hd/w0-020-load-32.3ijs', true); // Replace with your filename
xhr.responseType = 'arraybuffer'; // Get raw binary data
console.log('got run');

function decodeUTF32(uint8Array, isLittleEndian = true) {
const dataView = new DataView(uint8Array.buffer);
let result = "";
for (let i = 0; i < uint8Array.length; i += 4) {
let codePoint;
if (isLittleEndian) {
codePoint = dataView.getUint32(i, true); // Little-endian
} else {
codePoint = dataView.getUint32(i, false); // Big-endian
}
result += String.fromCodePoint(codePoint);
}
return result;
}

xhr.onload = function() {
console.log('got load');
if (xhr.status === 200) {
console.log('got script');
const utf32Data = xhr.response;
//const decoder = new TextDecoder('utf-32'); // Or 'utf-32be'
const jsCode = decodeUTF32(new Uint8Array(utf32Data), true); // Assuming little-endian
const scr = document.createElement('script');
//scr.type = 'module';
scr.text = jsCode;
//scr.dataset.moduleUrl = 'https://wasm.noahcohn.com/b3hd/'; // Base URL for module's relative paths
document.body.appendChild(scr);
setTimeout(function(){
var Module = libload();
Module.onRuntimeInitialized = function(){
Module.callMain();
console.log('call main');
};
},2500);
}
};
xhr.send();

});

setTimeout(function(){
document.querySelector('#splash2').style.zIndex=3000;
document.querySelector('#splash2').style.display='none';
},4200);
setTimeout(function(){
document.querySelector('#splash1').style.zIndex=3000;
document.querySelector('#splash1').style.display='none';
},4500);

setTimeout(function(){
document.getElementById('vsiz').innerHTML=parseInt(window.innerHeight,10);
// document.getElementById('vsiz').innerHTML=parseInt(window.innerHeight,10)*3.0;
document.getElementById('startBtn5').click();
},1500);

setTimeout(function(){
window.scrollTo({
top: 0,
left: 0,
behavior: "smooth",
});
},1500);

document.getElementById("getThree").addEventListener('click',function(){
document.querySelector('#mvi').id='ivi';
// document.querySelector('#tvi').style.zIndex=1300;
document.querySelector('#tvi').hidden=true;
document.querySelector('#tvi').opacity=0.0;
document.querySelector('#tvi').id='mvi';
document.querySelector('#startBtnC').click();
});


document.querySelector('#btnGif1').addEventListener('click', () => {
document.querySelector('#btnGif1').src = './image/btn2.gif'; // Reset the GIF to the beginning
var canvas = document.querySelector('#scanvas'); // Replace 'myCanvas' with your canvas ID

var newCanvas = document.createElement('canvas');
newCanvas.width = canvas.width;
newCanvas.height = canvas.height;
newCanvas.id = 'fcan';
document.body.appendChild(newCanvas);

var flippedCanvas = document.querySelector('#fcan');

var flippedContext = flippedCanvas.getContext('2d');

flippedContext.imageSmoothingEnabled = false;
flippedContext.save();
flippedContext.scale(-1,-1);

// var image=flippedContext.getImageData(0,0,canvas.width,canvas.height);
var image=new Image();

// var image=flipImageData(flippedContext.getImageData(0,0,canvas.width,canvas.height));

// flippedContext.drawImage(image, 0, 0);
// flippedContext.putImageData(image, 0, 0);

var dataURL2 = canvas.toDataURL('image/jpeg',1.0); // Or 'image/png', 'image/webp', etc.
image.src=dataURL2;
flippedContext.drawImage(image, canvas.height*-1, canvas.height*-1,canvas.height,canvas.height);

var dataURL = canvas.toDataURL('image/jpeg',1.0); // Or 'image/png', 'image/webp', etc.

var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `Snapshot_${timestamp}.jpg`;

var link = document.createElement('a');
link.download = filename;// Set the desired filename
link.href = dataURL2;
link.click();
// flippedCanvas.remove(); // Remove from DOM
// flippedCanvas = null;// Nullify reference
});

});

return 0;
}
