boost::function<EM_BOOL()>render;

//  single threaded
char wgl_cmp_srcA[2000]=
// "@group(0)@binding(0)var <storage,read> inputBuffer: array<f32,64>;\n"
// "@group(0)@binding(1)var <storage,read_write> outputBuffer: array<f32,64>;\n"
"@group(0)@binding(2)var textureIN: texture_2d <f32>;\n"
// "@group(0)@binding(3)var textureOUT: texture_storage_2d <rgba32float,write>;\n"
// "@group(0)@binding(4)var resizeSampler: sampler;\n"
"@group(0)@binding(5)var <uniform> iTime: u32;\n"
"@group(0)@binding(6)var videoOUT: texture_storage_2d <rgba32float,write>;\n"
// "@group(0)@binding(7)var colorOUT: texture_storage_2d <rgba8unorm,write>;\n"
"@compute@workgroup_size(1,1,1)\n"
"fn main_image(@builtin(global_invocation_id)global_id:vec3<u32>){\n"
"var outSizeU:u32=textureDimensions(videoOUT).x;\n"
"var inSizeU:u32=textureDimensions(textureIN).x;\n"
"var sizeRatio:f32=f32(inSizeU)/f32(outSizeU);\n"
"for(var x:u32=0u;x<=outSizeU;x=x+1u){\n"
"var xPos:u32=u32(round((f32(x))*sizeRatio));\n"
"for(var y:u32=0u;y<=outSizeU;y=y+1u){\n"
"var yPos:u32=u32(round((f32(y))*sizeRatio));\n"
"var INtexCoord:vec2<u32>=vec2<u32>(xPos,yPos);\n"
"var color:vec4<f32>=textureLoad(textureIN,INtexCoord,0);\n"
"color.r-=0.000005f;\n"
"color.r+=0.00001f;\n"
"color.g-=0.000005f;\n"
"color.g+=0.00001f;\n"
"color.b-=0.000005f;\n"
"color.b+=0.00001f;\n"
"textureStore(videoOUT,vec2<u32>(x,y),color);\n"
"}\n"
"}\n"
// "outputBuffer[2]=f32(textureDimensions(textureIN).x);\n"
// "outputBuffer[3]=f32(textureDimensions(textureOUT).x);\n"
"}";

char wgl_cmp_src[2000]=
// "@group(0)@binding(0)var <storage,read> inputBuffer: array<f32,64>;\n"
// "@group(0)@binding(1)var <storage,read_write> outputBuffer: array<f32,64>;\n"
"@group(0)@binding(2)var textureIN: texture_2d <f32>;\n"
// "@group(0)@binding(3)var textureOUT: texture_storage_2d <rgba32float,write>;\n"
// "@group(0)@binding(4)var resizeSampler: sampler;\n"
"@group(0)@binding(5)var <uniform> iTime: u32;\n"
"@group(0)@binding(6)var videoOUT: texture_storage_2d <rgba32float,write>;\n"
// "@group(0)@binding(7)var colorOUT: texture_storage_2d <rgba8unorm,write>;\n"
"@compute@workgroup_size(96,1,1)\n"
"fn main_image(@builtin(local_invocation_id)thread_id:vec3<u32>){\n"
"var threadU:u32=thread_id.x;\n"
"var threadF:f32=f32(thread_id.x);\n"
"var outSizeU:u32=textureDimensions(videoOUT).x;\n"
"var loopSizeU:u32=u32(ceil(f32(textureDimensions(videoOUT).x)/96.0f));\n"
"var loopSizeF:f32=f32(ceil(f32(textureDimensions(videoOUT).x)/96.0f));\n"
"var inSizeU:u32=textureDimensions(textureIN).x;\n"
"var sizeRatio:f32=f32(inSizeU)/f32(outSizeU);\n"
"for(var x:u32=0u;x<=outSizeU;x=x+1u){\n"
"var xPos:u32=u32(round(f32(x)*sizeRatio));\n"
"var outX:u32=x;\n"
"for(var y:u32=0u;y<=loopSizeU;y=y+1u){\n"
"var yPos:u32=u32(round((f32(y)+(loopSizeF*threadF))*sizeRatio));\n"
// "yPos+=u32(loopSizeF*sizeRatio)*threadU;\n"
"var outY:u32=y+(loopSizeU*threadU);\n"
"var INtexCoord:vec2<u32>=vec2<u32>(xPos,yPos);\n"
"var color:vec4<f32>=textureLoad(textureIN,INtexCoord,0);\n"
/*
"color.r-=0.000005f;\n"
"color.r+=0.00001f;\n"
"color.g-=0.000005f;\n"
"color.g+=0.00001f;\n"
"color.b-=0.000005f;\n"
"color.b+=0.00001f;\n"
*/
"textureStore(videoOUT,vec2<u32>(outX,outY),color);\n"
"}\n"
"}\n"
// "outputBuffer[2]=f32(textureDimensions(textureIN).x);\n"
// "outputBuffer[3]=f32(textureDimensions(textureOUT).x);\n"
"}";


