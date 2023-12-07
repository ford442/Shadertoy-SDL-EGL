#include "../../include/shader/loader.hpp"

EM_JS(void,js_main,(),{


var longString="var mnu=document.getElementsByTagName('nav'); var unem=mnu[0]; var selectElement=document.createElement('select'); selectElement.id='sh1'; unem.appendChild(selectElement); var optionElement=document.createElement('option'); optionElement.text='Default'; optionElement.value='Default'; selectElement.appendChild(optionElement); var optionElement=document.createElement('option'); optionElement.text='Random'; optionElement.value='Random'; selectElement.appendChild(optionElement); var selectElement=document.createElement('select'); selectElement.id='resMode'; unem.appendChild(selectElement); var optionElement=document.createElement('option'); optionElement.text='True'; optionElement.value='true'; selectElement.appendChild(optionElement); var optionElement=document.createElement('option'); optionElement.text='False'; optionElement.value='false'; selectElement.appendChild(optionElement); var divElement=document.createElement('div'); divElement.id='shut'; divElement.innerHTML='1'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='sourc'; divElement.hidden=true; document.body.appendChild(divElement); var inputElement=document.createElement('input'); inputElement.type='checkbox'; inputElement.hidden=true; inputElement.id='di'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='uniDown'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='viewDown'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='uniUp'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='viewUp'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='moveUp'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='moveDown'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='moveLeft'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='moveRight'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='sizeUp'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='sizeDown'; inputElement.hidden=true; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='menuBtn'; inputElement.style='background-color:black;position:absolute;display:block;left:3%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='startBtn2'; inputElement.style='background-color:blue;position:absolute;display:block;left:12%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='startBtn'; inputElement.style='background-color:gold;position:absolute;display:block;left:6%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='startBtn3'; inputElement.style='background-color:yellow;position:absolute;display:block;left:3%;top:9%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;'; document.body.appendChild(inputElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='reloadBtn'; inputElement.style='background-color:cyan;position:absolute;display:block;left:3%;top:12%;z-index:3200;border:4px solid #e7e7e7;border-radius:17%;'; document.body.appendChild(inputElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:5%;top:9%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='LOAD'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:5%;top:12%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='HARD RELOAD'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:8%;top:9%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='START'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:5%;top:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='MENU'; document.body.appendChild(divElement); var inputElement=document.createElement('input'); inputElement.type='button'; inputElement.id='musicBtn'; inputElement.style='background-color:cyan;position:absolute;display:block;left:3%;bottom:5%;z-index:3200;border:6px solid green;border-radius:20%;'; document.body.appendChild(inputElement); var divElement=document.createElement('div'); divElement.style='background-color:white;position:absolute;display:block;left:5%;bottom:5%;z-index:3200;border:6px solid #e7e7e7;border-radius:20%;'; divElement.innerHTML='CHANGE SONG'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='pmhig'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='path'; divElement.innerHTML='https://glsl.1ink.us/shaders/truchettubes'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='ihig'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='tim'; divElement.hidden=true; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='slideframe'; document.querySelector('#menu').appendChild(divElement); var canvasElement=document.createElement('canvas'); canvasElement.id='canvas'; document.querySelector('#contain1').appendChild(canvasElement); var divElement=document.createElement('div'); divElement.id='status'; document.body.appendChild(divElement); var divElement=document.createElement('div'); divElement.id='stat'; document.body.appendChild(divElement); var audioElement=document.createElement('audio'); audioElement.id='track'; audioElement.preload='none'; audioElement.hidden=true; audioElement.crossorigin=true; audioElement.style='pointer-events:none;'; document.body.appendChild(audioElement); document.querySelector('#startBtn3').addEventListener('click',function(){ let scr=document.createElement('script'); scr.async=true; scr.charset='utf-8'; scr.type='text/javascript'; scr.defer=true;";
  
//  === end long string ===  //
  
const setupChannel=new BroadcastChannel('setup');
const setupChannelA=new BroadcastChannel('setupA');
const setupChannelB=new BroadcastChannel('setupB');
const setupChannelC=new BroadcastChannel('setupC');
var srcA=document.querySelector('#sourc').innerHTML;
let Rlod=false;
let testNum=0;
var msgA="const setupChannelA=new BroadcastChannel('setupA');setupChannelA.addEventListener('message',ea=>{const deserializedString=JSON.parse(ea.data.data);eval(deserializedString);});document.querySelector('#reloadBtn').addEventListener('click',function(){window.location.reload(true);});";
var msgB="const setupChannelB=new BroadcastChannel('setupB');setupChannelB.addEventListener('message',ea=>{const deserializedString=JSON.parse(ea.data.data);eval(deserializedString);});document.querySelector('#reloadBtn').addEventListener('click',function(){window.location.reload(true);});";
var msgC="const setupChannelC=new BroadcastChannel('setupC');setupChannelC.addEventListener('message',ea=>{const deserializedString=JSON.parse(ea.data.data);eval(deserializedString);});document.querySelector('#reloadBtn').addEventListener('click',function(){window.location.reload(true);});";
var msgPart="document.querySelector('#setup').remove();";
var longStringA=longString+"scr.src='https://wasm.noahcohn.com/b3hd/"+srcA+"a.1ijs';document.body.appendChild(src);});"+msgA+msgPart;
var longStringB=longString+"scr.src='https://wasm.noahcohn.com/b3hd/"+srcA+"b.1ijs';document.body.appendChild(src);});"+msgB+msgPart;
var longStringC=longString+"scr.src='https://wasm.noahcohn.com/b3hd/"+srcA+"c.1ijs';document.body.appendChild(src);});"+msgC+msgPart;
const serializedStringA=JSON.stringify(longStringA);
const serializedStringB=JSON.stringify(longStringB);
const serializedStringC=JSON.stringify(longStringC);

document.querySelector('#startBtn').addEventListener('click',function(){
testNum++;
if(testNum==1){
window.open('https://test.1ink.us/r3b1/');
document.querySelector('#shut').innerHTML='2';
document.querySelector('#di').click();
setupChannel.onmessage=function(event){
setupChannel.postMessage({data:serializedStringA});
document.querySelector('#startBtn').click();
};
}else if(testNum==2){
window.open('https://test.1ink.us/r3b1/');
setupChannel.onmessage=function(event){
setupChannel.postMessage({data:serializedStringB});
document.querySelector('#startBtn').click();
};
}else if(testNum==3){
window.open('https://test.1ink.us/r3b1/');
setupChannel.onmessage=function(event){
setupChannel.postMessage({data:serializedStringC});
};
}else if(testNum==4){
setupChannel.onmessage=function(event){
setupChannel.postMessage({data:serializedStringD});
};
}
document.querySelector('#startBtn').click();
});
});

int main(){
js_main();
return 0;
}
