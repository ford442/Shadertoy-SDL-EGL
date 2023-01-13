extern "C"{

void pl();

}

#include <SDL2/SDL.h>
#undef main
#include "SDL_config.h"

SDL_AudioDeviceID dev;

struct{Uint8 * snd;int pos;Uint32 slen;SDL_AudioSpec request;SDL_AudioSpec receive;}wave;

void cls_aud();

void qu();

void opn_aud();

void SDLCALL bfr(void *,Uint8 *,int);

void plt();

#include <iostream>
