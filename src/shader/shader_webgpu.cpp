#include "../../include/shader/shader_webgpu_noegl.hpp"

Run run;

boost::function<EM_BOOL()>strtr=[](){
run.strt();
return EM_TRUE;
};

boost::function<EM_BOOL()>swpp=[](){
run.swap();
return EM_TRUE;
};

extern "C" {

EM_BOOL str(){
strtr();
return EM_TRUE;
}

EM_BOOL swp(){
swpp();
return EM_TRUE;
}

EM_BOOL ud(){
run.uniDOWN();
return EM_TRUE;
}

EM_BOOL uu(){
run.uniUP();
return EM_TRUE;
}

EM_BOOL vd(){
run.viewDOWN();
return EM_TRUE;
}

EM_BOOL vu(){
run.viewUP();
return EM_TRUE;
}

EM_BOOL mu(){
run.moveUP();
return EM_TRUE;
}

EM_BOOL md(){
run.moveDOWN();
return EM_TRUE;
}

EM_BOOL ml(){
run.moveLEFT();
return EM_TRUE;
}

EM_BOOL mr(){
run.moveRIGHT();
return EM_TRUE;
}

}
