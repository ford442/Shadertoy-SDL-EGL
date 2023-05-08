#include <emscripten.h>
#include <emscripten/html5.h>
#include "emscripten/html5_webgpu.h"
#include "webgpu/webgpu.h"
#include "webgpu/webgpu_cpp.h"
// #include <torch/script.h>
// #include <torch/csrc/api/include/torch/all.h>
// #include <ATen/ATen.h>

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1

#include "boost/tuple/tuple.hpp"
#include "boost/timer/timer.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/avx.hpp"
#include <boost/numeric/ublas/tensor.hpp>
// #include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <time.h>
#include <chrono>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <boost/context/fiber.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std::chrono_literals;
using namespace ::boost::tuples;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;

#include <iostream>

using namespace std;
using namespace boost::numeric::ublas;
using namespace boost::multiprecision;

using tensorVar=tensor<GLfloat>;
using tF=tensor<GLfloat>;
using tensorVarD=tensor<GLdouble>;
using tD=tensor<GLdouble>;
using tI=tensor<GLint>;
using tV=tensor<v128_t>;


class tens{

private:
  
float lol,olo;
tensorVar A=tensorVar{8,4};
tensorVar Aa=tensorVar{2,3};
uint128_t tst128;
  
  
public:

float rtt(float nm){
A.at(0,0)=nm;
tensorVar B=A;
lol=static_cast<float>(B.at(4,4));
olo=lol*100;
return olo;
}

};

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

inline int32_t Size;

inline EM_BOOL ms_l,clk_l;

inline struct{
float xx;
float yy;
float mX;
float mY;
float mm;
float nn;
float S;
float mouseY;
float mouseX;
double wi;
double hi;
GLclampf x;
GLclampf y;
}mouse;

inline EM_BOOL ms_clk(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return(EM_BOOL)1;
}

inline EM_BOOL ms_mv(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mouse.x=e->clientX;
mouse.y=e->clientY;
}}
return (EM_BOOL)1;
}

void mss(){
emscripten_get_element_css_size("canvas",&mouse.wi,&mouse.hi);
Size=static_cast<int32_t>(mouse.hi);
mouse.S=static_cast<float>(mouse.hi);
retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const float xxx=mouse.mouseX;
const float yyy=mouse.mouseY;
EM_ASM({
console.log($0);
},xxx);
mouse.mX=1.0f-(xxx*Size);
mouse.mY=1.0f-(yyy*Size);
clk_l=false;
}
mouse.mm=mouse.x*Size;
mouse.nn=Size*mouse.y;
}else{
clk_l=true;
EM_ASM({
console.log($0);
},mouse.nn);
}
return;
}

class funcs{

private:
  
boost::atomic<float>farray;
int r,m;
float cc,pp,uu,cc2,pp2,uu2,Tdlt,nn;
v128_t aa,vv,xx,l,tt;
tI inte=tI{1,1};
tF deci=tF{1,1};
tV q=tV{1,1};
tV intrn=tV{1,4};
  
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
cc2=num,pp2=num,uu2=num;cc=num,pp=num,uu=num;
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
GLfloat ggg=num,ppg=num,uug=num;
tie(ggg,ppg,uug);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
float Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uug;
}

v128_t tuple_avx(float num){
t1=std::chrono::steady_clock::now();
aa=wasm_i32x4_splat(num);
vv=wasm_i32x4_splat(num);
xx=wasm_i32x4_splat(num);
tie(aa,vv,xx);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return xx;
}

v128_t simd_test(float * a){
t1=std::chrono::steady_clock::now();
m=a[0]*1000.0;
l=wasm_i32x4_splat(m);
tt=wasm_f32x4_add(l,l);
t2=std::chrono::steady_clock::now();
std::chrono::duration<float, std::chrono::milliseconds::period> time_span=std::chrono::duration<float,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return tt;
}

v128_t double_add(float fl){
tie(inte,deci,q,intrn);
inte.at(0,0)=std::floor(fl);
deci.at(0,0)=fl-inte.at(0,0);
intrn.at(0,0)=wasm_f32x4_make(inte.at(0,0),deci.at(0,0),deci.at(0,0),deci.at(0,0));
intrn.at(0,1)=wasm_f32x4_make(1.0,100.0,10.0,1.0);
intrn.at(0,0)=wasm_f32x4_div(intrn.at(0,0),intrn.at(0,1));
intrn.at(0,2)=wasm_f32x4_sqrt(intrn.at(0,0));
intrn.at(0,0)=wasm_f32x4_mul(intrn.at(0,2),intrn.at(0,2));
intrn.at(0,3)=wasm_f32x4_mul(intrn.at(0,0),intrn.at(0,1));
return intrn.at(0,3);
}
  
float noblock(float y){
farray=y;
return farray;
 //   std::cout << ::at::ones({3,4}, at::CPU(at::kFloat)) << "\n";
 // emscripten_set_main_loop((void(*)())mss,0,0);

}

};
