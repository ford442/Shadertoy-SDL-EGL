#include "../../include/combine/video.hpp"

Video video;

extern "C" {

void clr(GLclampf cllr,GLclampf alp,GLclampf avr){
video.avgr.clrclr(cllr,alp,avr);
return;
}

void nano(short int Fnum,int leng,float *ptr,float *aptr){
video.avgr.avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,vid,(),{

    "use strict";

    var vv=document.getElementById('mv');
    var sh4d=false;
    var stp,Lstp;
    var stpInc=0.016;
    var setTim;
    var timFrm=16.66;
    var lockVid;
    var loopLoop;
    var mmvv;
    let revv;
    var $bb;

    function reverseLoopB(){
    if(setTim>Lstp){
        setTim-=stpInc;
        mmvv.currentTime=setTim;
    }else{
        revv=false;
        forwardLoop();
    }
}

function forwardLoop(){
    if(setTim<=stp){
        setTim+=stpInc;
        mmvv.currentTime=setTim;
    }else{
        revv=true;
        reverseLoopB();
    }
}

function reverseLoop(){
    if(setTim>Lstp){
        setTim-=stpInc;
        mmvv.currentTime=setTim;
    }else{
        revv=false;
        forwardLoop();
    }
}

function doKey(e){
    if(e.code=='Space'){
        e.preventDefault();
    }
    if (e.code=='KeyZ'){
        mmvv=document.getElementById('mv');
        mmvv.pause();
        stp=document.getElementById('mv').currentTime;
        stp=Math.ceil(stp);
        setTim=stp;
        Lstp=stp-2.0;
        loopLoop=true;
        revv=true;
    }
    if(e.code=='KeyX'){
        loopLoop=false;
        vv.play();
    }
    if(e.code=='KeyA'){
        sh4d=true;
    }
    if(e.code=='KeyS'){
        sh4d=false;
    }
}

const pnnl=document.body;
pnnl.addEventListener('keydown',doKey);
let $H64=Module.HEAPF64.buffer;
var inh=parseInt(window.innerHeight,10);
var s$=parseInt(inh,10);
var w$=parseInt(inh,10);
var h$=parseInt(inh,10);
// w$=parseInt(document.getElementById("wid").innerHTML,10);
// h$=parseInt(document.getElementById("hig").innerHTML,10);
var la=Math.ceil(h$*w$*8);
var pointa=Math.ceil(77*la);
var agav=new Float64Array($H64,pointa,304);
var sz=Math.ceil((h$*w$)/8);
var avag=0.750;
var min=1.000;
var max=0.000;
agav.fill(avag,0,33);
agav.fill(min,100,33);
agav.fill(max,200,33);
var blank$=Math.max((((w$-h$)*1.0)/8.0),0.0);
var nblank$=Math.max((((h$-w$)*1.0)/8.0),0.0);
let bCan=document.getElementById("bcanvas");
let gljs=bCan.getContext("webgl2",{
    colorType:'float64',
    precision:'highp',
    preferLowPowerToHighPerformance:false,
    logarithmicDepthBuffer:true,
    colorSpace:'display-p3',
    alpha:true,
    depth:true,
    stencil:true,
    imageSmoothingEnabled:true,
    preserveDrawingBuffer:false,
    premultipliedAlpha:false,
    desynchronized:false,
    lowLatency:false,
    powerPreference:'high-performance',
    antialias:false,
    willReadFrequently:false,
    xrCompatible:false,
    majorVersion:2,
    minorVersion:0
});

gljs.getExtension('OES_texture_float_linear');
gljs.getExtension('OES_texture_half_float_linear');
gljs.getExtension('EGL_EXT_pixel_format_float');  //  required for float/alpha   -- WEBGL2 --
gljs.getExtension('EXT_color_buffer_float');  //  required for float/alpha   -- WEBGL2 --
gljs.getExtension('EXT_color_buffer_half_float');
gljs.getExtension("EXT_float_blend");
gljs.getExtension("EXT_blend_minmax");
// gljs.getExtension('EGL_HI_colorformats');
// gljs.getExtension('EGL_EXT_gl_colorspace_display_p3');
/*
gljs.getExtension("WEBGL_color_buffer_float");
gljs.getExtension("OES_texture_float_linear");
gljs.getExtension("OES_single_precision");
gl.getExtension("WEBGL_color_buffer_half_float");
gl.getExtension("OES_texture_half_float_linear");
gl.getExtension("EXT_sRGB");
gl.getExtension("OES_fbo_render_mipmap");
gl.getExtension("WEBGL_blend_equation_advanced_coherent");
gl.getExtension("EXT_framebuffer_sRGB");
gl.getExtension("OES_depth32");
gl.getExtension("OES_fixed_point");
gl.getExtension("OES_shader_multisample_interpolation");
gl.getExtension("WEBGL_webcodecs_video_frame");
gl.getExtension("GL_NV_memory_attachment");
gl.getExtension("NV_depth_nonlinear");
gl.getExtension("EXT_gl_colorspace_display_p3");
// gl.getExtension('EGL_KHR_gl_colorspace');
// gl.getExtension('EGL_EXT_gl_colorspace_scrgb_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_display_p3_linear');
// gl.getExtension('EGL_EXT_gl_colorspace_bt2020_linear');
*/
gljs.getExtension("ARB_multisample");
gljs.getExtension('EXT_texture_filter_anisotropic');
gljs.getExtension('ARB_blend_func_extended');
// gljs.getExtension('EXT_framebuffer_sRGB');
gljs.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT,gl.NICEST);
gljs.hint(gl.GENERATE_MIPMAP_HINT,gl.NICEST);
// gl.enable(gl.BLEND);  //  webgl2 messed up effect
// gljs.enable(gl.FRAMEBUFFER_SRGB_EXT); 
// gljs.disable(gl.DITHER);
gljs.drawingBufferColorMetadata={mode:'extended'};
// gljs.renderbufferStorage(gl.RENDERBUFFER,gl.RGBAF64,bCan.height,bCan.height);
// gljs.blendColor(1.0,1.0,1.0,1.0);
// gljs.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.MAX);
gljs.blendEquationSeparate(gl.FUNC_ADD,gl.MAX);
// gljs.blendEquationSeparate(gl.FUNC_SUBTRACT,gl.FUNC_ADD);
// gljs.blendEquation(gl.MAX);
// gljs.blendFunc(gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
gljs.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
// gljs.blendFuncSeparate(gl.DST_COLOR,gl.SRC_COLOR,gl.ONE,gl.ONE_MINUS_SRC_ALPHA);
// gl.enable(gl.SAMPLE_ALPHA_TO_COVERAGE);  // <- crazy effect!
// gl.unpackColorSpace='display-p3';  // very slow
gljs.drawingBufferColorSpace='display-p3';
let g=new GPU({mode:"gpu",canvas:bcanvas,webGl:gljs});
let g2=new GPU({mode:"gpu"});
const glslSilver=`float Silver(float a){return((a+0.75+0.75+((a+0.75)/2.0))/4.0);}`;
const glslGoldR=`float GoldR(float a){return((a+0.831+0.831+0.831+((a+0.831)/2.0))/5.0);}`;
const glslGoldG=`float GoldG(float a){return((a+0.686+0.686+0.686+((a+0.686)/2.0))/5.0);}`;
const glslGoldB=`float GoldB(float a){return((a+0.215+0.215+0.215+((a+0.215)/2.0))/5.0);}`;
const glslRoseR=`float RoseR(float a){return((a+0.86+0.86+0.86+((a+0.86)/2.0))/5.0);}`;
const glslRoseG=`float RoseG(float a){return((a+0.13+0.13+0.13+((a+0.13)/2.0))/5.0);}`;
const glslRoseB=`float RoseB(float a){return((a+0.86+0.86+0.86+((a+0.86)/2.0))/5.0);}`;
const glslGreenR=`float GreenR(float a){return((a+0.11+0.11+0.11+((a+0.11)/2.0))/5.0);}`;
const glslGreenG=`float GreenG(float a){return((a+0.73+0.73+0.73+((a+0.73)/2.0))/5.0);}`;
const glslGreenB=`float GreenB(float a){return((a+0.14+0.14+0.14+((a+0.14)/2.0))/5.0);}`;
let glslAve="float Ave(float a,float b,float c){return(a+b+c)/3.0;}";
// const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float f,float g) {return (1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25)));}`;
let glslAveg="float Aveg(float a,float b){return(1.0-(((a)-(b))*((a)*(1.0/(1.0-b)))));}";
// const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*(f-g))))))+0.777777)/4.0);}`;
const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(c)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*(f-g))))))+(a+0.75))/5.0);}`;
// // let glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return ((1.4+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/5.0);}`;
// let glslAlphe="float Alphe(float a,float b,float c,float d,float e,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))+((f-g)*((1.0-g)*(f-g)))-((g-f)*((g)*(g-f))))))+0.777777)/4.0);}";
g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g.addNativeFunction('GreenR',glslGreenR,{returnType:'Number'});
g.addNativeFunction('GreenG',glslGreenG,{returnType:'Number'});
g.addNativeFunction('GreenB',glslGreenB,{returnType:'Number'});
g.addNativeFunction('RoseR',glslRoseR,{returnType:'Number'});
g.addNativeFunction('RoseG',glslRoseG,{returnType:'Number'});
g.addNativeFunction('RoseB',glslRoseB,{returnType:'Number'});
g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
const R=g2.createKernel(function(tv){
    var Pa=tv[this.thread.y][this.thread.x*4];
    return Ave(Pa[0],Pa[1],Pa[2]);
}).setTactic("speed").setPrecision('single').setOptimizeFloatMemory(true).setDynamicOutput(true).setOutput([sz]);
const t=g.createKernel(function(v){
    var P=v[this.thread.y][this.thread.x+this.constants.blnk-this.constants.nblnk];
    var av$=Ave(0.8*P[0],P[1],1.2*P[2]);
// var minuss=(av$-0.5)*(av$/(av$-0.5));
// av$=av$+(minuss*(av$*0.033));
    return[0.8*P[0],P[1],1.2*P[2],av$];
}).setTactic("precision").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setPipeline(true).setOutput([s$,s$]);
//     }).setConstants({nblnk:nblank$,blnk:blank$}).setTactic("precision").setPipeline(true).setDynamicOutput(true).setOutput([s$,s$]);
const r=g.createKernel(function(f){
    var p=f[this.thread.y][this.thread.x];
    var $fmax=this.constants.fmax;
    var $fmin=this.constants.fmin;
    var $amax=this.constants.amax;
    var $amin=this.constants.amin;
    var $favg=this.constants.favg;
    var $aavg=this.constants.aavg;

    var alph=Alphe($fmax,$amin,$fmax,$amin,$aavg,$aavg,p[3]);
    var Min=(4.0*(($amax-($aavg-$amin))/2.0));
    var ouT=Math.max(Min,alph);
    var aveg=Aveg(p[3],ouT);
    /*
  //  // 
  var rr;
  var gg;
  var bb;
  var der=p[0];
  var neerg=p[1];
  var eulb=p[2];
  // if(der>0.333){
   rr=GreenR(der);
  // }else{
  // rr=RoseR(der);
  // }
  // if(neerg>0.4){
  gg=GreenG(neerg);
  // }else{
  // gg=RoseG(neerg);
  // }
  // if(eulb>0.5){
  bb=GreenB(eulb);
  // }else{
  // bb=RoseB(eulb);
  // }//   
   */
// this.color(GreenR(p[0]),GreenG(p[1]),GreenB(p[2]),aveg);
// this.color(rr,gg,bb,aveg);
// 
//   var silvrr=Ave(p[0],p[1],p[2]);
// this.color(silvrr,silvrr,p[2],aveg);
    this.color(p[0],p[1],p[2],aveg);
}).setTactic("precision").setDynamicOutput(true).setGraphical(true).setOutput([h$,w$]);
// }).setConstants({nblnk:nblank$,blnk:blank$,amin:agav[100],amax:agav[200],aavg:agav[0]}).setTactic("precision").setGraphical(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([s$,s$]);
w$=parseInt(document.getElementById("wid").innerHTML,10);
h$=parseInt(document.getElementById("hig").innerHTML,10);
var inh=parseInt(window.innerHeight,10);
var s$=parseInt(inh,10);
vv=document.getElementById("mv");
blank$=Math.max((((w$-s$)*1.0)/8.0),0.0);
nblank$=Math.max((((s$-w$)*1.0)/8.0),0.0);
la=Math.ceil(h$*w$*8);
pointa=Math.ceil(77*la);
agav=new Float64Array($H64,pointa,304);
R.setOutput([sz]);
for(i=0;i<65;i++){
    var j=i+1;
    eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H64,point"+j+",la);");
};
var pointb=Math.ceil(66*la);
var $B=new Float64Array($H64,pointb,sz);
var $F=1;
var $Bu=33;
r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
t.setConstants({nblnk:nblank$,blnk:blank$});
for(var i=0;i<65;i++){
    var j=i+1;
    eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H64,point"+j+",la);var $$1=t(vv);$"+j+".set($$1);");
