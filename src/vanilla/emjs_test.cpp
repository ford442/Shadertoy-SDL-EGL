// #include <boost/cstdfloat.hpp>  // must be first include

#include <emscripten.h>
// #define __EMCSCRIPTEN__ 1

// #include "../../include/vanilla/avx.hpp"

#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>

using f_tensor=boost::numeric::ublas::tensor<float>;
using fp_tensor=boost::numeric::ublas::tensor<float *>;

static f_tensor flt=f_tensor{5,5};
static fp_tensor fltp=fp_tensor{5,5};

float * C_Array=new float[16];

EM_JS(void,hp,(),{
let H1=Module.HEAPF32.buffer;
let viewH=new Float32Array(H1,0,16);
console.log('EM_JS got FLOAT: ',viewH[0]);
console.log('EM_JS got FLOAT: ',viewH[1]);
});

// EM_JS(void,emjs_,(float * fPointer),{
void emjs_(float * fPointer){
EM_ASM({
console.log('void got FLOAT: ',$0);
let H1=Module.HEAPF32.buffer;
let viewH=new Float32Array(H1,0,16);
viewH[1]=24.24;
},fPointer[0]);
hp();
}
// });

void cf_(float * val){
EM_ASM({
console.log('C++ Function handing to EM_JS: ',$0);
},val[0]);
flt.at(0,0)=val[0];
fltp.at(0,0)=C_Array;
fltp.at(0,0)[0]=flt.at(0,0);
emjs_(fltp.at(0,0));
return;
}

extern "C"{

void emjs(float * f){
emjs_(f);
return;
}

void cfunc(float * a){
cf_(a);
return;
}

}

EM_JS(void,setup_js,(),{
document.querySelector('#btn1').addEventListener('click',function(){
//  JS to C passing HEAP array
let H1=Module.HEAPF32.buffer;
let viewH=new Float32Array(H1,0,16);
viewH[0]=42.42;
console.log('Handing JS-HEAPF32 ArrayBuffer->TypedArray: ',viewH[0]);
Module.ccall('emjs',null,["Number"],[viewH]);
});
document.querySelector('#btn2').addEventListener('click',function(){
let H1c=Module.HEAPF32.buffer;
let viewHc=new Float32Array(H1c,0,16);
viewHc[0]=42.42;
console.log('Handing C to EM_JS: ',viewHc[0]);
Module.ccall('cfunc',null,["Number"],[viewHc]);
});
});

int main(){
setup_js();
return 0;
}
