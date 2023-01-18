#include "../include/b3sdl.hpp"

void SDLCALL bfr(void * unused,Uint8 * stm,int len){
Uint8 * wptr;
int lft;
wptr=wave.snd+wave.pos;
lft=wave.slen-wave.pos;
while (lft<=len){
SDL_UnlockAudioDevice(dev);
SDL_memcpy(stm,wptr,lft);
stm+=lft;
len-=lft;
wptr=wave.snd;
lft=wave.slen;
wave.pos=0;
SDL_LockAudioDevice(dev);
}
SDL_memcpy(stm,wptr,len);
wave.pos+=len;
return;
}

int plays(){

    SDL_ThreadPriority prio = SDL_THREAD_PRIORITY_NORMAL;

SDL_memset(&wave.request,0,sizeof(wave.request));
wave.request.freq=44100;
wave.request.format=AUDIO_S32;
wave.request.channels=2;
wave.request.samples=1024;
wave.pos=0;
SDL_strlcpy(flnm,"/snd/sample.wav",sizeof(flnm));
SDL_Init(SDL_INIT_AUDIO);

SDL_LoadWAV(flnm,&wave.request,&wave.snd,&wave.slen);
wave.request.callback=bfr;
dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.request,NULL,0);
SDL_PauseAudioDevice(dev,SDL_FALSE);
return 1;
}

void plt(){

tls=SDL_TLSCreate();
SDL_assert(tls);
SDL_TLSSet(tls,"main thread",NULL);
SDL_Init(0);
SDL_CreateThread(plays,"One","#1");
return;
}

extern "C" {

void pl(){
plt();
return;
}
  
}
