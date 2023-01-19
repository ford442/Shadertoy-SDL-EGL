#include "../include/b3emsc.hpp"

#include <SDL2/SDL.h>
#undef main

char flnm[24];
SDL_AudioDeviceID dev;

struct{Uint8 * snd;int pos;Uint32 slen;SDL_AudioSpec request;}wave;

void SDLCALL bfr(void *,Uint8 *,int);

void plt();

extern "C"{

void pl();

}

#include <iostream>
