#pragma once
// #pragma pack(4)
// #pragma fenv_access(on)        // enable environment sensitivity
#include <boost/cstdfloat.hpp>  // must be first include

#include "../../include/shader/defs.hpp"
#include "../../include/shader/boost_defs.hpp"
#include "../../include/shader/intrins.hpp"
#include "../../include/shader/egl.hpp"

#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#define register

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include <boost/function.hpp>
#include "boost/tuple/tuple.hpp"
#include <random>
#include <cstdlib>
#include <emscripten.h>
#include <emscripten/html5.h>

using namespace ::boost::tuples;

static inline boost::function<EM_BOOL()>jss=[](){
js_main();
return EM_TRUE;
};

int r4nd4(int);
int rD,Rg,nm;

class js
{

private:

public:
 
std::random_device rd;

// v128_t Dr;

inline int rNd(int Th){
nm=Th*rd();
std::srand(nm);
rD=std::rand()%Th;
// Dr=wasm_i32x4_splat(rD);
return rD;
}

};

extern"C"{

int TH;
int RG;
int r4nd(int);

}
