
var tsl,slt,$ll,$h,wi,r$,$w,$r,$hi,$lt,rnum,$sc,$rn,$ls,lo,mv,vide,he,$pt,randSong;

var $iwid=document.getElementById("iwid");
var mV=document.getElementById("mv");
var loadV=document.getElementById("ldv");
let $sngs=[];
let $vids=[];
let $shds=[];

function sngs(xml){
var nparser=new DOMParser();
var htmlDoc=nparser.parseFromString(xml.responseText,'text/html');
var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
$sngs[0]=preList.length;
    console.log('Number of songs: '+$sngs[0]);
for (var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$sngs[i]=Self+"songs/"+txxt;
}}

function vids(xml){
var vparser=new DOMParser();
var htmlDoc=vparser.parseFromString(xml.responseText,'text/html');
var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
$vids[0]=preList.length;
      console.log('Number of videos: '+$vids[0]);

for (var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$vids[i]=Self+"video/"+txxt;
}}

function shds(xml){
var sparser=new DOMParser();
var htmlDoc=sparser.parseFromString(xml.responseText,'text/html');
var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
$shds[0]=preList.length;
      console.log('Number of shaders: '+$shds[0]);

for (var i=1;i<preList.length;i++){
var txxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxt=txxt.replace(Self,"");
$shds[i+1]=Self+"all/"+txxt;
}
var randShade=Math.random();
randShade=Math.floor($shds[0]*randShade)+5;
console.log('Random shader: #'+randShade+' '+$shds[randShade]);

document.getElementById("path").innerHTML=$shds[randShade];
}

function scanSongs(){
var nxhttp=new XMLHttpRequest();
nxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
sngs(this);
}
};
nxhttp.open("GET","songs/",true);
nxhttp.send();
}
function scanVideos(){
var fxhttp=new XMLHttpRequest();
fxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
vids(this);
}
};
fxhttp.open("GET","video/",true);
fxhttp.send();
}

function scanShaders(){
var dxhttp=new XMLHttpRequest();
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
shds(this);
}
};
dxhttp.open("GET","all/",true);
dxhttp.send();
}

scanVideos();
scanShaders();
scanSongs();

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById("scanvas").height=parseInt(window.innerHeight,10);
document.getElementById("scanvas").width=parseInt(window.innerHeight,10);

function snd(){
randSong=Math.floor(($sngs[0]-5)*Math.random());
  console.log('Random song: #'+randSong+' '+$sngs[randSong+5]);

var songSrc=$sngs[randSong+5];
document.getElementById("track").src=songSrc;
var sound=new Howl({src:[songSrc],volume:1,onend:function(){snd();}});
sound.play();
}

document.getElementById('btn8').addEventListener('click',function(){
snd();
});

const tem=document.getElementById("tim");
ban=document.getElementById("btn1");
const sfr=document.getElementById("slideframe");
function grab$lt(){
$lt=Math.round($lt);}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({"panel":document.getElementById("panel"),"menu":document.getElementById("menu"),"padding":384,"tolerance":70,"easing":"cubic-bezier(.32,2,.55,.27)"});
ban.addEventListener("click",function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
tsl=new rSlider({target:"#timeslider",values:{min:1.00,max:45.00},
step:[0.50],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById("menu").addEventListener("click",function(){
$ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);},16);});

let adr="./1inkus.png";
wi=1024;
he=809;
hii=window.innerHeight;
document.getElementById("ihid").innerHTML=hii;
r$=hii/he;
$w=wi*r$;
let $ihigB=document.getElementById("ihid");
let $ihig=document.getElementById("ihig");
var $hg=hii+"px";
$ihig.innerHTML=parseInt(window.innerHeight,10);
$iwid.innerHTML=parseInt($w,10);
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("isrc").innerHTML=adr;

setTimeout(function(){document.getElementById("btn2").click();},2000);
setTimeout(function(){document.getElementById("btn11").click();},2400);
// setTimeout(function(){document.getElementById("btn").click();},2800);
setTimeout(function(){document.getElementById("btn10").click();},3800);
// setTimeout(function(){document.getElementById("btn8").click();},3200);

function loada(){
document.getElementById('wrap').height=window.innerHeight;
document.getElementById('wrap').width=window.innerHeight;

document.getElementById("wid").innerHTML=loadV.naturalWidth;
document.getElementById("hig").innerHTML=loadV.naturalHeight;

vide=document.querySelectorAll("img");
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
hii=window.innerHeight;
document.getElementById("ihid").innerHTML=hii;
$lt=Math.round(tem.innerHTML);
$ldt=document.getElementById("tim").innerHTML;
$ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
rnum=Math.floor((Math.random()*($vids[0]-5))+5);
  console.log('Random video: #'+rnum+' '+$vids[rnum]);

document.getElementById("isrc").innerHTML=$vids[rnum];
$h=window.innerHeight;
var he=document.getElementById("hig").innerHTML;
var wi=document.getElementById("wid").innerHTML;
r$=he/$h;
$w=wi/r$;
hii=$ihigB.innerHTML;
$hi=$h-hii;
if($hi>1){$h=$ihigB.innerHTML;$ihig.innerHTML=$h;$r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;}
$hg=$h+"px";
window.scroll(0,0);
mv=vide[0].id;
lo=vide[1].id;
vide[0].id=lo;
vide[1].id=mv;
document.getElementById("ldv").src=document.getElementById("isrc").innerHTML;
$iwid.innerHTML=$w;
$ihig.innerHTML=window.innerHeight;
document.getElementById('pmhig').innerHTML=window.innerHeight;
setTimeout(function(){

document.getElementById('circle').height=window.innerHeight;
document.getElementById('circle').width=window.innerWidth;
    
document.getElementById('contain1').height=parseInt(window.innerHeight;
document.getElementById('contain1').width=window.innerHeight;
    
document.getElementById('contain2').height=window.innerHeight;
document.getElementById('contain2').width=window.innerHeight;
    
document.getElementById("di").click();
},500);
setTimeout(function(){
loada();
},$ldt);}

loada();
