#include "../../include/shader/main.h"

js JS;

int32_t r4nd4(int32_t tH){
Rg=JS.rNd(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}

extern"C"{

int r4nd(int TH){
RG=r4nd4(TH);
return RG;
}

}

int32_t main(void){
jss();
tie(JS.Th,JS.rD,JS.Dr);
return 0;
}
