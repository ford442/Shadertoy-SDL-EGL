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
const acanvas = document.querySelector("#scanvas");
const ctx = acanvas.getContext("2d");
const siz=parseInt(acanvas.height);
window.encoder = new APNGencoder(acanvas);
encoder.setRepeat(0);
encoder.setDelay(100);
encoder.setDispose(0);
encoder.setBlend(1);
var ii=0;

encoder.start();
setTimeout(function(){
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
},1500);
/*
function render() {
if (ii>21) {
return;
}
if (ii>20) {
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
ii++;
console.log('frame ',ii);
encoder.addFrame(ctx);
setTimeout(function(){
render();
},100);
}
}

setTimeout(function() {
encoder.start();
render(); 
}, 100); // Give some time for the initial frame to be drawn
*/

});

});

return 0;
}
