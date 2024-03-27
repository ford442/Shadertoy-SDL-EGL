// #include <boost/cstdfloat.hpp>  // must be first include

#include <emscripten.h>
// #define __EMCSCRIPTEN__ 1

// #include "../../include/vanilla/avx.hpp"

#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/tuple/tuple.hpp>

#include <vector>

using f_tensor=boost::numeric::ublas::tensor<float>;
using fp_tensor=boost::numeric::ublas::tensor<float *>;

static f_tensor flt=f_tensor{5,5};
static fp_tensor fltp=fp_tensor{5,5};

float * C_Array=new float[16];

EM_JS(void,emjs_,(float * fPointer),{
console.log(fPointer[8]);
})


void c(float val){
flt.at(0,0)=val;
fltp.at(0,0)=C_Array;
fltp.at(0,0)[8]=flt.at(0,0);
emjs_(fltp.at(0,0));
}

extern "C"{

void emjs(float * f){
emjs_(f);
}

void c(float a){
c_(a);
}

}

EM_JS(void,setup_js,(),{
document.querySelector('#btn1').addEventListener('click',function(){
//  JS to C passing array
let buffer=new ArrayBuffer(8);
let view=new Float32Array(buffer);
view[8]=42.42;
Module.ccall('emjs',null,["Number"],[view]);

//  JS to C passing HEAP array
let H1=Module.HEAPF32.buffer;
let viewH=new Float32Array(H1);

}
document.querySelector('#btn2').addEventListener('click',function(){
//  C to JS passing array
Module.ccall('c',null,["Number"],[42.42]);

//  C to JS passing HEAP array

}
})

int main(){
setup_js();
return 0;
}
