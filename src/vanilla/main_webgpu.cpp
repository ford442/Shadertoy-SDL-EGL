#include "../../include/vanilla/main_webgpu.h"

inline int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;  //division by zero?
return randomNumber;
}

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
double Range=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(1,0,1),uint32_t(0),DbufferSize);
WGPU_BufferMappedRange.at(0,0,0)=Range;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Buffer;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(1,0,1),WGPU_BufferMappedRange.at(0,0,0),uint32_t(0),WGPU_ResultBuffer.at(0,0,0),bufferSize);
/* for(int g=0;g<65536;g++){
int hh=g*4;
ColorA[hh]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh]);
ColorA[hh+1]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh+1]);
ColorA[hh+2]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh+2]);
ColorA[hh+3]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh+3]);
} */
wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
double WGPU_Map_Range=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(1,0,1),uint32_t(0),DbufferSize);
WGPU_BufferMappedRange.at(0,0,0)=WGPU_Map_Range;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(1,0,1),WGPU_BufferMappedRange.at(0,0,0),uint32_t(0),WGPU_ResultBuffer.at(0,0,0),bufferSize);
raN=rNd4(3);
glGenTextures(1,&wtexture[raN]);
glActiveTexture(GL_TEXTURE0+raN);
glBindTexture(GL_TEXTURE_2D,wtexture[raN]);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&WGPU_ResultBuffer.at(0,0,0));
glGenerateMipmap(GL_TEXTURE_2D); // broken gl textures without
wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
WGPU_UserData.at(0,0,0)=userDataA;
wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,0),&WGPU_UserData.at(0,0,0),mode1,0,DbufferSize);
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,1),&WGPU_UserData.at(0,0,0),mode1,0,DbufferSize);
return;
};

static void raf(WGpuDevice device){
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,2));
raN=rNd4(1024);
input[0]=raN;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
cs=wgpu_device_create_shader_module(WGPU_Device.at(0,0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_ComputeModule.at(0,0,0)=cs;
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
bindGroupLayout=wgpu_device_create_bind_group_layout(WGPU_Device.at(0,0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_BindGroupLayout.at(0,0,0)=bindGroupLayout;
pipelineLayout=wgpu_device_create_pipeline_layout(WGPU_Device.at(0,0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipelineLayout.at(0,0,0)=pipelineLayout;
computePipeline=wgpu_device_create_compute_pipeline(WGPU_Device.at(0,0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
WGPU_ComputePipeline.at(0,0,0)=computePipeline;
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=0;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=0;
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
bindGroup=wgpu_device_create_bind_group(WGPU_Device.at(0,0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_BindGroup.at(0,0,0)=bindGroup;
queue=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_Queue.at(0,0,0)=queue;
// encoder=wgpu_device_create_command_encoder(WGPU_Device.at(0,0,0),NULL);
encoder=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=encoder;
computePass=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
WGPU_ComputePassCommandEncoder.at(0,0,0)=computePass;
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,input.data(),DiBufferSize);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),64,4,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,DiBufferSize);
commandBuffer=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_CommandBuffer.at(0,0,0)=commandBuffer;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_ComputeDoneCallback.at(0,0,1)=onComputeDoneRun;
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
return;
}

static void WGPU_Run(){
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,1),0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,input.data(),DiBufferSize);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),64,4,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,DiBufferSize);
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
return;
}

static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
raf(WGPU_Device.at(0,0,0));
return;
}

static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData){
adapter=result;
WGPU_Adapter.at(0,0,0)=result;
WGPU_DeviceDescriptor.at(0,0,0)=deviceDescriptor;
WGPU_ObtainedDeviceCallback.at(0,0,0)=ObtainedWebGpuDeviceStart;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
return;
}

void WGPUCompute_Start(){
WGPU_RequestAdapterOptions.at(0,0,0)=options;;
WGPU_ObtainedAdapterCallback.at(0,0,0)=ObtainedWebGpuAdapterStart;
navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
return;
}
/*
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
int Colora[width*height];
for(int g=0;g<65536;g++){
Colora[g]=int(resulT[g]);
Colora[g+1]=int(resulT[g+1]);
Colora[g+2]=int(resulT[g+2]);
Colora[g+3]=int(resulT[g+3]);
}
glGenTextures(1,&texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,texture);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA_INTEGER,width,height,0,GL_RGBA_INTEGER,GL_INT,Colora);
glGenerateMipmap(GL_TEXTURE_2D);
};
wgpu_queue_set_on_submitted_work_done_callback(queue,onComputeDone,0);
wgpu_queue_submit_one(queue,commandBuffer);
return;
}
*/

extern"C"{

void startWebGPU(){
WGPUCompute_Start();
}

void runWebGPU(){
WGPUCompute_Run();
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
