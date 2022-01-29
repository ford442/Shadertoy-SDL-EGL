
document.getElementById('btn').addEventListener('click',function(){
Module.ccall('str');
  setTimeout(function(){
},14000);

});

document.getElementById('btn10').addEventListener('click',function(){
document.getElementById("canvas").style="height100vh;width:100vh;image-rendering:auto;";
// document.getElementById('pmhig').innerHTML=window.innerHeight;
});

document.getElementById('btn7').addEventListener('click',function(){
document.getElementById("canvas").height=window.innerHeight*1.5;
document.getElementById("canvas").width=window.innerHeight*1.5;
document.getElementById('btn4').style="background-color:grey;position:absolute;display:block;left:3%;top:33%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn5').style="background-color:pink;position:absolute;display:block;left:3%;top:43%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn3').style="background-color:red;position:absolute;display:block;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn6').style="background-color:yellow;position:absolute;display:block;left:3%;top:53%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById('btn').style="background-color:red;position:absolute;display:block;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('btn7').style="background-color:red;position:absolute;display:block;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById('pmhig').innerHTML=window.innerHeight*1.5;
Module.ccall("str");
});

