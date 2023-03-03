#include "../../include/vanilla/main_simd.hpp"

v128_t simd_test(float * a){
// float sum_arr[] = {a, a, 1.0, 1.0};
 // double uu=a/2.0;
//  double ee=5.0/2.0;
float m=a[0]*2.0;v128_t l=wasm_f32x4_splat(m);
float n=a[0]*3.0;v128_t k=wasm_f32x4_splat(n);
float o=a[0]*4.0;v128_t j=wasm_f32x4_splat(o);
float p=a[0]*5.0;v128_t ii=wasm_f32x4_splat(p);

 // v128_t Input=wasm_f64x2_splat(uu);
//  v128_t Add=wasm_f64x2_splat(ee);
// v128_t nn=wasm_f64x2_add(Input,Add);
// v128_t ab=wasm_f32x4_splat(a);
// wasm_v128_store(0,nn);
v128_t b5;
v128_t b1=_mm_insert_ps(ii,b5,0);
v128_t b2=_mm_insert_ps(j,b5,1);
v128_t b3=_mm_insert_ps(k,b5,2);
v128_t b4=_mm_insert_ps(l,b5,3);
// wasm_v128_store(0,b5);
// v128_t b=wasm_v128_load(0);
v128_t tt=wasm_f32x4_add(b5,b5);
// double c=wasm_f64x2_extract_lane(b,0);
// double d=wasm_f64x2_extract_lane(b,1);
//  float re=c+d;
// v128_t d=wasm_v128_load(sum_arr);
 //  for(int i=0;i<3;i++){
// v128_t f=wasm_i32x4_add(d,d);
// float g=wasm_f32x4_extract_lane(f,0);
 // }
// float e=(float)g;
// return g;
return tt;
}

extern"C"{
  
float js_simd(float * aa){
v128_t cc=simd_test(aa);
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
},950);
var tsta=document.getElementById('smd').innerHTML;
var tst=[tsta,tsta,tsta,tsta];
const $H=Module.HEAPF32.buffer;
const $P=Module.HEAPF32.subarray(0,4);
$P.set(tst,0);
console.log('Javascript HEAPF32: ',$H);
var pointa=800;
var sim=new Float32Array($H,pointa,4);
sim.set(tst,0);
var reslt=Module.ccall('js_simd',"Number",["Number"],[pointa]);
console.log(reslt);
}
  
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt=tem.innerHTML;

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
},550);

});
  
int main(){
  
js_main();
return 0;

}
