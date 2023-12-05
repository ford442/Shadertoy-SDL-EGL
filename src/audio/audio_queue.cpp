#include "../../include/audio/audio_queue.hpp"

Audio audio;

extern "C" {

EM_BOOL pl(){
audio.plt();
return EM_TRUE;
}
  
}
