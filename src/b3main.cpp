#include "../include/b3main.hpp"

void egla(){ 
eglconfig_fjs=NULL;
// emscripten_get_element_css_size("canvas",&wi_fjs,&hi_fjs);
// Size_fjs=(GLsizei)hi_fjs;
emscripten_webgl_init_context_attributes(&attr_fjs);
attr_fjs.alpha=EM_TRUE;
attr_fjs.stencil=EM_TRUE;
attr_fjs.depth=EM_TRUE;
attr_fjs.antialias=EM_TRUE;
attr_fjs.premultipliedAlpha=EM_FALSE;
attr_fjs.preserveDrawingBuffer=EM_TRUE;
attr_fjs.enableExtensionsByDefault=EM_TRUE;
attr_fjs.renderViaOffscreenBackBuffer=EM_FALSE;
attr_fjs.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr_fjs.failIfMajorPerformanceCaveat=EM_FALSE;
attr_fjs.majorVersion=2;
attr_fjs.minorVersion=0;
ctx_fjs=emscripten_webgl_create_context("#acanvas",&attr_fjs);
eglBindAPI(EGL_OPENGL_API);
display_fjs=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(display_fjs,&major_fjs,&minor_fjs);
eglChooseConfig(display_fjs,attribute_list_fjs,&eglconfig_fjs,(EGLint)1,&config_size_fjs);
contextegl_fjs=eglCreateContext(display_fjs,eglconfig_fjs,EGL_NO_CONTEXT,anEglCtxAttribs2_fjs);
surface_fjs=eglCreateWindowSurface(display_fjs,eglconfig_fjs,(NativeWindowType)0,attribut_list_fjs);
eglMakeCurrent(display_fjs,surface_fjs,surface_fjs,contextegl_fjs);
emscripten_webgl_make_context_current(ctx_fjs);
glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_NICEST);
emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_color_buffer_float");
emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_color_buffer_half_float");
emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_blend_equation_advanced_coherent");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_depth_texture");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_draw_buffers");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_provoking_vertex");
// emscripten_webgl_enable_extension(ctx_fjs,"WEBGL_webcodecs_video_frame");
emscripten_webgl_enable_extension(ctx_fjs,"OES_texture_float_linear");
emscripten_webgl_enable_extension(ctx_fjs,"OES_texture_half_float_linear");
emscripten_webgl_enable_extension(ctx_fjs,"OES_element_index_uint");
emscripten_webgl_enable_extension(ctx_fjs,"OES_fbo_render_mipmap");
emscripten_webgl_enable_extension(ctx_fjs,"OES_vertex_array_object");
emscripten_webgl_enable_extension(ctx_fjs,"OES_draw_buffers_indexed");
emscripten_webgl_enable_extension(ctx_fjs,"OES_fixed_point");
emscripten_webgl_enable_extension(ctx_fjs,"OES_shader_multisample_interpolation");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_single_precision");
// emscripten_webgl_enable_extension(ctx_fjs,"OES_standard_derivatives");
emscripten_webgl_enable_extension(ctx_fjs,"OES_float_blend");
emscripten_webgl_enable_extension(ctx_fjs,"OES_frag_depth");
emscripten_webgl_enable_extension(ctx_fjs,"OES_shader_texture_lod");
emscripten_webgl_enable_extension(ctx_fjs,"OES_sRGB");
emscripten_webgl_enable_extension(ctx_fjs,"OES_depth32");
// emscripten_webgl_enable_extension(ctx_fjs,"EXT_blend_minmax");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_disjoint_timer_query");
//  emscripten_webgl_enable_extension(ctx_fjs,"EXT_clip_cull_distance");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_shading_language_420pack");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_disjoint_timer_query_webgl2");
// emscripten_webgl_enable_extension(ctx_fjs,"GL_framebuffer_sRGB");
// emscripten_webgl_enable_extension(ctx_fjs,"ANGLE_instanced_arrays");
// emscripten_webgl_enable_extension(ctx_fjs,"KHR_parallel_shader_compile");
// emscripten_webgl_enable_extension(ctx_fjs,"EXT_texture_shadow_lod");
// emscripten_webgl_enable_extension(ctx_fjs,"EGL_NV_memory_attachment");
// emscripten_webgl_enable_extension(ctx_fjs,"EGL_NV_context_priority_realtime");
// emscripten_webgl_enable_extension(ctx_fjs,"EGL_NV_depth_nonlinear");
emscripten_webgl_enable_extension(ctx_fjs,"EGL_HI_colorformats");
emscripten_webgl_enable_extension(ctx_fjs,"KHR_gl_colorspace");
// emscripten_webgl_enable_extension(ctx_fjs,"EXT_pixel_format_float");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_bt2020_pq");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_bt2020_linear");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_display_p3");
emscripten_webgl_enable_extension(ctx_fjs,"EXT_gl_colorspace_display_p3_linear");
emscripten_webgl_enable_extension(ctx_fjs,"ARB_multisample");
emscripten_webgl_enable_extension(ctx_fjs,"ARB_robustness");
emscripten_webgl_enable_extension(ctx_fjs,"ARB_robust_buffer_access_behavior");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_gl_spirv");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_spirv_extensions");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_invalidate_subdata");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_texture_storage");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES2_compatibility");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES3_compatibility");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES3_1_compatibility");
// emscripten_webgl_enable_extension(ctx_fjs,"ARB_ES3_2_compatibility");
//emscripten_webgl_enable_extension(ctx_fjs,"EXT_gpu_shader5");
 // emscripten_webgl_enable_extension(ctx_fjs,"OES_gpu_shader5");
