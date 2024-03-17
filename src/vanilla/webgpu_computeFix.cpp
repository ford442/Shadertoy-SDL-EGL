#include "../../include/vanilla/webgpu_fix.hpp"

inline char wgl_cmp_src[2000]=
"@group(0)@binding(0)var <storage,read> inputBuffer: array<f32,64>;\n"
"@group(0)@binding(1)var <storage,read_write> outputBuffer: array<f32,64>;\n"
"@group(0)@binding(2)var textureIN: texture_2d <f32>;\n"
"@group(0)@binding(3)var textureOUT: texture_storage_2d <rgba8unorm,write>;\n"
"@group(0)@binding(4)var resizeSampler: sampler;\n"
"@group(0)@binding(5)var <uniform> iResolution: u32;\n"
// "@group(0)@binding(6)var videoTexture: texture_2d <f32>;\n"
"@compute@workgroup_size(1,1,64)\n"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){\n"
"var sizeINf=inputBuffer[0];\n"
"var loopx:u32=u32(sizeINf);\n"
"var sizeINu:u32=u32(sizeINf);\n"
"var sizeOUTf=inputBuffer[1];\n"
"var sizeOUTu:u32=u32(sizeOUTf);\n"
"for(var y:u32=0u;y<loopx;y=y+1u){\n"
"for(var x:u32=0u;x<loopx;x=x+1u){\n"
"var INtexCoord:vec2<u32>=vec2<u32>(vec2<u32>(x,y)*(sizeINu/sizeOUTu));\n"
"var colorTest:vec4<f32>=textureLoad(textureIN,INtexCoord,0);\n"
// "var colorTest:vec4<f32>=inputBuffer[INtexCoord.x*INtexCoord.y*4];\n"
"textureStore(textureOUT,vec2<u32>(u32(x),u32(y)),colorTest);\n"
// "outputBuffer[x*y*4]=inputBuffer[INtexCoord.x*INtexCoord.y*4];\n"
// "outputBuffer[(x*y*4)+1]=inputBuffer[(INtexCoord.x*INtexCoord.y*4)+1];\n"
// "outputBuffer[(x*y*4)+2]=inputBuffer[(INtexCoord.x*INtexCoord.y*4)+2];\n"
// "outputBuffer[(x*y*4)+3]=inputBuffer[(INtexCoord.x*INtexCoord.y*4)+3];\n"
"}"
"}"
"outputBuffer[0]=8.0808f;\n"
"outputBuffer[1]=0.0001;\n"
"}";

WGpuExternalTexture extTexture;
WGpuExternalTextureBindingLayout extTextureBindingLayout={};
WGpuExternalTextureDescriptor extTextureDescriptor={};
WGpuTextureView depthTextureView;
WGpuTextureView colorTextureView;
WGpuTextureView videoTextureView;
WGpuTextureView INTextureView;
WGpuTextureView OUTTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuTextureViewDescriptor videoTextureViewDescriptor={};
WGpuTextureViewDescriptor INTextureViewDescriptor={};
WGpuTextureViewDescriptor OUTTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment;
WGpuTexture depthTexture;
WGpuTexture colorTexture;
WGpuTexture videoTexture;
WGpuSampler videoSampler={};
WGpuSampler resizeSampler={};
WGpuTexture __128bit_Texture__;
WGpuTextureDescriptor highbitTextureDescriptor={};
WGpuBufferDescriptor bufferDescriptorSrc={};
WGpuBufferDescriptor bufferDescriptorDst={};
WGpuBufferDescriptor bufferDescriptorVid={};
WGpuSamplerDescriptor resizeSamplerDescriptor={};
WGpuSamplerDescriptor videoSamplerDescriptor={};
WGpuTextureDescriptor depthTextureDescriptor={};
WGpuTextureDescriptor colorTextureDescriptor={};
WGpuTextureDescriptor videoTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuCanvasConfiguration config;
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuDepthStencilState depthState;
WGpuVertexState vertState;
WGpuPrimitiveState priState;
WGpuFragmentState fragState;
WGpuBufferDescriptor bufferDescriptorUni={};
WGpuBufferDescriptor bufferDescriptor_iTime={};
WGpuBufferDescriptor bufferDescriptor_iResolution={};
WGpuBufferDescriptor bufferDescriptor_iFrame={};
WGpuBufferDescriptor bufferDescriptor_iTimeDelta={};
// WGpuPipelineLayoutDescriptor renderPipelineLayoutDesc;  // unused by webgpu.h
// WGpuPipelineLayout pipeline_layout=0;
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayoutEntry render_bindgroup_layout_entries[4]={};
WGpuBindGroupEntry render_bindgroup_entries[4]={};
WGpuBindGroup bindgroup=0;
// WGpuRenderPipelineDescriptor renderPipelineDesc;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuBuffer uniBuffer;
WGpuBuffer srcBuffer;
WGpuBuffer dstBuffer;
WGpuBuffer vidBuffer;
WGpuBuffer uni_iTime_Buffer;
WGpuBuffer uni_iTimeDelta_Buffer;
WGpuBuffer uni_iResolution_Buffer;
WGpuBuffer uni_iFrame_Buffer;
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuBufferBindingLayout bufferBindingLayoutR={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayoutFloat={};
WGpuTextureBindingLayout textureBindingLayoutDepth={};
WGpuSamplerBindingLayout samplerBindingLayout={};
WGpuImageCopyExternalImage videoFrm={};
WGPUImageCopyBuffer videoFrmBfrSrc={};
// const WGPUImageCopyBuffer videoFrmBfrDst={};
double szh,szw;
int szhI,szwI;
double szhDv,szwDv;
float szhFv,szwFv;
struct WGpuUniform{
uint64_t iTime;
};

struct{
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
}u_time;

WGpuUniform wTime;
uint64_t tme;

xyz_tensor oxyz=xyz_tensor{2,2};
xy_tensor oxy=xy_tensor{2,2};
wtbl_tensor wtbl=wtbl_tensor{2,2};
i_tensor on=i_tensor{3,3};
wetd_tensor wetd=wetd_tensor{2,2};
wet_tensor wet=wet_tensor{2,2};
i_tensor texid=i_tensor{2,2};
i_tensor sze=i_tensor{3,3};
f_tensor szef=f_tensor{2,2};
wce_tensor wce=wce_tensor{2,2};
wrpe_tensor wrpe=wrpe_tensor{2,2};
wcb_tensor wcb=wcb_tensor{2,2};
wd_tensor wd=wd_tensor{2,2};
wq_tensor wq=wq_tensor{2,2};
wa_tensor wa=wa_tensor{2,2};
wcc_tensor wcc=wcc_tensor{2,2};
wccf_tensor wccf=wccf_tensor{2,2};
wrp_tensor wrp=wrp_tensor{2,2};
wrp_tensor wrpl=wrp_tensor{2,2};
wb_tensor wb=wb_tensor{5,5};
wbgle_tensor wbgle=wbgle_tensor{2,2};
wbge_tensor wbge=wbge_tensor{2,2};
wbgl_tensor wbgl=wbgl_tensor{2,2};
wbg_tensor wbg=wbg_tensor{2,2};
wrpd_tensor wrpd=wrpd_tensor{2,2};
wrpca_tensor wrpca=wrpca_tensor{2,2};
wbbl_tensor wbbl=wbbl_tensor{2,2};
wsbl_tensor wsbl=wsbl_tensor{2,2};
wbd_tensor wbd=wbd_tensor{5,5};
wao_tensor wao=wao_tensor{2,2};
wdd_tensor wdd=wdd_tensor{2,2};
u64_tensor u64_uni=u64_tensor{4,4};
u64_tensor u64_siz=u64_tensor{4,4};
wrbe_tensor wrbe=wrbe_tensor{2,2};
wrbed_tensor wrbed=wrbed_tensor{2,2};
wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
wt_tensor wt=wt_tensor{3,3};
wtd_tensor wtd=wtd_tensor{3,3};
wtvd_tensor wtvd=wtvd_tensor{3,3};
wtf_tensor wtf=wtf_tensor{5,5};
wtv_tensor wtv=wtv_tensor{3,3};
wicb_tensor wicb=wicb_tensor{3,3};
wicei_tensor wicei=wicei_tensor{2,2};
js_tensor js_data_pointer=js_tensor{2,2};
fjs_tensor fjs_data_pointer=fjs_tensor{2,2};
js_data_tensor frame_tensor=js_data_tensor{2,2};
js_data_tensor64 frame_tensor64=js_data_tensor64{2,2};
u64_tensor u64_bfrSze=u64_tensor{4,4};
wict_tensor wict=wict_tensor{4,4};
wsd_tensor wsd=wsd_tensor{2,2};
ws_tensor wsmp=ws_tensor{4,4};
v_tensor imgData=v_tensor{2,2};

wq_tensor WGPU_Queue=wq_tensor{1,1,2};
wcb_tensor WGPU_CommandBuffer=wcb_tensor{1,1,3};
wb_tensor WGPU_Buffers=wb_tensor{3,3,3};
wce_tensor WGPU_CommandEncoder=wce_tensor{1,1,4};
wcpe_tensor WGPU_ComputePassCommandEncoder=wcpe_tensor{1,1,3};
wcpd_tensor WGPU_ComputePassDescriptor=wcpd_tensor{1,1,3};
wcp_tensor WGPU_ComputePipeline=wcp_tensor{1,1,1};
wpl_tensor WGPU_ComputePipelineLayout=wpl_tensor{1,1,1};
wsm_tensor WGPU_ComputeModule=wsm_tensor{1,1,1};
wbg_tensor WGPU_BindGroup=wbg_tensor{1,1,2};
wbgl_tensor WGPU_BindGroupLayout=wbgl_tensor{1,1,2};
wbgle_tensor WGPU_Compute_Bindgroup_Layout_Entries=wbgle_tensor{1,1,2};
wbge_tensor WGPU_BindGroupEntries=wbge_tensor{1,1,2};
wbmc_tensor WGPU_MapCallback=wbmc_tensor{1,1,3};
wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
wbbl_tensor WGPU_BufferBindingLayout=wbbl_tensor{1,1,4};
wbd_tensor WGPU_BufferDescriptor=wbd_tensor{1,1,4};
wsmd_tensor WGPU_ShaderModuleDescriptor=wsmd_tensor{1,1,3};
di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
void_tensor WGPU_UserData=void_tensor{1,1,2};
fptr_tensor WGPU_ResultBuffer=fptr_tensor{1,1,1};
fptr_tensor WGPU_InputBuffer=fptr_tensor{1,1,1};
i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
wt_tensor WGPU_Texture=wt_tensor{3,3,3};
wtd_tensor WGPU_TextureDescriptor=wtd_tensor{3,3,3};
wstbl_tensor WGPU_StorageTextureBindingLayout=wstbl_tensor{1,1,1};
wtvd_tensor WGPU_TextureViewDescriptor=wtvd_tensor{3,3,3};
uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
wced_tensor WGPU_CommandEncoderDescriptor=wced_tensor{1,1,1};
wbms_tensor WGPU_BufferStatus=wbms_tensor{1,1,1};

c_tensor wgsl=c_tensor{2,2};

uint32_t workgroupSize=64;

uint32_t OutputBufferBytesI=64*4;
uint32_t InputBufferBytesI=64*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytesI;
double_int53_t OutputBufferBytes=OutputBufferBytesI;
double_int53_t InputBufferBytes=InputBufferBytesI;
uint32_t InputBufferBytesU=64*4;
uint32_t OutputBufferBytesU=64*4;

const char * Entry="computeStuff";
// uint32_t invocationCount=BufferMapSize/sizeof(int);
// uint32_t workgroupCount=(invocationCount+workgroupSize-1)/workgroupSize;
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
void * userDataB;
WGpuTexture textureA;
// WGpuAdapter adapter=0;
// WGpuDevice device=0;
// WGpuQueue queue=0;
WGpuBindGroupLayout bindGroupLayout=0;
WGpuBindGroupLayout bindGroupLayoutB=0;
WGpuComputePipeline computePipeline=0;
WGpuBuffer inputBuffer=0;
WGpuBuffer outputBuffer=0;
WGpuBuffer mapBuffer=0;
// WGpuBuffer uniBuffer=0;
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
WGpuBindGroupLayoutEntry Compute_Bindgroup_Layout_Entries[8]={};
WGpuBindGroupEntry Compute_Bindgroup_Entries[8]={};
WGpuBufferBindingLayout bufferBindingLayoutIn={3};
WGpuBufferBindingLayout bufferBindingLayoutOut={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storagetextureBindingLayoutFloat={1,18,2};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
WGpuBufferDescriptor bufferDescriptorI={};
WGpuBufferDescriptor bufferDescriptorO={};
WGpuBufferDescriptor bufferDescriptorM={};
WGpuBufferDescriptor bufferDescriptorC={};
WGpuTextureDescriptor textureDescriptorIn={};
WGpuTextureDescriptor textureDescriptorOut={};
WGpuTextureViewDescriptor textureViewDescriptorIn={};
WGpuTextureViewDescriptor textureViewDescriptorOut={};
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={cmp_bdy,0,NULL};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;
WGpuImageCopyTexture WGPU_Input_Image={};
WGpuImageCopyTexture WGPU_Output_Image={};
WGpuImageCopyBuffer WGPU_Input_Buffer={};
WGpuImageCopyBuffer WGPU_Output_Buffer={};
WGpuImageCopyBuffer WGPU_Mapped_Buffer={};
uint32_t outP;
double_int53_t WGPU_Range_PointerB;
double_int53_t WGPU_Range_PointerC;

float * WGPU_Result_Array=new float[OutputBufferBytes];
float * WGPU_Input_Array=new float[InputBufferBytes];

struct Vertex{
GLfloat position[4];
};

Vertex vertices[]={
{-1.0,-1.0,1.0,1.0},
{1.0,-1.0,1.0,1.0},
{1.0,1.0,1.0,1.0},
{-1.0,1.0,1.0,1.0},
{-1.0,-1.0,-1.0,1.0},
{1.0,-1.0,-1.0,1.0},
{1.0,1.0,-1.0,1.0},
{-1.0,1.0,1.0,1.0}
};

uint32_t indices[35]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};

inline int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

const char * vertexShader=
"struct VertexOutput{\n"
"@builtin(position) Position : vec4<f32>,\n"
"@location(0) fragUV : vec2<f32>\n"
"};\n"
"@vertex\n"
"fn main(@builtin(vertex_index) VertexIndex : u32) -> VertexOutput {\n"
"var pos=array<vec2<f32>,6>(\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(1.0f,-1.0f),\n"
"vec2<f32>(-1.0f,-1.0f),\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(-1.0f,-1.0f),\n"
"vec2<f32>(-1.0f,1.0f)\n"
");\n"
"var uv=array<vec2<f32>,6>(\n"
"vec2<f32>(1.0f,0.0f),\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(0.0f,1.0f),\n"
"vec2<f32>(1.0f,0.0f),\n"
"vec2<f32>(0.0f,1.0f),\n"
"vec2<f32>(0.0f,0.0f)\n"
");\n"
"var output : VertexOutput;\n"
"output.Position=vec4(pos[VertexIndex],0.0f,1.0f);\n"
"output.fragUV=uv[VertexIndex];\n"
"return output;\n"
"}\n";

const char * vertexShaderB=
"struct VertexOutput{\n"
"@builtin(position) Position : vec4<f32>,\n"
"@location(0) fragUV : vec2<f32>\n"
"};\n"
"@vertex\n"
"fn main(@builtin(vertex_index) VertexIndex : u32) -> VertexOutput {\n"
"var pos=array<vec2<f32>,6>(\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(1.0f,-1.0f),\n"
"vec2<f32>(-1.0f,-1.0f),\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(-1.0f,-1.0f),\n"
"vec2<f32>(-1.0f,1.0f)\n"
");\n"
"var output : VertexOutput;\n"
"output.Position=vec4(pos[VertexIndex],0.0f,1.0f);\n"
"output.fragUV = vec2<f32>(output.Position.x + 1.0f, output.Position.y + 1.0f) * 0.5f;\n"
"return output;\n"
"}\n";

const char * frag_body=
"@group(0) @binding(0) var <uniform> iTime : u32;\n"
"@group(0) @binding(1) var mySampler : sampler;\n"
"@group(0) @binding(2) var myTexture : texture_2d <f32>;\n"
// "@group(0) @binding(3) var extTexture : texture_external;\n"
"@fragment\n"
"fn main(@location(0) fragUV : vec2<f32>) ->\n"
"@location(0) vec4<f32> {\n"
"return textureSample(myTexture,mySampler,fragUV);"
"}\n";

const char * Fnm=reinterpret_cast<const char *>("/shader/shader.glsl");

static char * result=NULL;
static char * results=NULL;
static long int length=0;

const inline char * rd_fl(const char * Fnm){
FILE * file=fopen(Fnm,"r");
::boost::tuples::tie(result,results,file);
if(file){
int32_t stat=fseek(file,(int32_t)0,SEEK_END);
if(stat!=0){
fclose(file);
return nullptr;
}
length=ftell(file);
stat=fseek(file,(int32_t)0,SEEK_SET);
if(stat!=0){
fclose(file);
return nullptr;
}
result=static_cast<char *>(malloc((length+1)*sizeof(char)));
if(result){
size_t actual_length=fread(result,sizeof(char),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
// results=reinterpret_cast<char *>(result);
return result;
}
return nullptr;
}

const char * Fnm2=reinterpret_cast<const char *>("/video/frame.gl");

uint8_t * result2=NULL;
float * resultf=NULL;
uint8_t * results2=NULL;
float * resultsf=NULL;
long int length2=0;

uint8_t * rd_frm(const char * Fnm2){
FILE * file2=fopen(Fnm,"r");
::boost::tuples::tie(result2,results2,file2);
if(file2){
int32_t stat=fseek(file2,0,SEEK_END);
if(stat!=0){
fclose(file2);
return nullptr;
}
length=ftell(file2);
stat=fseek(file2,0,SEEK_SET);
if(stat!=0){
fclose(file2);
return nullptr;
}
result2=static_cast<uint8_t *>(malloc((length+1)*sizeof(uint8_t)));
if(result2){
size_t actual_length=fread(result2,sizeof(uint8_t),length,file2);
result[actual_length++]={'\0'};
}
fclose(file2);
return result2;
}
return nullptr;
}

float * rd_frmf(const char * Fnm2){
FILE * file2=fopen(Fnm,"r");
::boost::tuples::tie(result2,results2,file2);
if(file2){
int32_t stat=fseek(file2,0,SEEK_END);
if(stat!=0){
fclose(file2);
return nullptr;
}
length=ftell(file2);
stat=fseek(file2,0,SEEK_SET);
if(stat!=0){
fclose(file2);
return nullptr;
}
resultf=static_cast<float *>(malloc((length+1)*sizeof(float)));
if(resultf){
size_t actual_length=fread(resultf,sizeof(float),length,file2);
result[actual_length++]={'\0'};
}
fclose(file2);
return resultf;
}
return nullptr;
}

void * fram;
// uint8_t * fram;

void getCode(const char * Fnm){
// const char * frag_body=(char *)rd_fl(Fnm);
wgsl.at(0,0)=frag_body;
return;
}

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
on.at(1,1)=1;
return;
};

WGpuBufferMapCallback mapCallbackRun=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuBufferMapCallback mapCallbackRun2=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
/*
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_BufferRange.at(0,0,1),0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
}
// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
on.at(1,1)=1;
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
// wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),WGPU_MapCallback.at(0,0,0),&WGPU_UserData.at(0,0,0),mode1,0,OutputBufferBytes);
}
EM_ASM({
document.querySelector('#outText1').innerHTML='Output0:'+$0.toFixed(2);
},WGPU_ResultBuffer.at(0,0,0)[0]);
// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
*/
return;
};

// void raf(){
boost::function<EM_BOOL()>render=[](){
u64_uni.at(3,3)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u64_uni.at(0,0)=u_time.time_spana.count()*1000;
u64_uni.at(1,1)=u_time.time_spanb.count()*1000;
// u64_uni.at(2,2)=u_time.time_spanb.count()/1.0f;
wce.at(0,0)=wgpu_device_create_command_encoder(wd.at(0,0),0);
colorAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
// colorTexture=wgpu_device_create_texture(wd.at(1,1),&wtd.at(1,1));
colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
// colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(wcc.at(0,0)),0);
colorAttachment.view=wtv.at(1,1);
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
// colorAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
colorAttachment.clearValue.r=1.0f;
colorAttachment.clearValue.g=1.0f;
colorAttachment.clearValue.b=1.0f;
colorAttachment.clearValue.a=1.0f;
wrpca.at(0,0)=colorAttachment;
depthAttachment={};
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0f;
depthAttachment.stencilClearValue=0;
depthAttachment.depthReadOnly=0;
depthAttachment.stencilReadOnly=1;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment.depthStoreOp=WGPU_STORE_OP_STORE;
// depthAttachment.stencilLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment.stencilStoreOp=WGPU_STORE_OP_STORE;
wrpdsa.at(0,0)=depthAttachment;
passDesc={};
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(0,0);
passDesc.depthStencilAttachment=wrpdsa.at(0,0);
wrpd.at(0,0)=passDesc;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
  
  //  frame data
// fram=static_cast<uint8_t *>(rd_frm(Fnm2));
// fram=(void *)rd_frmf(Fnm2);
std::ifstream fram(Fnm2,std::ios::binary);
// std::vector<char> data((std::istreambuf_iterator<char>(fram)),(std::istreambuf_iterator<char>()));
std::vector<uint8_t> data((std::istreambuf_iterator<char>(fram)),(std::istreambuf_iterator<char>()));
frame_tensor.at(0,0)=data;
wetd.at(0,0).source=texid.at(0,0);
// extTexture=wgpu_device_import_external_texture(wd.at(0,0),&wetd.at(0,0));
// wet.at(0,0)=extTexture;

       // Compute Pass
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Input_Image.origin=oxyz.at(0,0);
WGPU_Input_Image.aspect=WGPU_TEXTURE_ASPECT_ALL;
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_Output_Image.origin=oxyz.at(0,0);
WGPU_Output_Image.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(1,1)=WGPU_Input_Image;
wict.at(2,2)=WGPU_Output_Image;

INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;

// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&wict.at(1,1),&frame_tensor.at(1,1),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);
  
WGPU_InputBuffer.at(0,0,0)[0]=sze.at(1,1);
WGPU_InputBuffer.at(0,0,0)[1]=sze.at(0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&WGPU_InputBuffer.at(0,0,0),InputBufferBytes);

// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(wd.at(0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&WGPU_ComputePassDescriptor.at(0,0,0));
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
      
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),1,1,64);
  
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
  // wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,64,1,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
  // wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,64,1,1);
wgpu_command_encoder_copy_texture_to_texture(WGPU_CommandEncoder.at(0,0,0),&wict.at(2,2),&wict.at(0,0),sze.at(0,0),sze.at(0,0),1);
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
 wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,OutputBufferBytes,1,1);
// wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&wict.at(1,1),sze.at(0,0),sze.at(0,0),1);
  // wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&wict.at(0,0),sze.at(0,0),sze.at(0,0),1);
  // wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&wict.at(0,0),&WGPU_Mapped_Buffer,64,1,1);
  // wgpu_command_encoder_copy_texture_to_texture(WGPU_CommandEncoder.at(0,0,0),&wict.at(0,0),&wict.at(1,1),sze.at(0,0),sze.at(0,0),1);
// wgpu_queue_write_texture(wq.at(0,0),&wict.at(1,1),&WGPU_ResultBuffer.at(0,0,0),sze.at(0,0)*4,sze.at(0,0),sze.at(0,0),sze.at(0,0),1);
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_BufferRange.at(0,0,1),0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
}
if(WGPU_BufferStatus.at(0,0,0)!=3&&on.at(1,1)==0){
on.at(1,1)=1;
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
// wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),WGPU_MapCallback.at(0,0,0),&WGPU_UserData.at(0,0,0),mode1,0,OutputBufferBytes);
EM_ASM({
document.querySelector('#outText').innerHTML='Buffer at [0]:'+$0.toFixed(2);
},WGPU_ResultBuffer.at(0,0,0)[0]);
}

WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1&&on.at(1,1)==1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
on.at(1,1)=0;
}
  
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));

  


wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one_and_destroy(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));

  // Render Pass
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(3,3),0,&fram,sze.at(0,0)*sze.at(0,0));
// wgpu_command_encoder_copy_buffer_to_texture(wrpe.at(0,0),&wicb.at(1,1),wict.at(2,2),sze.at(0,0),sze.at(0,0),1);
wgpu_queue_write_texture(wq.at(0,0),&wict.at(1,1),&frame_tensor.at(0,0),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,szef.at(0,0),szef.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
// return;
return EM_TRUE;
// }
};

void raf(){
render();
}

void sz(int hh){
sze.at(1,1)=hh;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result,void *userData){
wd.at(0,0)=result;
on.at(1,1)=0;
js_data_pointer.at(0,0)=0;
fjs_data_pointer.at(0,0)=0;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
// const char * frag_body=(char*)rd_fl(Fnm);
WGPU_TEXTURE_FORMAT canvasFormat=navigator_gpu_get_preferred_canvas_format();
wtf.at(2,2)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(2,2)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
WGPU_TEXTURE_FORMAT canvasViewFormat[1]={wtf.at(0,0)};
config=WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
config.device=wd.at(0,0);
config.format=wtf.at(0,0);
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
// config.numViewFormats=1;
config.viewFormats=&canvasViewFormat[0];
// config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
// config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_canvas_element_size("canvas",&szwI,&szhI);
emscripten_get_element_css_size("canvas",&szw,&szh);
emscripten_get_element_css_size("#mvi",&szwDv,&szhDv);
u64_siz.at(0,0)=szhI;
sze.at(0,0)=int(szhI);
sze.at(1,1)=720; // int(szhDv);
szef.at(0,0)=floor(float(szh));
// sze.at(0,1)=szh;
WGpuOrigin3D OriginXYZ={};
OriginXYZ.x=0;
OriginXYZ.y=0;
OriginXYZ.z=0;
oxyz.at(0,0)=OriginXYZ;
WGpuOrigin2D OriginXY={};
OriginXY.x=0;
OriginXY.y=0;
oxy.at(0,0)=OriginXY;
workgroupSize=1;

WGPU_UserData.at(0,0,0)=userData;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorIn.format=wtf.at(0,0);
textureDescriptorIn.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorIn.width=sze.at(1,1);
textureDescriptorIn.height=sze.at(1,1); // default = 1;
textureDescriptorIn.depthOrArrayLayers=1;
textureDescriptorIn.mipLevelCount=1;
textureDescriptorIn.sampleCount=1;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT textureAviewFormats[1]={wtf.at(0,0)};
textureDescriptorIn.numViewFormats=0; // &textureAviewFormats[0];
textureDescriptorIn.viewFormats=nullptr; // &textureAviewFormats[0];
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.format=wtf.at(0,0);
textureDescriptorOut.usage=WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorOut.width=sze.at(0,0);
textureDescriptorOut.height=sze.at(0,0); // default = 1;
textureDescriptorOut.depthOrArrayLayers=1;
textureDescriptorOut.mipLevelCount=1;
textureDescriptorOut.sampleCount=1;
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT textureBviewFormats[1]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0; // &textureBviewFormats[0];
videoTextureDescriptor.viewFormats=nullptr; // &textureBviewFormats[0];
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorIn;
WGPU_TextureDescriptor.at(0,0,1)=textureDescriptorOut;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));

WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Input_Image.origin=oxyz.at(0,0);
WGPU_Input_Image.aspect=WGPU_TEXTURE_ASPECT_ALL;
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_Output_Image.origin=oxyz.at(0,0);
WGPU_Output_Image.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(2,2)=WGPU_Input_Image;
wict.at(0,0)=WGPU_Output_Image;

textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloat.multisampled=0;
wtbl.at(1,1)=textureBindingLayoutFloat;
textureBindingLayoutDepth.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_DEPTH;
textureBindingLayoutDepth.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutDepth.multisampled=0;
wtbl.at(2,2)=textureBindingLayoutDepth;

textureViewDescriptorIn.format=wtf.at(0,0);
textureViewDescriptorIn.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorIn.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorIn.baseMipLevel=0; // default = 0
textureViewDescriptorIn.mipLevelCount=1;
textureViewDescriptorIn.baseArrayLayer=0; // default = 0
textureViewDescriptorIn.arrayLayerCount=1;

textureViewDescriptorOut.format=wtf.at(0,0);
textureViewDescriptorOut.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorOut.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorOut.baseMipLevel=0; // default = 0
textureViewDescriptorOut.mipLevelCount=1;
textureViewDescriptorOut.baseArrayLayer=0; // default = 0
textureViewDescriptorOut.arrayLayerCount=1;

WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorIn;
WGPU_TextureViewDescriptor.at(0,0,1)=textureViewDescriptorOut;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
bufferDescriptorI={InputBufferBytesU,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
bufferDescriptorO={OutputBufferBytesU,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
bufferDescriptorM={OutputBufferBytesU,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
bufferDescriptorC={OutputBufferBytesU,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
bufferDescriptor_iTime={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptor_iTime;
uni_iTime_Buffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptor_iTime);
wb.at(0,0)=uni_iTime_Buffer;
bufferDescriptor_iFrame={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(1,1)=bufferDescriptor_iFrame;
uni_iFrame_Buffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptor_iFrame);
wb.at(1,1)=uni_iFrame_Buffer;
bufferDescriptor_iResolution={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(2,2)=bufferDescriptor_iResolution;
uni_iResolution_Buffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptor_iResolution);
wb.at(2,2)=uni_iResolution_Buffer;
bufferBindingLayoutR.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayoutR.hasDynamicOffset=0,
bufferBindingLayoutR.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayoutR;
// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
// if(WGPU_BufferStatus.at(0,0,0)!=1){
// wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// }
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=(floor((sze.at(0,0)*4)/256)+1)*256;
WGPU_Output_Buffer.rowsPerImage=sze.at(0,0);
// wicb.at(2,2)=WGPU_Output_Buffer;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=(floor((sze.at(0,0)*4)/256)+1)*256;
WGPU_Mapped_Buffer.rowsPerImage=sze.at(0,0);
resizeSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.lodMinClamp=0;
resizeSamplerDescriptor.lodMaxClamp=32;
// resizeSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
resizeSamplerDescriptor.maxAnisotropy=1;
wsd.at(1,1)=resizeSamplerDescriptor;
resizeSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(1,1));
wsmp.at(3,3)=resizeSampler;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(wd.at(0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayoutIn;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayoutOut;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storagetextureBindingLayoutFloat;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;
Compute_Bindgroup_Layout_Entries[0].binding=0;
Compute_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
Compute_Bindgroup_Layout_Entries[1].binding=1;
Compute_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
Compute_Bindgroup_Layout_Entries[2].binding=2;
Compute_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
Compute_Bindgroup_Layout_Entries[3].binding=3;
Compute_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[3].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
Compute_Bindgroup_Layout_Entries[4].binding=4;
Compute_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Compute_Bindgroup_Layout_Entries[4].layout.sampler=wsbl.at(0,0);
Compute_Bindgroup_Layout_Entries[5].binding=5;
Compute_Bindgroup_Layout_Entries[5].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[5].layout.buffer=wbbl.at(0,0);
WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0)=Compute_Bindgroup_Layout_Entries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(wd.at(0,0),WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0),6);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(wd.at(0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(wd.at(0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
Compute_Bindgroup_Entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[0].binding=0;
Compute_Bindgroup_Entries[0].resource=WGPU_Buffers.at(1,1,1);
Compute_Bindgroup_Entries[0].bufferBindOffset=0;
Compute_Bindgroup_Entries[0].bufferBindSize=InputBufferBytes;
Compute_Bindgroup_Entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[1].binding=1;
Compute_Bindgroup_Entries[1].resource=WGPU_Buffers.at(0,0,0);
Compute_Bindgroup_Entries[1].bufferBindOffset=0;
Compute_Bindgroup_Entries[1].bufferBindSize=OutputBufferBytes;
Compute_Bindgroup_Entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[2].binding=2;
Compute_Bindgroup_Entries[2].resource=wtv.at(3,3);
Compute_Bindgroup_Entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[3].binding=3;
Compute_Bindgroup_Entries[3].resource=wtv.at(4,4); 
Compute_Bindgroup_Entries[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[4].binding=4;
Compute_Bindgroup_Entries[4].resource=wsmp.at(3,3);
Compute_Bindgroup_Entries[5].binding=5;
Compute_Bindgroup_Entries[5].resource=wb.at(2,2);
Compute_Bindgroup_Entries[5].bufferBindOffset=0;
Compute_Bindgroup_Entries[5].bufferBindSize=sizeof(uint64_t);
WGPU_BindGroupEntries.at(0,0,0)=Compute_Bindgroup_Entries;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(wd.at(0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),6);
WGPU_ComputePassDescriptor.at(0,0,0)=computePassDescriptor;
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(wd.at(0,0));

  
multiSamp={};
multiSamp.count=0;
multiSamp.mask=-1;
shaderModuleDescV={};
shaderModuleDescF={};
shaderModuleDescV.code=vertexShader;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=frag_body;
// shaderModuleDescF.code=fragmentShader;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
WGpuColorTargetState colorTarget={};
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=15;
depthState={};
depthState.format=WGPU_TEXTURE_FORMAT_DEPTH24PLUS;
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
vertState={};
vertState.module=vs;
vertState.entryPoint="main";
vertState.numBuffers=0;
vertState.buffers=nullptr;
vertState.numConstants=0;
vertState.constants=nullptr;
priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_NONE; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
fragState={};
fragState.module=fs;
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&colorTarget;
u64_bfrSze.at(0,0)=sze.at(0,0)*sze.at(0,0)*4;
WGpuBufferDescriptor bufferDescriptorIn={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorOut={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
wbd.at(3,3)=bufferDescriptorIn;
wbd.at(4,4)=bufferDescriptorOut;
srcBuffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(3,3));
dstBuffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(4,4));
wb.at(3,3)=srcBuffer;
wb.at(4,4)=dstBuffer;
WGPUImageCopyBuffer videoFrmBfrDst={};
// videoFrmBfrDst.buffer=dstBuffer;
wicb.at(1,1)=videoFrmBfrDst;

// videoFrm.source; // must point to a WGpuImageBitmap (could also point to a HTMLVideoElement, HTMLCanvasElement or OffscreenCanvas, but those are currently unimplemented)
videoFrm.origin=oxy.at(0,0);
videoFrm.flipY=EM_FALSE;
videoSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_REPEAT;
videoSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_REPEAT;
videoSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_REPEAT;
videoSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
  // videoSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
videoSamplerDescriptor.lodMinClamp=0;
videoSamplerDescriptor.lodMaxClamp=32;
// videoSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
videoSamplerDescriptor.maxAnisotropy=1;
wsd.at(0,0)=videoSamplerDescriptor;
videoSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
wsmp.at(0,0)=videoSampler;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoTextureDescriptor.format=wtf.at(2,2);
videoTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
videoTextureDescriptor.width=sze.at(0,0);
videoTextureDescriptor.height=sze.at(0,0); // default = 1;
videoTextureDescriptor.depthOrArrayLayers=1;
videoTextureDescriptor.mipLevelCount=1;
videoTextureDescriptor.sampleCount=1;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT videoViewFormats[1]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0; // &videoViewFormats[0];
videoTextureDescriptor.viewFormats=nullptr; // &videoViewFormats[0];
wtd.at(2,2)=videoTextureDescriptor;
videoTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(2,2));
wt.at(2,2)=videoTexture;
videoTextureViewDescriptor.format=wtf.at(2,2);
videoTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
videoTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
videoTextureViewDescriptor.baseMipLevel=0; // default = 0
videoTextureViewDescriptor.mipLevelCount=1;
videoTextureViewDescriptor.baseArrayLayer=0; // default = 0
videoTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(2,2)=videoTextureViewDescriptor;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
texid.at(0,0)=77;
extTextureDescriptor.source=texid.at(0,0);
extTextureDescriptor.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
wetd.at(0,0)=extTextureDescriptor;
// extTexture=wgpu_device_import_external_texture(wd.at(0,0),&wetd.at(0,0));
// wet.at(0,0)=extTexture;

WGpuImageCopyTexture videoTextureCopy;
videoTextureCopy.texture=wt.at(2,2);
videoTextureCopy.mipLevel=0;
videoTextureCopy.origin=oxyz.at(0,0);
videoTextureCopy.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(0,0)=videoTextureCopy;
bufferDescriptorUni={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptorUni;
uniBuffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptorUni);
wb.at(0,0)=uniBuffer;
bufferBindingLayout1.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayout1.hasDynamicOffset=0,
bufferBindingLayout1.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayout1;
textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
// textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UNFILTERABLE_FLOAT;
// textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UINT;
textureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloat.multisampled=0;
samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_FILTERING;
// samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_NON_FILTERING;
wsbl.at(1,1)=samplerBindingLayout;
render_bindgroup_layout_entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_layout_entries[0].binding=0;
render_bindgroup_layout_entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
render_bindgroup_layout_entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
render_bindgroup_layout_entries[0].layout.buffer=wbbl.at(0,0);
render_bindgroup_layout_entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_layout_entries[1].binding=1;
render_bindgroup_layout_entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
render_bindgroup_layout_entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
render_bindgroup_layout_entries[1].layout.sampler=wsbl.at(1,1);
render_bindgroup_layout_entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_layout_entries[2].binding=2;
render_bindgroup_layout_entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
render_bindgroup_layout_entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
render_bindgroup_layout_entries[2].layout.texture=textureBindingLayoutFloat;
render_bindgroup_layout_entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_layout_entries[3].binding=3;
render_bindgroup_layout_entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
render_bindgroup_layout_entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_EXTERNAL_TEXTURE;
render_bindgroup_layout_entries[3].layout.externalTexture=extTextureBindingLayout;
wbgle.at(0,0)=render_bindgroup_layout_entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),3);
wbgl.at(0,0)=bindgroup_layout;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
WGpuRenderPipelineDescriptor renderPipelineDesc={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.primitive=priState;
renderPipelineDesc.fragment=fragState;
renderPipelineDesc.depthStencil=depthState;
renderPipelineDesc.layout=wrpl.at(0,0);
// renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc.multisample=multiSamp;
wrp.at(0,0)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc);
render_bindgroup_entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_entries[0].binding=0;
render_bindgroup_entries[0].resource=wb.at(0,0);
render_bindgroup_entries[0].bufferBindOffset=0;
render_bindgroup_entries[0].bufferBindSize=sizeof(uint64_t);
render_bindgroup_entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_entries[1].binding=1;
render_bindgroup_entries[1].resource=wsmp.at(0,0);
render_bindgroup_entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_entries[2].binding=2;
render_bindgroup_entries[2].resource=wtv.at(2,2);
render_bindgroup_entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
render_bindgroup_entries[3].binding=3;
render_bindgroup_entries[3].resource=wet.at(0,0);
wbge.at(0,0)=render_bindgroup_entries;
// renderBundleEncoderDescriptor.sampleCount=1;
// renderBundleEncoderDescriptor.depthStencilFormat=WGPU_TEXTURE_FORMAT_DEPTH24PLUS_STENCIL8;
// wrbed.at(0,0)=renderBundleEncoderDescriptor;
// renderBundleEncoder=wgpu_device_create_render_bundle_encoder(wd.at(0,0),&wrbed.at(0,0));
// wrbe.at(0,0)=renderBundleEncoder;
depthTextureViewDescriptor.format=WGPU_TEXTURE_FORMAT_DEPTH24PLUS;
depthTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
depthTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
depthTextureViewDescriptor.baseMipLevel=0; // default = 0
depthTextureViewDescriptor.mipLevelCount=1;
depthTextureViewDescriptor.baseArrayLayer=0; // default = 0
depthTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(0,0)=depthTextureViewDescriptor;
colorTextureViewDescriptor.format=wtf.at(0,0);
colorTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
colorTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
colorTextureViewDescriptor.baseMipLevel=0; // default = 0
colorTextureViewDescriptor.mipLevelCount=1;
colorTextureViewDescriptor.baseArrayLayer=0; // default = 0
colorTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(1,1)=colorTextureViewDescriptor;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor.format=WGPU_TEXTURE_FORMAT_DEPTH24PLUS;
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers=1;
depthTextureDescriptor.mipLevelCount=1;
depthTextureDescriptor.sampleCount=1;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT depthViewFormats[1]={WGPU_TEXTURE_FORMAT_DEPTH24PLUS};
depthTextureDescriptor.viewFormats=&depthViewFormats[0];
wtd.at(0,0)=depthTextureDescriptor;
depthTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(0,0));
wt.at(0,0)=depthTexture;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorTextureDescriptor.format=wtf.at(0,0);
colorTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
colorTextureDescriptor.width=sze.at(0,0);
colorTextureDescriptor.height=sze.at(0,0); // default = 1;
colorTextureDescriptor.depthOrArrayLayers=1;
colorTextureDescriptor.mipLevelCount=1;
colorTextureDescriptor.sampleCount=1;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
wtd.at(1,1)=colorTextureDescriptor;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),3);
wbg.at(0,0)=bindgroup;
u64_uni.at(0,0)=0;
u64_uni.at(3,3)=0;
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
// emscripten_set_main_loop_timing(2,1);
emscripten_set_main_loop((void(*)())raf,0,0);
// emscripten_request_animation_frame_loop(raf,0);
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
on.at(2,2)=0;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
WGPU_FEATURES_BITFIELD ftr=wgpu_adapter_or_device_get_features(wa.at(0,0));
deviceDesc.requiredFeatures=ftr;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(int hh){
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
sz(hh);
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
}

EM_JS(void,js_main,(),{

FS.mkdir('/shader');
FS.mkdir('/video');

const g=new GPUX();
let $H=Module.HEAPU8.buffer;
let $$1;

let running=0;
  
function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}
}


let vv=document.querySelector('#mv');
let vvi=document.querySelector('#mvi');
  
function flipImageData(imageData) {
const width = imageData.width;
const height = imageData.height;
const data = imageData.data;
for (let y = 0; y < height / 2; y++) {
for (let x = 0; x < width; x++) {
const topIndex = (y * width + x) * 4;
const bottomIndex = ((height - 1 - y) * width + x) * 4;
for (let c = 0; c < 4; c++) {
[data[topIndex + c], data[bottomIndex + c]] = [data[bottomIndex + c], data[topIndex + c]];
}
}
}
return imageData;
}
  /*
async function videoFramesG(){
let SiZ=window.innerHeight;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
Module.ccall("frm",null,['Number'],['Number'],SiZ,SiZ);
console.log("vid size: ",h$,", ",w$);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
let blank$=Math.max((((w$-h$))/2.0),0);
let nblank$=Math.max((((h$-w$)*1)/1),0);
let t=g.createKernel(function(v){
var P=v[this.thread.y][this.thread.x+this.constants.blank$];
return (P[0],P[1],P[2],P[3]);
}).setTactic("precision").setGraphical(false).setDynamicOutput(true).setOutput([SiZ,SiZ]).setStrictIntegers(false).setFixIntegerDivisionAccuracy(false);
t.setConstants({nblnk:nblank$,blnk:blank$});
let frrm=new Uint8ClampedArray($H,0,la);
$$1=t(vv);
frrm.set($$1,0);
FS.writeFile('/video/frame.gl',frrm);
setInterval(function(){
$$1=t(vv);
frrm.set($$1,0);
FS.writeFile('/video/frame.gl',frrm);
},16.6);
}
  */
async function videoFrames(){
// document.querySelector("#mvi").height=SiZ;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
let SiZ=window.innerHeight;
let tstSiZ=h$;
// document.querySelector("#mvi").height=h$;
// document.querySelector("#mvi").width=w$;
if(running==0){
// Module.ccall("frm",null,['Number'],['Number'],h$,h$);
setTimeout(function(){
Module.ccall("startWebGPU",null,"Number",h$);
console.log('Starting..');
running=1;
},500);
}
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=h$;
cnvb.height=SiZ;
cnv.width=h$;
cnvb.width=SiZ;
let offS=Math.floor((w$-h$)/2.0);
let la=nearestPowerOf2(((w$*h$*4)/4)*4);
const gl2=cnv.getContext('2d',{willReadFrequently:false,alpha:true}); // 
gl2.drawImage(vvi,offS,0,h$,h$,0,0,tstSiZ,tstSiZ);
let image=gl2.getImageData(0,0,tstSiZ,tstSiZ);
// let mageData=flipImageData(image);
let imageData=image.data;
let pixelData=new Uint8ClampedArray(imageData);
//  let frrm=new Uint8ClampedArray($H,0,imageData.length);
// Module.ccall("frm",null,['Number'],['Number'],h$,h$);
// frrm.set(pixelData);
FS.writeFile('/video/frame.gl',pixelData);
setInterval(function(){
gl2.drawImage(vvi,offS,0,h$,h$,0,0,tstSiZ,tstSiZ);
image=gl2.getImageData(0,0,tstSiZ,tstSiZ);
// mageData=flipImageData(image);
imageData=image.data;
pixelData=new Uint8ClampedArray(imageData);
//  frrm=new Uint8ClampedArray($H,0,imageData.length);
// frrm.set(imageData);
FS.writeFile('/video/frame.gl',pixelData);
},16.6);
}

  /*
async function GvideoFrames(){
let SiZ=window.innerHeight;
document.querySelector("#mvi").height=SiZ;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
document.querySelector("#mvi").height=h$;
document.querySelector("#mvi").width=w$;

let vv=document.querySelector('#mvi');
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
const context = cnvb.getContext("webgpu");
const gpu = navigator.gpu;
const format = gpu.getPreferredCanvasFormat();
const adapter = await gpu.requestAdapter();
const device = await adapter.requestDevice();
context.configure({ device, format, alphaMode: "opaque" });
let texture = device.createTexture({
format: "rgba8unorm",
size: [SiZ, SiZ, 2],
usage:GPUTextureUsage.COPY_DST|GPUTextureUsage.RENDER_ATTACHMENT|GPUTextureUsage.TEXTURE_BINDING,
}); 
// const gl2=cnv.getContext('2d',{colorType:'float32',willReadFrequently:false,alpha:true}); // 
const gl2=cnv.getContext('2d');
cnvb.height=SiZ;
cnvb.width=SiZ;
cnv.height=SiZ;
cnv.width=SiZ;
let offS=Math.floor((w$-h$)/2.0);
gl2.drawImage(vvi,offS,0,h$,h$,0,0,SiZ,SiZ);
let image=gl2.getImageData(0,0,SiZ,SiZ);
let imageData=image.data;
Module.ccall("frm",null,['Number'],['Number'],SiZ,SiZ);
let pixelData=new Uint8Array(imageData);

  
setInterval(function(){
gl2.drawImage(vv,0,0);
image=gl2.getImageData(0,0,SiZ,SiZ);
imageData=image.data;
pixelData=new Uint8Array(imageData);
device.queue.writeTexture({texture}, pixelData.buffer, {},{SiZ,SiZ});
// device.queue.writeTexture({texture,bytesPerRow: 4 * cnv.height,rowsPerImage: cnv.height,}, pixelData.buffer, pixelData.byteOffset,[SiZ,SiZ, 2]);
// device.queue.writeTexture({texture,bytesPerRow: 4 * cnv.height,rowsPerImage: cnv.height,}, pixelData.buffer, pixelData.byteOffset,[texture.size[0], texture.size[1], 2]);
const imageDataW = new Uint8Array(cnv.height * cnv.height * 4); // Assuming RGBA format
device.queue.readTexture({texture},imageDataW.buffer, {},{SiZ,SiZ});
// device.queue.readTexture({texture,bytesPerRow: 4 * cnv.width,rowsPerImage: cnv.height,}, imageDataW.buffer, imageDataW.byteOffset, [SiZ,SiZ, 2]);
// device.queue.readTexture({texture,bytesPerRow: 4 * cnv.width,rowsPerImage: cnv.height,}, imageDataW.buffer, imageDataW.byteOffset, [texture.size[0],texture.size[1], 2]);
const externalTexture=device.importExternalTexture({source:vv});
device.queue.readTexture({externalTexture},imageDataW.buffer,{},{SiZ,SiZ});
// device.queue.readTexture({externalTexture,bytesPerRow:4*vv.videoWidth,rowsPerImage:vv.videoHeight,
// },imageDataW.buffer,imageDataW.byteOffset);
FS.writeFile('/video/frame.gl',pixelData);

},16.666);

}
*/
function normalResStart(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#canvas').height=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#canvas').width=parseInt(window.innerHeight,10);
document.querySelector('#bcanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#di').click();
videoFrames();
},1500);
document.querySelector('#status').style.backgroundColor="green";
}
document.querySelector('#status').height=20;
document.querySelector('#status').width=parseInt(window.innerHeight,10);
const tem=document.querySelector('#tim');
const ban=document.querySelector('#menuBtn');
const sfr=document.querySelector('#slideframe');
var $lt=tem.innerHTML;
function grab$lt(){
$lt=Math.round($lt);
}
$lt=tem.innerHTML;
grab$lt();
const slo=new Slideout({'panel':document.querySelector('#panel'),'menu':document.querySelector('#menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
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
document.querySelector('#menu').addEventListener('click',function(){
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
  
document.querySelector('#startBtn').addEventListener('click',function(){
// var pth="https://glsl.1ink.us/wgsl/galaxy.wgsl";
  var pth=document.querySelector('#path').innerHTML;
// var pth="https://test.1ink.us/3arth/melt.wgsl";
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/shader.glsl',sfil);
document.querySelector('#stat').innerHTML='Downloaded Shader';
document.querySelector('#stat').style.backgroundColor='blue';
normalResStart();
}
});
ff.send(null);
});
  
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});

extern"C"{

void startWebGPU(int hh){
WGPU_Start(hh);
}

}

int main(){
js_main();
return 0;
}
