#include "../../include/shader/shader_webgpu.h"

Run run;

boost::function<EM_BOOL(void)>strtr=[](void){
run.strt();
return EM_TRUE;
};

boost::function<EM_BOOL(void)>swpp=[](void){
run.swap();
return EM_TRUE;
};

extern "C" {

EM_BOOL str(){
strtr();
return 1;
}

EM_BOOL swp(){
swpp();
return 1;
}

EM_BOOL ud(void){
run.uniDOWN();
return 1;
}

EM_BOOL uu(void){
run.uniUP();
return 1;
}

EM_BOOL vd(void){
run.viewDOWN();
return 1;
}

EM_BOOL vu(void){
run.viewUP();
return 1;
}

EM_BOOL mu(void){
run.moveUP();
return 1;
}

EM_BOOL md(void){
run.moveDOWN();
return 1;
}

EM_BOOL ml(void){
run.moveLEFT();
return 1;
}

EM_BOOL mr(void){
run.moveRIGHT();
return 1;
}

}
