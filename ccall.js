
document.getElementById("btn").addEventListener("click",function(){
Module.ccall("str");
});

document.getElementById("btn11").addEventListener("click",function(){
Module.ccall("b3");
});

document.getElementById("btn10").addEventListener("click",function(){
document.getElementById("scanvas").height=window.innerHeight;
document.getElementById("scanvas").style.height='100vh';
document.getElementById("scanvas").width=window.innerHeight;
document.getElementById("scanvas").style.width='100vh';
});

document.getElementById("btn7").addEventListener("click",function(){
document.getElementById("scanvas").height=window.innerHeight*2;
document.getElementById("scanvas").style.height='200vh';
document.getElementById("scanvas").width=window.innerHeight*2;
document.getElementById("scanvas").style.width='200vh';
document.getElementById("btn4").style="background-color:grey;position:absolute;display:block;left:3%;top:33%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById("btn5").style="background-color:pink;position:absolute;display:block;left:3%;top:43%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById("btn3").style="background-color:red;position:absolute;display:block;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("btn6").style="background-color:yellow;position:absolute;display:block;left:3%;top:53%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById("btn").style="background-color:red;position:absolute;display:block;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("btn7").style="background-color:red;position:absolute;display:block;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("pmhig").innerHTML=window.innerHeight*2;
Module.ccall("str");
document.getElementById("btn10").click();
});

document.getElementById("btn77").addEventListener("click",function(){
document.getElementById("scanvas").height=2880;
document.getElementById("scanvas").width=2880;
document.getElementById("btn4").style="background-color:grey;position:absolute;display:block;left:3%;top:33%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById("btn5").style="background-color:pink;position:absolute;display:block;left:3%;top:43%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById("btn3").style="background-color:red;position:absolute;display:block;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("btn6").style="background-color:yellow;position:absolute;display:block;left:3%;top:53%;z-index:999997;border:5px solid green;border-radius:50%;";
document.getElementById("btn").style="background-color:red;position:absolute;display:block;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("btn7").style="background-color:red;position:absolute;display:block;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;";
document.getElementById("pmhig").innerHTML=2880;
Module.ccall("str");
document.getElementById("btn10").click();
});
