#include "../../include/vanilla/webgpu_egl.hpp"

WGpuBufferDescriptor bufferDescriptor_indice={};
WGpuBuffer indice_Buffer;
WGpuVertexAttribute vertAtt={};
WGpuVertexBufferLayout vertBufLayout={};
WGpuBufferDescriptor bufferDescriptor_vertex={};
WGpuBuffer vertex_Buffer;
WGpuBufferBindingLayout bufferBindingLayoutV={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuShaderModuleCompilationHint fragHint={};
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

WGpuRenderPassColorAttachment colorAttachment={};
WGpuRenderPassDepthStencilAttachment depthAttachment={};
WGpuTexture depthTexture;
WGpuTexture colorTexture;

WGpuTexture videoTexture;
WGpuSampler videoSampler={};
WGpuSampler resizeSampler={};
WGpuTexture __128bit_Texture__;

WGpuSamplerDescriptor resizeSamplerDescriptor={};
WGpuSamplerDescriptor videoSamplerDescriptor={};
WGpuTextureDescriptor depthTextureDescriptor={};
WGpuTextureDescriptor colorTextureDescriptor={};
WGpuTextureDescriptor videoTextureDescriptor={};

WGpuTextureDescriptor highbitTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuRenderPassDescriptor passDesc2={};
WGpuCanvasConfiguration config;
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuDepthStencilState depthState;
WGpuDepthStencilState depthState2;
WGpuVertexState vertState;
WGpuPrimitiveState priState;
WGpuFragmentState fragState;
WGpuFragmentState fragState2;
WGpuBufferDescriptor bufferDescriptor_iTime={};
WGpuBufferDescriptor bufferDescriptor_iResolution={};
WGpuBufferDescriptor bufferDescriptor_iFrame={};
WGpuBufferDescriptor bufferDescriptor_iTimeDelta={};
WGpuBufferDescriptor bufferDescriptorSrc={};
WGpuBufferDescriptor bufferDescriptorDst={};
WGpuBufferDescriptor bufferDescriptorVid={};
// WGpuPipelineLayoutDescriptor renderPipelineLayoutDesc;  // unused by webgpu.h
// WGpuPipelineLayout pipeline_layout=0;
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayout bindgroup_layout2=0;
WGpuBindGroupLayoutEntry bindgroup_layout_entries[8]={};
WGpuBindGroupEntry bindgroup_entries[8]={};
WGpuBindGroup bindgroup=0;
WGpuRenderPipeline renderPipeline1;
WGpuRenderPipeline renderPipeline2;
WGpuRenderPipelineDescriptor renderPipelineDesc;
WGpuRenderPipelineDescriptor renderPipelineDesc2;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuMultisampleState multiSamp2;
WGpuBuffer uni_iTime_Buffer;
WGpuBuffer uni_iTimeDelta_Buffer;
WGpuBuffer uni_iResolution_Buffer;
WGpuBuffer uni_iFrame_Buffer;
WGpuBuffer srcBuffer;
WGpuBuffer dstBuffer;
WGpuBuffer vidBuffer;
WGpuBufferBindingLayout bufferBindingLayoutR={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayout1={};
WGpuTextureBindingLayout textureBindingLayout2={};
WGpuTextureBindingLayout textureBindingLayout3={};
WGpuSamplerBindingLayout samplerBindingLayout={};
WGPUImageCopyBuffer videoFrmBfrSrc={};
WGpuColorTargetState colorTarget={};
WGpuColorTargetState colorTarget2={};
WGpuCommandEncoder wceA={};
WGpuCommandEncoder wceB={};
WGpuSampler iChannel0Sampler={};
WGpuSamplerDescriptor iChannel0SamplerDescriptor={};
WGPU_TEXTURE_FORMAT canvasViewFormats[1];
WGPU_TEXTURE_FORMAT colorViewFormats[1];
WGPU_TEXTURE_FORMAT depthViewFormats[1];
WGPU_TEXTURE_FORMAT canvasFormat;
double szh,szw;
int szhI,szwI;

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
void * fram;
uint8_t * ufram;
float * ffram;

i_tensor on=i_tensor{2,2};
i_tensor sze=i_tensor{2,2};
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
wpl_tensor wrpl=wpl_tensor{2,2};
wb_tensor wb=wb_tensor{8,8};
wbgle_tensor wbgle=wbgle_tensor{2,2};
wbge_tensor wbge=wbge_tensor{2,2};
wbgl_tensor wbgl=wbgl_tensor{2,2};
wbg_tensor wbg=wbg_tensor{2,2};
wrpd_tensor wrpd=wrpd_tensor{2,2};
wrpca_tensor wrpca=wrpca_tensor{2,2};
wbbl_tensor wbbl=wbbl_tensor{2,2};
wbd_tensor wbd=wbd_tensor{8,8};
wao_tensor wao=wao_tensor{2,2};
wdd_tensor wdd=wdd_tensor{2,2};
u64_tensor u64_uni=u64_tensor{8,8};
u64_tensor u64_siz=u64_tensor{1,1};
wrbe_tensor wrbe=wrbe_tensor{2,2};
wrbed_tensor wrbed=wrbed_tensor{2,2};
wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
wt_tensor wt=wt_tensor{3,3};
wtd_tensor wtd=wtd_tensor{3,3};
wtvd_tensor wtvd=wtvd_tensor{2,2};
wtf_tensor wtf=wtf_tensor{5,5};
wtv_tensor wtv=wtv_tensor{2,2};
wms_tensor wms=wms_tensor{2,2};
wsm_tensor wsm=wsm_tensor{2,2};
wsmd_tensor wsmd=wsmd_tensor{2,2};
wcts_tensor wcts=wcts_tensor{2,2};
wdss_tensor wdss=wdss_tensor{2,2};
wvs_tensor wvs=wvs_tensor{2,2};
wps_tensor wps=wps_tensor{2,2};
wfs_tensor wfs=wfs_tensor{2,2};
wrpid_tensor wrpid=wrpid_tensor{2,2};
wtbl_tensor wtbl=wtbl_tensor{2,2};
c_tensor wgsl=c_tensor{2,2};
c32_tensor wgsl32=c32_tensor{2,2};
wsd_tensor wsd=wsd_tensor{3,3};
ws_tensor wgpu_sampler=ws_tensor{3,3};
wsbl_tensor wsbl=wsbl_tensor{3,3};
wvbl_tensor wvbl=wvbl_tensor{2,2};
wict_tensor wict=wict_tensor{3,3};
u64_tensor u64_bfrSze=u64_tensor{4,4};
wicb_tensor wicb=wicb_tensor{3,3};
js_data_tensor frame_tensor=js_data_tensor{2,2};
js_data_tensorf frame_tensorf=js_data_tensorf{2,2};
js_data_tensorGL frame_tensorGL=js_data_tensorGL{2,2};

/*
mouse_tensor mms=mouse_tensor{2,2};
mouse_tensor mms2=mouse_tensor{2,2};

inline struct{
boost::compute::double_ wi=0.0;
boost::compute::double_ hi=0.0;
}mouse;

inline EMSCRIPTEN_RESULT retCl,retMu,retMd,retMv,retSa,retSb,retSc;

EM_BOOL ms_clk(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEDOWN&&e->buttons!=0){
ms_l=true;
}
if(eventType==EMSCRIPTEN_EVENT_MOUSEUP){
ms_l=false;
}}
return EM_TRUE;
}

EM_BOOL ms_mv(int32_t eventType,const EmscriptenMouseEvent * e,void * userData){
if(e->screenX!=0&&e->screenY!=0&&e->clientX!=0&&e->clientY!=0&&e->targetX!=0&&e->targetY!=0){
if(eventType==EMSCRIPTEN_EVENT_MOUSEMOVE&&(e->movementX!=0||e->movementY!=0)){
mms2.at(0,0)=e->clientX;
mms2.at(0,1)=e->clientY;
}}
return EM_TRUE;
}
*/

inline char wgl_cmp_src[2000]=
"@group(0)@binding(0)var <storage,read> inputBuffer: array <f32,64>;\n"
"@group(0)@binding(1)var <storage,read_write> outputBuffer: array <f32,64>;\n"
"@group(0)@binding(2)var textureIN: texture_2d <f32>;\n"
"@group(0)@binding(3)var textureOUT: texture_storage_2d <rgba8unorm,write>;\n"
// "@group(0)@binding(4)var resizeSampler:sampler;\n"
// "@group(0)@binding(4)var<storage,read_write>vertexBuffer:array<u32,64>;\n"
"@compute@workgroup_size(1,1,1)\n"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){\n"
"var buffSizIn:f32=inputBuffer[0];\n"
"var buffSizOut:f32=inputBuffer[1];\n"
"var sizeINu=textureDimensions(textureIN,0);\n"
"var sizeINf:f32=f32(sizeINu.x);\n"
"var sizeOUTf=inputBuffer[1];\n"
"var sizeOUTu:u32=u32(sizeOUTf);\n"
"for(var y=0u;y<sizeOUTu;y++){\n"
"for(var x=0u;x<sizeOUTu;x++){\n"
// "if(x*y<=sizeOUTu*sizeOUTu){\n"
"var INtexCoord:vec2<u32>=vec2<u32>(x,y)/vec2<u32>(sizeINu.x,sizeINu.y);\n"
"var colorTest:vec4<f32>=textureLoad(textureIN,INtexCoord,0);\n"
"var color:vec4<f32>=vec4<f32>(0.0f,0.88f,0.0f,1.0f);\n"
// "let color32u:vec4<f32>=clamp(vec4<f32>(round(color*255.0)),vec4<u32>(0u,0u,0u,0u),vec4<u32>(255u,255u,255u,255u));\n"
"outputBuffer[0]=777.777;\n"
"outputBuffer[1]=2048.2048;\n"
"textureStore(textureOUT,vec2<u32>(x,y),color);\n"
// "}"
"}"
"}"
"}";

const char * vertexShaderA =
"@vertex\n"
"fn main(@location(0) position: vec4<f32>,@location(1) uv: vec2<f32>) -> @builtin(position) vec4<f32> {\n"
"return vec4<f32>(position.xyzw);"
"}\n";

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

const char * vertexShaderL=
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
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(1.0f,0.0f),\n"
"vec2<f32>(0.0f,0.0f),\n"
"vec2<f32>(1.0f,1.0f),\n"
"vec2<f32>(0.0f,0.0f),\n"
"vec2<f32>(0.0f,1.0f)\n"
");\n"
"var output : VertexOutput;\n"
"output.Position=vec4(pos[VertexIndex],0.0f,1.0f);\n"
"output.fragUV=uv[VertexIndex];\n"
"return output;\n"
"}\n";

const char * frag_body=
"@group(0) @binding(0) var <uniform> iTime : u32;\n"
"@group(0) @binding(1) var videoSampler : sampler;\n"
"@group(0) @binding(2) var videoTexture : texture_2d <f32>;\n"
// "@group(0) @binding(3) var extTexture : texture_external;\n"
"@fragment\n"
"fn main(@location(0) fragUV : vec2<f32>) ->\n"
"@location(0) vec4<f32> {\n"
"return textureSample(videoTexture,videoSampler,fragUV);"
"}\n";

const char * fragHeader="";

const char * fragEntry="main_1";

const char * Fnm=reinterpret_cast<const char *>("/shader/shader.wgsl");
const char * FnmB=reinterpret_cast<const char *>("/shader/shader.wgsl");

char * result=NULL;
char * results=NULL;
float * resultf=NULL;
float * resultsf=NULL;
long int length=0;

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
wbgle_tensor WGPU_BindGroupLayoutEntries=wbgle_tensor{1,1,2};
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
wtv_tensor WGPU_TextureView=wtv_tensor{3,3,3};
uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
wced_tensor WGPU_CommandEncoderDescriptor=wced_tensor{1,1,1};
wbms_tensor WGPU_BufferStatus=wbms_tensor{1,1,1};

uint32_t workgroupSize;
uint32_t OutputBufferUnits;
uint32_t OutputBufferBytes;
uint32_t InputBufferUnits;
uint32_t InputBufferBytes;
uint64_t WGPU_InputRangeSize;

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
WGpuBuffer uniBuffer=0;
WGpuShaderModule cs=0;
WGpuCommandBuffer commandBuffer=0;
WGpuCommandEncoder encoder=0;
WGpuComputePassEncoder computePass=0;
WGpuBindGroup bindGroup=0;
WGpuBindGroup bindGroupB=0;
WGpuPipelineLayout pipelineLayout=0;
WGpuQuerySet querySet=0;
WGpuComputePassDescriptor computePassDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[8]={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntriesB[2]={};
WGpuBindGroupEntry bindGroupEntry[8]={};
WGpuBindGroupEntry bindGroupEntryB[2]={};
WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayout1={1,18,2};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};

WGpuBufferDescriptor bufferDescriptorI={};
WGpuBufferDescriptor bufferDescriptorO={};
WGpuBufferDescriptor bufferDescriptorM={};
WGpuBufferDescriptor bufferDescriptorC={};
// 14 = R32FLOAT   34 = RGBA32UINT
WGpuTextureDescriptor textureDescriptorA={};
WGpuTextureDescriptor textureDescriptorB={};
WGpuTextureViewDescriptor textureViewDescriptorA={};
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

struct Vertex{
GLfloat position[4];
};

Vertex nvertices[]={
{1.0f,1.0f,0.0f,1.0f},
{-1.0f,1.0f,0.0f,1.0f},
{-1.0f,-1.0f,0.0f,1.0f},
{1.0f,1.0f,0.0f,1.0f},
{1.0f,-1.0f,0.0f,1.0f},
{-1.0f,-1.0f,0.0f,1.0f}
};

Vertex lvertices[]={
{-1.0f,-1.0f,1.0f,1.0f},
{1.0f,-1.0f,1.0f,1.0f},
{1.0f,1.0f,1.0f,1.0f},
{-1.0f,1.0f,1.0f,1.0f},
{-1.0f,-1.0f,-1.0f,1.0f},
{1.0f,-1.0f,-1.0f,1.0f},
{1.0f,1.0f,-1.0f,1.0f},
{-1.0f,1.0f,1.0f,1.0f}
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

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
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
// EM_ASM({
// document.getElementById('outText').innerHTML=$0+' '+$1;
// },WGPU_ResultBuffer.at(0,0,0)[0],WGPU_ResultBuffer.at(0,0,0)[1]);
// wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&wict.at(0,0),&wb.at(3,3),1,64,1);
// std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
// if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// }
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
*/
return;
};

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
results=reinterpret_cast<char *>(result);
return results;
}
return nullptr;
}

