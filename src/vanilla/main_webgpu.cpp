#include "../../include/vanilla/main_webgpu.h"
// #include <boost/algorithm/hex.hpp>

void raf(WGpuDevice device){
mapBuffer=wgpu_device_create_buffer(device,&bufferDescriptorM);
inputBuffer=wgpu_device_create_buffer(device,&bufferDescriptorI);
outputBuffer=wgpu_device_create_buffer(device,&bufferDescriptorO);
for(int i=0;i<input.size();++i){
input[i]=i;
}
shaderModuleDescriptor={computeShader,0,NULL};
cs=wgpu_device_create_shader_module(device,&shaderModuleDescriptor);
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=bufferBindingLayout1;
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=bufferBindingLayout2;
bindGroupLayout=wgpu_device_create_bind_group_layout(device,bindGroupLayoutEntries,2);
pipelineLayout=wgpu_device_create_pipeline_layout(device,&bindGroupLayout,1);
computePipeline=wgpu_device_create_compute_pipeline(device,cs,Entry,pipelineLayout,NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=inputBuffer;
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=0;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=outputBuffer;
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=0;
           
bindGroup=wgpu_device_create_bind_group(device,bindGroupLayout,bindGroupEntry,2);
encoder=wgpu_device_create_command_encoder(device,0);
computePass=wgpu_command_encoder_begin_compute_pass(encoder,&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(computePass,computePipeline);
wgpu_encoder_set_bind_group(computePass,0,bindGroup,0,0);
queue=wgpu_device_get_queue(device);
wgpu_queue_write_buffer(queue,inputBuffer,0,input.data(),input.size()*sizeof(int));
wgpu_compute_pass_encoder_dispatch_workgroups(computePass,uint32_t(256),uint32_t(256),uint32_t(1));
wgpu_encoder_end(computePass);
wgpu_command_encoder_copy_buffer_to_buffer(encoder,outputBuffer,0,mapBuffer,0,IbufferSize);
commandBuffer=wgpu_encoder_finish(encoder);
WGpuOnSubmittedWorkDoneCallback onComputeDone=[](WGpuQueue queue,void *userData){
WGpuBufferMapCallback mapCallback=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
double output=wgpu_buffer_get_mapped_range(mapBuffer,uint32_t(0),IbufferSize);
           
wgpu_buffer_read_mapped_range(mapBuffer,output,0,&resulT,16);
           
std::cout << resulT[0] << std::endl;
std::cout << resulT[1] << std::endl;
std::cout << resulT[2] << std::endl;
std::cout << resulT[3] << std::endl;
           
std::cout << &output << std::endl;
std::cout << output << std::endl;
           
EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;
emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_TRUE;
attr.depth=EM_TRUE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_TRUE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=2;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
emscripten_webgl_make_context_current(ctx);
    // texture
GLsizei width=256;
GLsizei height=256;
GLuint texture=0,textureb=0,texturec=0,textured=0;
unsigned char* Colora=new unsigned char[width*height*sizeof(unsigned char)];
for(int g=0;g<65536;g++){
Colora[g+0]=0;
Colora[g+1]=222;
Colora[g+2]=0;
Colora[g+3]=230;
}
glGenTextures(1,&texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,texture);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,Colora);
glGenerateMipmap(GL_TEXTURE_2D);
           
           // create buffer
GLuint pbo;
glGenBuffers(1, &pbo);
glBindBuffer(GL_TEXTURE_BUFFER, pbo);
glBufferData(GL_TEXTURE_BUFFER, width*height*sizeof(unsigned char), texture, GL_STATIC_READ);
// get texture image
// glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)(0));
// map pixel buffer
void * data_ptr = glMapBufferRange(GL_TEXTURE_BUFFER,0,64, GL_MAP_READ_BIT );
std::cout << "tex data -" << std::endl;
std::cout << &data_ptr << std::endl;
std::cout << data_ptr << std::endl;
glUnmapBuffer(GL_TEXTURE_BUFFER);
           
};
wgpu_buffer_map_async(mapBuffer,mapCallback,&userDataA,mode1,uint32_t(0),IbufferSize);
};
wgpu_queue_set_on_submitted_work_done_callback(queue,onComputeDone,0);
wgpu_queue_submit_one(queue,commandBuffer);
return;
}

void ObtainedWebGpuDevice(WGpuDevice result,void * userData){
device=result;
raf(device);
}

void ObtainedWebGpuAdapter(WGpuAdapter result,void * userData){
adapter=result;
wgpu_adapter_request_device_async(adapter,&deviceDescriptor,ObtainedWebGpuDevice,0);
}

void gpuStart(){
navigator_gpu_request_adapter_async(&options,ObtainedWebGpuAdapter,0);
}

extern"C"{

void startWebGPU(){
gpuStart();
}

}

EM_JS(void,js_main,(),{

function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall("startWebGPU");
});
}

document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
           
const tem=document.getElementById('tim');
const ban=document.getElementById('menuBtn');
const sfr=document.getElementById('slideframe');
var $lt=tem.innerHTML;

function grab$lt(){
$lt=Math.round($lt);
}

$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
setTimeout(function(){
grab$lt();
slt=$lt/1000;
slt=Math.round(slt);
sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
const tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
step:[0.25],labels:false,tooltip:true,scale:false,});
grab$lt();
slt=($lt/1000);
slt=slt*100;
slt=Math.round(slt);
slt=slt/100;
tsl.setValues(slt);
document.getElementById('menu').addEventListener('click',function(){
$ll=tsl.getValue();
$ll=$ll*100;
$ll=Math.round($ll);
$ll=$ll/100;$ll=($ll*1000);
tem.innerHTML=$ll;
});
setTimeout(function(){
slt=tem.innerHTML;
},8);
},16);
});
               
document.getElementById('startBtn').addEventListener('click',function(){
normalResStart();
});

setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);

});
    
int main(void){
js_main();
return 0;
}
