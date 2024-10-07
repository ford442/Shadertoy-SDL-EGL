#include <emscripten.h>

int main(){

EM_ASM({

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

FS.mkdir('/frames');

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

});

return 0;
}
