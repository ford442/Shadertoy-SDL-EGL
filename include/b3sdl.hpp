#include <SDL2/SDL.h>
#undef main
#include "SDL_config.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
SDL_AudioDeviceID dev;
struct{Uint8* snd;int pos;Uint32 slen;SDL_AudioSpec spec;}wave;
void cls_aud();
void qu(int rc);
void opn_aud();
void SDLCALL bfr(void *unused,Uint8* stm,int len);
void plt();
extern "C"{
void pl();
};
