#include "../include/b3emsc.hpp"
#include <SDL2/SDL.h>
#undef main
#include "SDL_config.h"

char flnm[24];
SDL_AudioDeviceID dev;
struct{Uint8 * snd;int_fast32_t pos;Uint32 slen;SDL_AudioSpec request;}wave;

void SDLCALL bfr(void *,Uint8 *,int_fast32_t);
  
void plt();

extern "C"{  
  
void pl();
  
};

#include <iostream>
