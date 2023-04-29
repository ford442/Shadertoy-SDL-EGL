#include "../../include/shader/shader_speed.hpp"

inline EM_BOOL ms_clk(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

inline EM_BOOL ms_mv(int eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
x=e->clientX;
y=e->clientY;
}}
return (EM_BOOL)1;
}

Run run;

// static inline GLuint(* cs)(GLenum,GLsizei,const GLchar **){&cmpl_shd};

// static inline void(*st)(){&strt};

extern "C" {

void str(){
strt();
return;
}

}
