#include <emscripten.h>
#include <png.h>
#include <sstream>
#include <cstdio> 
#include <cstdlib>
#include <vector>
#include <cstring>

struct Frame {
  png_bytep* rows;
  int width;
  int height;
};

std::vector<Frame> frames;

int frameWidth = 0;
int frameHeight = 0;

extern "C" {
  void runApng(uint8_t* data, int width, int height) {

   // Allocate memory for the rows
    png_bytep* rows = new png_bytep[height];
    for (int y = 0; y < height; y++) {
      rows[y] = data + y * width * 4;
    }

    Frame frame = { rows, width, height };
    frames.push_back(frame);
  }

  void createAPNG(int size) {
        frameWidth = size;
    frameHeight = size;
    // Create a file to write the APNG
    FILE* fp = fopen("output.png", "wb");
    if (!fp) {
      fprintf(stderr, "Could not open file for writing\n");
      return;
    }
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
      fprintf(stderr, "Could not create PNG write struct\n");
      fclose(fp);
      return;
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
      fprintf(stderr, "Could not create PNG info struct\n");
      png_destroy_write_struct(&png, NULL);
      fclose(fp);
      return;
    }
    if (setjmp(png_jmpbuf(png))) {
      fprintf(stderr, "Error during PNG creation\n");
      png_destroy_write_struct(&png, &info);
      fclose(fp);
      return;
    }
    png_init_io(png, fp);
    // Set the image information
          fprintf(stderr, "IHDR width: ",frameWidth);

    png_set_IHDR(png, info, frameWidth, frameHeight, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    // Write each frame
   for (const auto& frame : frames) {
      png_write_image(png, frame.rows);
    }
    png_write_end(png, NULL);
    // Clean up
    fclose(fp);
    png_destroy_write_struct(&png, &info);
    // Free allocated memory
    for (auto& frame : frames) {
      delete[] frame.rows;
    }
    frames.clear();
  }
}

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
#await micropip.install('opencv-python')
#await micropip.install('exodide')
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

# Save or further process the APNG animation

apng_bytes = apng_animation.to_bytes()

# Encode to base64
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
