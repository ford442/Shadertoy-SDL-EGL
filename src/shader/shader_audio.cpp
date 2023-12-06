
#include "../../include/shader/shader_webgpu.hpp"

Run run;

boost::function<EM_BOOL(void)>strtr=[](void){
run.strt();
return EM_TRUE;
};

boost::function<EM_BOOL(void)>swpp=[](void){
run.swap();
return EM_TRUE;
};

#include "../../include/audio/audio.hpp"

Audio audio;

extern "C" {

EM_BOOL str(){
strtr();
return EM_TRUE;
}

EM_BOOL swp(){
swpp();
return EM_TRUE;
}

EM_BOOL ud(){
run.uniDOWN();
return EM_TRUE;
}

EM_BOOL uu(){
run.uniUP();
return EM_TRUE;
}

EM_BOOL vd(){
run.viewDOWN();
return EM_TRUE;
}

EM_BOOL vu(){
run.viewUP();
return EM_TRUE;
}

EM_BOOL mu(){
run.moveUP();
return EM_TRUE;
}

EM_BOOL md(){
run.moveDOWN();
return EM_TRUE;
}

EM_BOOL ml(){
run.moveLEFT();
return EM_TRUE;
}

EM_BOOL mr(){
run.moveRIGHT();
return EM_TRUE;
}


EM_BOOL pl(){
audio.plt();
return EM_TRUE;
}

}
