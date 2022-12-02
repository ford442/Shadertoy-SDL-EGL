let bz=new BroadcastChannel('bez');
document.getElementById('btn').addEventListener('click',function(){
let hi=window.innerHeight;
let wi=window.innerWidth;
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById("ihig").innerHTML=hi;
document.getElementById("circle").width=wi;
document.getElementById("circle").height=hi;
document.getElementById("di").click();
bz.postMessage({
data:222
});});
function pll(){
Module.ccall("pl");
};

const fll=new BroadcastChannel('file');
fll.addEventListener('message',ea=> {
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
pll();
});

document.getElementById('btn3').addEventListener('click',function(){
window.open('https://test.1ink.us/libflac.js');
});

document.getElementById('btn2').addEventListener('click',function(){
document.getElementById("ihig").innerHTML=window.innerHeight;
document.getElementById("circle").height=window.innerHeight;
document.getElementById("circle").width=window.innerWidth;
document.getElementById("scanvas").height=window.innerHeight;
document.getElementById("scanvas").width=window.innerHeight;
document.getElementById("bcanvas").height=window.innerHeight;
document.getElementById('btn3').style.border="5px solid green";
document.getElementById('btn2').style.border="5px solid red";
document.getElementById('btn2').style.background="red";
document.getElementById('btn').style.border="5px solid green";
document.getElementById('btn7').style.border="5px solid green";
document.getElementById('di').click();
});

document.getElementById('btn').addEventListener('click',function(){
document.getElementById('btn3').style="background-color:red;position:absolute;display:block;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn4').style="background-color:grey;position:absolute;display:block;left:3%;top:33%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn5').style="background-color:pink;position:absolute;display:block;left:3%;top:43%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn6').style="background-color:yellow;position:absolute;display:block;left:3%;top:53%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn7').style="background-color:red;position:absolute;display:block;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn').style="background-color:red;position:absolute;display:block;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;"
});

document.getElementById('btn6').addEventListener('click',function(){
let widd=document.getElementById("iwid").innerHTML;
document.getElementById("contain2").style="pointer-events:none;z-index:999993;height:"+window.innerHeight+"px;width:"+window.innerHeight+"px;position:absolute;top:0;left:0;right:0;";
document.getElementById("bcanvas").style="background-color:rgba(1,1,1,0);z-index:999992;height:100vh;width:100vh;position:absolute;top:0;";
document.getElementById("scanvas").style="position:absolute;top:0;background-color:rgba(1,1,1,0);z-index:999993;image-rendering:auto;width:"+window.innerHeight+"px;height:"+window.innerHeight+"px;opacity:0.3;";
document.getElementById('ihig').innerHTML=window.innerHeight;
document.getElementById("circle").height=window.innerHeight;
document.getElementById("circle").width=window.innerWidth;
document.getElementById('di').click();
});

document.getElementById('btn7').addEventListener('click',function(){
document.getElementById('btn4').style="background-color:grey;position:absolute;display:block;left:3%;top:33%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn5').style="background-color:pink;position:absolute;display:block;left:3%;top:43%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn3').style="background-color:red;position:absolute;display:block;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("bcanvas").style="background-color:rgba(1,1,1,1);z-index:999994;height:100vh;width:auto;position:absolute;text-align:center;";
document.getElementById("scanvas").style="background-color:rgba(1,1,1,0);z-index:999994;height:100vh;width:auto;position:absolute;text-align:center;";
document.getElementById('btn6').style="background-color:yellow;position:absolute;display:block;left:3%;top:53%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn').style="background-color:red;position:absolute;display:block;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn7').style="background-color:red;position:absolute;display:block;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('shut').innerHTML=2;
document.getElementById('di').click();
});