const char * Fnm2=reinterpret_cast<const char *>("/video/frame.gl");

void getCode(const char * Fnm){
// const char * frag_body=(char *)rd_fl(Fnm);
wgsl.at(0,0)=frag_body;
return;
}

inline boost::function<EM_BOOL()>render=[](){
// void raf(){
/*
if(ms_l==true){
mms.at(0,1)=round(mms2.at(0,0)/i_size.at(0,1));
mms.at(1,1)=round((mms2.at(0,1))/i_size.at(0,1));
}
// retCl=emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
// retMd=emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(ms_l==true){
// retMv=emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_mv);
// retMu=emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,0,(EM_BOOL)0,ms_clk);
if(clk_l==true){
const long xxx=mms2.at(0,0);
const long yyy=mms2.at(0,1);
mms.at(0,0)=float(xxx);
mms.at(1,0)=float((i_size.at(0,1)-yyy));
clk_l=false;
}
mms.at(2,0)=float(mms2.at(0,0));
mms.at(2,1)=float(i_size.at(0,1)-mms2.at(0,1));
  //  glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,0),mms.at(1,0));
}
else{
clk_l=true;
}
*/
u64_uni.at(1,1)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u64_uni.at(0,0)=u_time.time_spana.count()*1000;
u64_uni.at(3,3)=u_time.time_spanb.count()*1000;
// u64_uni.at(4,4)=u_time.time_spanb.count()/1.0f;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
// colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(wcc.at(0,0)),0);
colorAttachment.view=wtv.at(1,1);
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
// colorAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
colorAttachment.clearValue.r=0.8;
colorAttachment.clearValue.g=0.0;
colorAttachment.clearValue.b=0.3;
colorAttachment.clearValue.a=1.0;
wrpca.at(0,0)=colorAttachment;
// depthAttachment={};
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0;
depthAttachment.stencilClearValue=0;
depthAttachment.depthReadOnly=0;
depthAttachment.stencilReadOnly=0;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment.depthStoreOp=WGPU_STORE_OP_STORE;
depthAttachment.stencilLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment.stencilStoreOp=WGPU_STORE_OP_STORE;
wrpdsa.at(0,0)=depthAttachment;
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(0,0);
wrpd.at(0,0)=passDesc;
passDesc2.numColorAttachments=0;
passDesc2.depthStencilAttachment=wrpdsa.at(0,0);
wrpd.at(1,1)=passDesc2;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,0));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;
      // Compute Pass

