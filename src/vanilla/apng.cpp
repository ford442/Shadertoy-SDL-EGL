#include <emscripten.h>
#include <emscripten/bind.h>

int main(){

EM_ASM({
let scr=document.createElement("script");
scr.async=true;
scr.charset='utf-8';
scr.type='text/javascript';
scr.defer=true;
scr.src="https://js.1ink.us/canvas2apng.js";
document.body.appendChild(scr);
  
document.getElementById("apngBtn").addEventListener('click',function(){
const acanvas = document.querySelector("#scanvas");  // Animation drawn on this canvas
const bcanvas = document.querySelector("#bcanvas");  // Animation drawn on this canvas
const context=acanvas.getContext('2d');
const siz=parseInt(acanvas.height);
window.encoder = new APNGencoder(acanvas);
window.encoder2 = new APNGencoder(bcanvas);
encoder.setRepeat(0);    // auto-loop is 0
encoder.setDelay(100);    // 1/100 sec  // really ms ?
encoder.setDispose(0);
encoder.setBlend(1);
var ii=0;
encoder.start();

  //  test
console.log('frame ',ii);
context.getImageData(0,0,siz,siz).data;
encoder.addFrame(context);
encoder.finish(); // Finalize encoding when done
var out = encoder.stream();
var href= URL.createObjectURL(new Blob([new Uint8Array(out.bin)], {type : "image/png" } ));
var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `APNG_${timestamp}.png`;
var link = document.createElement('a');
link.download = filename;  // Set the desired filename
link.href =href;
link.click();
console.log('finished a');
console.log('frame ',ii);
encoder.start();

encoder.addFrame(acanvas);
encoder.finish(); // Finalize encoding when done
var out = encoder.stream();
var href= URL.createObjectURL(new Blob([new Uint8Array(out.bin)], {type : "image/png" } ));
var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `APNG_${timestamp}.png`;
var link = document.createElement('a');
link.download = filename;  // Set the desired filename
link.href =href;
link.click();
console.log('finished b');

encoder2.start();

console.log('frame ',ii);
context.getImageData(0,0,siz,siz).data;
encoder2.addFrame(context);
encoder2.finish(); // Finalize encoding when done
var out = encoder.stream();
var href= URL.createObjectURL(new Blob([new Uint8Array(out.bin)], {type : "image/png" } ));
var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `APNG_${timestamp}.png`;
var link = document.createElement('a');
link.download = filename;  // Set the desired filename
link.href =href;
link.click();
console.log('finished c');
console.log('frame ',ii);
encoder2.start();

encoder2.addFrame(acanvas);
encoder2.finish(); // Finalize encoding when done
var out = encoder.stream();
var href= URL.createObjectURL(new Blob([new Uint8Array(out.bin)], {type : "image/png" } ));
var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `APNG_${timestamp}.png`;
var link = document.createElement('a');
link.download = filename;  // Set the desired filename
link.href =href;
link.click();
console.log('finished d');

/*
function render() {
setTimeout(function(){
if (ii>40) {
encoder.finish(); // Finalize encoding when done
var out = encoder.stream();
var href= URL.createObjectURL(new Blob([new Uint8Array(out.bin)], {type : "image/png" } ));
var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `APNG_${timestamp}.png`;
var link = document.createElement('a');
link.download = filename;  // Set the desired filename
link.href =href;
link.click();
window.open(href);
console.log('finished');
var base64Out = bytesToBase64(encoder.stream().bin);     // ANIMATION
var img = document.getElementById("imgAnimPNG");
img.style.width = acanvas.width;
img.style.height = acanvas.height;
img.src = "data:image/png;base64," + base64Out;
} else {
if(ii<41){
ii++;
console.log('frame ',ii);
context.getImageData(0,0,siz,siz);
encoder.addFrame(context);
render();
}
}
},100);
}
  
render();
*/

});

});

return 0;
}
