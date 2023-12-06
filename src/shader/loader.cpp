#include "../../include/shader/loader.hpp"

EM_JS(void,js_main,(),{
var sr=document.getElementById('sourc').innerHTML;
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='menuBtn';
inputElement.style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
document.body.appendChild(inputElement);
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='startBtn';
inputElement.style='background-color:gold;position:absolute;display:block;left:6%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;';
document.body.appendChild(inputElement);
var divElement=document.createElement('div');
divElement.style='background-color:white;position:absolute;display:block;left:8%;top:9%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
divElement.innerHTML='START';
document.body.appendChild(divElement);
var divElement=document.createElement('div');
divElement.style='background-color:white;position:absolute;display:block;left:5%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
divElement.innerHTML='MENU';
document.body.appendChild(divElement);
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='musicBtn';
inputElement.style='background-color:cyan;position:absolute;display:block;left:3%;bottom:5%;z-index:3200;border:6px solid green;border-radius:20%;';
document.body.appendChild(inputElement);
var divElement=document.createElement('div');
divElement.style='background-color:white;position:absolute;display:block;left:5%;bottom:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
divElement.innerHTML='CHANGE SONG';
document.body.appendChild(divElement);
var divElement=document.createElement('div');
divElement.id='pmhig';
divElement.hidden=true;
document.body.appendChild(divElement);
var divElement=document.createElement('div');
divElement.id='ihig';
divElement.hidden=true;
document.body.appendChild(divElement);
var divElement=document.createElement('div');
divElement.id='ihig';
divElement.hidden=true;
document.body.appendChild(divElement);
var divElement=document.createElement('div');
divElement.id='tim';
divElement.hidden=true;
document.body.appendChild(divElement);
var divElement=document.createElement('div');
divElement.id='slideframe';
document.getElementById('menu').appendChild(divElement);
var canvasElement=document.createElement('canvas');
canvasElement.id='canvas';
document.getElementById('contain1').appendChild(canvasElement);
var divElement=document.createElement('div');
divElement.id='status';
document.body.appendChild(divElement);
var scr=document.createElement("script");
scr.async=true;
scr.charset='utf-8';
scr.type='text/javascript';
scr.defer=true;
scr.src="https://wasm.noahcohn.com/b3hd/w3001.1ijs";
document.body.appendChild(scr);
});

int main(){
js_main();
return 0;
}