// raN=rNd4(256);
WGPU_InputBuffer.at(0,0,0)[0]=szef.at(0,0);
WGPU_InputBuffer.at(0,0,0)[1]=float(1024);szef.at(0,0);
WGPU_InputBuffer.at(0,0,0)[2]=u64_uni.at(0,0)/22.0f;
WGPU_InputBuffer.at(0,0,0)[3]=u64_uni.at(1,1)*0.001f;
WGPU_InputBuffer.at(0,0,0)[4]=float(u64_uni.at(1,1));
  
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
wict.at(2,2)=WGPU_Input_Image;
wict.at(0,0)=WGPU_Output_Image;
  
// ffram=(float *)rd_frm_f(Fnm2);
std::ifstream fram(Fnm2,std::ios::binary);
std::vector<GLubyte> data((std::istreambuf_iterator<char>(fram)),(std::istreambuf_iterator<char>()));
frame_tensorGL.at(0,0)=data;
// wg_size.at(0,0,0)=int(floor(std::cbrt(sze.at(0,0)*sze.at(0,0))))+1;
// int wgs=int(floor(std::cbrt((sze.at(0,0)*sze.at(0,0))/1000)));
wgpu_queue_write_texture(wq.at(0,0),&wict.at(2,2),&frame_tensorGL.at(0,0),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);

WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(wd.at(0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&WGPU_ComputePassDescriptor.at(0,0,0));
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);

wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&WGPU_Input_Image,&WGPU_ColorBuffer.at(0,0,0),1024,0,1,1,1);
  
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),1,1,1);
// wgpu_command_encoder_copy_texture_to_texture(WGPU_CommandEncoder.at(0,0,0),&wict.at(0,0),&wict.at(1,1),sze.at(0,0),sze.at(0,0),1);
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,64*sizeof(float));

wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));

    //  get result for test
// WGPU_ResultBuffer.at(0,0,0)[0]=1010;
// WGPU_ResultBuffer.at(0,0,0)[1]=111.111;
WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,64*sizeof(float));
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_BufferRange.at(0,0,1),0,&WGPU_ResultBuffer.at(0,0,0),64*sizeof(float));
WGPU_ResultBuffer.at(0,0,0)[2]=1024;
WGPU_ResultBuffer.at(0,0,0)[3]=1024.1024;
  EM_ASM({
document.getElementById('outText').innerHTML='Buffer at [0]:'+$0;
document.getElementById('outText').innerHTML+='Buffer at [1]:'+$1;
document.getElementById('outText').innerHTML+='Buffer at [2] (int):'+$2;
document.getElementById('outText').innerHTML+='Buffer at [3] (float):'+$3;
},WGPU_ResultBuffer.at(0,0,0)[0],WGPU_ResultBuffer.at(0,0,0)[1],WGPU_ResultBuffer.at(0,0,0)[2],WGPU_ResultBuffer.at(0,0,0)[3]);

 // wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
//  WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
// wgpu_object_destroy(WGPU_Buffers.at(2,0,2));
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_ComputePassCommandEncoder.at(0,0,0),wb.at(3,3),0,WGPU_Buffers.at(1,1,1),0,sizeof(vertices));
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
  // wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,64,1,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
  // wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,64,1,1);
// wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&wb.at(3,3),1,64,1);
// wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),wb.at(3,3),0,WGPU_ResultBuffer.at(0,0,0),sizeof(vertices));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one_and_destroy(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
//  if(WGPU_BufferStatus.at(0,0,0)!=3){
// wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
//wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,OutputBufferBytes);
// }
  // Render pass A (color)

wceA=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(0,0)=wceA;
// wgpu_command_encoder_copy_texture_to_texture(wce.at(0,0),&wict.at(0,0),&wict.at(1,1),sze.at(0,0),sze.at(0,0),1);

wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
/*
void wgpu_command_encoder_copy_texture_to_texture(WGpuCommandEncoder commandEncoder, const WGpuImageCopyTexture *source NOTNULL, const WGpuImageCopyTexture *destination NOTNULL, uint32_t copyWidth, uint32_t copyHeight _WGPU_DEFAULT_VALUE(1), uint32_t copyDepthOrArrayLayers _WGPU_DEFAULT_VALUE(1));
*/

  // wgpu_queue_write_texture(wq.at(0,0),&wict.at(1,1),&frame_tensorGL.at(0,0),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);
// wgpu_queue_write_texture(wq.at(0,0),&wict.at(2,2),&frame_tensorGL.at(0,0),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);

// wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(1,1),0,&u64_uni.at(1,1),sizeof(uint64_t));
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&u64_uni.at(2,2),sizeof(uint64_t));
//  wgpu_render_pass_encoder_set_index_buffer(wrpe.at(0,0),wb.at(4,4),WGPU_INDEX_FORMAT_UINT32,0,36*sizeof(uint32_t));
// wgpu_render_pass_encoder_set_vertex_buffer(wrpe.at(0,0),0,wb.at(3,3),0,sizeof(vertices));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,szef.at(0,0),szef.at(0,0),0.0,1.0);
// wgpu_render_pass_encoder_draw_indexed(wrpe.at(0,0),36,1,0,0,0);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
wceA={};
  // Render pass B (depth)
wceB=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(1,1)=wceB;
  wgpu_command_encoder_copy_texture_to_texture(wce.at(1,1),&wict.at(0,0),&wict.at(1,1),sze.at(0,0),sze.at(0,0),1);

wrpe.at(1,1)=wgpu_command_encoder_begin_render_pass(wce.at(1,1),&wrpd.at(1,1));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(1,1),wrp.at(1,1));
wgpu_encoder_set_bind_group(wrpe.at(1,1),0,wbg.at(0,0),0,0);
// wgpu_render_pass_encoder_set_index_buffer(wrpe.at(1,1),wb.at(4,4),WGPU_INDEX_FORMAT_UINT32,0,36*sizeof(uint32_t));
// wgpu_render_pass_encoder_set_vertex_buffer(wrpe.at(1,1),0,wb.at(3,3),0,sizeof(vertices));
wgpu_render_pass_encoder_set_viewport(wrpe.at(1,1),0.0,0.0,szef.at(0,0),szef.at(0,0),0.0,1.0);
// wgpu_render_pass_encoder_draw_indexed(wrpe.at(1,1),36,1,0,0,0);
wgpu_render_pass_encoder_draw(wrpe.at(1,1),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(1,1));
wcb.at(1,1)=wgpu_command_encoder_finish(wce.at(1,1));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(1,1));
wceB={};
return EM_TRUE;
};

