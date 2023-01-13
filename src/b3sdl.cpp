#include "../include/b3sdl.hpp"

void cls_aud(){
if(dev!=0){
SDL_PauseAudioDevice(dev,SDL_TRUE);
SDL_CloseAudioDevice(dev);
dev=0;
return;
}}

void qu(){
SDL_Quit();
return;
}

void opn_aud(){
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.request,NULL,SDL_AUDIO_ALLOW_FORMAT_CHANGE|SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
if(!dev){
SDL_FreeWAV(wave.snd);
}
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
}

void SDLCALL bfr(void * unused,Uint8 * stm,int len){
Uint8 * wptr;
int lft;
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while (lft<=len){
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
}

void plt(){
char flnm[24];
SDL_FreeWAV(wave.snd);
SDL_SetMainReady();
if (SDL_Init(SDL_INIT_AUDIO)<0){
qu();
}
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.request,&wave.snd,&wave.slen)==NULL){
qu();
}
// SDL_memset(&wave.request,0,sizeof(wave.request));
// wave.request.freq=48000;
// wave.request.format=AUDIO_F32MSB;
// wave.request.channels=2;
// wave.request.samples=4096;
wave.pos=0;
wave.request.callback=bfr;
opn_aud();
SDL_PauseAudioDevice(dev,SDL_FALSE);
return;
}

extern"C"{
  
void pl(){
plt();
return;
}
  
}
