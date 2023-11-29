#include "../../include/audio/audio_sdl.hpp"

Audio audio;

extern "C" {

EM_BOOL pl(){
audio.plt();
return EM_TRUE;
}
  
}
