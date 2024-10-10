#include <emscripten.h>

int main(){

emscripten_async_run_script("depth.js", 1); // 1 for async

return 0;
}
