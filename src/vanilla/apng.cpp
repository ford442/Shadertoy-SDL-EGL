#include <emscripten.h>
#include <png.h>
#include <sstream>
#include <cstdio> 
#include <cstdlib>

png_structp png_aptr_write;
png_infop info_aptr_write;

struct PngData {
png_bytep* rows;
png_uint_32 width;
png_uint_32 height;
};

PngData decoded_png_data;

png_bytep* frame_data=nullptr;
png_bytepp row_pointers=nullptr;

int CframeCount=10;
int num_frames=10;

void read_png(FILE *fp, int sig_read) {
png_structp png_ptr;
png_infop info_ptr;
png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr=png_create_info_struct(png_ptr);
png_init_io(png_ptr, fp);
png_set_sig_bytes(png_ptr, sig_read);
png_read_info(png_ptr, info_ptr);
png_uint_32 width, height;
int bit_depth, color_type, interlace_type;
png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL,  NULL);
decoded_png_data.width=width;
decoded_png_data.height=height;
decoded_png_data.rows=(png_bytep*) malloc(sizeof(png_bytep) * height);
for (int y=0; y < height; y++) {
decoded_png_data.rows[y]=(png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
}
png_read_image(png_ptr, decoded_png_data.rows);
png_read_end(png_ptr, NULL);
png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
return;
}


void runApngC(int size) {
int delay=500, num_frames=10;
png_aptr_write=png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_aptr_write=png_create_info_struct(png_aptr_write);
png_structp png_write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
png_infop info_ptr_write = png_create_info_struct(png_write_ptr);
png_set_IHDR(png_aptr_write, info_aptr_write, size, size, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
png_set_acTL(png_aptr_write, info_aptr_write, 10, 0); 

for (int i=0; i < 10; ++i) {
std::stringstream ss;
ss << "/frames/frame" << (i + 1) << ".png";
std::string fileName=ss.str();
FILE* fp=fopen(fileName.c_str(), "rb",[0777]);
FILE* fpw=fopen(fileName.c_str(), "wb",[0777]);
unsigned int rowbytes, j;
png_byte** row_pointers; // pointer to image bytes
row_pointers = (png_byte**)malloc(sizeof(png_byte*) * size);
rowbytes = png_get_rowbytes(png_write_ptr, info_ptr_write);
size_t image_size = size * size * 4;
unsigned char* image_data = (unsigned char*)malloc(image_size);
fread(image_data, image_size, 1, fp);
for (j=0; j<size; j++){
row_pointers[i] = (png_byte*)malloc(4*size);
}
for (j=0; j<size; j++){
row_pointers[j] = image_data + j*rowbytes;
}

png_init_io(png_write_ptr, fpw);
png_set_compression_level(png_write_ptr, 9);
png_set_IHDR(png_write_ptr, info_ptr_write, size, size, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    
         png_write_info(png_write_ptr, info_ptr_write);

    
png_write_image(png_write_ptr, row_pointers);
png_write_end(png_write_ptr, NULL);
read_png(fp, 0);
png_set_next_frame_fcTL(png_aptr_write,info_aptr_write,decoded_png_data.width,decoded_png_data.height,0,0,100,1000, PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE); 
png_write_image(png_aptr_write, decoded_png_data.rows);
fclose(fp);
}
png_write_end(png_aptr_write, NULL);
png_destroy_write_struct(&png_aptr_write, &info_aptr_write);
return;
}

extern "C" {

void runApng(int sz) {
runApngC(sz);
return;
}

}

int main(){

EM_ASM({
FS.mkdir('/frames');
document.getElementById("apngBtn").addEventListener('click',function(){
const acanvas=document.querySelector("#scanvas");
    const ctx=acanvas.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});

const siz=parseInt(acanvas.height);
let ii=0;
let totalFrames=0;
const delay=500; 

function render() {
totalFrames++;
if (totalFrames%30==0) {
if (ii > 10) {
Module.ccall("runApng",null,["Number"],[siz]);
return;
}
ii++;
console.log('Frame: ', ii);

const image = ctx.getImageData(0, 0, siz, siz); // Assuming square canvas
const imageData = image.data;
const pixelData = new Uint8Array(imageData);

const fileStream=FS.open('/frames/frame' + ii + '.png', 'w+', { encoding: 'binary',mode:0777 });
 console.log('/frames/frame' + ii + '.png');
// const encoder=new TextEncoder(); // To convert the string to Uint8Array
// const uint8Array=encoder.encode(dataURL);
FS.write(fileStream, pixelData, 0, pixelData.length, 0); 
FS.close(fileStream);
}
setTimeout(function(){
render();
}, 16);
}

setTimeout(function() {
render(); 
}, 100); 
});

});

return 0;
}