const char * frag_body2 = R"delimiter(
  //   //
@group(0)@binding(0)var videoSampler: sampler;
// @group(0)@binding(1)var textureIN: texture_storage_2d <rgba32float,write>;
@group(0)@binding(2)var videoOUT: texture_2d <f32>;
@group(0)@binding(5)var<uniform> iResolution : u32;
@group(0)@binding(6)var<uniform> iFrame : u32;
@group(0)@binding(7)var<uniform> iTime : u32;
var<private> fragColor_1 : vec4<f32>;
var<private> gl_FragCoord : vec4<f32>;
var<private> iMouse : vec4<f32>;
var<private> iPosition : vec4<f32>;
fn mainImage_vf4_vf2_(fragColor: ptr<function, vec4<f32>>,fragCoord: ptr<function, vec2<f32>>) {
var col : vec3<f32>;
col = vec3<f32>(0.40000000596046447754f, 0.0f, 0.5f);
let x_24 : vec3<f32> = col;
*(fragColor) = vec4<f32>(x_24.x, x_24.y, x_24.z, 1.0f);
//  let b3_col : vec4<f32> = *(fragColor);textureStore(textureIN,vec2<u32>(gl_FragCoord.xy),vec4<f32>(b3_col.rgb,1.0f));
return;}
fn main_1() {
var param : vec4<f32>;
var param_1 : vec2<f32>;
let x_36 : vec4<f32> = gl_FragCoord;
param_1 = vec2<f32>(x_36.x, x_36.y);
mainImage_vf4_vf2_(&(param), &(param_1));
let x_39 : vec4<f32> = param;
let tstcr:vec4<f32>=vec4<f32>(0.3,0.0,0.44,1.0);
let ress:u32=u32(textureDimensions(videoOUT).x);
// fragColor_1=vec4<f32>(textureSample(videoOUT,videoSampler,gl_FragCoord.xy/vec2<f32>(vec2<u32>(ress,ress))));
fragColor_1=vec4<f32>(textureSampleBaseClampToEdge(videoOUT,videoSampler,gl_FragCoord.xy/vec2<f32>(vec2<u32>(iResolution,iResolution))));
return;
}
struct main_out {
@location(0)
fragColor_1_1 : vec4<f32>,
@location(1)
iPosition_1 : vec4<f32>,
}
@fragment
fn main(@builtin(position) gl_FragCoord_param : vec4<f32>) -> main_out {
gl_FragCoord = gl_FragCoord_param;
main_1();
return main_out(fragColor_1, iPosition);
}
  //   //
)delimiter";

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


