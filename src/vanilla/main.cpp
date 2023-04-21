#include "../../include/vanilla/main.hpp"

using namespace ::boost::tuples;

float tuple_float(float num){
boost::timer::auto_cpu_timer a1;
float cc=num,pp=num,uu=num;
tie(cc,pp,uu);
return uu;
}

GLfloat tuple_gl(GLfloat num){
boost::timer::auto_cpu_timer a2;
GLfloat gg=num,pp=num,uu=num;
tie(gg,pp,uu);
return uu;
}

v128_t tuple_avx(float num){
boost::timer::auto_cpu_timer a3;
v128_t aa=wasm_i32x4_splat(num);
v128_t vv=wasm_i32x4_splat(num);
v128_t xx=wasm_i32x4_splat(num);
tie(aa,vv,xx);
return xx;
}

v128_t simd_test(float * a){
int m=a[0]*1000;
v128_t l=wasm_i32x4_splat(m);
v128_t b5;
v128_t b1=_mm_insert_ps(m,b5,0);
v128_t b2=_mm_insert_ps(m,b5,1);
v128_t b3=_mm_insert_ps(m,b5,2);
v128_t b4=_mm_insert_ps(m,b5,3);
v128_t tt=wasm_f32x4_add(b5,b5);
return tt;
}

extern "C"{

float js_tuple_float(float nm){ 
return tuple_float(nm);
}

GLfloat js_tuple_gl(float nm){
return tuple_gl(nm);
}
  
float js_tuple_avx(float nm){
return tuple_avx(nm);
}
  
float js_simd(float * aa){
v128_t cc=simd_test(aa);
wasm_v128_store(&out[i], prod);
float c=wasm_f32x4_extract_lane(cc,0);
float d=wasm_f32x4_extract_lane(cc,1);
float ce=wasm_f32x4_extract_lane(cc,2);
float de=wasm_f32x4_extract_lane(cc,3);
float re=c+d+ce+de;
return re;
}

}

EM_JS(void,js_main,(),{

"use strict";

function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall('js_hello');
var tst=[tsta,10.0,10.0,10.0];
const $H=Module.HEAPF32.buffer;
const $P=Module.HEAPF32.subarray(0,4);
$P.set(tst,0);
console.log('Javascript HEAPF32: ',$H);
var pointa=800;
var sim=new Float32Array($H,pointa,4);
sim.set(tst,0);
var reslt=Module.ccall('js_simd',"Number",["Number"],[pointa]);
console.log(reslt);
},1000);
setTimeout(function(){
var reslt=Module.ccall('js_tuple_float',"Number",["Number"],[1.0]);
console.log(reslt);
},1000);
setTimeout(function(){
var reslt=Module.ccall('js_tuple_gl',"Number",["Number"],[1.0]);
console.log(reslt);
},1000);
setTimeout(function(){
var reslt=Module.ccall('js_tuple_avx',"Number",["Number"],[1.0]);
console.log(reslt);
},1000);

}
  
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var  $lt=tem.innerHTML;

function grab$lt(){
$lt=Math.round($lt);
}

$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16)
;});
document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});
setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);

});
  
int main(void){
  
js_main();
return 1;

}
