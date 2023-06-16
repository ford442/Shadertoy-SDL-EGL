#include "../../include/vanilla/main_webgpu.h"

inline char wgl_cmp_src[2000]=
"@group(0)@binding(0)var<storage,read>inputBuffer:array<i32,1>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<i32,262144>;"
"@compute@workgroup_size(64,4,1)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){"
"let f:u32=global_id.x*global_id.y*4;"
"for(var g:u32=0;g<256;g++){"
"var h:u32=f*g;"
"outputBuffer[h]=133;"
"outputBuffer[h+1]=0;"
"outputBuffer[h+2]=80;"
"outputBuffer[h+3]=222;"
"}}";

static shad_tensor Sh=shad_tensor{3,3};
static prg_tensor S1=prg_tensor{1,1,1};
static sz_tensor Si=sz_tensor{1,1};
static d_tensor d_time=d_tensor{2,2};
static f_tensor Fi=f_tensor{2,2};
static d_tensor Di=d_tensor{2,2};
static gi_tensor uni_i=gi_tensor{1,1};
static i_tensor i_view=i_tensor{1,2};
static i_tensor i_date=i_tensor{2,2};
static f_tensor t_size=f_tensor{1,2};
static li_tensor i_size=li_tensor{1,2};
static void_tensor cntx=void_tensor{2,2};
static i_tensor cntxi=i_tensor{2,2};
static mouse_tensor mms=mouse_tensor{2,2};
static li_tensor mms2=li_tensor{2,2};
static void_tensor bin=void_tensor{1,1};
static wa_tensor WGPU_Adapter=wa_tensor{1,1,2};
static wd_tensor WGPU_Device=wd_tensor{1,1,2};
static wq_tensor WGPU_Queue=wq_tensor{1,1,2};
static cb_tensor WGPU_CommandBuffer=cb_tensor{1,1,2};
static wb_tensor WGPU_Buffers=wb_tensor{2,2,2};
static ce_tensor WGPU_CommandEncoder=ce_tensor{1,1,2};
static cpe_tensor WGPU_ComputePassCommandEncoder=cpe_tensor{1,1,2};
static cp_tensor WGPU_ComputePipeline=cp_tensor{1,1,1};
static pl_tensor WGPU_ComputePipelineLayout=pl_tensor{1,1,1};
static cm_tensor WGPU_ComputeModule=cm_tensor{1,1,1};
static bg_tensor WGPU_BindGroup=bg_tensor{1,1,1};
static bgl_tensor WGPU_BindGroupLayout=bgl_tensor{1,1,1};
static bgle_tensor WGPU_BindGroupLayoutEntries=bgle_tensor{1,1,1};
static bge_tensor WGPU_BindGroupEntries=bge_tensor{1,1,1};
static bmc_tensor WGPU_MapCallback=bmc_tensor{1,1,2};
static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,2};
static oac_tensor WGPU_ObtainedAdapterCallback=oac_tensor{1,1,2};
static odc_tensor WGPU_ObtainedDeviceCallback=odc_tensor{1,1,2};
static bbl_tensor WGPU_BufferBindingLayout=bbl_tensor{1,1,3};
static bd_tensor WGPU_BufferDescriptor=bd_tensor{1,1,3};
static md_tensor WGPU_ShaderModuleDescriptor=md_tensor{1,1,3};
static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
static void_tensor WGPU_UserData=void_tensor{1,1,1};
static rao_tensor WGPU_RequestAdapterOptions=rao_tensor{1,1,1};
static dd_tensor WGPU_DeviceDescriptor=dd_tensor{1,1,1};
static iptr_tensor WGPU_ResultBuffer=iptr_tensor{1,1,1};

unsigned char * ColorA=new unsigned char[262144*sizeof(unsigned char)];

uint32_t workgroupSize=64;
int bufferSize=262144*sizeof(int);
uint64_t bufferMapSize=262144*sizeof(int);
uint64_t ibufferMapSize=1*sizeof(unsigned int);
int bufferSize=1*sizeof(unsigned int);
uint64_t DescriptorBufferSize=262144*sizeof(unsigned int);
uint64_t iDescriptorBufferSize=1*sizeof(unsigned int);
const char * Entry="computeStuff";
uint32_t invocationCount=bufferMapSize/sizeof(unsigned int);
uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
GLsizei width=256;
GLsizei height=256;
GLuint wtexture[4];
WGpuAdapter adapter=0;
WGpuDevice device=0;
WGpuQueue queue=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuComputePipeline computePipeline=0;
WGpuBuffer inputBuffer=0;
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroup bindGroup=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[2];

WGpuBindGroupEntry bindGroupEntry[2];

WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferDescriptor bufferDescriptorI={iDescriptorBufferSize,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={DescriptorBufferSize,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
WGpuBufferDescriptor bufferDescriptorM={DescriptorBufferSize,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
std::vector<unsigned int>input(iBufferSize/sizeof(unsigned int));
std::vector<unsigned int>outputd(bufferSize/sizeof(unsigned int));
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={cmp_bdy,0,NULL};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;

inline int rNd4(int randomMax){
randomNumber=0,entropySeed=0;
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;  //division by zero?
return randomNumber;
}

int * WGPU_Result_Buffer=new int[bufferSize/sizeof(int)];

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
uint64_t Range=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(1,0,1),uint64_t(0),bufferMapSize);
WGPU_BufferMappedRange.at(0,0,0)=Range;

  //  std::vector<unsigned int>WGPU_Result_Buffer(bufferSize/sizeof(unsigned int));
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Buffer;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(1,0,1),WGPU_BufferMappedRange.at(0,0,0),uint64_t(0),&WGPU_Result_Buffer,bufferMapSize);
std::cout << "Result Buffer:\n";
std::cout << WGPU_Result_Buffer[0];
    /* 
    for(int g=0;g<65536;g++){
int hh=g*4;
ColorA[hh]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh]);
ColorA[hh+1]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh+1]);
ColorA[hh+2]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh+2]);
ColorA[hh+3]=uint32_t(WGPU_ResultBuffer.at(0,0,0)[hh+3]);
} 
*/
wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
 //   WGPU_Result_Buffer.del()
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
uint64_t WGPU_Map_Range=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(1,0,1),uint64_t(0),bufferMapSize);
WGPU_BufferMappedRange.at(0,0,0)=WGPU_Map_Range;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(1,0,1),WGPU_BufferMappedRange.at(0,0,0),uint32_t(0),&WGPU_ResultBuffer.at(0,0,0),bufferMapSize);

    /*
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
    */
wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
WGPU_UserData.at(0,0,0)=userDataA;
wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,0),&WGPU_UserData.at(0,0,0),mode1,uint64_t(0),bufferMapSize);
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,1),&WGPU_UserData.at(0,0,0),mode1,uint64_t(0),bufferMapSize);
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
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,input.data(),bufferMapSize);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),64,4,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,bufferMapSize);
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
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,input.data(),bufferMapSize);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),64,4,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(1,0,1),0,bufferMapSize);
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

void WGPU_Start(){
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

extern"C"{

void startWebGPU(){
WGPU_Start();
}

void runWebGPU(){
WGPU_Run();
}

}

int main(void){
js_main();
return 0;
}
