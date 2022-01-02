let bz=new BroadcastChannel('bez');
document.getElementById('btn').addEventListener('click',function(){
document.getElementById('pmhig').innerHTML=window.innerHeight;
bz.postMessage({
data:222
});});

document.getElementById('btn2').addEventListener('click',function(){
let hi=Math.round(window.innerHeight);
let wi=Math.round(window.innerWidth);
document.getElementById("ihig").innerHTML=hi;
document.getElementById("iwid").innerHTML=wi;
document.getElementById("circle").width=wi;
document.getElementById("circle").height=hi;
document.getElementById("canvas").height=hi;
document.getElementById("canvas").width=hi;
document.getElementById("wrap").height=hi;
document.getElementById("wrap").width=hi;
document.getElementById("contain2").height=hi;
document.getElementById("contain2").width=hi;
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
let midl=(window.innerWidth*0.5)-(window.innerHeight*0.5);
document.getElementById("contain2").style="pointer-events:none;z-index:999993;height:"+window.innerHeight+"px;width:"+window.innerHeight+"px;position:absolute;top:0px;left:"+midl+"px;";
document.getElementById("canvas").style="position:absolute;left:0;top:0;background-color:rgba(1,1,1,0);z-index:999995;image-rendering:pixelated;width:"+window.innerHeight+"px;height:"+window.innerHeight+"px;";
document.getElementById('ihig').innerHTML=Math.round(window.innerHeight);
document.getElementById("circle").height=window.innerHeight;
document.getElementById("circle").width=window.innerWidth;
document.getElementById('di').click();
});


