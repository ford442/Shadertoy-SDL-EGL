#include <emscripten.h>

void js_hello(){
EM_ASM({
console.log('Javascript: Hello.');
});
return;
}
