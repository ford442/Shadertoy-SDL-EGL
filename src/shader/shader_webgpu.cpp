#include "../../include/shader/shader_webgpu.h"

Run run;

boost::function<EM_BOOL()>strtr=[](){
run.strt();
return EM_TRUE;
};

boost::function<void()>swpp=[](){
run.swap();
};

extern "C" {

void str(){
strtr();
return;
}

void swp(){
swpp();
return;
}

void ud(){
run.uniDOWN();
return;
}

void uu(){
run.uniUP();
return;
}

void vd(){
run.viewDOWN();
return;
}

void vu(){
run.viewUP();
return;
}

void mu(){
run.moveUP();
return;
}

void md(){
run.moveDOWN();
return;
}

void ml(){
run.moveLEFT();
return;
}

void mr(){
run.moveRIGHT();
return;
}

}
