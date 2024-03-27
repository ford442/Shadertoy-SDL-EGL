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
console.log(fPointer[0]);
})


void c_(float val){
flt.at(0,0)=val;
fltp.at(0,0)=C_Array;
// fltp.at(0,0)[0]=flt.at(0,0);
// emjs_(C_Array);
}

extern "C"{

void emjs(float * f){
emjs_(f);
}

void cfunc(float a){
c_(a);
}

}

EM_JS(void,setup_js,(),{
document.querySelector('#btn1').addEventListener('click',function(){
//  JS to C passing array
let buffer=new ArrayBuffer(16);
let view=new Float32Array(buffer,0,16);
var rr=new Array(1);
// rr[0]=42.42;
// view.set(rr,0,1);
// Module.ccall('emjs',null,["Number"],[view]);

//  JS to C passing HEAP array
let H1=Module.HEAPF32.buffer;
let viewH=new Float32Array(H1,0,16);
// rr[0]=42.42;
// viewH.set(rr,0,1);
// Module.ccall('emjs',null,["Number"],[H1]);

});
document.querySelector('#btn2').addEventListener('click',function(){
//  C to JS passing array
Module.ccall('cfunc',null,["Number"],[42.42]);

//  C to JS passing HEAP array

});
})

int main(){
setup_js();
return 0;
}
