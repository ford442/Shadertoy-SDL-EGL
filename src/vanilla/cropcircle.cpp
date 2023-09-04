#include "../../include/vanilla/cropcircle.hpp"

EM_JS(void, ma1, (), {
var mil,sfr,slo,tsl,tem,dat,datb,pan,a,hms,rihe,higg,slt,$loo,he,wi,adr,inhre,ihe,rato,iwi,nrato,nvids,$vids,hig,men,di,$lt,rnum,$sc,$rtm,$rn,$ls,endc,lo,mv,vide,adrl;
tem=document.getElementById("temptime");
pan=document.getElementById("panel");
ban=document.getElementById("buttona");
sfr=document.getElementById("slideframe");
function grab$lt(){
$lt=tem.innerHTML;
$lt=($lt*10);
$lt=Math.round($lt);
$lt=($lt/10);}
grab$lt();
slo=new Slideout({
"panel":document.getElementById("panel"),
"menu":document.getElementById("menu"),
"padding":384,
"tolerance":70,
"easing":"cubic-bezier(.32,2,.55,.27)"});
ban.addEventListener("click",function(){
slo.toggle();
sfr.innerHTML="";
setTimeout(function(){
sfr.innerHTML='<input type='+'"te'+'xt"id'+'="time'+'slider"/'+'>';
tsl=new rSlider({
target:"#timeslider",
values:{min:2,max:100},
step:[1],
labels:false,
tooltip:true,
scale:false,});
grab$lt();
slt=($lt/1000);
slt=(slt*10);
slt=Math.round(slt);
slt=(slt/10);
tsl.setValues(slt);
document.getElementById("menu").addEventListener("click",function(){
$loo=tsl.getValue();
$loo=($loo*10);
$loo=Math.round($loo);
$loo=($loo/10);
$loo=($loo*1000);
tem.innerHTML=$loo;});
setTimeout(function(){
slt=tem.innerHTML;},8);},16);});
nvids=<?php $cntr=file_get_contents("ctr.txt");echo "$cntr";?>;
$vids=<?php $cnt=file_get_contents("vids.txt");echo "$cnt";?>;
adr=$vids[0][0];
wi=$vids[0][1];
he=$vids[0][2];
document.getElementById("hig").innerHTML=he;
document.getElementById("wid").innerHTML=wi;
inhre=window.innerHeight;
inhre=Math.round(inhre);
document.getElementById("inhred").innerHTML=inhre;
rato=((wi/he)*100);
rato=Math.round(rato);
rato=(rato/100);
ihe=window.innerHeight;
ihe=Math.round(ihe);
iwi=(ihe*rato);
dat=document.getElementById("inhred");
datb=document.getElementById("ihig");
higg=(inhre+"px");
document.getElementById("ihig").innerHTML=ihe;
document.getElementById("iwid").innerHTML=iwi;
document.getElementById("wrap").style.lineheight=higg;
document.getElementById("wrap").style.height=higg;
document.getElementById("myvideo").src=adr;
function loada(){
inhre=window.innerHeight;
inhre=Math.round(inhre);
document.getElementById("inhred").innerHTML=inhre;
$lt=tem.innerHTML;
$ldt=($lt*0.4);
$ldt=Math.round($ldt);
$ls=(($lt/1000)+(2*($ldt/1000)));
$ldt=Math.round($ldt);
$rn=Math.random();
rnum=($rn*nvids);
rnum=Math.round(rnum);
wi=$vids[rnum][1];
he=$vids[rnum][2];
document.getElementById("hig").innerHTML=he;
document.getElementById("wid").innerHTML=wi;
adrl="https://img.1ink.us/cr1p/";
adr=$vids[rnum][0];
ihe=window.innerHeight;
ihe=(ihe*1);
ihe=Math.round(ihe);
rato=((ihe/he)*100);
rato=Math.round(rato);
rato=(rato/100);
iwi=(wi*rato);
iwi=Math.round(iwi);
dat=document.getElementById("inhred");
inhre=(dat.innerHTML);
high=(ihe-dat.innerHTML);
window.scroll(0,0);
setTimeout(function(){
higg=(inhre+"px");},$ldt);
vide=document.querySelectorAll("img");
document.getElementById("ihig").innerHTML=ihe;
document.getElementById("iwid").innerHTML=iwi;
document.getElementById("loadv").src=adr;
document.getElementById("loadv").width=iwi;
document.getElementById("loadv").height=ihe;
setTimeout(function(){
var cirw=window.innerWidth+5;
var cirh=ihe+5;
document.getElementById("circle").style.width=window.innerWidth+"px";
document.getElementById("circle").style.height=ihe+"px";
document.getElementById("wrap").style.lineheight=higg;
document.getElementById("wrap").style.height=higg;
document.getElementById("wrap").style.width=iwi+"px";
document.getElementById("imag").height=ihe;
document.getElementById("imag").width=iwi;
mv=vide[1].id;
lo=vide[2].id;
vide[1].id=lo;
vide[2].id=mv;

document.getElementById("di").click();
},$ldt);
// setTimeout(function(){document.getElementById("loadv").hidden=false;document.getElementById("myvideo").hidden=false;
// setTimeout(function(){document.getElementById("loadv").hidden=true;document.getElementById("myvideo").hidden=true;
// },2200);},200);
setTimeout(function(){loada();},$lt);}
loada();
});

