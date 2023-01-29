#include "../include/b3main.hpp"

EM_JS(void,js_main,(),{

  "use strict";
  var $h,$pt,slt,$ll,r$,$w,$r,$lt,$hg,$ls,lo,mv,he,wi;

  function highResStart(){
    document.getElementById('scanvas').height=window.innerHeight*2;
    document.getElementById('scanvas').width=window.innerHeight*2;
    document.getElementById('scanvas').style.height=(window.innerHeight*2)+'px';
    document.getElementById('scanvas').style.width=(window.innerHeight*2)+'px';
    document.getElementById('pmhig').innerHTML=window.innerHeight*2;
    setTimeout(function(){
      Module.ccall('str');
    },550);
    setTimeout(function(){
      document.getElementById('scanvas').height=window.innerHeight;
      document.getElementById('scanvas').width=window.innerHeight;
      document.getElementById('scanvas').style.height=window.innerHeight+'px';
      document.getElementById('scanvas').style.width=window.innerHeight+'px';
      document.getElementById('pmhig').innerHTML=window.innerHeight;
    },750);
    setTimeout(function(){
      document.getElementById('shut').innerHTML=2;
      document.getElementById('circle').width=window.innerWidth;
      document.getElementById('circle').height=window.innerHeight;
    },1250);
  }

  function normalResStart(){
    setTimeout(function(){
Module.ccall('b3_egl');
          },350);
    setTimeout(function(){
      Module.ccall('str');
    },750);
    setTimeout(function(){
      document.getElementById('shut').innerHTML=2;
      document.getElementById('circle').width=window.innerWidth;
      document.getElementById('circle').height=window.innerHeight;
    },950);
  }

  const fll=new BroadcastChannel('file');
  const shutDown=new BroadcastChannel('shutDown');

  var $iwid=document.getElementById('iwid');

  var $shds=[];

  function shds(xml){
    const sparser=new DOMParser();
    const htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
    const preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
    $shds[0]=preList.length;
    for(var i=1;i<preList.length;i++){
      var txxt=preList[i].href;
      var Self=location.href;
      Self=Self.replace(/1ink.1ink/,"");
      txxt=txxt.replace(Self,"");
      $shds[i+1]='https://glsl.1ink.us/shaders/'+txxt;
    };
    var randShade=Math.random();
    randShade=Math.floor($shds[0]*randShade)+5;
    if(document.getElementById('rndShader')=='1'){
      document.getElementById('path').innerHTML=$shds[randShade];
    }
    var pth=document.getElementById('path').innerHTML;
    const ff=new XMLHttpRequest();
    ff.open('GET',pth,true);
    ff.responseType='arraybuffer';
    ff.onload=function(oEvent){
      const sarrayBuffer=ff.response;
      if(sarrayBuffer){
        const sfil=new Uint8ClampedArray(sarrayBuffer);
        FS.writeFile('/shader/shader1.toy',sfil);
        setTimeout(function(){
          normalResStart();
        },350);
      };};
    ff.send(null);
  }

  function scanShaders(){
    const dxhttp=new XMLHttpRequest();
    dxhttp.onreadystatechange=function(){
      if(this.readyState==4&&this.status==200){
        shds(this);
      };};
    dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
    dxhttp.send();
  }

  scanShaders();

  document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
  document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
  document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
  document.getElementById('scanvas').width=parseInt(window.innerHeight,10);

  const tem=document.getElementById('tim');
  const ban=document.getElementById('menuBtn');
  const sfr=document.getElementById('slideframe');

  function grab$lt(){
    $lt=Math.round($lt);
  }

$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({
  'panel':document.getElementById('panel'),
  'menu':document.getElementById('menu'),
  'padding':384,
  'tolerance':70,
  'easing':'cubic-bezier(.32,2,.55,.27)'
  });
  ban.addEventListener('click',function(){
    slo.toggle();
    sfr.innerHTML="";
  setTimeout(function(){
grab$lt();
    slt=$lt/1000;
    slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({
  target:'#timeslider',
  values:{
    min:0.25,
    max:30.00
    },
  step:[0.25],
  labels:false,
  tooltip:true,
  scale:false,
});
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
  $ll=$ll/100;
  $ll=($ll*1000);
  tem.innerHTML=$ll;
  });
setTimeout(function(){
  slt=tem.innerHTML;
},8);
  },16);
  });
  wi=parseInt(window.innerHeight,10);
  he=parseInt(window.innerHeight,10);
  var hii=window.innerHeight;
  document.getElementById('ihid').innerHTML=hii;
  r$=hii/he;
  $w=wi*r$;
  const $ihigB=document.getElementById('ihid');
  const $ihig=document.getElementById('ihig');
  $hg=hii+'px';
  $ihig.innerHTML=parseInt(window.innerHeight,10);
  $iwid.innerHTML=parseInt($w,10);
  document.getElementById('wrap').style.lineheight=$hg;
  document.getElementById('wrap').style.pointerEvents='auto';

  const pnnl=document.body;
  pnnl.addEventListener('keydown',spKey);

  function loada(){
      document.getElementById('wid').innerHTML=parseInt(document.innerHeight);
      document.getElementById('hig').innerHTML=parseInt(document.innerHeight);
      document.getElementById('pmhig').innerHTML=parseInt(document.innerHeight);
      document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
      hii=window.innerHeight;
      document.getElementById('ihid').innerHTML=hii;
      $lt=Math.round(tem.innerHTML);
      var $ldt=document.getElementById('tim').innerHTML;
      $ls=$lt/1000;
      $ls=$ls*1000;
      $ls=Math.round($ls);
      $ls=$ls/1000;
      $h=window.innerHeight;
      he=document.getElementById('hig').innerHTML;
      wi=document.getElementById('wid').innerHTML;
      r$=he/$h;
      $w=wi/r$;
      hii=$ihigB.innerHTML;
      var $hi=$h-hii;
      if($hi>1){$h=$ihigB.innerHTML;$ihig.innerHTML=$h;$r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;};
      $hg=$h+'px';
      window.scroll(0,0);
      $iwid.innerHTML=parseInt($w,10);
      $ihig.innerHTML=parseInt(window.innerHeight,10);
      document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
      document.getElementById('circle').height=parseInt(window.innerHeight,10);
      document.getElementById('circle').width=parseInt(window.innerWidth,10);
      document.getElementById('di').click();
    setTimeout(function(){
      loada();
    },$ldt);
  }
  loada();

  });

  int main(){

    EM_ASM({
      "use strict";
      FS.mkdir("/snd");
      FS.mkdir("/shader");
    });

    js_main();
    return 0;

  };
