#include "../../include/shader/loader.hpp"

EM_JS(void,js_main,(),{
// Fetch the WebAssembly module binary
var sr=document.getElementById('sourc').innerHTML;
fetch(sr)
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
});

int main(){
js_main();
return 0;
}
