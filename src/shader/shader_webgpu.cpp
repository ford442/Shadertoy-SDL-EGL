#include "../../include/shader/shader_webgpu.h"

Run run;

// void strtt(){
// run.strt();
// }

boost::function<void()>strtr=[](){
// void strtr(){
// tbb::task_group g;
  //  g.run(strtt);
  //  g.wait();
  run.strt();
//  strtt();
};

extern "C" {

void str(){
strtr();
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
