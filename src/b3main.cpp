#include <emscripten.h>
int main(){
EM_ASM({
"use strict";
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 0;
}
