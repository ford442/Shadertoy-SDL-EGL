function opn(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById("circle").width=window.innerWidth;
document.getElementById("circle").height=window.innerHeight;
let $hg=window.innerHeight+"px";
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("di").click();
},500);
setTimeout(function(){
document.getElementById("btn2").click();
},500);
};
let Frme;
function b3Play(){
const S=document.getElementById('pmhig').innerHTML;
let o=[S,S];
const bcanvas=document.getElementById("bcanvas");
const contx=bcanvas.getContext('webgl2',{
alpha:true,stencil:false,depth:false,preserveDrawingBuffer:false,premultipliedAlpha:false,lowLatency:true,powerPreference:'high-performance',majorVersion:2,minorVersion:0,desynchronized:false});
const v=document.getElementById("mv");
const g=new GPU({canvas:bcanvas,webGl:contx});
var t=g.createKernel(function(v){const P=v[this.thread.y][this.thread.x];const aveg=1.0-((((P[0]+P[1]+P[2])/3)-0.75)*4.0);return[P[0],P[1],P[2],(aveg)];}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput(o);
var r=g.createKernel(function(f){const p=f[this.thread.y][this.thread.x];this.color(p[0],p[1],p[2],p[3]);}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setOutput(o);
let l=(S*S*4);let m=Math.floor((l/65536)+1);
const W1=new WebAssembly.Memory({initial:m});
const W2=new WebAssembly.Memory({initial:m});
const W3=new WebAssembly.Memory({initial:m});
const W4=new WebAssembly.Memory({initial:m});
const W5=new WebAssembly.Memory({initial:m});
const W6=new WebAssembly.Memory({initial:m});
const W7=new WebAssembly.Memory({initial:m});
const W8=new WebAssembly.Memory({initial:m});
const $1=new Uint8ClampedArray(W1.buffer,0,l);
const $2=new Uint8ClampedArray(W2.buffer,0,l);
const $3=new Uint8ClampedArray(W3.buffer,0,l);
const $4=new Uint8ClampedArray(W4.buffer,0,l);
const $5=new Uint8ClampedArray(W5.buffer,0,l);
const $6=new Uint8ClampedArray(W6.buffer,0,l);
const $7=new Uint8ClampedArray(W7.buffer,0,l);
const $8=new Uint8ClampedArray(W8.buffer,0,l);
Frme=1;
};

function b3Frame(){
if(Frme==1){
r(t($1));
$5.set(t(v),0);
Frme=2;
}
if(Frm==2){
r(t($2));
$6.set(t(v),0);
Frme=3;
}
if(Frm==3){
r(t($3));
$7.set(t(v),0);
Frme=4;
}
if(Frm==4){
r(t($4));
$8.set(t(v),0);
Frme=5;
}
if(Frm==5){
r(t($5));
$1.set(t(v),0);
}
if(Frm==6){
r(t($6));
$2.set(t(v),0);
}
if(Frm==7){
r(t($7));
$3.set(t(v),0);
}
if(Frm==8){
r(t($8));
$4.set(t(v),0);
}};