WGpuColor clearColor={};
WGpuCommandEncoder wceA={};
WGpuCommandEncoder wceB={};
WGPUImageCopyBuffer videoFrmBfrSrc={};
WGPUImageCopyBuffer videoFrmBfrDst={};
WGpuImageCopyTexture videoTextureCopy;
WGpuExternalTexture extTexture;
WGpuExternalTextureBindingLayout extTextureBindingLayout={};
WGpuExternalTextureDescriptor extTextureDescriptor={};
WGpuTextureView depthTextureView;
WGpuTextureView depthTextureView2;
WGpuTextureView colorTextureView;
WGpuTextureView videoTextureView;
WGpuTextureView INTextureView;
WGpuTextureView OUTTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor depthTextureViewDescriptor2={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuTextureViewDescriptor videoTextureViewDescriptor={};
WGpuTextureViewDescriptor INTextureViewDescriptor={};
WGpuTextureViewDescriptor OUTTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment;
WGpuRenderPassColorAttachment videoAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment2;
WGpuTexture depthTexture;
WGpuTexture depthTexture2;
WGpuTexture colorTexture;
WGpuTexture videoTexture;
WGpuTexture textureIn;
WGpuTexture textureOut;
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
WGpuTextureDescriptor depthTextureDescriptor2={};
WGpuTextureDescriptor colorTextureDescriptor={};
WGpuTextureDescriptor videoTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuRenderPassDescriptor passDesc2={};
WGpuCanvasConfiguration config;
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModuleDescriptor shaderModuleDescF2={};
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuShaderModule fs2;
WGpuDepthStencilState depthState;
WGpuDepthStencilState depthState2;
WGpuVertexState vertState;
WGpuPrimitiveState priState;
WGpuFragmentState fragState;
WGpuFragmentState fragState2;
WGpuBufferDescriptor bufferDescriptorUni={};
WGpuBufferDescriptor bufferDescriptor_iTime={};
WGpuBufferDescriptor bufferDescriptor_iResolution={};
WGpuBufferDescriptor bufferDescriptor_iResolution_2={};
WGpuBufferDescriptor bufferDescriptor_iFrame={};
WGpuBufferDescriptor bufferDescriptor_iTimeDelta={};
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayout bindgroup_layout_2=0;
WGpuBindGroupLayoutEntry Render_Bindgroup_Layout_Entries[8]={};
WGpuBindGroupLayoutEntry Render_Bindgroup_Layout_Entries_2[8]={};
WGpuBindGroupEntry Render_Bindgroup_Entries[8]={};
WGpuBindGroupEntry Render_Bindgroup_Entries_2[8]={};
WGpuBindGroupEntry bindgroup_entries[8]={};  //  for video.cpp
WGpuBindGroup bindgroup=0;
WGpuBindGroup bindgroup_2=0;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuMultisampleState multiSamp2;
WGpuBuffer uniBuffer;
WGpuBuffer srcBuffer;
WGpuBuffer dstBuffer;
WGpuBuffer vidBuffer;
WGpuBuffer uni_iTime_Buffer;
WGpuBuffer uni_iTimeDelta_Buffer;
WGpuBuffer uni_iResolution_Buffer;
WGpuBuffer uni_iResolution_Buffer_2;
WGpuBuffer uni_iFrame_Buffer;
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuBufferBindingLayout bufferBindingLayoutR={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayoutFloat={};
WGpuTextureBindingLayout textureBindingLayoutFloatM={};
WGpuTextureBindingLayout textureBindingLayoutFloat32={};
WGpuTextureBindingLayout textureBindingLayoutDepth={};
WGpuTextureBindingLayout textureBindingLayout1={}; // for video.cpp
WGpuSamplerBindingLayout samplerBindingLayout={};
WGpuImageCopyExternalImage videoFrm={};
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

wcolor_tensor clearC=wcolor_tensor{2,2};
xyz_tensor oxyz=xyz_tensor{2,2};
xy_tensor oxy=xy_tensor{2,2};
wtbl_tensor wtbl=wtbl_tensor{4,4};
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
wpl_tensor wrpl=wpl_tensor{2,2};
wb_tensor wb=wb_tensor{8,8};
wbgle_tensor wbgle=wbgle_tensor{2,2};
wbge_tensor wbge=wbge_tensor{2,2};
wbgl_tensor wbgl=wbgl_tensor{2,2};
wbg_tensor wbg=wbg_tensor{2,2};
wrpd_tensor wrpd=wrpd_tensor{2,2};
wrpca_tensor wrpca=wrpca_tensor{2,2};
wbbl_tensor wbbl=wbbl_tensor{2,2};
wsbl_tensor wsbl=wsbl_tensor{2,2};
wbd_tensor wbd=wbd_tensor{8,8};
wao_tensor wao=wao_tensor{2,2};
wdd_tensor wdd=wdd_tensor{2,2};
u64_tensor u64_uni=u64_tensor{4,4};
u64_tensor u64_siz=u64_tensor{4,4};
wrbe_tensor wrbe=wrbe_tensor{2,2};
wrbed_tensor wrbed=wrbed_tensor{2,2};
wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
wt_tensor wt=wt_tensor{8,8};
wtd_tensor wtd=wtd_tensor{8,8};
wtvd_tensor wtvd=wtvd_tensor{8,8};
wtf_tensor wtf=wtf_tensor{5,5};
wtv_tensor wtv=wtv_tensor{8,8};
wicb_tensor wicb=wicb_tensor{6,6};
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
wcp_tensor WGPU_ComputePipeline=wcp_tensor{3,3,3};
wpl_tensor WGPU_ComputePipelineLayout=wpl_tensor{1,1,1};
wsm_tensor WGPU_ComputeModule=wsm_tensor{3,3,3};
wbg_tensor WGPU_BindGroup=wbg_tensor{1,1,2};
wbgl_tensor WGPU_BindGroupLayout=wbgl_tensor{1,1,2};
wbgle_tensor WGPU_Compute_Bindgroup_Layout_Entries=wbgle_tensor{1,1,2};
wbge_tensor WGPU_BindGroupEntries=wbge_tensor{1,1,2};
wbmc_tensor WGPU_MapCallback=wbmc_tensor{1,1,3};
wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
wbbl_tensor WGPU_BufferBindingLayout=wbbl_tensor{1,1,4};
wbd_tensor WGPU_BufferDescriptor=wbd_tensor{1,1,4};
wsmd_tensor WGPU_ShaderModuleDescriptor=wsmd_tensor{3,3,3};
di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
void_tensor WGPU_UserData=void_tensor{1,1,2};
fptr_tensor WGPU_ResultBuffer=fptr_tensor{1,1,1};
fptr_tensor WGPU_InputBuffer=fptr_tensor{1,1,1};
i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
wt_tensor WGPU_Texture=wt_tensor{3,3,3};
wtd_tensor WGPU_TextureDescriptor=wtd_tensor{3,3,3};
wstbl_tensor WGPU_StorageTextureBindingLayout=wstbl_tensor{2,2,2};
wtvd_tensor WGPU_TextureViewDescriptor=wtvd_tensor{3,3,3};
uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
wced_tensor WGPU_CommandEncoderDescriptor=wced_tensor{1,1,1};
wbms_tensor WGPU_BufferStatus=wbms_tensor{1,1,1};
c_tensor wgsl=c_tensor{2,2};
uint32_t workgroupSize=64;
uint32_t OutputBufferBytes=64*4;
uint32_t InputBufferBytes=64*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytes;
const char * Entry="main_image";
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE
void * userDataA;
void * userDataB;
WGpuTexture textureA;
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
WGpuBindGroupLayoutEntry bindgroup_layout_entries[8]={};
WGpuShaderModuleCompilationHint shaderModuleCompilationHint={};
WGpuBindGroupEntry Compute_Bindgroup_Entries[8]={};
WGpuBufferBindingLayout bufferBindingLayoutIn={3};
WGpuBufferBindingLayout bufferBindingLayoutOut={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayoutFloat={};
WGpuStorageTextureBindingLayout storageTextureBindingLayoutFloat32={};
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
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;
WGpuImageCopyTexture Input_Image_Texture={};
WGpuImageCopyTexture Output_Image_Texture={};
WGpuImageCopyBuffer Input_Image_Buffer={};
WGpuImageCopyBuffer Output_Image_Buffer={};
WGpuImageCopyBuffer Mapped_Image_Buffer={};
uint32_t outP;
double_int53_t WGPU_Range_PointerB;
double_int53_t WGPU_Range_PointerC;
float * WGPU_Result_Array=new float[OutputBufferBytes];
float * WGPU_Input_Array=new float[InputBufferBytes];
const char * Fnm2=reinterpret_cast<const char *>("/video/frame.gl");
const char * FnmC=reinterpret_cast<const char *>("/shader/compute.wgsl");
uint8_t * result2=NULL;
float * resultf=NULL;
uint8_t * results2=NULL;
float * resultsf=NULL;
long int length2=0;
void * fram;
const char * Fnm=reinterpret_cast<const char *>("/shader/shader.wgsl");
static char * result=NULL;
static char * results=NULL;
static long int length=0;

struct Vertex{
// GLfloat position[4];
float position[4];
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

