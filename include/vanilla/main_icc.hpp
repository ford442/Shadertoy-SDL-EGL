#pragma pack(4)
// #pragma float_control(precise, on)  // enable precise semantics
#pragma fenv_access(on)             // enable environment sensitivity
// #pragma float_control(except, on)   // enable exception semantics

#include <boost/cstdfloat.hpp>  // must be first include
#include <cfloat>
#include <climits>
#include <math.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <unistd.h>
#include <experimental/simd>
using std::experimental::native_simd;
using float_v=std::experimental::simd<float,std::experimental::simd_abi::scalar>;

#define _XOPEN_SOURCE 700

#define BOOST_CHRONO_HEADER_ONLY 1
#define BOOST_ERROR_CODE_HEADER_ONLY 1
#define BOOST_UBLAS_MOVE_SEMANTICS
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_USE_LONG_DOUBLE
#define BOOST_NO_EXCEPTIONS
// #define BOOST_HAS_FLOAT128
// #define BOOST_HAS_CLOCK_GETTIME 1
// #define BOOST_HAS_NANOSLEEP 1
// #define BOOST_HAS_NRVO 1
// #define BOOST_HAS_STDINT_H 1

#include "boost/tuple/tuple.hpp"
#include "boost/timer/timer.hpp"
#include "../../include/vanilla/gl.hpp"
#include "../../include/vanilla/avx.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/tensor.hpp>

#include <time.h>
#include <chrono>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <boost/context/fiber.hpp>
// #include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

using namespace std::chrono_literals;
using namespace ::boost::tuples;

std::chrono::steady_clock::time_point t1;
std::chrono::steady_clock::time_point t2;

#include <iostream>

using namespace std;
using namespace boost::numeric::ublas;
// using namespace boost::multiprecision;
using namespace boost::random;

using tensorVar=tensor<GLfloat>;
using tF=tensor<GLfloat>;
using tf=tensor<float>;
using td=tensor<double>;
using tld=tensor<long double>;
using tensorVarD=tensor<GLdouble>;
using tD=tensor<GLdouble>;
using tI=tensor<GLint>;
using tV=tensor<v128_t>;

#include <cassert>
#include <iomanip>
#include <ctime>

#include <stdio.h>

#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "/usr/include/glm/glm.hpp"

constexpr float PI = 3.14159265358979323846f;

using glm::mat4x4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

using namespace std;

#include <functional>

tf sx=tf{2,2};
std::function<float(float,float)>TensorAdd(){
return[](float a,float b){sx.at(0,0)=a;sx.at(0,1)=b;sx.at(1,0)=sx.at(0,0)+sx.at(0,1);return sx.at(1,0);};
}
auto tensorAdd=TensorAdd();

td sy=td{2,2};

std::function<double(double,double)>DoubleAdd(){
return[](double a,double b){
sy.at(0,0)=a;
sy.at(0,1)=b;
sy.at(1,0)=sy.at(0,0)+sy.at(0,1);
return sy.at(1,0);};
}
auto doubleAdd=DoubleAdd();

tV sz=tV{2,2};
std::function<v128_t(v128_t,v128_t)>IntrinsAdd(){
return[](v128_t a,v128_t b){
sz.at(0,0)=a;
sz.at(0,1)=b;
sz.at(1,0)=wasm_f64x2_add(a,b);
return sz.at(1,0);
};
}
auto intrinsAdd=IntrinsAdd();

