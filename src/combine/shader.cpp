#include "../../include/combine/shader.hpp"

Run run;

static void Swap(){
run.procc.swap();
}

static void Frm(){
run.procc.Rend();
return;
}

extern "C" {

void frm(){
Frm();
return;
}

void str(){
run.strt();
return;
}

void swp(){
Swap();
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
