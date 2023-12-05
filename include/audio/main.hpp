#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>

// #pragma clang diagnostic ignored "-Wdeprecated-declarations"
/*
// #undef _FLT_EVAL_METHOD
// #define _FLT_EVAL_METHOD 0
#pragma STDC CX_LIMITED_RANGE ON
#pragma STDC FP_CONTRACT OFF
#define _XOPEN_REALTIME 1
#define _POSIX_ASYNC_IO 1
#define _POSIX_PRIO_IO 1
#define _POSIX_SYNC_IO 1
#define	_XOPEN_SHM 1
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS
#define _FLT_ROUNDS 1
#define _POSIX_REGEXP	1
*/

#include <wasm_simd128.h>
#include <tmmintrin.h> // ssse 3
#include <smmintrin.h>  // sse 4.1
#include <xmmintrin.h>
#include <immintrin.h> 
#include <nmmintrin.h>  //  sse 4.2
#include <avxintrin.h>  // AVX

#include <unistd.h>
// #include <GL/gl.h>

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include "boost/tuple/tuple.hpp"
#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#define register

#include <boost/function.hpp>
using namespace ::boost::tuples;

#include <cstdlib>
#include <ctime>
#include <random>

class song_select{

private:

std::random_device rd;
v128_t Dr;
int rD=0;

public:

inline v128_t rNd(int Th){
tie(Th,rD,Dr);
std::srand(rd());
rD=std::rand()%Th;
Dr=wasm_i32x4_splat(rD);
return Dr;
}

};

extern "C"{
  
v128_t Rg;
int c=0;

int r4nd(int);

}


EM_JS(void,js_main,(),{

'use strict';

var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

function normalResStart(){
document.getElementById('di').click();
// setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
// },100);
}

function pll(){
Module.ccall('pl');
}

const fll=new BroadcastChannel('file');
const shutDown=new BroadcastChannel('shutDown');
  
setTimeout(function(){
window.open('./flac');
},500);
  
setTimeout(function(){
shutDown.postMessage({data:222});
},4000);
  
fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
setTimeout(function(){
shutDown.postMessage({data:222});
pll();
},100);
});

var $iwid=document.getElementById('iwid');
var mV=document.getElementById('mv');
var loadV=document.getElementById('ldv');
var $sngs=[];

function sngs(xml){
const nparser=new DOMParser();
const htmlDocs=nparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocs.getElementsByTagName('pre')[0].getElementsByTagName('a');
$sngs[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$sngs[i]=Self+'songs/'+txxt;
}}

function scanSongs(){
const nxhttp=new XMLHttpRequest();
nxhttp.addEventListener("load",function(){
sngs(this);
});
nxhttp.open('GET','songs/',true);
nxhttp.send();
}

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);

function snd(){
var sngsNum=$sngs[0];
const randSong=Module.ccall('r4nd','Number',['Number'],[sngsNum]);
const songSrc=$sngs[randSong+5];
document.getElementById('track').src=songSrc;
const sng=new BroadcastChannel('sng');
sng.postMessage({data:songSrc});
}

document.getElementById('musicBtn').addEventListener('click',function(){
window.open('./flac');
setTimeout(function(){
snd();
},1300);
});

const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){slt=tem.innerHTML;},8);},16);});

function spKey(e){
if(e.code=='KeyQ'){
window.open('./flac');
setTimeout(function(){
snd();
},2000);
};
}

const pnnl=document.body;
pnnl.addEventListener('keydown',spKey);
scanSongs();
normalResStart();
});
