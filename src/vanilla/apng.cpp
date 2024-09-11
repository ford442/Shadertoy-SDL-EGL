#include <emscripten.h>
#include <emscripten/bind.h>
#include "/content/RAMDRIVE2/libpng-1.6.39/png.h"

png_structp png_ptr_write;
png_infop info_ptr_write;

png_bytep* frame_data = nullptr; 
png_bytepp row_pointers = nullptr;

void generate(){
int num_frames = 20; 
frame_data = (png_bytep*) malloc(sizeof(png_bytep) * num_frames);
row_pointers = (png_bytepp*) malloc(sizeof(png_bytepp) * num_frames * Cheight); 
frame_data[CframeCount - 1] = (png_bytep) malloc(Cwidth * Cheight * 4);
for (int y = 0; y < Cheight; ++y) {
row_pointers[(CframeCount - 1) * Cheight + y] = frame_data[CframeCount - 1] + y * Cwidth * 4;
}
}

extern"C"{

void runApng(){
generate();
}

}

void assembleAndSaveAnimatedPNG(png_bytep* frame_data, png_bytepp* row_pointers, int num_frames, int width, int height, int* delays) {
// Create the APNG write struct
png_ptr_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
if (!png_ptr_write) {
fprintf(stderr, "Error: could not create PNG write struct\n");
return;
}
// Create the APNG info struct
info_ptr_write = png_create_info_struct(png_ptr_write);
if (!info_ptr_write) {
png_destroy_write_struct(&png_ptr_write, nullptr);
fprintf(stderr, "Error: could not create PNG info struct\n");
return;
}
// Set up error handling (implement png_error and png_warning)
if (setjmp(png_jmpbuf(png_ptr_write))) {
png_destroy_write_struct(&png_ptr_write, &info_ptr_write);
fprintf(stderr, "Error during PNG writing\n");
return;
}

// ... (Set up output file or buffer using Emscripten's file system API)

// Initialize PNG writing
png_set_IHDR(png_ptr_write, info_ptr_write, width, height, 8, PNG_COLOR_TYPE_RGBA,
 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
// Write animation control chunk (acTL)
png_write_acTL(png_ptr_write, info_ptr_write, num_frames, 0); // 0 for infinite loop
// Write each frame
for (int i = 0; i < num_frames; ++i) {
// Write frame control chunk (fcTL)
png_write_fcTL(png_ptr_write, info_ptr_write, width, height, 0, 0, delays[i] / 1000.0, 
 PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE);
// Write the image data for the frame
png_write_image(png_ptr_write, row_pointers + i * height);
}
// End the write operation
png_write_end(png_ptr_write, info_ptr_write);
// Clean up
png_destroy_write_struct(&png_ptr_write, &info_ptr_write);
for (int i = 0; i < num_frames; ++i) {
free(frame_data[i]);
}
free(frame_data);
free(row_pointers);
}

int main(){

EM_ASM({

document.getElementById("apngBtn").addEventListener('click',function(){
const acanvas = document.querySelector("#scanvas");
const ctx = acanvas.getContext("2d");
const siz=parseInt(acanvas.height);
const fileStream=FS.open('/frame.png','w+');
var ii=0;

function render() {
if (ii>21) {
return;
}
if (ii>20) {

} else {
ii++;
console.log('frame ',ii);
const image = ctx.getImageData(0, 0, w$, h$);
const imageData = image.data;
const pixelData = new Float32Array(imageData);
FS.write(fileStream, pixelData, 0, pixelData.length, 0);
setTimeout(function(){
render();
},100);
}
}

setTimeout(function() {
Module.ccall('runApng');
render(); 
}, 100); // Give some time for the initial frame to be drawn

});

});


return 0;
}
