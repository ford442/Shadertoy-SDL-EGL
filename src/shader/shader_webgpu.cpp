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

extern "C" {

EM_BOOL str(){
strtr();
return 1;
}

EM_BOOL swp(){
swpp();
return 1;
}

EM_BOOL ud(){
run.uniDOWN();
return 1;
}

EM_BOOL uu(){
run.uniUP();
return 1;
}

EM_BOOL vd(){
run.viewDOWN();
return 1;
}

EM_BOOL vu(){
run.viewUP();
return 1;
}

EM_BOOL mu(){
run.moveUP();
return 1;
}

EM_BOOL md(){
run.moveDOWN();
return 1;
}

EM_BOOL ml(){
run.moveLEFT();
return 1;
}

EM_BOOL mr(){
run.moveRIGHT();
return 1;
}

}
