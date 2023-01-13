extern "C"{

void pl();

}

#include <SDL2/SDL.h>
#undef main
#include "SDL_config.h"

SDL_AudioDeviceID dev;

SDL_AudioSpec request,recieve;
SDL_memset(&request,0,sizeof(request));
request.freq=44100;
request.format=AUDIO_F32;
request.channels=2;
request.samples=4096;
request.callback=bfr; 

struct{Uint8 * snd;int pos;Uint32 slen;}wave;

void cls_aud();

void qu();

void opn_aud();

void SDLCALL bfr(void *,Uint8 *,int);

void plt();

#include <iostream>