// eval("var point"+j+"="+i+"*la;var $"+j+"=new Float64Array($H64,point"+j+",la);var $$1=0.0;$"+j+".fill($$1);");
};
var d=S();if(d){d()};d=S();function S(){
    vv=document.getElementById("mv");
    w$=parseInt(document.getElementById("wid").innerHTML,10);
    h$=parseInt(document.getElementById("hig").innerHTML,10);
    var inh=parseInt(window.innerHeight,10);
    var s$=parseInt(inh,10);
    blank$=Math.max((((w$-s$)*1.0)/8.0),0.0);
    nblank$=Math.max((((s$-w$)*1.0)/8.0),0.0);
    s$=parseInt(window.innerHeight,10);
    la=Math.ceil(h$*w$*8);
    pointa=Math.ceil(77*la);
    var agav=new Float64Array($H64,pointa,304);  // has to var?
    R.setOutput([sz]);
    for(var i=0;i<65;i++){
        j=i+1;
        eval("point"+j+"="+i+"*la;$"+j+"=new Float64Array($H64,point"+j+",la);");
    };
    pointb=Math.ceil(66*la);
    var $B=new Float64Array($H64,pointb,sz);  // has to var?
    r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
    t.setConstants({nblnk:nblank$,blnk:blank$});
    var T=false;
    function M(){
        t.setConstants({nblnk:nblank$,blnk:blank$});
        r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
        if(T){
            return;
        }
        for(var i=64;i>0;i--){
            var loca=$F+1;
            if(loca>64){loca=1;}
            var locb=$Bu+1;
            if(locb>64){locb=1;}
            if($F==i){
                eval("$r"+i+"=t($"+i+");r($r"+i+");$$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+",0,la);$F="+loca+";$Bu="+locb+";");
            }};
        $bb=R(vv);
        $B.set($bb,0,sz);
        pointb=Math.ceil(66*la);  // has to revar?
        Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
        if(sh4d==1){
            Module.ccall("clr",null,["Number","Number","Number"],[agav[200],agav[100],agav[0]]);
            Module.ccall("frm",null,[],[]);
        }
        setTimeout(function(){
            M();
            if(loopLoop==true){
                timFrm=8.33;
                if(revv==true){
                    reverseLoop();
                }else{
                    timFrm=16.66;
                    forwardLoop();
                }
            }
        },timFrm)}
    M();
    document.getElementById("di").onclick=function(){
        T=true;
        S();
    };
    return()=>{
        T=true;
    };
}

});

void(*B3)(){&vid};

extern "C" {

void b3_egl(){
Video::egl();
return;
}

void b3(){
video.avgr.resetAvg();
B3();
return;
}

}
