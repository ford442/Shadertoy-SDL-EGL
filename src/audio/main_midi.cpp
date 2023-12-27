#include "../../include/audio/main_midi.hpp"

rnnd rnnd;

extern"C"{

int r4nd(int tH){
Rg=rnnd.rNd(tH);
c=wasm_i32x4_extract_lane(Rg,0);
return c;
}
  
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

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);

function rnd(){
  // const random=Module.ccall('r4nd','Number',['Number'],[total possible]);
}

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

const pnnl=document.body;
pnnl.addEventListener('keydown',spKey);
scanSongs();
normalResStart();
});

static inline boost::function<void()>jss=[](){js_main();};

int main(){
emscripten_run_script('./test.js');
tie(jss,js_main);
jss();
return 0;
}
