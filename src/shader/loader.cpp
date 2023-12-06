#include "../../include/shader/loader.hpp"

EM_JS(void,js_main,(),{
var sr=document.getElementById('sourc').innerHTML;
let inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='menuBtn';
inputElement.style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
document.body.appendChild(inputElement);
let divElement=document.createElement('div');
divElement.style='background-color:white;position:absolute;display:block;left:5%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
divElement.innerHTML='MENU';
document.body.appendChild(divElement);
inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='musicBtn';
inputElement.style='background-color:cyan;position:absolute;display:block;left:3%;bottom:5%;z-index:3200;border:6px solid green;border-radius:20%;';
document.body.appendChild(inputElement);
divElement=document.createElement('div');
divElement.style='background-color:white;position:absolute;display:block;left:5%;bottom:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
divElement.innerHTML='CHANGE SONG';
document.body.appendChild(divElement);
divElement=document.createElement('div');
divElement.id='pmhig';
divElement.hidden=true;
document.body.appendChild(divElement);
divElement=document.createElement('div');
divElement.id='ihig';
divElement.hidden=true;
document.body.appendChild(divElement);
let canvasElement=document.createElement('canvas');
canvasElement.id='canvas';
document.getElementById('contain1').appendChild(canvasElement);
let scr=document.createElement("script");
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
