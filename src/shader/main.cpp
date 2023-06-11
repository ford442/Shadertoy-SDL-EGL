#include "../../include/shader/main.h"

js JS;

int r4nd4(int tH){
Rg=JS.rNd(tH);
// c=wasm_i32x4_extract_lane(Rg,0);
return Rg;
}

extern"C"{

int r4nd(int TH){
RG=r4nd4(TH);
return RG;
}

}

int main(void){
jss();
return 0;
}
