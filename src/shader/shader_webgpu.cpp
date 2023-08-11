#include "../../include/shader/shader_webgpu.h"

Run run;

boost::function<EM_BOOL(void)>strtr=[](void){
run.strt(void);
return EM_TRUE;
};

boost::function<EM_BOOL(void)>swpp=[](void){
run.swap(void);
return EM_TRUE;
};

extern "C" {

EM_BOOL str(void){
strtr(void);
return 1;
}

EM_BOOL swp(void){
swpp(void);
return 1;
}

EM_BOOL ud(void){
run.uniDOWN(void);
return 1;
}

EM_BOOL uu(void){
run.uniUP(void);
return 1;
}

EM_BOOL vd(void){
run.viewDOWN(void);
return 1;
}

EM_BOOL vu(void){
run.viewUP(void);
return 1;
}

EM_BOOL mu(void){
run.moveUP(void);
return 1;
}

EM_BOOL md(void){
run.moveDOWN(void);
return 1;
}

EM_BOOL ml(void){
run.moveLEFT(void);
return 1;
}

EM_BOOL mr(void){
run.moveRIGHT(void);
return 1;
}

}
