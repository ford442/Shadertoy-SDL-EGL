#include "../../include/audio/main.hpp"

song_select song;

extern"C"{

int r4nd(int tH){
Rg=song.rNd(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}
  
}

// static inline void(*jss)(){&js_main};
static inline boost::function<void()>jss=[](){js_main();};

int main(){
EM_ASM({
"use strict";
FS.mkdir('/snd');
});
tie(jss,js_main);
jss();
return 0;
}
