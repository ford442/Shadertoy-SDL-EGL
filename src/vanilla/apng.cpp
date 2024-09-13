#include <emscripten.h>
#include <emscripten/bind.h>
#include <png.h>
#include <sstream> // Include the necessary header for std::stringstream
#include <cstdio> 

png_structp png_ptr_write;
png_infop info_ptr_write;

struct PngData {
png_bytep* rows;
png_uint_32 width;
png_uint_32 height;
};

PngData decoded_png_data;
png_bytep* frame_data = nullptr;
png_bytepp row_pointers = nullptr;
int CframeCount=10;
int num_frames = 10;

void read_png(FILE *fp, int sig_read) {
png_structp png_ptr;
png_infop info_ptr;
png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr = png_create_info_struct(png_ptr);
png_init_io(png_ptr, fp);
png_set_sig_bytes(png_ptr, sig_read);
png_read_info(png_ptr, info_ptr);
png_uint_32 width, height;
int bit_depth, color_type, interlace_type;
png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL,NULL);
decoded_png_data.width = width;
decoded_png_data.height = height;
decoded_png_data.rows = (png_bytep*) malloc(sizeof(png_bytep) * height);
for (int y = 0; y < height; y++) {
decoded_png_data.rows[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
}
png_read_image(png_ptr, decoded_png_data.rows);
png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

EMSCRIPTEN_KEEPALIVE
int writePNG(const unsigned char* imageData, int frameNumber, int width, int height) {
png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
if (!png_ptr) {
fprintf(stderr, "Error: could not create PNG write struct\n");
return 1;
}
png_infop info_ptr = png_create_info_struct(png_ptr);
if (!info_ptr) {
png_destroy_write_struct(&png_ptr, nullptr);
fprintf(stderr, "Error: could not create PNG info struct\n");
return 1;
}
// Set up error handling (implement png_error and png_warning)
if (setjmp(png_jmpbuf(png_ptr))) {
png_destroy_write_struct(&png_ptr, &info_ptr);
fprintf(stderr, "Error during PNG writing\n");
return 1;
}
std::stringstream ss;
ss << "/frames/frame" << frameNumber << ".png";
std::string fileName = ss.str();
// Open the file for writing
FILE* fp = fopen(fileName.c_str(), "wb");
if (!fp) {
fprintf(stderr, "Error: could not open file %s\n", fileName.c_str());
return 1;
}
png_init_io(png_ptr, fp);
png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA,
 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
png_write_info(png_ptr, info_ptr); 
png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
for (int y = 0; y < height; ++y) {
row_pointers[y] = (png_bytep)(imageData + y * width * 4);
}
png_write_image(png_ptr, row_pointers);
png_write_end(png_ptr, nullptr);
// Clean up
fclose(fp);
png_destroy_write_struct(&png_ptr, &info_ptr);
free(row_pointers);
return 0; // Indicate success
}

int assembleAPNG(int* delays, int num_frames, int width, int height) {
png_ptr_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr_write = png_create_info_struct(png_ptr_write);
png_set_IHDR(png_ptr_write, info_ptr_write, width, height, 8, PNG_COLOR_TYPE_RGBA,
PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
png_set_acTL(png_ptr_write, info_ptr_write, num_frames, 0); 

for (int i = 0; i < num_frames; ++i) {
std::stringstream ss;
ss << "/frames/frame" << (i + 1) << ".png";
std::string fileName = ss.str();
FILE* fp = fopen(fileName.c_str(), "r");
unsigned char header[8];
fread(header, 1, 8, fp);
printf("File Header for %s: ", fileName.c_str());
for (int j = 0; j < 8; j++) {
printf("%02X ", header[j]); 
}
printf("\n");
rewind(fp);
read_png(fp, 0);
png_set_next_frame_fcTL(png_ptr_write, info_ptr_write, decoded_png_data.width, decoded_png_data.height, 0, 0, 
static_cast<png_uint_16>(delays[i]), 1000, PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE); 
png_write_image(png_ptr_write, decoded_png_data.rows);
fclose(fp);
for (int y = 0; y < decoded_png_data.height; y++) {
free(decoded_png_data.rows[y]);
}
free(decoded_png_data.rows);
}
png_write_end(png_ptr_write, info_ptr_write);
png_destroy_write_struct(&png_ptr_write, &info_ptr_write);
return 0; 
}

extern "C" {

void createAPNG(int* delays,int num_frames,int size){
assembleAPNG(delays,num_frames,size);
}

void savePNG(const unsigned char* imageData,int frameNumber,int size){
writePNG(imageData,frameNumber,size);
}

}

int main(){

EM_ASM({
FS.mkdir('/frames');
document.getElementById("apngBtn").addEventListener('click',function(){
const acanvas = document.querySelector("#scanvas");
const ctx = acanvas.getContext("2d");
const siz = parseInt(acanvas.height);
let ii = 0;
const delays = []; 

function render() {
if (ii > 21) {
// Animation complete, assemble APNG
Module.ccall('createAPNG', 'number', 
 ['array', 'number', 'number'], 
 [delays, ii, siz]); 
return;
}
ii++;
console.log('Frame: ', ii);
const image = ctx.getImageData(0, 0, siz, siz);
const imageData = image.data;
Module.ccall('savePNG', 'number', ['array', 'number', 'number'], [imageData, ii, siz]);
delays.push(100); 
setTimeout(function(){
render();
}, 100);
}
setTimeout(function() {
render(); 
}, 100); 
});
});

});

return 0;
}