class tens{

private:

// boost::random::random_device rng;
float lol,olo;
tensorVar A=tensorVar{8,4};
tensorVar Aa=tensorVar{2,3};
// uint128_t tst128;

public:

float rtt(float nm){
long long timE=time(0);
struct tm *datE=localtime(&timE);
short yr=1900+datE->tm_year;
short mn=1+datE->tm_mon;
short dy=datE->tm_mday;
short hr=datE->tm_hour;
short mi=datE->tm_min;
short sc=datE->tm_sec;
setprecision(3);
std::cout << "--------------------------" << std::endl;
std::cout << "-----ctime----------------" << std::endl;
std::cout << "-------" << timE << "----------" << std::endl;
  std::cout << yr << std::endl;
  std::cout << mn << std::endl;
  std::cout << dy << std::endl;
  std::cout << hr << std::endl;
  std::cout << mi << std::endl;
  std::cout << sc << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
float ppi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;
double ppd=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
long double ppD=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L;
std::cout << "-float------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppi <<"-----" << std::endl;
std::cout << "-double------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppd <<"-----" << std::endl; 
std::cout << "-long double------------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< ppD <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "Tensor adding input: 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
sx.at(1,1)=tensorAdd(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f,3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f);
std::cout << "----------float-----------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< sx.at(1,1) <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
sy.at(1,1)=doubleAdd(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679,3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679);
std::cout << "-----------double---------" << std::endl;
std::cout << fixed << setprecision(64) << "-----"<< sy.at(1,1) <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
sz.at(1,1)=intrinsAdd(wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f),wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f));
// szz.at(1,1)=intrinsLDAdd(wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L),wasm_f64x2_splat(3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679L));
std::cout << "------intrins-------------" << std::endl;
float ou2=wasm_f64x2_extract_lane(sz.at(1,1),0);
double ou3=wasm_f64x2_extract_lane(sz.at(1,1),0);
// long double ou5=wasm_f64x2_extract_lane(szz.at(1,1),0);
std::cout << fixed << setprecision(64) << "--float---"<< ou2 <<"-----" << std::endl;
std::cout << fixed << setprecision(64) << "--double---"<< ou3 <<"-----" << std::endl;
// std::cout << fixed << setprecision(64) << "--long double---"<< ou5 <<"-----" << std::endl;
std::cout << "--------------------------" << std::endl;
std::cout << "--------------------------" << std::endl;
A.at(0,0)=nm;
tensorVar B=A;
lol=static_cast<float>(B.at(4,4));
olo=lol*100;
// float llo=rng();
return olo;
}

};

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

inline int32_t Size;

inline EM_BOOL ms_l,clk_l;

static tI inte=tI{1,1};
static tF sdeci=tF{1,1};
static tV q=tV{1,1};
static tV intrn=tV{1,4};
static boost::atomic<float>farray;
static v128_t aa,vv,xx,l,tt;

class funcs{

private:
  
public:

union{
float tuple_float_short(float num){
float cc,pp,uu,cc2,pp2,uu2,nn;
int r;
float Tdlt;

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

float tuple_float_long(float num){float cc,pp,uu,cc2,pp2,uu2,nn;
float Tdlt;
int r;
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
float Tdlt;
t1=std::chrono::steady_clock::now();
GLfloat ggg=num,ppg=num,uug=num;
tie(ggg,ppg,uug);
t2=std::chrono::steady_clock::now();
std::chrono::duration<double,std::chrono::milliseconds::period>time_span=std::chrono::duration<double,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return uug;
}

v128_t tuple_avx(float num){
float Tdlt;
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
float Tdlt;
t1=std::chrono::steady_clock::now();
int m=a[0]*1000.0;
l=wasm_i32x4_splat(m);
tt=wasm_f32x4_add(l,l);
t2=std::chrono::steady_clock::now();
std::chrono::duration<float, std::chrono::milliseconds::period> time_span=std::chrono::duration<float,std::chrono::milliseconds::period>(t2-t1);
Tdlt=time_span.count()*1000.0;
cout << Tdlt << endl;
return tt;
}

v128_t double_add(float fl){
tie(inte,sdeci,q,intrn);
inte.at(0,0)=std::floor(fl);
sdeci.at(0,0)=fl-inte.at(0,0);
intrn.at(0,0)=wasm_f32x4_make(inte.at(0,0),sdeci.at(0,0),sdeci.at(0,0),sdeci.at(0,0));
intrn.at(0,1)=wasm_f32x4_make(1.0,100.0,10.0,1.0);
intrn.at(0,0)=wasm_f32x4_div(intrn.at(0,0),intrn.at(0,1));
intrn.at(0,2)=wasm_f32x4_sqrt(intrn.at(0,0));
intrn.at(0,0)=wasm_f32x4_mul(intrn.at(0,2),intrn.at(0,2));
intrn.at(0,3)=wasm_f32x4_mul(intrn.at(0,0),intrn.at(0,1));
return intrn.at(0,3);
}
  
// native_simd<float> noblock(float y){
float noblock(float y){
__m64 p={6.0,6.0};
// __m64 pt={12.0,12.0};
// __m64 py3=_mm_adds_pi16_(p,pt);
// int reet=_m_to_int_(py3);
// int reet2=_mm_cvtsi64_si32_(py3);
// int tsst=_mm_extract_epi32(pt,1);
float_v reet=7.7f;
farray=y;
// boost::float128_t tyt=farray;
return farray;
 //   std::cout << ::at::ones({3,4}, at::CPU(at::kFloat)) << "\n";
 // emscripten_set_main_loop((void(*)())mss,0,0);

}

}rnn;

};
