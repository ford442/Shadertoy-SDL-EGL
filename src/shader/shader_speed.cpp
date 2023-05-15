#include "../../include/shader/shader_speed.hpp"

Run run;

extern "C" {

void str(){
run.strt();
return;
}

void swp(){
run.swap();
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

}
