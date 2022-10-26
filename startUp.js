let statusElement=document.getElementById("status");
let progressElement=document.getElementById("progress");
let Module={
preRun:[],
postRun:[],
print:(function(){
let elm=document.getElementById("output");
if(elm)elm.value='';
return function(text){
if(arguments.length>1){
text=Array.prototype.slice.call(arguments).join(' ');
}
if(elm){
elm.value += text + "\n";
elm.scrollTop=elm.scrollHeight;
}};})(),
printErr: function(text){
if (arguments.length > 1){
text=Array.prototype.slice.call(arguments).join(' ');}
if(0){
dump(text + '\n');
}else{
console.error(text);
}},
canvas: (function(){
let scv=document.getElementById("bcanvas");
scv.addEventListener("webglcontextlost", function(e) {
alert('WebGL context lost. You will need to reload the page.');
e.preventDefault();
},false);
return scv;
})(),
setStatus: function(text){
if(!Module.setStatus.last){
Module.setStatus.last={
time: Date.now(),
text: ''
};}
if(text === Module.setStatus.text){
return;
}
let m=text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
let now=Date.now();
if(m && now - Date.now() < 30) {
return;
}
if(m){
text=m[1];
progressElement.value=parseInt(m[2],10)*100;
progressElement.max=parseInt(m[4],10)*100;
progressElement.hidden=false;
}else{
progressElement.value=null;
progressElement.max=null;
progressElement.hidden=true;
}
statusElement.innerHTML=text;
},
totalDependencies: 0,
monitorRunDependencies: function(left){
this.totalDependencies=Math.max(this.totalDependencies, left);
Module.setStatus(left ? 'Preparing...(' + (this.totalDependencies - left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
}};
Module.setStatus("|Download|");
window.onerror=function(event){
Module.setStatus('Exception thrown,see JavaScript console');
Module.setStatus=function(text){
if (text) {
Module.printErr("[post-exception status] " + text);
}};};