void raf(){
render();
}

void ObtainedWebGpuDeviceStart(WGpuDevice resultD, void *userData){
workgroupSize=64;
OutputBufferUnits=64;
OutputBufferBytes=64*4;
InputBufferUnits=64;
InputBufferBytes=64*4;
WGPU_InputRangeSize=OutputBufferBytes;
float * WGPU_Result_Array=new float[OutputBufferBytes];
float * WGPU_Input_Array=new float[InputBufferBytes];
uint32_t * WGPU_Color_Input_Array=new uint32_t[InputBufferBytes];
std::vector<float>color_input(InputBufferUnits);
std::vector<uint8_t>input(InputBufferBytes);
std::vector<uint8_t>outputd(OutputBufferBytes);
std::vector<uint8_t>outpute(OutputBufferBytes);
// inline boost::function<void(WGpuDevice,void *)>ObtainedWebGpuDeviceStart=[](WGpuDevice result, void *userData){
wd.at(0,0)=resultD;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
// const char * frag_body=(char*)rd_fl(Fnm);
//      #include <string.h>
//char full_frag_body[strlen(fragHeader) + strlen(frag_body) + 1];
//strcpy(full_frag_body, fragHeader);
//strcat(full_frag_body, frag_body);
      /*
clk_l=true;
mms.at(0,0)=0.5*float_size.at(0,0);
// mms.at(0,1)=0.5*(mms2.at(0,1)-float_size.at(0,0));
mms.at(0,1)=0.5*float_size.at(0,0);
mms.at(1,0)=0.5*float_size.at(0,0);
mms.at(1,1)=0.5*float_size.at(0,0);
// mms.at(1,1)=0.5*(mms2.at(0,1)-float_size.at(0,0));
mms.at(2,0)=float_size.at(0,0)*0.5;
mms.at(2,1)=(mms2.at(0,1)-float_size.at(0,0))*0.5;
  //  glUniform4f(uni_mse,mms.at(2,0),mms.at(2,1),mms.at(0,1),mms.at(1,0));
      */
// canvasFormat=navigator_gpu_get_preferred_canvas_format();
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGB10A2UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
// canvasFormat=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM_SRGB;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RG11B10UFLOAT;
// canvasFormat=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
wtf.at(3,3)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
wtf.at(4,4)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(3,3)=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
canvasViewFormats[0]={wtf.at(3,3)};
config=WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
config.device=wd.at(0,0);
config.format=wtf.at(0,0);
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
config.viewFormats=&canvasViewFormats[0];
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
// config.alphaMode=WGPU_CANVAS_ALPHA_MODE_OPAQUE;
config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
// config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_SRGB;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_element_css_size("canvas",&szh,&szw);
emscripten_get_canvas_element_size("canvas",&szhI,&szwI);
u64_siz.at(0,0)=(szhI/4)*4;
szef.at(0,0)=float((szh/4.0)*4.0);
sze.at(0,0)=float((szh/4.0)*4.0);
sze.at(0,1)=280;
sze.at(1,1)=720;
szef.at(1,1)=float(sze.at(1,1));

// sze.at(1,1)=EM_ASM_INT({var sz=parseInt(document.querySelector("#mvi").videoHeight);return sz;});
WGPU_UserData.at(0,0,0)=userData;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
textureDescriptorA.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorA.format=wtf.at(0,0);
textureDescriptorA.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorA.width=sze.at(1,1);
textureDescriptorA.height=sze.at(1,1); // default = 1;
textureDescriptorA.depthOrArrayLayers=1;
textureDescriptorA.mipLevelCount=1;
textureDescriptorA.sampleCount=1;
textureDescriptorA.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT textureAviewFormats[1]={wtf.at(0,0)};
textureDescriptorA.numViewFormats=0; // &textureAviewFormats[0];
textureDescriptorA.viewFormats=nullptr; // &textureAviewFormats[0];
textureDescriptorB.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorB.format=wtf.at(0,0);
textureDescriptorB.usage=WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorB.width=sze.at(0,0);
textureDescriptorB.height=sze.at(0,0); // default = 1;
textureDescriptorB.depthOrArrayLayers=1;
textureDescriptorB.mipLevelCount=1;
textureDescriptorB.sampleCount=1;
textureDescriptorB.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT textureBviewFormats[1]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0; // &textureBviewFormats[0];
videoTextureDescriptor.viewFormats=nullptr; // &textureBviewFormats[0];
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_TextureDescriptor.at(0,0,1)=textureDescriptorB;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));
WGpuOrigin3D xyz={};
xyz.x=0;
xyz.y=0;
xyz.z=0;
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Input_Image.origin=xyz;
WGPU_Input_Image.aspect=WGPU_TEXTURE_ASPECT_ALL;
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_Output_Image.origin=xyz;
WGPU_Output_Image.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(2,2)=WGPU_Input_Image;
wict.at(0,0)=WGPU_Output_Image;
textureBindingLayout1.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UINT;
textureBindingLayout1.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout1.multisampled=0;
wtbl.at(0,0)=textureBindingLayout1;
textureBindingLayout2.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayout2.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout2.multisampled=0;
wtbl.at(1,1)=textureBindingLayout2;
textureBindingLayout3.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_DEPTH;
textureBindingLayout3.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout3.multisampled=0;
wtbl.at(2,2)=textureBindingLayout3;
textureViewDescriptorA.format=wtf.at(0,0);
textureViewDescriptorA.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorA.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorA.baseMipLevel=0; // default = 0
textureViewDescriptorA.mipLevelCount=1;
textureViewDescriptorA.baseArrayLayer=0; // default = 0
textureViewDescriptorA.arrayLayerCount=1;
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorA;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
WGPU_ColorBuffer.at(0,0,0)=WGPU_Color_Input_Array;
bufferDescriptorI={InputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
bufferDescriptorO={OutputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
// WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
// if(WGPU_BufferStatus.at(0,0,0)!=1){
// wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// }
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=512;
WGPU_Output_Buffer.rowsPerImage=64;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=512;
WGPU_Mapped_Buffer.rowsPerImage=64;
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
wgpu_sampler.at(3,3)=resizeSampler;
raN=rNd4(256);
input[0]=raN;
  // WGPU_InputBuffer.at(0,0,0)[0]=raN;
// std::cout << "Random input:" << std::endl;
// std::cout << raN << std::endl;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(wd.at(0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayout1;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,0));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
bindGroupLayoutEntries[2].binding=2;
bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindGroupLayoutEntries[2].layout.texture=wtbl.at(1,1);
bindGroupLayoutEntries[3].binding=3;
bindGroupLayoutEntries[3].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
bindGroupLayoutEntries[3].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
bindGroupLayoutEntries[4].binding=4;
bindGroupLayoutEntries[4].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
bindGroupLayoutEntries[4].layout.sampler=wsbl.at(0,0);
    /*
bindGroupLayoutEntries[5].binding=5;
bindGroupLayoutEntries[5].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[5].type=1;
bindGroupLayoutEntries[5].layout.buffer=wbbl.at(1,1);
*/
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(wd.at(0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),5);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(wd.at(0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(wd.at(0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
bindGroupEntry[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=InputBufferBytes;
bindGroupEntry[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=OutputBufferBytes;
bindGroupEntry[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindGroupEntry[2].binding=2;
bindGroupEntry[2].resource=wtv.at(3,3);
bindGroupEntry[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindGroupEntry[3].binding=3;
bindGroupEntry[3].resource=wtv.at(4,4); 
bindGroupEntry[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindGroupEntry[4].binding=4;
bindGroupEntry[4].resource=wgpu_sampler.at(3,3);
/*
bindGroupEntry[5].binding=5;
bindGroupEntry[5].resource=wb.at(3,3);
bindGroupEntry[5].bufferBindOffset=0;
bindGroupEntry[5].bufferBindSize=sizeof(vertices);
*/
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(wd.at(0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),5);
WGPU_ComputePassDescriptor.at(0,0,0)=computePassDescriptor;
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(wd.at(0,0));
multiSamp={};
multiSamp.count=0;
multiSamp.mask=-1;
multiSamp2={};
multiSamp2.count=4; // 4;
multiSamp2.mask=-1;
wms.at(1,1)=multiSamp2;
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=WGPU_COLOR_WRITE_ALL;
      /*
colorTarget.blend.color.operation=WGPU_BLEND_OPERATION_ADD;
colorTarget.blend.color.srcFactor=WGPU_BLEND_FACTOR_ZERO;
colorTarget.blend.color.dstFactor=WGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
colorTarget.blend.alpha.operation=WGPU_BLEND_OPERATION_ADD;
colorTarget.blend.alpha.srcFactor=WGPU_BLEND_FACTOR_ZERO;
colorTarget.blend.alpha.dstFactor=WGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
*/
wcts.at(0,0)=colorTarget;
wtf.at(1,1)=WGPU_TEXTURE_FORMAT_INVALID;
wtf.at(2,2)=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
colorTarget2.format=wtf.at(1,1);
// colorTarget2.writeMask=WGPU_COLOR_WRITE_ALL;
wcts.at(1,1)=colorTarget2;
shaderModuleDescV={};
shaderModuleDescF={};
fragHint.entryPointName=fragEntry;
shaderModuleDescF.code=wgsl.at(0,0);
// shaderModuleDescF.hint=fragHint;
shaderModuleDescV.code=vertexShader;
wsmd.at(0,0)=shaderModuleDescV;
wsmd.at(1,1)=shaderModuleDescF;
vs=wgpu_device_create_shader_module(wd.at(0,0),&wsmd.at(0,0));
wsm.at(0,0)=vs;
fs=wgpu_device_create_shader_module(wd.at(0,0),&wsmd.at(1,1));
wsm.at(1,1)=fs;
bufferDescriptor_vertex={sizeof(vertices),WGPU_BUFFER_USAGE_VERTEX|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(3,3)=bufferDescriptor_vertex;
vertAtt.offset=0;
vertAtt.shaderLocation=0;
vertAtt.format=WGPU_VERTEX_FORMAT_FLOAT32X4;
vertBufLayout.numAttributes=1;
vertBufLayout.attributes=&vertAtt;  //  * ?
vertBufLayout.arrayStride=sizeof(Vertex);
vertBufLayout.stepMode=WGPU_VERTEX_STEP_MODE_VERTEX;
wvbl.at(0,0)=vertBufLayout;
bufferBindingLayoutV.type=WGPU_BUFFER_BINDING_TYPE_STORAGE;
bufferBindingLayoutV.hasDynamicOffset=0,
bufferBindingLayoutV.minBindingSize=sizeof(vertices);
wbbl.at(1,1)=bufferBindingLayoutV;
vertex_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(3,3));
wb.at(3,3)=vertex_Buffer;
bufferDescriptor_indice={36*sizeof(uint32_t),WGPU_BUFFER_USAGE_INDEX|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(4,4)=bufferDescriptor_indice;
indice_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(4,4));
wb.at(4,4)=indice_Buffer;
depthState={};
depthState.format=WGPU_TEXTURE_FORMAT_INVALID;
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_INVALID;
wdss.at(0,0)=depthState;
depthState2={};
depthState2.format=wtf.at(2,2);
depthState2.depthWriteEnabled=0;
depthState2.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
// depthState2.depthCompare=WGPU_COMPARE_FUNCTION_ALWAYS;
wdss.at(1,1)=depthState2;
vertState={};
vertState.module=wsm.at(0,0);
vertState.entryPoint="main";
vertState.numBuffers=0;
// vertState.numBuffers=1;
// vertState.buffers=&wvbl.at(0,0);
vertState.numConstants=0;
vertState.constants=nullptr;
wvs.at(0,0)=vertState;
priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32;
priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32;
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_NONE; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.
wps.at(0,0)=priState;
fragState={};
fragState.module=wsm.at(1,1);
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&wcts.at(0,0);
wfs.at(0,0)=fragState;
fragState2={};
fragState2.module=wsm.at(1,1);
fragState2.entryPoint="main";
fragState2.numTargets=0;
// fragState2.targets=&wcts.at(1,1);
wfs.at(1,1)=fragState;
  u64_bfrSze.at(0,0)=sze.at(1,1)*sze.at(1,1);
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
videoSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
videoSamplerDescriptor.lodMinClamp=0;
videoSamplerDescriptor.lodMaxClamp=32;
// videoSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
videoSamplerDescriptor.maxAnisotropy=1;
wsd.at(0,0)=videoSamplerDescriptor;
videoSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
wgpu_sampler.at(2,2)=videoSampler;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoTextureDescriptor.format=wtf.at(0,0);
videoTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
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
videoTextureViewDescriptor.format=wtf.at(0,0);
videoTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
videoTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
videoTextureViewDescriptor.baseMipLevel=0; // default = 0
videoTextureViewDescriptor.mipLevelCount=1;
videoTextureViewDescriptor.baseArrayLayer=0; // default = 0
videoTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(2,2)=videoTextureViewDescriptor;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;

WGpuImageCopyTexture videoTextureCopy;
videoTextureCopy.texture=wt.at(2,2);
videoTextureCopy.mipLevel=0;
videoTextureCopy.origin=xyz;
videoTextureCopy.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(1,1)=videoTextureCopy;
iChannel0SamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
iChannel0SamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
iChannel0SamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
iChannel0SamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
iChannel0SamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
// iChannel0SamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
iChannel0SamplerDescriptor.lodMinClamp=0;
iChannel0SamplerDescriptor.lodMaxClamp=32;
// iChannel0SamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
iChannel0SamplerDescriptor.maxAnisotropy=1;
wsd.at(0,0)=iChannel0SamplerDescriptor;
iChannel0Sampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
wgpu_sampler.at(0,0)=iChannel0Sampler;
samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_FILTERING;
wsbl.at(1,1)=samplerBindingLayout;
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
bindgroup_layout_entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[0].binding=0;
bindgroup_layout_entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[0].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[1].binding=4;
bindgroup_layout_entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[1].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[2].binding=3;
bindgroup_layout_entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[2].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[3].binding=2;
bindgroup_layout_entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[3].layout.texture=wtbl.at(1,1);
bindgroup_layout_entries[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[4].binding=1;
bindgroup_layout_entries[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
bindgroup_layout_entries[4].layout.sampler=wsbl.at(0,0);
   /* 
   
bindgroup_layout_entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[3].binding=3;
bindgroup_layout_entries[3].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindgroup_layout_entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[3].layout.buffer=wbbl.at(1,1);
bindgroup_layout_entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[3].binding=3;
bindgroup_layout_entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[3].layout.texture=wtbl.at(0,0);
bindgroup_layout_entries[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[4].binding=4;
bindgroup_layout_entries[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[4].layout.texture=wtbl.at(1,1);
bindgroup_layout_entries[5]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[5].binding=5;
bindgroup_layout_entries[5].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[5].layout.texture=wtbl.at(2,2);
bindgroup_layout_entries[6]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[6].binding=6;
bindgroup_layout_entries[6].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[6].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
bindgroup_layout_entries[6].layout.sampler=wsbl.at(0,0);
  */
wbgle.at(0,0)=bindgroup_layout_entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),5);
wbgl.at(0,0)=bindgroup_layout;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
renderPipelineDesc={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc.vertex=wvs.at(0,0);
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.primitive=wps.at(0,0);
renderPipelineDesc.fragment=wfs.at(0,0);
renderPipelineDesc.depthStencil=wdss.at(0,0);
renderPipelineDesc.layout=wrpl.at(0,0);
renderPipelineDesc.multisample=wms.at(0,0);
wrpid.at(0,0)=renderPipelineDesc;
renderPipeline1=wgpu_device_create_render_pipeline(wd.at(0,0),&wrpid.at(0,0));
wrp.at(0,0)=renderPipeline1;
renderPipelineDesc2={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc2.vertex=wvs.at(0,0);
renderPipelineDesc2.vertex.entryPoint="main";
renderPipelineDesc2.primitive=wps.at(0,0);
// renderPipelineDesc2.fragment=wfs.at(1,1);
renderPipelineDesc2.depthStencil=wdss.at(1,1);
// renderPipelineDesc2.layout=wrpl.at(0,0);
renderPipelineDesc2.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc2.multisample=wms.at(0,0);
wrpid.at(1,1)=renderPipelineDesc2;
renderPipeline2=wgpu_device_create_render_pipeline(wd.at(0,0),&wrpid.at(1,1));
wrp.at(1,1)=renderPipeline2;
depthTextureViewDescriptor.format=wtf.at(2,2);
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
depthTextureDescriptor.format=wtf.at(2,2);
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers=1;
depthTextureDescriptor.mipLevelCount=1;
depthTextureDescriptor.sampleCount=1; // 4;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthViewFormats[0]={wtf.at(2,2)};
depthTextureDescriptor.viewFormats=&depthViewFormats[0];
wtd.at(0,0)=depthTextureDescriptor;
depthTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(0,0));
wt.at(0,0)=depthTexture;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorTextureDescriptor.format=wtf.at(3,3);
colorTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
colorTextureDescriptor.width=sze.at(0,0);
colorTextureDescriptor.height=sze.at(0,0); // default = 1;
colorTextureDescriptor.depthOrArrayLayers=1;
colorTextureDescriptor.mipLevelCount=1;
colorTextureDescriptor.sampleCount=1; // 4;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorViewFormats[0]={wtf.at(4,4)};
colorTextureDescriptor.viewFormats=&colorViewFormats[0];
wtd.at(1,1)=colorTextureDescriptor;
colorTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(1,1));
wt.at(1,1)=colorTexture;
highbitTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
highbitTextureDescriptor.format=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
highbitTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
highbitTextureDescriptor.width=sze.at(0,0);
highbitTextureDescriptor.height=sze.at(0,0); // default = 1;
highbitTextureDescriptor.depthOrArrayLayers=1;
highbitTextureDescriptor.mipLevelCount=1;
highbitTextureDescriptor.sampleCount=1;
highbitTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorViewFormats[0]={WGPU_TEXTURE_FORMAT_RGBA32FLOAT};
highbitTextureDescriptor.viewFormats=&colorViewFormats[0];
wtd.at(2,2)=highbitTextureDescriptor;
// __128bit_Texture__=wgpu_device_create_texture(wd.at(0,0),&wtd.at(2,2));
// wt.at(2,2)=__128bit_Texture__;
bindgroup_entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[0].binding=0;
bindgroup_entries[0].resource=wb.at(0,0);
bindgroup_entries[0].bufferBindOffset=0;
bindgroup_entries[0].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[1].binding=3;
bindgroup_entries[1].resource=wb.at(1,1);
bindgroup_entries[1].bufferBindOffset=0;
bindgroup_entries[1].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[2].binding=4;
bindgroup_entries[2].resource=wb.at(2,2);
bindgroup_entries[2].bufferBindOffset=0;
bindgroup_entries[2].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[3].binding=1;
bindgroup_entries[3].resource=wgpu_sampler.at(2,2);
bindgroup_entries[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[4].binding=2;
bindgroup_entries[4].resource=wtv.at(2,2);
    /*
bindgroup_entries[3]={};
bindgroup_entries[3].binding=3;
bindgroup_entries[3].resource=wb.at(3,3);
bindgroup_entries[3]={};
bindgroup_entries[3].binding=3;
bindgroup_entries[3].resource=wt.at(1,1);
bindgroup_entries[4]={};
bindgroup_entries[4].binding=4;
bindgroup_entries[4].resource=wt.at(2,2);
bindgroup_entries[5]={};
bindgroup_entries[5].binding=5;
bindgroup_entries[5].resource=wt.at(0,0);
bindgroup_entries[6]={};
bindgroup_entries[6].binding=6;
bindgroup_entries[6].resource=wt.at(2,2);
  */
wbge.at(0,0)=bindgroup_entries;
// renderBundleEncoderDescriptor.sampleCount=1;
// renderBundleEncoderDescriptor.depthStencilFormat=wtf.at(2,2);
// wrbed.at(0,0)=renderBundleEncoderDescriptor;
// renderBundleEncoder=wgpu_device_create_render_bundle_encoder(wd.at(0,0),&wrbed.at(0,0));
// wrbe.at(0,0)=renderBundleEncoder;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
  // wgpu_queue_write_buffer(wq.at(0,0),wb.at(3,3),0,vertices,sizeof(vertices));
  // wgpu_queue_write_buffer(wq.at(0,0),WGPU_Buffers.at(1,1,1),0,vertices,sizeof(vertices));
  // wgpu_queue_write_buffer(wq.at(0,0),wb.at(4,4),0,indices,36*sizeof(uint32_t));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),5);
wbg.at(0,0)=bindgroup;
colorAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
// colorTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(1,1));
u64_uni.at(0,0)=0;
u64_uni.at(1,1)=0;
u64_uni.at(2,2)=u64_siz.at(0,0);
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
if(on.at(0,0)==1){emscripten_cancel_main_loop();}
double sizzA,sizzB;
emscripten_get_element_css_size("canvas",&sizzB,&sizzA);
EGLint numSamples;
EGLint numSamplesNV;
EGLint numBuffersNV;
EGLint numGreen;
EGLint numRed;
EGLint numBlue;
EGLint numAlpha;
EGLint numDepth;
EGLint numStencil;
EGLint numBuffer;
EGLint numMBuffers;
EGLint colorSpace;
EGLint colorFormat;
EGLDisplay display;
EGLSurface surface;
EGLContext contextegl;
EGLConfig eglconfig=NULL;
EGLint config_size,major,minor,atb_pos;
int Size=(int)sizzA;
float S=(float)Size;
display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
PFNEGLGETCONFIGATTRIBPROC eglGetConfigAttribHI = reinterpret_cast<PFNEGLGETCONFIGATTRIBPROC>(eglGetProcAddress("eglGetConfigAttribHI"));
eglInitialize(display,&major,&minor);
eglGetConfigAttrib(display,eglconfig,EGL_SAMPLES,&numSamples);
eglGetConfigAttrib(display,eglconfig,EGL_COVERAGE_BUFFERS_NV,&numSamplesNV);
eglGetConfigAttrib(display,eglconfig,EGL_SAMPLE_BUFFERS,&numMBuffers);
eglGetConfigAttrib(display,eglconfig,EGL_RED_SIZE,&numRed);
eglGetConfigAttrib(display,eglconfig,EGL_GREEN_SIZE,&numGreen);
eglGetConfigAttrib(display,eglconfig,EGL_BLUE_SIZE,&numBlue);
eglGetConfigAttrib(display,eglconfig,EGL_ALPHA_SIZE,&numAlpha);
eglGetConfigAttrib(display,eglconfig,EGL_DEPTH_SIZE,&numDepth);
eglGetConfigAttrib(display,eglconfig,EGL_STENCIL_SIZE,&numStencil);
eglGetConfigAttrib(display,eglconfig,EGL_BUFFER_SIZE,&numBuffer);
eglGetConfigAttrib(display,eglconfig,EGL_COVERAGE_BUFFERS_NV,&numBuffersNV);
eglGetConfigAttrib(display,eglconfig,EGL_GL_COLORSPACE,&colorSpace);
eglGetConfigAttrib(display,eglconfig,EGL_COLOR_FORMAT_HI,&colorFormat);
EGLint ctx_att[]={
EGL_CONTEXT_CLIENT_TYPE,EGL_OPENGL_ES_API,
EGL_CONTEXT_CLIENT_VERSION,4,
EGL_CONTEXT_MAJOR_VERSION_KHR,6,
EGL_CONTEXT_MINOR_VERSION_KHR,0,
// EGL_CONTEXT_FLAGS_KHR,EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_REALTIME_NV,
// EGL_CONTEXT_PRIORITY_LEVEL_IMG,EGL_CONTEXT_PRIORITY_HIGH_IMG,
EGL_NONE
};
EGLint att_lst2[]={ 
/*
  Google Colab
If BT-2020 is set to linear, it will degrade the fidelity of image representation. 
This is because the BT.2020 color space is a non-linear color space, and when it is set to linear,
the values of the components are directly proportional to the perceived brightness or lightness of the color.
This means that the colors in the image will be misrepresented,
and the image will not be as accurate as it would be if it were in the original BT.2020 color space.
*/
EGL_GL_COLORSPACE_KHR,colorSpace,
EGL_NONE
};
EGLint att_lst[]={
EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
// EGL_COLOR_COMPONENT_TYPE_EXT,EGL_COLOR_COMPONENT_TYPE_FIXED_EXT,
// EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR,
EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
// EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,  // EGL 1.5 needed  (WASM cannot Window surface)
// EGL_RENDERABLE_TYPE,EGL_NONE,
// EGL_CONFORMANT,EGL_OPENGL_ES_API,
// EGL_CONFORMANT,EGL_NONE,
//  EGL_CONFIG_CAVEAT,EGL_NONE,
EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT,EGL_TRUE,
// EGL_CONTEXT_OPENGL_NO_ERROR_KHR,EGL_TRUE,
// EGL_DEPTH_ENCODING_NV,EGL_DEPTH_ENCODING_NONLINEAR_NV,
// EGL_RENDER_BUFFER,EGL_TRIPLE_BUFFER_NV,
EGL_RENDER_BUFFER,EGL_QUADRUPLE_BUFFER_NV, //   available in OpenGL
// EGL_SURFACE_TYPE,EGL_MULTISAMPLE_RESOLVE_BOX_BIT,
EGL_SURFACE_TYPE,EGL_SWAP_BEHAVIOR_PRESERVED_BIT|EGL_MULTISAMPLE_RESOLVE_BOX_BIT,
EGL_MULTISAMPLE_RESOLVE,EGL_MULTISAMPLE_RESOLVE_BOX,
//  EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE,EGL_TRUE, // EGL 1.5 "...the context will only support OpenGL ES 3.0 and later features."
EGL_COLOR_FORMAT_HI,colorFormat, //  available in OpenGL
// EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY,EGL_NO_RESET_NOTIFICATION,
// EGL_NATIVE_RENDERABLE,EGL_TRUE,
EGL_COLOR_BUFFER_TYPE,EGL_RGB_BUFFER,
EGL_LUMINANCE_SIZE,0, // available in OpenGL
EGL_RED_SIZE,numRed,
EGL_GREEN_SIZE,numGreen,
EGL_BLUE_SIZE,numBlue,
EGL_ALPHA_SIZE,numAlpha,
EGL_DEPTH_SIZE,numDepth,
EGL_STENCIL_SIZE,numStencil,
EGL_BUFFER_SIZE,numBuffer,
EGL_COVERAGE_BUFFERS_NV,numBuffersNV, // available in GLES 3.1
EGL_COVERAGE_SAMPLES_NV,numSamplesNV,
EGL_SAMPLE_BUFFERS,numMBuffers,
EGL_SAMPLES,numSamples,
EGL_NONE
};
eglChooseConfig(display,att_lst,&eglconfig,1,&config_size);
contextegl=eglCreateContext(display,eglconfig,EGL_NO_CONTEXT,ctx_att);
surface=eglCreateWindowSurface(display,eglconfig,(NativeWindowType)0,att_lst2);
// eglBindAPI(EGL_OPENGL_ES_API);
eglBindAPI(EGL_OPENGL_API);
eglMakeCurrent(display,surface,surface,contextegl);
emscripten_set_main_loop((void(*)())raf,0,0);
// emscripten_set_main_loop_timing(2,1);
// emscripten_request_animation_frame_loop(raf,0);
on.at(0,0)=1;
return;
};

void ObtainedWebGpuAdapterStart(WGpuAdapter resultA, void *userData){
wa.at(0,0)=resultA;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8|WGPU_FEATURE_FLOAT32_FILTERABLE|WGPU_FEATURE_RG11B10UFLOAT_RENDERABLE;
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
WGPU_FEATURES_BITFIELD ftr=wgpu_adapter_or_device_get_features(wa.at(0,0));
deviceDesc.requiredFeatures=ftr;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
return;
}

void WGPU_Start(){
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
return;
}

EM_BOOL framm(int h,int offs){
// texid.at(0,0)=em;
sze.at(1,0)=h;
sze.at(0,1)=offs;
sze.at(1,1)=h;
szef.at(1,1)=float(sze.at(1,1));
return EM_TRUE;
}

extern "C"{

void frm(int h,int offs){
framm(h,offs);
return;
}

}


EM_JS(void,js_page,(),{

var obbj=document.querySelector('#tileNum').innerHTML;
var contain=document.querySelector('#contain1a');
var nmTile=parseInt(obbj,10);
var thisChrt;
var place;
var side;
  
function sizeData(y,nm){
var szz=parseInt(document.innerHeight*0.25);
if(y==1){place=0;side=0;}
if(y==2){place=20;side=0;}
if(y==3){place=40;side=0;}
if(y==4){place=0;side=20;}
if(y==5){place=20;side=20;}
if(y==6){place=40;side=20;}
if(y==7){place=0;side=40;}
if(y==8){place=20;side=40;}
if(y==9){place=40;side=40;}
var rows=Math.floor(nm/3);
var column=((nm%3)*60)+szz;
var topp=rows*60;
var ll=column+place;
var tt=topp+side;
  console.log(tt+','+ll+','+column+','+topp);
return{noteTop:tt,noteLeft:ll,tileLeft:column,tileTop:topp};
}
  
function addChart(nmChart){
for (var i=0;i<nmChart;i++){
let chrtDat=sizeData(i,nmTile);
let chrt=document.createElement("div");
chrt.id='chrt'+nmTile;
chrt.className='chrt';
chrt.style.top=chrtDat.tileTop+'px';
chrt.style.left=chrtDat.tileLeft+'px';
contain.appendChild(chrt);
eval("thisChrt=document.querySelector('#chrt"+nmTile+"');");
for(var y=0;y<9;y++){
let noteDat=sizeData(i,nmTile);
let note=document.createElement("div");
note.style.left=noteDat.noteLeft+'px';
note.style.top=noteDat.noteTop+'px';
note.innerHTML=y;
note.className='note';
note.id='chrt'+nmTile+'note'+y;
thisChrt.appendChild(note);
}
nmTile+=1;
obbj=nmTile;
}
}

function addData(nm){
var tns=Math.floor(nm/10);
var chrt=obbj;
addChart(tns);
for(var i=0;i<tns;i++){

}
  
}

addData(21);
  
});

extern"C"{

void page_js(){
js_page();
}

}

EM_JS(void,js_main,(),{
FS.mkdir('/shader');
FS.mkdir('/video');
window.scroll(0,0);

function nearestPowerOf2(n){
if(n&(n-1)){
return Math.pow(2,Math.ceil(Math.log2(n)));
}else{
return n;
}
}
document.querySelector('#testBtn').addEventListener('click',function(){
Module.ccall('page_js');
});

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

async function videoFrames(){
let $H=Module.HEAPU8.buffer;
// document.querySelector("#mvi").height=SiZ;
let w$=parseInt(document.querySelector("#mvi").videoWidth);
let h$=parseInt(document.querySelector("#mvi").videoHeight);
let SiZ=window.innerHeight;
let tstSiZ=h$;
let offS=Math.floor((w$-h$)/2);
// document.querySelector("#mvi").height=h$;
// document.querySelector("#mvi").width=w$;
Module.ccall("frm",null,['Number'],['Number'],h$,offS);
  Module.ccall("startWebGPU",{async:true});
console.log("vid size: ",h$,", ",w$);
let cnv=document.querySelector('#bcanvas');
let cnvb=document.querySelector('#canvas');
cnv.height=h$;
cnvb.height=SiZ;
cnv.width=h$;
cnvb.width=SiZ;
let la=nearestPowerOf2(((h$*h$*4)/4)*4);
const gl2=cnv.getContext('2d',{
// colorType:'uint',
precision:'highp',
preferLowPowerToHighPerformance:false,
alpha:true,
depth:true,
stencil:true,
// preserveDrawingBuffer:false,
premultipliedAlpha:false,
// imageSmoothingEnabled:false,
willReadFrequently:true,
lowLatency:false,
powerPreference:'high-performance',
antialias:false}); // 
gl2.drawImage(vvi,offS,0,h$,h$,0,0,tstSiZ,tstSiZ);
let image=gl2.getImageData(0,0,tstSiZ,tstSiZ);
// let mageData=flipImageData(image);
let imageData=image.data;
let pixelData=new Uint8ClampedArray(imageData);
//  let frrm=new Uint8ClampedArray($H,0,imageData.length);
// frrm.set(pixelData);
FS.writeFile('/video/frame.gl',pixelData,{encoding:"binary",flag:"w+",mode:0o666});
setInterval(function(){
gl2.drawImage(vvi,offS,0,h$,h$,0,0,tstSiZ,tstSiZ);
image=gl2.getImageData(0,0,tstSiZ,tstSiZ);
// mageData=flipImageData(image);
imageData=image.data;
pixelData=new Uint8ClampedArray(imageData);
//  frrm=new Uint8ClampedArray($H,0,imageData.length);
// frrm.set(imageData);
FS.writeFile('/video/frame.gl',pixelData,{encoding:"binary",flag:"w+",mode:0o666});
},16.6);
}

function highResStart(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#bcanvas').width=window.innerWidth*4;
document.querySelector('#bcanvas').height=window.innerHeight*4;
document.querySelector('#di').click();
setTimeout(function(){
document.querySelector('#stat').innerHTML='Sending Start';
document.querySelector('#stat').style.backgroundColor='green';
Module.ccall('str',{async:true});
},50);
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#canvas').width=window.innerHeight;
document.querySelector('#canvas').height=window.innerHeight;
document.querySelector('#bcanvas').width=window.innerHeight;
document.querySelector('#bcanvas').height=window.innerHeight;
document.querySelector('#di').click();
},150);
}

function normalResStart(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
videoFrames();
},100);
document.querySelector('#status').style.backgroundColor="green";
}

var $shds=[];

function shds(xml){
const sparser=new DOMParser();
let htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
let preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
$shds[0]=preList.length;
for(var i=1;i<preList.length;i++){
var txxts=preList[i].href;
var Self=location.href;
Self=Self.replace(/1ink.1ink/,"");
txxts=txxts.replace(Self,"");
var x=document.getElementById("sh1");
var option=document.createElement("option");
option.text=txxts;
$shds[i+1]='https://glsl.1ink.us/wgsl/'+txxts;
option.value=txxts;
x.add(option);
}
}

let codeMessage=new BroadcastChannel('codeMessage');
codeMessage.addEventListener('message',event=>{
document.querySelector('#status').style.backgroundColor="blue";
let flDat=event.data.data;
var buffer = new ArrayBuffer(flDat.length*2);
var bufferView = new Uint16Array(buffer);
for (var i = 0; i < flDat.length; i++) {
    bufferView[i] = flDat.charCodeAt(i);
}
// console.log(bufferView);
FS.writeFile('/shader/shader.wgsl',bufferView);
// document.querySelector('#startBtn').click();
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
document.querySelector('#status').style.backgroundColor="green";
Module.ccall("startWebGPUb");
},1000);
});

function scanShaders(){
const dxhttp=new XMLHttpRequest();
// dxhttp.withCredentials=false;
dxhttp.addEventListener("load",function(){
shds(this);
});
dxhttp.open('GET','https://glsl.1ink.us/wgsl/',true);
dxhttp.send();
}
// scanShaders();

document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
// document.querySelector('#bcanvas').height=parseInt(window.innerHeight,10);
// document.querySelector('#bcanvas').width=parseInt(window.innerHeight,10);
document.querySelector('#canvas').height=parseInt(window.innerHeight,10);
document.querySelector('#canvas').width=parseInt(window.innerHeight,10);
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

document.getElementById('uniUp').addEventListener('click',function(){
Module.ccall('resUp');
});

document.getElementById('uniDown').addEventListener('click',function(){
Module.ccall('resDown');
});

const pnnl=document.body;
function Key(e){
if(e.code=='KeyQ'){document.getElementById('startBtn').click();};
if(e.code=='KeyE'){document.getElementById('startBtn2').click();};
if(e.code=='KeyD'){document.getElementById('uniUp').click();};
if(e.code=='KeyA'){document.getElementById('uniDown').click();};
if(e.code=='KeyW'){document.getElementById('viewUp').click();};
if(e.code=='KeyS'){document.getElementById('viewDown').click();};
if(e.code=='KeyJ'){document.getElementById('moveLeft').click();};
if(e.code=='KeyK'){document.getElementById('moveRight').click();};
if(e.code=='KeyI'){document.getElementById('moveDown').click();};
if(e.code=='KeyM'){document.getElementById('moveUp').click();};
if(e.code=='Digit1'){document.getElementById('sizeDown').click();};
if(e.code=='Digit3'){document.getElementById('sizeUp').click();};
}
pnnl.addEventListener('keydown',Key);

document.querySelector('#startBtn').addEventListener('click',function(){
normalResStart();

/*
// var pth="https://glsl.1ink.us/wgsl/galaxy.wgsl";
let shdMenu=document.querySelector('#sh1');
let highRes=document.querySelector('#resMode').value;
document.querySelector('#path').innerHTML='https://glsl.1ink.us/wgsl/'+shdMenu.value;
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
FS.writeFile('/shader/shader.wgsl',sfil);
document.querySelector('#stat').innerHTML='Downloaded Shader';
document.querySelector('#stat').style.backgroundColor='blue';
normalResStart();
}
});
ff.send(null);
*/
});
  
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
},500);
});

void uniUp(){
u64_uni.at(2,2)=int(u64_uni.at(2,2)*1.01);
return;
}

void uniDown(){
u64_uni.at(2,2)=int(u64_uni.at(2,2)*0.99);
return;
}

extern"C"{

void resUp(){
uniUp();
return;
}

void resDown(){
uniDown();
return;
}

void startWebGPU(){
const char * FnmC=reinterpret_cast<const char *>("/shader/shader.wgsl");
getCode(FnmC);
WGPU_Start();
return;
}

void startWebGPUb(){
const char * FnmC=reinterpret_cast<const char *>("/shader/shader.wgsl");
getCode(FnmC);
WGPU_Start();
return;
}

}

int main(void){
on.at(0,0)=0;
js_main();
return 0;
}
