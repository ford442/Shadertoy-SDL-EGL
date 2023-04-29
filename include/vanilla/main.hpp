#include <emscripten.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp.h"
#include "boost/tuple/tuple.hpp"
#include "boost/timer/timer.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/avx.hpp"
#include <time.h>
#include <chrono>

using namespace std::chrono_literals;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;

using namespace ::boost::tuples;
#include <iostream>
using namespace std;

Class funcs{
  private:
  int r;
float Tdlt;
float nn;
public:

float tuple_float_short(float num){
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;

for(r=0;r<100;r++){
tie(cc,pp,uu);
tie(cc2,pp2,uu2);
}
t1=std::chrono::steady_clock::now();
for(r=0;r<100;r++){
nn=cc+pp+uu+cc2+pp2+uu2;
}
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return nn;
}

float tuple_float_long(float num){
int r;
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
float Tdlt;
float nn;
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
for(r=0;r<100;r++){
tie(cc,pp,uu,cc2,pp2,uu2);
}
t1=std::chrono::steady_clock::now();
for(r=0;r<100;r++){
nn=cc+pp+uu+cc2+pp2+uu2;
}
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uu;
}

GLfloat tuple_gl(GLfloat num){
t1=std::chrono::steady_clock::now();
GLfloat gg=num,pp=num,uu=num;
tie(gg,pp,uu);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
float Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uu;
}

v128_t tuple_avx(float num){
t1=std::chrono::steady_clock::now();
v128_t aa=wasm_i32x4_splat(num);
v128_t vv=wasm_i32x4_splat(num);
v128_t xx=wasm_i32x4_splat(num);
tie(aa,vv,xx);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
float Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return xx;
}

v128_t simd_test(float * a){
t1=std::chrono::steady_clock::now();
int m=a[0]*1000.0;
v128_t l=wasm_i32x4_splat(m);
v128_t tt=wasm_f32x4_add(l,l);
t2=std::chrono::steady_clock::now();
std::chrono::duration<float, std::chrono::milliseconds::period> time_span=std::chrono::duration<float,std::chrono::milliseconds::period>(t2-t1);
float Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return tt;
}

}
