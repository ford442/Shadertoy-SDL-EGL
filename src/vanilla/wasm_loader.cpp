#include <emscripten.h>
#include <emscripten/bind.h>

int main(){

EM_ASM({
  
let Module_lib1ink;

var scr=document.createElement("script");
scr.async=true;
scr.charset='utf-8';
scr.type='text/javascript';
scr.defer=true;
scr.src="https://wasm.noahcohn.com/b3hd/w0-008-mod.1ijs";
document.body.appendChild(scr);
setTimeout(function(){
Module_lib1ink=lib1ink();
Module_lib1ink.onRuntimeInitialized=function(){
Module_lib1ink.callMain();
};
},700);

let codeCall=new BroadcastChannel('codeCall');

const vsiz=document.querySelector('#vsiz');
let menuSz=parseInt(window.innerWidth*.75,10);

function normalResSetup(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#di').click();
},500);
document.querySelector('#status').style.backgroundColor="green";
}

document.querySelector('#status').height=20;
document.querySelector('#status').width=parseInt(window.innerHeight,10);
const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');
var $lt=tem.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();

const slo=new Slideout({
'panel':document.querySelector('#panel'),
'menu':document.querySelector('#menu'),
'padding':menuSz,'tolerance':70,
'easing':'cubic-bezier(.32,2,.55,.27)'
});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.025,max:1.50},
step:[0.005],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(1.0);
vsiz.innerHTML=Math.round(window.innerHeight);
document.querySelector('#menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;
$ll=($ll*1000);
tem.innerHTML=$ll;
vsiz.innerHTML=Math.round($ll/1000*window.innerHeight);
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16);
});

normalResSetup();

});

return 0;
}
