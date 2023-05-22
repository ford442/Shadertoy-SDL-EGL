#include "../../include/shader/shader_speed.h"

Run run;

void(*FrM)(){&Run::renderFrame};

extern "C" {

void frm(){
FrM();
return;
}

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
