#include <emscripten.h>

#include <SDL2/SDL.h>

char flnm[24];
SDL_AudioDeviceID dev;
struct{Uint8 * snd;int_fast32_t pos;Uint32 slen;SDL_AudioSpec request;}wave;

void SDLCALL bfr(void *,Uint8 *,int_fast32_t);
  
void plt();

extern "C"{  
  
void pl();
  
};

#include <iostream>
