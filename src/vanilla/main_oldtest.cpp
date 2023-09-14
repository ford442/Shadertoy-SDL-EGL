#include "../../include/vanilla/main_oldtest.hpp"

float cc,pp,uu;
float cc2,pp2,uu2;
float ccc,ppc,uuc;
float cc2c,pp2c,uu2c;

funcs Funcs;
tens Tens;

extern "C"{
  
float js_double(float nem){ 
v128_t rtt=Funcs.rnn.double_add(nem);
float retrnI=wasm_f32x4_extract_lane(rtt,0);
float retrnD=wasm_f32x4_extract_lane(rtt,4);
return retrnI;
}
  
float js_Tensors(float nm){ 
return Tens.rtt(nm);
}
  
float js_tuple_float_short(float nm){ 
return Funcs.rnn.tuple_float_short(nm);
}
  
float js_tuple_float_long(float nm){ 
return Funcs.rnn.tuple_float_long(nm);
}

GLfloat js_tuple_gl(float nm){
return Funcs.rnn.tuple_gl(nm);
}
  
float js_tuple_avx(float nm){
v128_t ans=Funcs.rnn.tuple_avx(nm);
float retrn=wasm_f32x4_extract_lane(ans,0);
return retrn;
}

float js_tuple_avx_gl(GLfloat nm){
v128_t ans=Funcs.rnn.tuple_avx(nm);
GLfloat retrn=wasm_f32x4_extract_lane(ans,0);
return retrn;
}
  
float js_simd(float * aa){
v128_t cc=Funcs.rnn.simd_test(aa);
// wasm_v128_store(&out[i], prod);
float c=wasm_f32x4_extract_lane(cc,0);
float d=wasm_f32x4_extract_lane(cc,1);
float ce=wasm_f32x4_extract_lane(cc,2);
float de=wasm_f32x4_extract_lane(cc,3);
float re=c+d+ce+de;
return re;
}

float js_noblock(float yy){
float tt=(float)Funcs.rnn.noblock(yy);
return tt;
}
  
void wgpu_init1(){
init1();
return;
}
  
void wgpu_init2(){
init2();
return;
}
  
void wgpu_init3(){
init3();
return;
}
  
void wgpu_init4(){
init4();
return;
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
var tst=[10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0,];
const $H=Module.HEAPF32.buffer;
const $P=Module.HEAPF32.subarray(0,32);
$P.set(tst,0);
console.log('Javascript HEAPF32: ',$H);
let pointa=800;
var sim=new Float32Array($H,pointa,32);
sim.set(tst,0);
console.log("intrins function:");
var reslt=Module.ccall('js_simd',"Number",["Number"],[pointa]);
console.log(reslt);
},400);
setTimeout(function(){
console.log("float function short:");
var reslt=Module.ccall('js_tuple_float_short',"Number",["Number"],[1.0]);
console.log(reslt);
},500);
setTimeout(function(){
console.log("float function long:");
var reslt=Module.ccall('js_tuple_float_long',"Number",["Number"],[1.0]);
console.log(reslt);
},600);
setTimeout(function(){
console.log("gl function:");
var reslt=Module.ccall('js_tuple_gl',"Number",["Number"],[1.0]);
console.log(reslt);
},700);
setTimeout(function(){
console.log("avx function:");
var reslt=Module.ccall('js_tuple_avx',"Number",["Number"],[1.0]);
console.log(reslt);
},800);
setTimeout(function(){
console.log("avx gl function:");
var reslt=Module.ccall('js_tuple_avx_gl',"Number",["Number"],[1.0]);
console.log(reslt);
},900);
setTimeout(function(){
console.log("Tensor class def:");
var reslt=Module.ccall('js_Tensors',"Number",["Number"],[1.0]);
console.log(reslt);
},1000);
setTimeout(function(){
console.log("Intrins Tensor:");
var reslt=Module.ccall('js_double',"Number",["Number"],[1.0]);
console.log(reslt);
},1100);
setTimeout(function(){
console.log("noblock (and native_simd):");
var pointa=800;
var reslt=Module.ccall('js_noblock',"Number",["Number"],[pointa]);
console.log(reslt);
},1200);
setTimeout(function(){
console.log("noblock (and native_simd):");
Module.ccall('wgpu_init1',{async:true});
},1400);
setTimeout(function(){
Module.ccall('wgpu_init2');
},2600);
setTimeout(function(){
Module.ccall('wgpu_init3');
},3800);
setTimeout(function(){
// Module.ccall('wgpu_init4');
},5000);
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
},500);

});
  
int main(void){
icctest();
sleep(1);
js_main();
return 0;
}