// glViewport((GLint)0,(GLint)0,(GLsizei)Size_fjs,(GLsizei)Size_fjs);
// glScissor((GLint)0,(GLint)0,(GLsizei)Size_fjs,(GLsizei)Size_fjs);
glDisable(GL_DITHER);
glEnable(GL_SCISSOR_TEST);
// glDisable(GL_STENCIL_TEST);
// glDisable(GL_DEPTH_TEST);
return; 
}

extern "C" {

void fire_egl(){
egla();
return;
}

};

EM_JS(void,js_main,(),{

"use strict";

window.scroll(0,0);

const fll=new BroadcastChannel('file');
const shutDown=new BroadcastChannel('shutDown');

function pll(){
Module.ccall('pl');
}

fll.addEventListener('message',ea=>{
const fill=new Uint8Array(ea.data.data);
FS.writeFile('/snd/sample.wav',fill);
setTimeout(function(){
pll();
},1500);
setTimeout(function(){
shutDown.postMessage({data:222});
},2000);
});

var vide=document.querySelectorAll('video');
var mV=document.getElementById('mv');
var loadV=document.getElementById('ldv');
let $tim=document.getElementById('tim');
let $itim=document.getElementById('itim');
let $high=document.getElementById('canvasSize');
let winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
document.getElementById('circle').height=winSize;
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('di').click();
var lockVid=0;

function spKey(e){
if(e.code=='Space'){
e.preventDefault();
if(lockVid==0){lockVid=1;};
if(lockVid==1){lockVid=0;};
};
if(e.code=='KeyZ'){lockVid=1;};
if(e.code=='KeyX'){lockVid=0;};
}

const pnnl=document.body;
pnnl.addEventListener('keydown',spKey);

var $sngs=[];
var $vids=[];
var $shds=[];

function sngs(xml){
const nparser=new DOMParser();
const htmlDocs=nparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocs.getElementsByTagName('pre')[0].getElementsByTagName('a');
$sngs[0]=preList.length;
for(var i=1;i<preList.length;i++){
var stxxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
stxxt=stxxt.replace(Self,"");
$sngs[i]=Self+'songs/'+stxxt;
};
}

function scanSongs(){
const nxhttp=new XMLHttpRequest();
nxhttp.withCredentials=false;
nxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
sngs(this);
};};
nxhttp.open('GET','songs/',true);
nxhttp.send();
}

function snd(){
const randSong=Math.floor(($sngs[0]-5)*Math.random());
const songSrc=$sngs[randSong+5];
document.getElementById('track').src=songSrc;
const sng=new BroadcastChannel('sng');
sng.postMessage({data:songSrc});
}

document.getElementById('musicBtn').addEventListener('click',function(){
window.open('./flac');
setTimeout(function(){
snd();
},550);
});

function vids(xml){
const vparser=new DOMParser();
const htmlDocv=vparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDocv.getElementsByTagName('pre')[0].getElementsByTagName('a');
$vids[0]=preList.length;
for(var i=1;i<preList.length;i++){
var vtxxt=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
vtxxt=vtxxt.replace(Self,"");
const vidMenu1=document.getElementById('vi1').value;
var ar1=vidMenu1+'video/'+vtxxt;
var ar2=Self+'video/'+vtxxt;
if(vidMenu1!='Default'){
$vids[i]=ar1;
}else{
$vids[i]=ar2;
};
};
}

function scanVideos(){
const fxhttp=new XMLHttpRequest();
fxhttp.withCredentials=false;
fxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
vids(this);
};};
const vidMenu1=document.getElementById('vi1').value;
if(vidMenu1!='Default'){
var looc=vidMenu1+'video/';
}else{
var looc='video/';
};
fxhttp.open('GET',looc,true);
fxhttp.send();
}

