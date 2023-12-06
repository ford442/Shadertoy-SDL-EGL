#include "../../include/shader/loader.hpp"

EM_JS(void,js_main,(),{
window.open('https://test.1ink.us/r3b1/');
var sr=document.getElementById('sourc').innerHTML;
var longString="var divElement=document.createElement('div'); divElement.id='sourc'; divElement.hidden=true; document.body.appendChild(divElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='menuBtn'; inputElement.style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='startBtn'; inputElement.style='background-color:gold;position:absolute;display:block;left:6%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='startBtn3'; inputElement.style='background-color:yellow;position:absolute;display:block;left:3%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;'; document.body.appendChild(inputElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:8%;top:9%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='START'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:5%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='MENU'; document.body.appendChild(divElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='musicBtn'; inputElement.style='background-color:cyan;position:absolute;display:block;left:3%;bottom:5%;z-index:3200;border:6px solid green;border-radius:20%;'; document.body.appendChild(inputElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:5%;bottom:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='CHANGE SONG'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='pmhig'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='ihig'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='ihig'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='tim'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='slideframe'; document.getElementById('menu').appendChild(divElement); var canvasElement=document.createElement('canvas'); canvasElement.id='canvas'; document.getElementById('contain1').appendChild(canvasElement); var divElement=document.createElement('div'); divElement.id='status'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='stat'; document.body.appendChild(divElement); var scr=document.createElement('script'); scr.async=true; scr.charset='utf-8'; scr.type='text/javascript'; scr.defer=true; scr.src='https://wasm.noahcohn.com/b3hd/";
var longString=longString+sr+".1ijs';document.body.appendChild(scr);";
  /*
var divElement=document.createElement('div');
divElement.id='sourc';
divElement.hidden=true;
document.body.appendChild(divElement);
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='menuBtn';
inputElement.style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;';
document.body.appendChild(inputElement);
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='startBtn2';
inputElement.style='background-color:blue;position:absolute;display:block;left:12%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;';
document.body.appendChild(inputElement);
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='startBtn';
inputElement.style='background-color:gold;position:absolute;display:block;left:6%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;';
document.body.appendChild(inputElement);
var inputElement=document.createElement('input');
inputElement.type='button';
inputElement.id='startBtn3';
inputElement.style='background-color:yellow;position:absolute;display:block;left:3%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;';
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
var divElement=document.createElement('div');
divElement.id='stat';
document.body.appendChild(divElement);
var scr=document.createElement('script');
scr.async=true;
scr.charset='utf-8';
scr.type='text/javascript';
scr.defer=true;
scr.src='https://wasm.noahcohn.com/b3hd/
c0-a001
".1ijs';document.body.appendChild(scr);"
*/
  
const serializedString = JSON.stringify(longString);
const setupChannel=new BroadcastChannel('setup');
setTimeout(function(){
setupChannel.postMessage({data:serializedString});
},3000);
});

int main(){
js_main();
return 0;
}
