#include "../../include/shader/shader_webgpu.h"

Run run;

boost::function<EM_BOOL(void)>strtr=[](void){
run.strt();
return EM_TRUE;
};

boost::function<EM_BOOL(void)>swpp=[](void){
run.swap();
};

extern "C" {

EM_BOOL str(){
strtr();
return;
}

EM_BOOL swp(){
swpp();
return;
}

EM_BOOL ud(){
run.uniDOWN();
return;
}

EM_BOOL uu(){
run.uniUP();
return;
}

EM_BOOL vd(){
run.viewDOWN();
return;
}

EM_BOOL vu(){
run.viewUP();
return;
}

EM_BOOL mu(){
run.moveUP();
return;
}

EM_BOOL md(){
run.moveDOWN();
return;
}

void ml(){
run.moveLEFT();
return;
}

EM_BOOL mr(){
run.moveRIGHT();
return;
}

}
