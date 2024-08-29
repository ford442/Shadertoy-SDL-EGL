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

setTimeout(function(){
var Module = libapng();
Module.onRuntimeInitialized = function(){
Module.callMain();
console.log('call apng main');
};
},2500);

document.getElementById("apngBtn").addEventListener('click',function(){
var acanvas = document.querySelector("#scanvas");  // Animation drawn on this canvas
window.encoder = new APNGencoder(acanvas);
encoder.setRepeat(0);    // auto-loop is 0
encoder.setDelay(60);    // 1/100 sec  // really ms ?
encoder.setDispose(0);
encoder.setBlend(1);
var ii=0;
encoder.start();
function render() {
ii++;
encoder.addFrame(acanvas, { delay: 40 }); // Capture the frame from your main canvas
if (ii>40) {
encoder.finish(); // Finalize encoding when done
var out = encoder.stream();
var href= URL.createObjectURL(new Blob([new Uint8Array(out.bin)], {type : "image/png" } ));
var timestamp = new Date().toISOString().replace(/[-:.]/g, ''); // Format: YYYYMMDDTHHMMSS
var filename = `APNG_${timestamp}.png`;
var link = document.createElement('a');
link.download = filename;  // Set the desired filename
link.href = href;
link.click();
window.open(href);
console.log('finished');
var base64Out = bytesToBase64(encoder.stream().bin);     // ANIMATION
var img = document.getElementById("imgAnimPNG");
img.style.width = acanvas.width;
img.style.height = acanvas.height;
img.src = "data:image/png;base64," + base64Out;
} else {
setTimeout(function(){
render();
},40);
} // Continue the animation
}

render();

});

});

return 0;
}
