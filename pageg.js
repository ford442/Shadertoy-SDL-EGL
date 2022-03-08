
var slt,$ll,$h,wi,r$,$w,$r,$hi,$lt,rnum,$sc,$rn,$ls,lo,mv,vide,he,$pt,randSong;
const $iwid=document.getElementById("iwid");
const mV=document.getElementById("mv");
var $sngs=[];
var $vids=[];
var $shds=[];
function sngs(xml){
    var parser=new DOMParser();
    var htmlDoc=parser.parseFromString(xml.responseText,'text/html');
    var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
    $sngs[0]=preList.length;
    for (i=1;i<preList.length;i++){
        var txxt=preList[i].href;
        var Self=location.href;
        Self=Self.replace(/1ink.1ink/,"");
        txxt=txxt.replace(Self,"");
        $sngs[i+1]=Self+"songs/"+txxt;
    }}
function vids(xml){
    var parser=new DOMParser();
    var htmlDoc=parser.parseFromString(xml.responseText,'text/html');
    var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
    $vids[0]=preList.length;
    for (i=1;i<preList.length;i++){
        var txxt=preList[i].href;
        var Self=location.href;
        Self=Self.replace(/1ink.1ink/,"");
        txxt=txxt.replace(Self,"");
        $vids[i]=Self+"video/"+txxt;
    }}
function shds(xml){
    var parser=new DOMParser();
    var htmlDoc=parser.parseFromString(xml.responseText,'text/html');
    var preList=htmlDoc.getElementsByTagName("pre")[0].getElementsByTagName("a");
    $shds[0]=preList.length;
    for (i=1;i<preList.length;i++){
        var txxt=preList[i].href;
        var Self=location.href;
        Self=Self.replace(/1ink.1ink/,"");
        txxt=txxt.replace(Self,"");
        $shds[i+1]=Self+"all/"+txxt;
    }
    var randShade=Math.random();
    randShade=Math.round($shds[0]*randShade)+5;
    document.getElementById("path").innerHTML=$shds[randShade];
}

function scanSongs(){
    var xhttp=new XMLHttpRequest();
    xhttp.onreadystatechange=function(){
        if(this.readyState==4&&this.status==200){
            sngs(this);
        }
    };
    xhttp.open("GET","songs/",true);
    xhttp.send();
}
function scanVideos(){
    var xhttp=new XMLHttpRequest();
    xhttp.onreadystatechange=function(){
        if(this.readyState==4&&this.status==200){
            vids(this);
        }
    };
    xhttp.open("GET","video/",true);
    xhttp.send();
}
function scanShaders(){
    var xhttp=new XMLHttpRequest();
    xhttp.onreadystatechange=function(){
        if(this.readyState==4&&this.status==200){
            shds(this);
        }
    };
    xhttp.open("GET","all/",true);
    xhttp.send();
}
scanVideos();
scanShaders();
scanSongs();
document.getElementById('pmhig').innerHTML=Math.round(window.innerHeight);
// document.getElementById('ihig').innerHTML=window.innerHeight;
document.getElementById("scanvas").height=parseInt(window.innerHeight,10);
document.getElementById("scanvas").width=parseInt(window.innerHeight,10);
const loadV=document.getElementById("ldv");
loadV.addEventListener('canplay',function(){
    document.getElementById("hig").innerHTML=this.videoWidth;
    document.getElementById("wid").innerHTML=this.videoHeight;
    $sc=this.duration;
  var  mil=Math.round($sc*1000);
    $pt=Math.random()*mil;
    $pt=$pt*1000;
    $pt=$pt/1000;
    $pt=Math.round($pt);
    $pt=$pt/1000;
    document.getElementById("idur").innerHTML=mil/1000;
    document.getElementById("itim").innerHTML=$pt;
});
function snd(){
    randSong=Math.round(($sngs[0]-5)*Math.random());
  var  songSrc=$sngs[randSong+5];
    document.getElementById("track").src=songSrc;
   var sound=new Howl({src:[songSrc],volume:1,onend:function(){snd();}});
    sound.play();
    console.log(songSrc);
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
     var   tsl=new rSlider({target:"#timeslider",values:{min:1,max:15},
            step:[.10],labels:false,tooltip:true,scale:false,});
        grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
        slt=slt/100;tsl.setValues(slt);
        document.getElementById("menu").addEventListener("click",function(){
            $ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
        });
        setTimeout(function(){
            slt=tem.innerHTML;
        },8);},16);});
let adr="./intro.mp4";
wi=1920;he=1080;
setTimeout(function(){
    document.getElementById("btn").style.display="none";
    document.getElementById("btn3").style.display="none";
    document.getElementById("btn4").style.display="none";
    document.getElementById("btn5").style.display="none";
    document.getElementById("btn6").style.display="none";
    document.getElementById("btn7").style.display="none";
},1800);
document.getElementById("hig").innerHTML=he;
document.getElementById("wid").innerHTML=wi;
hii=Math.round(window.innerHeight);
document.getElementById("ihid").innerHTML=hii;
r$=(hii/he)*1000;r$=Math.round(r$);r$=r$/1000;
$w=Math.round(wi*r$);
const dat=document.getElementById("ihid");
const datb=document.getElementById("ihig");
var $hg=hii+"px";
datb.innerHTML=window.innerHeight;
$iwid.innerHTML=$w;
mV.width=$iwid.innerHTML;
mV.height=datb.innerHTML;
loadV.width=$iwid.innerHTML;
loadV.height=datb;
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("isrc").innerHTML=adr;
mV.play();
setTimeout(function(){document.getElementById("btn11").click();},2100);
 setTimeout(function(){document.getElementById("btn").click();},1750);
 setTimeout(function(){document.getElementById("btn3").click();},1750);
vide=document.querySelectorAll("video");
function loada(){
    document.getElementById('pmhig').innerHTML=window.innerHeight;
    hii=Math.round(window.innerHeight);
    document.getElementById("ihid").innerHTML=hii;
    $lt=Math.round(tem.innerHTML);
    $ldt=document.getElementById("tim").innerHTML;
    $ls=$lt/1000;
    $ls=$ls*1000;
    $ls=Math.round($ls);
    $ls=$ls/1000;
    rnum=Math.round((Math.random()*($vids[0]-5))+5);
    document.getElementById("isrc").innerHTML=$vids[rnum];
    $h=Math.round(window.innerHeight);
    he=document.getElementById("hig").innerHTML;
    r$=$h/he;
    $w=wi*r$;
    hii=Math.round(dat.innerHTML);
    $hi=$h-hii;
    if($hi>1){$h=Math.round(dat.innerHTML);datb.innerHTML=$h;$r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;}
    $hg=$h+"px";
    $iwid.innerHTML=Math.round($w);
    datb.innerHTML=window.innerHeight;
    window.scroll(0,0);
    console.log("h: "+loadV.naturalHeight);
    console.log("w: "+loadV.naturalWidth);
    
    console.log("h: "+loadV.naturalHeight);
    console.log("w: "+loadV.naturalWidth);
    setTimeout(function(){
        loadV.src=document.getElementById("isrc").innerHTML;
        loadV.currentTime=document.getElementById("itim").innerHTML;
        loadV.width=$iwid.innerHTML;
        loadV.height=datb.innerHTML;
        loadV.play();
        mv=vide[0].id;
        lo=vide[1].id;
        vide[0].id=lo;
        vide[1].id=mv;
        document.getElementById("di").click();
        loada();
    },$ldt);}
loada();

