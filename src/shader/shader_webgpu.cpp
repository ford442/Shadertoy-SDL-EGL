#include "../../include/shader/shader_webgpu.h"

oneapi::tbb::task_group g;

void nanoPause(){
nanosleep(&req2,&rem);
}

g.run(nanoPause);
g.wait();

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