EM_JS(void, ma, (), {
  var dis = set();
  if (dis) dis();dis = set();

  function set() {
    var i;
    var c = document.getElementById("masque");
    var cb = document.getElementById("orig");
    var cc = document.getElementById("temp");
    var ctx = c.getContext("2d");
    var ctxb = cb.getContext("2d");
    var ctxc = cc.getContext("2d");
    var cnP = document.getElementById("cp");
    var flP = document.getElementById("flip");
    var thr = document.getElementById("thr").innerHTML;
    var ra = document.getElementById("pckr").innerHTML;
    var ga = document.getElementById("pckg").innerHTML;
    var ba = document.getElementById("pckb").innerHTML;
    var rb = document.getElementById("pckbr").innerHTML;
    var gb = document.getElementById("pckbg").innerHTML;
    var bb = document.getElementById("pckbb").innerHTML;
    var alf = document.getElementById("alf").innerHTML;
    var alfb = document.getElementById("alfb").innerHTML;
    var ww = document.getElementById("iwid").innerHTML;
    var h = document.getElementById("ihig").innerHTML;
    var vd = document.getElementById("myvideo");
  
    ctxc.drawImage(vd, 0, 0, ww, h);
    var imgData = ctxc.getImageData(0, 0, ww, h);
    ctxb.drawImage(vd, 0, 0, ww, h);
    var rgbdat = new ImageData(ww, h);
    var rgbd = rgbdat.data;
    var imgg = imgData.data;
    for (i = 0; i < (ww * h * 4); i = i + 4) {
      var rgb = (imgg[i] * 0.2126) + (imgg[i + 1] * 0.7152) + (imgg[i + 2] * 0.0722);
      if (rgb > thr) {
        rgbd[i] = ra;
        rgbd[i + 1] = ga;
        rgbd[i + 2] = ba;
        rgbd[i + 3] = alf;
      } else {
        rgbd[i] = rb;
        rgbd[i + 1] = gb;
        rgbd[i + 2] = bb;
        rgbd[i + 3] = alfb;
      }
    }
    ctx.putImageData(rgbdat, 0, 0);

    function Ra() {
      flP.setAttribute("style", "transform: scaleX(1);");
      cnP.setAttribute("style", "transform: scaleY(1);");
    }

    function Rb() {
      flP.setAttribute("style", "transform: scaleX(-1);");
      cnP.setAttribute("style", "transform: scaleY(-1);");
    }
    var knb = document.getElementById("rra");
    var kna = document.getElementById("mainr");
    var knc = document.getElementById("rrb");
    var knd = document.getElementById("rrc");
    var knbb = document.getElementById("rrab");
    var kncb = document.getElementById("rrbb");
    var kndb = document.getElementById("rrcb");
    var rott = 0;
    var rottb = 0;
    var rottc = 0;
    var dsd = false;

    function $rn() {
      if (dsd) {
        return;
      };
      var rate = (kna.innerHTML);

      function rrra(rta) {
        cnP.setAttribute("style", "transform:rotate(" + rta + "deg);");
      }

      function rrrb(rtb) {
        cnP.setAttribute("style", "transform:rotate(" + rtb + "deg);");
      }

      function rrrc(rtc) {
        cnP.setAttribute("style", "transform:rotate(" + rtc + "deg);");
      }
      if ((rott - knd.innerHTML) < 0) {
        rott = (rott + 360 - knd.innerHTML);
      } else {
        rott = rott - knd.innerHTML;
      }
      rrra(rott);
      if ((rottb - knc.innerHTML) < 0) {
        rottb = (rottb + 360 - knc.innerHTML);
      } else {
        rottb = (rottb - knc.innerHTML);
      }
      setTimeout(function() {
        Rb();
        rrrb(rottb);
      }, rate);
      if ((rottc + knb.innerHTML) > 360) {
        rottc = ((rottc + knb.innerHTML) - 360);
      } else {
        rottc = (rottc + knb.innerHTML);
      }
      setTimeout(function() {
        Ra();
        rrrc(rottc);
      }, rate);
      setTimeout(function() {
        $rn();
      }, rate);
    }
    $rn();
    document.getElementById("di").onclick = function() {
      dsd = true;
      set();
    };
    return () => {
      dsd = true;
    };
  }
});

int main() {
  ma1();
  ma();
  return 1;
}
