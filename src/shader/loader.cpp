#include "../../include/shader/loader.hpp"

// Fetch the WebAssembly module binary
fetch('https://example.com/myModule.wasm')
  .then(response => response.arrayBuffer())
  .then(buffer => {
    // Instantiate the WebAssembly module
    WebAssembly.instantiate(buffer)
      .then(module => {
        // Use the module instance
        const instance = module.instance;
        const exportedFunction = instance.exports.exportedFunction;
        exportedFunction();
      })
      .catch(error => {
        console.error('Failed to instantiate WebAssembly module:', error);
      });
  });
