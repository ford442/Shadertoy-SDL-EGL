#include "../../include/video/video.hpp"

void avgFrm(int Fnum,int leng,float *ptr,float *aptr){
float max=0.0;
float min=1.0;
float sum=0.0;
float avgSum=0.0;
float minSum=0.0;
float maxSum=0.0;
for(int i=0;i<leng;i++){
sum+=ptr[i];
if(max<ptr[i]){max=ptr[i];
}
if(min>ptr[i]&&ptr[i]>0){min=ptr[i];
}
}
sum=sum/leng;
aptr[Fnum]=sum;
aptr[Fnum+100]=min;
aptr[Fnum+200]=max;
for(int i=33;i<65;i++){
avgSum+=aptr[i];
}
aptr[0]=avgSum/32;
for(int i=33;i<65;i++){
minSum+=aptr[i+100];
}
aptr[100]=minSum/32;
for(int i=33;i<65;i++){
maxSum+=aptr[i+200];
}
aptr[200]=maxSum/32;
return;
}

extern "C" {

void nano(int Fnum,int leng,float *ptr,float *aptr){
avgFrm(Fnum,leng,ptr,aptr);
return;
}

}

EM_JS(void,ma,(),{

   // "use strict";
    const pnnl=document.body;
    var vv=document.getElementById("mv");
    var intervalLoop=null;
    var f;
    var a;
    var b;
    var loopLoop;

    function backForth(stp){
    loopLoop=true;
    f=true;
    a=stp;
    b=stp+1.2;
};

function stpBackForth(){clearInterval(intervalLoop);loopLoop=false;};

function doKey(e) {
    if (e.code == 'Space') {
        e.preventDefault();
    }
    if (e.code == 'KeyZ') {
        vv = document.getElementById("mv");
        vv.pause();
        var stp = vv.currentTime;
        backForth(stp);
    }
    if (e.code == 'KeyX') {
        vv = document.getElementById("mv");
        stpBackForth();
        vv.play();
    }
}
    pnnl.addEventListener('keydown',doKey);

    var w$=parseInt(document.getElementById("wid").innerHTML,10);
    var h$=parseInt(document.getElementById("hig").innerHTML,10);
    const $H=Module.HEAPF32.buffer;
    var la=h$*h$*4;
    var pointa=77*la;
    var agav=new Float32Array($H,pointa,300);
    var sz=(h$*h$)/8;
    var avag=0.750;
    var min=1.000;
    var max=0.000;
    agav.fill(avag,0,33);
    agav.fill(min,100,33);
    agav.fill(max,200,33);
    const bcanvas=document.getElementById("bcanvas");
    const gl=bcanvas.getContext("webgl2",{colorType:'float32',preferLowPowerToHighPerformance:false,precision:'highp',logarithmicDepthBuffer:true,colorSpace:'display-p3',alpha:true,depth:false,stencil:true,imageSmoothingEnabled:true,preserveDrawingBuffer:true,premultipliedAlpha:false,desynchronized:false,lowLatency:true,powerPreference:'high-performance',antialias:true,willReadFrequently:true,majorVersion:2,minorVersion:0});
    const g=new GPU({canvas:bcanvas,webGl:gl});
    const g2=new GPU();
    const glslAve=`float Ave(float a,float b,float c){return(a+b+c)/3.0;}`;
/// const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((0.7+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-e)*((1.0-g)*0.1))))))/4.0);}`;
// const glslAlphe=`float Alphe(float a,float b,float c,float d,float e,float f,float g){return((g+(3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/4.0);}`;
    const glslAlphe=`float Alphe(float a,float b,float f,float g){return(((3.0*((1.0-b)-(((((1.0-f)-(a)+b)*1.5)/2.0)+((f-0.5)*((1.0-f)*0.25))-((0.5-f)*(f*0.25))-((g-f)*((1.0-g)*0.1))))))/3.0);}`;
    const glslAveg=`float Aveg(float a,float b){return(0.999-(((a)-(b))*((a)*(0.999/(0.999-b)))));}`;
    g.addNativeFunction('Ave',glslAve,{returnType:'Number'});
    g.addNativeFunction('Alphe',glslAlphe,{returnType:'Number'});
    g.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
    g2.addNativeFunction('Aveg',glslAveg,{returnType:'Number'});
    g2.addNativeFunction('Ave',glslAve,{returnType:'Number'});
    const R=g2.createKernel(function(tv){
        const Pa=tv[this.thread.y][this.thread.x*4];
        return Ave(Pa[0],Pa[1],Pa[2]);
    }).setTactic("speed").setDynamicOutput(true).setArgumentTypes(["HTMLVideo"]).setOutput([sz]);
    const t=g.createKernel(function(v){
        const P=v[this.thread.y][this.thread.x-this.constants.blnk-this.constants.nblnk];
        const av$=Ave(P[0],P[1],P[2]);
        return[P[0],P[1],P[2],av$];
// }).setTactic("precision").setPrecision('single').setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
    }).setTactic("precision").setPipeline(true).setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
// }).setTactic("precision").setPipeline(true).setPrecision('unsigned').setArgumentTypes(["HTMLVideo"]).setDynamicOutput(true).setOutput([w$,h$]);
    const r=g.createKernel(function(f){
        const p=f[this.thread.y][this.thread.x-this.constants.nblnk-this.constants.blnk];
// var $fmax=this.constants.fmax;
// var $fmin=this.constants.fmin;
        const $amax=this.constants.amax;
        const $amin=this.constants.amin;
// var $favg=this.constants.favg;
        const $aavg=this.constants.aavg;
        const alph=Alphe($amax,$amin,$aavg,p[3]);
/// var Min=(4.0*(($fmax-($aavg-$fmin))/2.0));
        const Min=(4.0*(($amax-($aavg-$amin))/2.0));
// var Min=(4.0*(($fmax-(p[3]-$amin))/2.0));
        const ouT=Math.max(Min,alph);
        const aveg=Aveg(p[3],ouT);
const rng=ouT-(ouT*0.5);
var grr=(p[0]-rng)+(p[1]-rng)+(p[2]-rng);
// var grr=(p[0]-0.55)+(p[1]-0.55)+(p[2]-0.55);
grr=Math.max((grr*4.0),0.0);
const rr=Math.min((p[0]+grr),1.0)-((p[3]*0.3)*0.14);
const gg=Math.min((p[1]+grr),1.0)-((p[3]*0.3)*0.14);
const bb=Math.min((p[2]+grr),1.0)-((p[3]*0.3)*0.14);
this.color(rr,gg,bb,aveg);
    }).setTactic("precision").setGraphical(true).setArgumentTypes(['HTMLVideo']).setDynamicOutput(true).setOutput([w$,h$]);
    gl.getExtension('WEBGL_color_buffer_float');
    gl.getExtension('WEBGL_color_buffer_half_float');
    gl.getExtension('OES_texture_float_linear');
    gl.getExtension('OES_texture_half_float_linear');
    gl.getExtension('EXT_float_blend');
    gl.getExtension('EXT_frag_depth');
    gl.getExtension('EXT_shader_texture_lod');
    gl.getExtension('EXT_sRGB');
    gl.getExtension('EXT_blend_minmax');
    gl.getExtension('ANGLE_instanced_arrays');
    gl.getExtension('EXT_disjoint_timer_query');
    gl.getExtension('EXT_clip_cull_distance');
    gl.getExtension('EXT_disjoint_timer_query_webgl2');
    gl.getExtension('KHR_parallel_shader_compile');
    gl.getExtension('OES_draw_buffers_indexed');
    gl.getExtension('OES_element_index_uint');
    gl.getExtension('OES_fbo_render_mipmap');
    gl.getExtension('OES_standard_derivatives');
    gl.getExtension('OES_vertex_array_object');
    gl.getExtension('WEBGL_blend_equation_advanced_coherent');
    gl.getExtension('WEBGL_depth_texture');
    gl.getExtension('WEBGL_draw_buffers');
    gl.getExtension('WEBGL_provoking_vertex');
    gl.getExtension('EXT_framebuffer_sRGB');
    gl.getExtension('OES_depth32');
    gl.getExtension('OES_fixed_point');
    gl.getExtension('OES_shader_multisample_interpolation');
    gl.getExtension('WEBGL_webcodecs_video_frame');
    gl.getExtension('OES_single_precision');
    gl.getExtension('GL_EXT_texture_shadow_lod');
    gl.getExtension('GL_NV_memory_attachment');
    gl.getExtension('NV_depth_nonlinear');
    gl.getExtension('EXT_gl_colorspace_display_p3');
    gl.getExtension('GL_ARB_multisample');
// gl.enable(MULTISAMPLE_ARB);
// gl.hint(gl.GENERATE_MIPMAP_HINT, gl.NICEST);
// gl.hint(gl.FRAGMENT_SHADER_DERIVATIVE_HINT_OES, gl.NICEST);
// gl.drawingBufferColorSpace='display-p3';
// gl.unpackColorSpace='display-p3';
    gl.disable(gl.DITHER);
// gl.disable(gl.CULL_FACE);
// gl.disable(gl.DEPTH_TEST);
// gl.enable(gl.BLEND);
// gl.disable(gl.STENCIL_TEST);
// gl.disable(gl.SCISSOR_TEST);
    w$=parseInt(document.getElementById("wid").innerHTML,10);
    h$=parseInt(document.getElementById("hig").innerHTML,10);
    vv=document.getElementById("mv");
    var blank$=Math.max((((w$-h$)*1)/2),0);
    var nblank$=Math.max((((h$-w$)*1)/2),0);
    var l=w$*h$*16;
    la=h$*h$*4;
    var al=w$*h$*8;
    sz=(h$*h$)/8;
    pointa=77*la;
    agav=new Float32Array($H,pointa,300);
    R.setOutput([sz]);
    for(var i=0;i<65;i++){
        var j=i+1;
        eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
    };
    var pointb=77*la;
    var $B=new Float32Array($H,pointb,sz);
    var $F=1;
    var $Bu=33;
    r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
    t.setConstants({nblnk:nblank$,blnk:blank$});
    var $$1=t(vv);
    for (i=0;i<65;i++){
        var j=i+1;
        eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);$"+j+".set($$1);");
    };
    var d=S();if(d)d();d=S();function S(){
        w$=parseInt(document.getElementById("wid").innerHTML,10);
        h$=parseInt(document.getElementById("hig").innerHTML,10);
        var blank$=Math.max((((w$-h$)*0)/2),0);
        var nblank$=Math.max((((h$-w$)*0)/2),0);
        l=w$*h$*16;
        la=h$*h$*4;
        al=w$*h$*8;
        sz=(h$*h$)/8;
        pointa=77*la;
        var agav=new Float32Array($H,pointa,300);
        R.setOutput([sz]);
        for(var i=0;i<65;i++){
            var j=i+1;
            eval("var point"+j+"="+i+"*la;var $"+j+"=new Float32Array($H,point"+j+",la);");
        };
        pointb=66*la;
        var $B=new Float32Array($H,pointb,sz);
        r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
        t.setConstants({nblnk:nblank$,blnk:blank$});
        var T=false;
        function M(){
            vv=document.getElementById("mv");
            t.setConstants({nblnk:nblank$,blnk:blank$});
            r.setConstants({nblnk:nblank$,blnk:blank$,favg:agav[$F],fmin:agav[$F+100],fmax:agav[$F+200],amin:agav[100],amax:agav[200],aavg:agav[0]});
            if(T){return;}
            for(var i=64;i>0;i--){
                var loca=$F+1;
                if(loca>64){loca=1;}
                var locb=$Bu+1;
                if(locb>64){locb=1;}
                eval("if ($F=="+i+"){var $r"+i+"=t($"+i+");r($r"+i+");}");
                eval("if ($F=="+i+"){var $$"+$Bu+"=t(vv);$"+$Bu+".set($$"+$Bu+");$F="+loca+";$Bu="+locb+";}");
            };
            if($F%4==0){
                var $bb=R(vv);
                $B.set($bb,0,sz);
                pointb=66*la;
                Module.ccall("nano",null,["Number","Number","Number","Number"],[$F,sz,pointb,pointa]);
            };
            setTimeout(function(){
                M();

                if(loopLoop==true){
                    if(f==true){
                        if(vv.currentTime>a){
                            vv.currentTime-=0.016;
                        }else{
                            f=false;
                            if(vv.currentTime<b){
                                vv.currentTime+=0.016;
                            }else{
                                f=true;
                            }}};
                    if(f==false){
                        if(vv.currentTime<b){
                            vv.currentTime+=0.016;
                        }else{
                            f=true;
                            if(vv.currentTime>a){
                                vv.currentTime-=0.016;
                            }else{
                                f=false;
                            }}}};
            },16.66)};
        M();
        document.getElementById("di").onclick=function(){
            T=true;
            S();
        };
        return()=>{
            T=true;
        }};
});

extern "C" {

void b3(){
ma();
return;
}

}
