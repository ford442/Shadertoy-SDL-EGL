#include "../../include/combine/main.h"

v128_t rNd(int Th){
std::srand(rd());
rD=std::rand()%Th;
Dr=wasm_i32x4_splat(rD);
return Dr;
}

v128_t(* RnD)(int){&rNd};

extern"C"{

int r4nd(int tH){
Rg=RnD(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}

}

void(*jss)(){&js_main};

int main(void){
jss();
return 0;
}
