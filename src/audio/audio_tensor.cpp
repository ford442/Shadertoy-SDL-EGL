#include "../../include/audio/audio_tensor.hpp"

Audio audio;

extern "C" {

EM_BOOL pl(){
audio.plt();
audio.ort();
return EM_TRUE;
}
  
}
