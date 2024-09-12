#include <emscripten.h>
#include <emscripten/bind.h>
#include <png.h>

png_structp png_ptr_write;
png_infop info_ptr_write;

struct PngData {
    png_bytep* rows;
    int width;
    int height;
};
PngData decoded_png_data;

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

void read_png(FILE *fp, int sig_read) {
   png_structp png_ptr;
   png_infop info_ptr;
   png_uint_32 width, height;
   int bit_depth, color_type, interlace_type;    // After reading the image information
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &decoded_png_data.width, &decoded_png_data.height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    // Allocate memory for row pointers and read the image data
    decoded_png_data.rows = (png_bytep*) malloc(sizeof(png_bytep) * decoded_png_data.height);
    for (int y = 0; y < decoded_png_data.height; y++) {
        decoded_png_data.rows[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, decoded_png_data.rows);
    // ... (rest of your read_png code, including cleanup)
}

extern "C" {

int runApng(const char** pngFilePaths, int* delays, int num_frames, int width, int height) {
        // ... (Create APNG write and info structs, set up error handling) ... 

        // Initialize PNG writing
        png_set_IHDR(png_ptr_write, info_ptr_write, width, height, 8, PNG_COLOR_TYPE_RGBA,
                     PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

        // Write animation control chunk (acTL) using png_set_acTL
        png_set_acTL(png_ptr_write, info_ptr_write, num_frames, 0); 

        // Read and write each frame
        for (int i = 0; i < num_frames; ++i) {
            // Open the PNG file from Emscripten FS
            FILE* fp = fopen(pngFilePaths[i], "rb");
            if (!fp) {
                fprintf(stderr, "Error: could not open file %s\n", pngFilePaths[i]);
                return 1; 
            }

            // Read the PNG file
            read_png(fp, 0); 

            // Write frame control chunk (fcTL)
            png_set_next_frame_fcTL(png_ptr_write, info_ptr_write, decoded_png_data.width, decoded_png_data.height, 0, 0, 
                                    delays[i] * 1000 / 1000, 1000,
                                    PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE); 

            // Write the image data for the frame
            png_write_image(png_ptr_write, decoded_png_data.rows);

            // Close the file and free memory allocated by read_png
            fclose(fp);
            for (int y = 0; y < decoded_png_data.height; y++) {
                free(decoded_png_data.rows[y]);
            }
            free(decoded_png_data.rows);
        }

        // End the write operation
        png_write_end(png_ptr_write, info_ptr_write);

        // Clean up
        png_destroy_write_struct(&png_ptr_write, &info_ptr_write);

        return 0; // Indicate success
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
const siz = parseInt(acanvas.height);
let ii = 0;
const delays = []; // Array to store delays for each frame

function render() {
if (ii > 21) {
// Animation complete, assemble APNG
const pngFilePaths = [];
for (let j = 1; j <= ii; j++) {
pngFilePaths.push('/frame' + j + '.png');
}
Module.ccall('runApng', 'number', ['array', 'array', 'number', 'number', 'number'], [pngFilePaths, delays, ii, siz, siz]);
return;
}

ii++;
console.log('Frame: ', ii);

const image = ctx.getImageData(0, 0, siz, siz); // Assuming square canvas
const imageData = image.data;
const pixelData = new Uint8Array(imageData);

const fileStream = FS.open('/frame' + ii + '.png', 'w+');
FS.write(fileStream, pixelData, 0, pixelData.length, 0);
FS.close(fileStream);

delays.push(100); // Add delay for this frame (adjust as needed)

setTimeout(function(){
render();
}, 100);
}

setTimeout(function() {
render(); 
}, 100); 
});

});


return 0;
}
