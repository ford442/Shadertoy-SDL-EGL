#include "../../include/audio/audio.hpp"

// static inline void(*lp)(){&plt};
Audio audio;

extern "C" {

void pl(){
audio.plt();
return;
}
  
}
