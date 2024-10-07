#include <emscripten.h>



int main(){

EM_ASM({
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
