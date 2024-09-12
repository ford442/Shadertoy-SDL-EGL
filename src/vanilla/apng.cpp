#include <emscripten.h>
#include <emscripten/bind.h>
#include <png.h>

png_structp png_ptr_write;
png_infop info_ptr_write;

png_bytep* frame_data = nullptr; 
png_bytepp row_pointers = nullptr;
int height=1024;
int CframeCount=10;

void generate(){
int num_frames = 20; 
frame_data = (png_bytep*) malloc(sizeof(png_bytep) * num_frames);
row_pointers = (png_bytepp) malloc(sizeof(png_bytepp) * num_frames * height); 
frame_data[CframeCount - 1] = (png_bytep) malloc(height * height * 4);
for (int y = 0; y < height; ++y) {
row_pointers[(CframeCount - 1) * height + y] = frame_data[CframeCount - 1] + y * height * 4;
}
}

extern"C"{

void runApng(){
generate();
}

}
void assembleAndSaveAnimatedPNG(png_bytep* frame_data, png_bytepp* row_pointers, int num_frames, int width, int height, int* delays) {
    // ... (Create APNG write and info structs, set up error handling) ... 
    // Initialize PNG writing
    png_set_IHDR(png_ptr_write, info_ptr_write, width, height, 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    // Write animation control chunk (acTL) using png_set_acTL
    png_set_acTL(png_ptr_write, info_ptr_write, num_frames, 0); // 0 for infinite loop
    // Write each frame
    for (int i = 0; i < num_frames; ++i) {
        // Write frame control chunk (fcTL) using png_set_next_frame_fcTL
        png_set_next_frame_fcTL(png_ptr_write, info_ptr_write, width, height, 0, 0, 
                                delays[i] * 1000 / 1000, 1000, // Convert delay to seconds (numerator/denominator)
                                PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE); 
        // Write the image data for the frame
        png_write_image(png_ptr_write, *(row_pointers + i * height)); 
    }
    // ... (rest of the function)
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