function shds(xml){
const sparser=new DOMParser();
const htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
const preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxts=txxts.replace(Self,"");
$shds[i+1]='https://glsl.1ink.us/shaders/'+txxts;
};
var randShade=Math.random();
randShade=Math.floor($shds[0]*randShade)+5;
const shdMenu=document.getElementById('sh1');
if(shdMenu.value!='Default'){
if(shdMenu.value=='Random'){
document.getElementById('path').innerHTML=$shds[randShade];
}else{
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+shdMenu.value;
};
}else{
var fle=document.getElementById('path').innerHTML;
document.getElementById('path').innerHTML='https://glsl.1ink.us/shaders/'+fle;
};
var pth=document.getElementById('path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
ff.onload=function(oEvent){
const sarrayBuffer=ff.response;
if(sarrayBuffer){
const sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader1.toy',sfil);
setTimeout(function(){
   normalResStart();
},450);
};};
ff.send(null);
}

function scanShaders(){
const dxhttp=new XMLHttpRequest();
dxhttp.withCredentials=false;
dxhttp.onreadystatechange=function(){
if(this.readyState==4&&this.status==200){
shds(this);
};};
dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
dxhttp.send();
}

/*
function highResStart(){
document.getElementById('scanvas').height=window.innerHeight*2;
document.getElementById('scanvas').width=window.innerHeight*2;
document.getElementById('scanvas').style.height=(window.innerHeight*2)+'px';
document.getElementById('scanvas').style.width=(window.innerHeight*2)+'px';
$high.innerHTML=window.innerHeight*2;
setTimeout(function(){
Module.ccall('b3_egl');
},450);
setTimeout(function(){
Module.ccall('b3');
},550);
setTimeout(function(){
document.getElementById('scanvas').height=window.innerHeight;
document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').style.height=window.innerHeight+'px';
document.getElementById('scanvas').style.width=window.innerHeight+'px';
$high.innerHTML=window.innerHeight;
},750);
setTimeout(function(){
Module.ccall('str');
},850);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
// const bz=new BroadcastChannel('bez');
// bz.postMessage({data:222});
},1250);
}
*/
  
function normalResStart(){

document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;

document.getElementById('scanvas').width=window.innerHeight;
document.getElementById('scanvas').height=window.innerHeight;

document.getElementById('bcanvas').width=window.innerHeight;
document.getElementById('bcanvas').height=window.innerHeight;

document.getElementById('acanvas').width=window.innerHeight;
document.getElementById('acanvas').height=window.innerHeight;

setTimeout(function(){
Module.ccall('fire_egl');
},150);
setTimeout(function(){
Module.ccall('b3_egl');
},350);
setTimeout(function(){
Module.ccall('b3');
},550);
setTimeout(function(){
Module.ccall('str');
},750);
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},950);
}
  
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt;
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();var slt=$lt/1000;slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
slt=slt/100;tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
var $ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
});setTimeout(function(){slt=tem.innerHTML;},8);},16);});

function loada(){
var mv,lo;
if(lockVid!=1){
winSize=parseInt(window.innerHeight,10);
$high.innerHTML=winSize;
document.getElementById('circle').height=winSize;
document.getElementById('circle').width=parseInt(window.innerWidth,10);
document.getElementById('ldv').addEventListener('canplay',function(){
document.getElementById('ldv').height=winSize;
// loadV.width=this.videoWidth;
document.getElementById('wid').innerHTML=parseInt(this.videoWidth,10);
document.getElementById('hig').innerHTML=parseInt(this.videoHeight,10);
var $sc=this.duration;
var mic=Math.round($sc*1000000);
var $pt=Math.random()*mic;
$pt=$pt*1000000;
$pt=$pt/1000000;
$pt=Math.round($pt);
$pt=$pt/1000000;
document.getElementById('idur').innerHTML=mic/1000000;
document.getElementById('itim').innerHTML=$pt;
});
winSize=parseInt(window.innerHeight,10);
$lt=Math.round(tem.innerHTML);
var $ldt=$tim.innerHTML;
var $ls=$lt/1000;
$ls=$ls*1000;
$ls=Math.round($ls);
$ls=$ls/1000;
var rnum=Math.floor((Math.random()*($vids[0]-5))+5);
var vidSrc=$vids[rnum];
var $h=window.innerHeight;
var he=document.getElementById('hig').innerHTML;
var wi=document.getElementById('wid').innerHTML;
var r$=he/$h;
var $w=wi/r$;
var $hi=he-winSize;
if($hi>1){$h=winSize;var $r=$h/he;$r=$r*1000;$r=$r/1000;$w=wi*$r;};
var $hg=$h+'px';
mv=vide[0].id;
lo=vide[1].id;
vide[0].id=lo;
vide[1].id=mv;
document.getElementById('mv').play();
document.getElementById("wrap").style.lineheight=$hg;
document.getElementById("wrap").style.pointerEvents="auto";
document.getElementById('ldv').src=vidSrc;
document.getElementById('ldv').currentTime=$itim.innerHTML;
document.getElementById('ldv').load();
document.getElementById('di').click();
};
setTimeout(function(){
loada();
},$ldt);
}
   
document.getElementById('startBtn').addEventListener('click',function(){
scanSongs();
scanVideos();
loada();
scanShaders();
});

});

int main(){
"use strict";
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});

js_main();
return 0;

}
