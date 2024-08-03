import fs from 'fs';
import path from 'path';

async function loadWasmModule() {
    const wasmFiles = fs.readdirSync('./').filter(file => file.match(/^w0-.*\.js$/)); 
    const wasmModulePath = path.join('./', wasmFiles[0]); // Get the first (and only) matching file
    const { init, FS } = await import(wasmModulePath); 
    await init();
}

loadWasmModule();

const videoElement = document.getElementById("mvi") as HTMLVideoElement;
const canvas = new OffscreenCanvas(videoElement.videoWidth,videoElement.videoHeight); 
const context = canvas.getContext("2d")!;

function processFrame() {
  context.drawImage(videoElement, 0, 0, canvas.width, canvas.height);
  const imageData = context.getImageData(0, 0, canvas.width, canvas.height);
  const frameData = imageData.data.buffer; // Raw pixel data (Uint8ClampedArray)
  FS.writeFile("/video/frame.gl", new Uint8Array(frameData));

  requestAnimationFrame(processFrame);
}

videoElement.addEventListener("play", () => {
  requestAnimationFrame(processFrame);
});
