#include "../../include/shader/shader_glsl.hpp"

Run run;

extern "C" {

void str(){
run.strt();
return;
}

void swp(){
run.procc.swap();
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
