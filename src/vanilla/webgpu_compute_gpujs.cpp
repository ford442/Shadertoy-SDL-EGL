EM_JS(void,gpu_js,(),{

var vv=document.getElementById('mvi');
var bcanvas=document.getElementById("bcanvas");
var ctx=bcanvas.getContext('webgl2',{alpha:true});
var siz=window.innerHeight;
bcanvas.height=siz;

var g=new GPUX({mode:'gpu',canvas:bcanvas});

var r=g.createKernel(function(f){
var p=f[this.thread.y][this.thread.x+100];
this.color(p[0],p[1],p[2],p[3]);
}).setTactic("precision").setGraphical(true).setDynamicOutput(true).setOutput([siz,siz]);





});
