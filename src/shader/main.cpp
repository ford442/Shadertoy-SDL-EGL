#include "../../include/shader/main.h"


js JS;

extern"C"{

int32_t r4nd(int32_t tH){
Rg=JS.rNd(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}

}
 
int main(){
tie(JS.Th,JS.rD,JS.Dr);
return 0;
}
