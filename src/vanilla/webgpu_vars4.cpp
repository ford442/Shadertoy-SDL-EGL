#include "../../include/vanilla/webgpu_tex4.hpp"

WGpuBufferMapCallback mapCallbackStart=[](WGpuBuffer buffer,void * userData,WGPU_MAP_MODE_FLAGS mode,double_int53_t offset,double_int53_t size){
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneStart=[](WGpuQueue queue,void *userData){
return;
};

struct VertexF{
// GLfloat position[4];
float position[4];
};

VertexF Fvertices[]={
{-1.0,-1.0,1.0,1.0},
{1.0,-1.0,1.0,1.0},
{1.0,1.0,1.0,1.0},
{-1.0,1.0,1.0,1.0},
{-1.0,-1.0,-1.0,1.0},
{1.0,-1.0,-1.0,1.0},
{1.0,1.0,-1.0,1.0},
{-1.0,1.0,1.0,1.0}
};

VertexF Ffvertices[]={
{-1.0f,-1.0f,1.0f,1.0f},
{1.0f,-1.0f,1.0f,1.0f},
{1.0f,1.0f,1.0f,1.0f},
{-1.0f,1.0f,1.0f,1.0f},
{-1.0f,-1.0f,-1.0f,1.0f},
{1.0f,-1.0f,-1.0f,1.0f},
{1.0f,1.0f,-1.0f,1.0f},
{-1.0f,1.0f,1.0f,1.0f}
};

struct VertexFUV{
float x, y, z, w; // Position
float u, v;       // UV texture coordinates
};

VertexFUV FUVvertices[]={
{-1.0,-1.0,1.0,1.0,  0.0,0.0},
{1.0,-1.0,1.0,1.0,  1.0,0.0},
{1.0,1.0,1.0,1.0,  1.0,1.0},
{-1.0,1.0,1.0,1.0,  0.0,1.0},
{-1.0,-1.0,-1.0,1.0,  0.0,0.0},
{1.0,-1.0,-1.0,1.0,  1.0,0.0},
{1.0,1.0,-1.0,1.0,  1.0,1.0},
{-1.0,1.0,1.0,1.0,  0.0,1.0}
};

uint32_t indices[35]={3,0,1,1,2,3,4,0,3,3,7,4,1,5,6,6,2,1,4,7,6,6,5,4,2,6,6,7,3,0,4,1,1,4,5};

options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
WGpuRenderPipelineDescriptor renderPipelineDesc={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
WGpuBufferDescriptor bufferDescriptor_indice={};
WGpuBuffer indice_Buffer;
WGpuVertexAttribute vertAtt={};
WGpuVertexAttribute vertAtt2={};
WGpuVertexBufferLayout vertBufLayout={};
WGpuBufferDescriptor bufferDescriptor_vertex={};
WGpuBuffer vertex_Buffer;
WGpuBufferBindingLayout bufferBindingLayoutV={};
WGpuBufferBindingLayout bufferBindingLayoutF={};

//  egl render (no texture uv)
const char * vertexShaderEG =
R"delimiter(@vertex
fn main(@location(0) position: vec4<f32>) -> @builtin(position) vec4<f32> {
return vec4<f32>(position.xyzw);
})delimiter";

//  with index/vertex buffers and tex
const char * vertexShaderTX =
R"delimiter(
  //   // 
struct VertexInput {
    @location(0) position : vec4<f32>,
    @location(1) uv : vec2<f32>,
};
struct VertexOutput {
    @builtin(position) position : vec4<f32>,
    @location(0) fragUV : vec2<f32>, 
};
@vertex
fn main(vertexInput : VertexInput) -> VertexOutput {
    var output : VertexOutput;
    output.position = vertexInput.position;
    output.fragUV = vertexInput.uv;
    return output;
}
  //   //  
)delimiter";

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
@group(0)@binding(5)var<uniform> iResolution : f32;
@group(0)@binding(6)var<uniform> iFrame : u32;
@group(0)@binding(7)var<uniform> iTime : f32;
var<private> fragColor_1 : vec4<f32>;
var<private> gl_FragCoord : vec4<f32>;
var<private> iMouse : vec4<f32>;
var<private> iPosition : vec4<f32>;
fn mainImage_vf4_vf2_(fragColor: ptr<function, vec4<f32>>,fragCoord: ptr<function, vec2<f32>>) {
var col : vec3<f32>;
col = vec3<f32>(0.40000000596046447754f, 0.0f, 0.5f);
let x_24 : vec3<f32> = col;
*(fragColor) = vec4<f32>(x_24.x, x_24.y, x_24.z, 1.0f);
//  let b3_col : vec4<f32> = *(fragColor);
// textureStore(textureIN,vec2<u32>(gl_FragCoord.xy),vec4<f32>(b3_col.rgb,1.0f));
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
fragColor_1=vec4<f32>(textureSampleBaseClampToEdge(videoOUT,videoSampler,gl_FragCoord.xy/vec2<f32>(vec2<f32>(iResolution,iResolution))));
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

     // non vertex index / indice index shader
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
"@group(0) @binding(0) var <uniform> iTime : f32;\n"
"@group(0) @binding(1) var mySampler : sampler;\n"
"@group(0) @binding(2) var myTexture : texture_2d <f32>;\n"
// "@group(0) @binding(3) var extTexture : texture_external;\n"
"@fragment\n"
"fn main(@location(0) fragUV : vec2<f32>) ->\n"
"@location(0) vec4<f32> {\n"
"return textureSample(myTexture,mySampler,fragUV);"
"}\n";

WGpuRenderPassTimestampWrites renderTimestampWrites={};
WGPU_TEXTURE_FORMAT canvasFormat;
WGPU_TEXTURE_FORMAT canvasViewFormat[1];
WGpuCanvasConfiguration config={WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER};
WGpuOrigin3D OriginXYZ={0,0,0};
// OriginXYZ.x=0;
// OriginXYZ.y=0;
// OriginXYZ.z=0;
WGpuOrigin2D OriginXY={0,0};
// OriginXY.x=0;
// OriginXY.y=0;
WGPU_TEXTURE_FORMAT textureBviewFormats[1];
WGPU_TEXTURE_FORMAT videoViewFormats[1];
WGPU_TEXTURE_FORMAT depthViewFormats[1];
WGPU_TEXTURE_FORMAT depthViewFormats2[1];
WGPU_TEXTURE_FORMAT textureAviewFormats[1];
WGpuColorTargetState colorTarget32={};
WGpuColorTargetState colorTarget={};
WGpuOrigin3D xyz={};
WGpuColor clearColor={};
WGpuCommandEncoder wceA={};
WGpuCommandEncoder wceB={};
WGPUImageCopyBuffer videoFrmBfrSrc={};
WGPUImageCopyBuffer videoFrmBfrDst={};
WGpuExternalTextureBindingLayout extTextureBindingLayout={};
WGpuExternalTextureDescriptor extTextureDescriptor={};
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor depthTextureViewDescriptor2={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuTextureViewDescriptor videoTextureViewDescriptor={};
WGpuTextureViewDescriptor INTextureViewDescriptor={};
WGpuTextureViewDescriptor OUTTextureViewDescriptor={};
WGpuTextureViewDescriptor MSTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
WGpuRenderPassColorAttachment videoAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
WGpuRenderPassDepthStencilAttachment depthAttachment={};
WGpuRenderPassDepthStencilAttachment depthAttachment2={};
WGpuSampler videoSampler={};
WGpuSampler resizeSampler={};
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
WGpuTextureDescriptor MSTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuRenderPassDescriptor passDesc2={};
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModuleDescriptor shaderModuleDescF2={};
WGpuDepthStencilState depthState={};
WGpuDepthStencilState depthState2={};
WGpuVertexState vertState={};
WGpuPrimitiveState priState={};
WGpuFragmentState fragState={};
WGpuFragmentState fragState2={};
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
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
WGpuMultisampleState multiSamp={};
WGpuMultisampleState multiSamp2={};
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuBufferBindingLayout bufferBindingLayoutR={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayoutFloat={};
WGpuTextureBindingLayout textureBindingLayoutFloatM={};
WGpuTextureBindingLayout textureBindingLayoutFloat32={};
WGpuTextureBindingLayout textureBindingLayoutDepth={};
WGpuTextureBindingLayout textureBindingLayout1={}; // for video.cpp
WGpuSamplerBindingLayout samplerBindingLayout={};
WGpuImageCopyExternalImage videoFrm={};

struct{
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spana;
boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>time_spanb;
boost::chrono::high_resolution_clock::time_point t1;
boost::chrono::high_resolution_clock::time_point t2;
boost::chrono::high_resolution_clock::time_point t3;
}u_time;
d_tensor d64_uniform=d_tensor{8,8};
f_tensor f32_uniform=f_tensor{8,8};
wvbl_tensor wvbl=wvbl_tensor{2,2};
wcolor_tensor clearC=wcolor_tensor{2,2};
xyz_tensor oxyz=xyz_tensor{2,2};
xy_tensor oxy=xy_tensor{2,2};
wtbl_tensor wtbl=wtbl_tensor{4,4};
i_tensor on=i_tensor{3,3};
wetd_tensor wetd=wetd_tensor{2,2};
wet_tensor wet=wet_tensor{2,2};
i_tensor texid=i_tensor{2,2};
i_tensor sze=i_tensor{8,8};
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
wbbl_tensor wbbl=wbbl_tensor{6,6};
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
wict_tensor wict=wict_tensor{8,8};
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
wt_tensor WGPU_Texture=wt_tensor{4,4,4};
wtd_tensor WGPU_TextureDescriptor=wtd_tensor{4,4,4};
wstbl_tensor WGPU_StorageTextureBindingLayout=wstbl_tensor{2,2,2};
wtvd_tensor WGPU_TextureViewDescriptor=wtvd_tensor{4,4,4};
uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
wced_tensor WGPU_CommandEncoderDescriptor=wced_tensor{1,1,1};
wbms_tensor WGPU_BufferStatus=wbms_tensor{1,1,1};
c_tensor wgsl=c_tensor{2,2};
uint32_t OutputBufferBytes=64*4;
uint32_t InputBufferBytes=64*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytes;
const char * Entry="main_image";
WGPU_MAP_MODE_FLAGS mode1=0x1; // READ MODE

WGpuComputePassDescriptor computePassDescriptor={};
WGpuCommandBufferDescriptor commandBufferDescriptor={};
WGpuCommandEncoderDescriptor commandEncoderDescriptor={};
WGpuDeviceDescriptor deviceDescriptor={};
WGpuBindGroupLayoutEntry Compute_Bindgroup_Layout_Entries[18]={};
WGpuBindGroupLayoutEntry bindgroup_layout_entries[18]={};
WGpuShaderModuleCompilationHint shaderModuleCompilationHint={};
WGpuBindGroupEntry Compute_Bindgroup_Entries[18]={};
WGpuBufferBindingLayout bufferBindingLayoutIn={3};
WGpuBufferBindingLayout bufferBindingLayoutOut={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayoutFloat={};
WGpuStorageTextureBindingLayout storageTextureBindingLayoutFloat32={};
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
WGpuBufferDescriptor bufferDescriptorI={};
WGpuBufferDescriptor bufferDescriptorO={};
WGpuBufferDescriptor bufferDescriptorM={};
WGpuBufferDescriptor bufferDescriptorC={};
WGpuTextureDescriptor textureDescriptorIn={};
WGpuTextureDescriptor textureDescriptorInV={};
WGpuTextureDescriptor textureDescriptorOut={};
WGpuTextureDescriptor textureDescriptorOut2={};
WGpuTextureViewDescriptor textureViewDescriptorIn={};
WGpuTextureViewDescriptor textureViewDescriptorInV={};
WGpuTextureViewDescriptor textureViewDescriptorOut={};
WGpuTextureViewDescriptor textureViewDescriptorOut2={};
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={};
std::random_device randomizer;
WGpuImageCopyTexture Input_Image_Texture={};
WGpuImageCopyTexture Input_Image_TextureV={};
WGpuImageCopyTexture Output_Image_Texture={};
WGpuImageCopyTexture Output_Image_Texture2={};
WGpuImageCopyBuffer Input_Image_Buffer={};
WGpuImageCopyBuffer Output_Image_Buffer={};
WGpuImageCopyBuffer Mapped_Image_Buffer={};

float * WGPU_Result_Array=new float[OutputBufferBytes];
float * WGPU_Input_Array=new float[InputBufferBytes];
const char * Fnm2=reinterpret_cast<const char *>("/video/frame.gl");
const char * FnmC=reinterpret_cast<const char *>("/shader/compute.wgsl");
uint8_t * result2=NULL;
float * resultf=NULL;
uint8_t * results2=NULL;
float * resultsf=NULL;

const char * Fnm=reinterpret_cast<const char *>("/shader/shader.wgsl");
static char * result=NULL;
static char * results=NULL;



//  tensor definitions

const char * frag_body=(char*)rd_fl(Fnm);
const char * comp_body=(char*)rd_fl(FnmC);
// canvasFormat=navigator_gpu_get_preferred_canvas_format();
wtf.at(2,2)=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
// wtf.at(0,0)=navigator_gpu_get_preferred_canvas_format();
wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA8UNORM;
// wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
wtf.at(4,4)=WGPU_TEXTURE_FORMAT_INVALID;
// wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
// wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH24PLUS_STENCIL8;
wtf.at(5,5)=WGPU_TEXTURE_FORMAT_DEPTH16UNORM;
// wtf.at(0,0)=canvasFormat;

js_data_pointer.at(0,0)=0;
fjs_data_pointer.at(0,0)=0;

clearColor.r=0.5;
clearColor.g=0.5;
clearColor.b=0.5;
clearColor.a=1.0;
clearC.at(0,0)=clearColor;

oxyz.at(0,0)=OriginXYZ;
oxy.at(0,0)=OriginXY;

u64_bfrSze.at(0,0)=256; // (floor((sze.at(0,0))/256)+1)*256;
u64_bfrSze.at(1,1)=256; // (floor((sze.at(1,1))/256)+1)*256;

bufferDescriptorI={u64_bfrSze.at(1,1),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
bufferDescriptorO={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,EM_FALSE};
bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;

WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
textureBindingLayoutFloat.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloat.multisampled=0;
textureBindingLayoutFloatM.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayoutFloatM.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutFloatM.multisampled=1;
wtbl.at(1,1)=textureBindingLayoutFloat;
wtbl.at(3,3)=textureBindingLayoutFloatM;
textureBindingLayoutDepth.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_DEPTH;
textureBindingLayoutDepth.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayoutDepth.multisampled=0;
wtbl.at(2,2)=textureBindingLayoutDepth;
textureViewDescriptorIn.format=wtf.at(2,2);
textureViewDescriptorIn.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorIn.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorIn.baseMipLevel=0; // default = 0
textureViewDescriptorIn.mipLevelCount=1;
textureViewDescriptorIn.baseArrayLayer=0; // default = 0
textureViewDescriptorIn.arrayLayerCount=1;
textureViewDescriptorOut.format=wtf.at(2,2);
textureViewDescriptorOut.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorOut.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorOut.baseMipLevel=0; // default = 0
textureViewDescriptorOut.mipLevelCount=1;
textureViewDescriptorOut.baseArrayLayer=0; // default = 0
textureViewDescriptorOut.arrayLayerCount=1;
textureViewDescriptorOut2.format=wtf.at(2,2);
textureViewDescriptorOut2.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureViewDescriptorOut2.aspect=WGPU_TEXTURE_ASPECT_ALL;
textureViewDescriptorOut2.baseMipLevel=0; // default = 0
textureViewDescriptorOut2.mipLevelCount=1;
textureViewDescriptorOut2.baseArrayLayer=0; // default = 0
textureViewDescriptorOut2.arrayLayerCount=1;
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorIn;
WGPU_TextureViewDescriptor.at(0,0,1)=textureViewDescriptorOut;
WGPU_TextureViewDescriptor.at(0,0,2)=textureViewDescriptorOut2;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;

// bufferDescriptor_iTime={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
bufferDescriptor_iTime={sizeof(float),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptor_iTime;
uni_iTime_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(0,0));
wb.at(0,0)=uni_iTime_Buffer;
bufferDescriptor_iFrame={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(1,1)=bufferDescriptor_iFrame;
uni_iFrame_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(1,1));
wb.at(1,1)=uni_iFrame_Buffer;
bufferDescriptor_iResolution={sizeof(float),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(2,2)=bufferDescriptor_iResolution;
uni_iResolution_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(2,2));
wb.at(2,2)=uni_iResolution_Buffer;
bufferDescriptor_iResolution_2={sizeof(float),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(5,5)=bufferDescriptor_iResolution_2;

bufferBindingLayoutR.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayoutR.hasDynamicOffset=0,
bufferBindingLayoutR.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayoutR;
bufferBindingLayoutF.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayoutF.hasDynamicOffset=0,
bufferBindingLayoutF.minBindingSize=sizeof(float);
wbbl.at(2,2)=bufferBindingLayoutF;

WGpuBufferDescriptor bufferDescriptorIn={u64_bfrSze.at(1,1),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
WGpuBufferDescriptor bufferDescriptorOut={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,EM_FALSE};
wbd.at(3,3)=bufferDescriptorIn;
wbd.at(4,4)=bufferDescriptorOut;

    //  vert / indice buffers
bufferDescriptor_vertex.size=sizeof(Ffvertices);
bufferDescriptor_vertex.usage=WGPU_BUFFER_USAGE_VERTEX|WGPU_BUFFER_USAGE_COPY_DST;
bufferDescriptor_vertex.mappedAtCreation=EM_FALSE;
wbd.at(6,6)=bufferDescriptor_vertex;
vertAtt.offset=0;
vertAtt.shaderLocation=0;
vertAtt.format=WGPU_VERTEX_FORMAT_FLOAT32X4;
vertAtt2.offset=16;
vertAtt2.shaderLocation=1;
vertAtt2.format=WGPU_VERTEX_FORMAT_FLOAT32X2;
WGpuVertexAttribute vertAttArray[2]={vertAtt,vertAtt2};
vertBufLayout.numAttributes=1;
vertBufLayout.attributes=&vertAtt; // vertAttArray;
vertBufLayout.arrayStride=sizeof(VertexF);
vertBufLayout.stepMode=WGPU_VERTEX_STEP_MODE_VERTEX;
wvbl.at(0,0)=vertBufLayout;
bufferBindingLayoutV.type=WGPU_BUFFER_BINDING_TYPE_STORAGE;
bufferBindingLayoutV.hasDynamicOffset=0,
bufferBindingLayoutV.minBindingSize=sizeof(Ffvertices);
wbbl.at(1,1)=bufferBindingLayoutV;

bufferDescriptor_indice.size=36*sizeof(uint32_t);
bufferDescriptor_indice.usage=WGPU_BUFFER_USAGE_INDEX|WGPU_BUFFER_USAGE_COPY_DST;
bufferDescriptor_indice.mappedAtCreation=EM_FALSE;
wbd.at(7,7)=bufferDescriptor_indice;

resizeSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
resizeSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
resizeSamplerDescriptor.lodMinClamp=0;
resizeSamplerDescriptor.lodMaxClamp=0;
// resizeSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
resizeSamplerDescriptor.maxAnisotropy=16;
wsd.at(1,1)=resizeSamplerDescriptor;

WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayoutIn;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayoutOut;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
storageTextureBindingLayoutFloat32.access=WGPU_STORAGE_TEXTURE_ACCESS_WRITE_ONLY;
storageTextureBindingLayoutFloat32.format=wtf.at(2,2);
storageTextureBindingLayoutFloat32.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
storageTextureBindingLayoutFloat.access=WGPU_STORAGE_TEXTURE_ACCESS_WRITE_ONLY;
storageTextureBindingLayoutFloat.format=wtf.at(0,0);
storageTextureBindingLayoutFloat.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayoutFloat;
WGPU_StorageTextureBindingLayout.at(1,1,1)=storageTextureBindingLayoutFloat32;

videoTextureViewDescriptor.format=wtf.at(2,2);
videoTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
videoTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
videoTextureViewDescriptor.baseMipLevel=0; // default = 0
videoTextureViewDescriptor.mipLevelCount=1;
videoTextureViewDescriptor.baseArrayLayer=0; // default = 0
videoTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(2,2)=videoTextureViewDescriptor;


WGpuComputePassTimestampWrites computePassTimestampWrites={};
computePassTimestampWrites.querySet=0;
computePassDescriptor.timestampWrites=computePassTimestampWrites;
WGPU_ComputePassDescriptor.at(0,0,0)=computePassDescriptor;

multiSamp.count=1;
multiSamp.mask=-1;
multiSamp2.count=1;
multiSamp2.mask=-1;

colorTarget32.format=wtf.at(2,2); // wtf.at(0,0);
colorTarget32.writeMask=15;
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=15;
depthState2.format=wtf.at(4,4);
depthState2.depthWriteEnabled=0;
depthState2.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
depthState.format=wtf.at(4,4);
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;

priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
priState.frontFace=WGPU_FRONT_FACE_CCW; // Defaults to WGPU_FRONT_FACE_CCW ('ccw')
priState.cullMode=WGPU_CULL_MODE_FRONT; // Defaults to WGPU_CULL_MODE_NONE ('none')
priState.unclippedDepth=EM_FALSE; // defaults to EM_FALSE.

videoSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
videoSamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
videoSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
videoSamplerDescriptor.lodMinClamp=0;
videoSamplerDescriptor.lodMaxClamp=0;  //  default=32
// videoSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
videoSamplerDescriptor.maxAnisotropy=32;
wsd.at(0,0)=videoSamplerDescriptor;

texid.at(0,0)=77;
extTextureDescriptor.source=texid.at(0,0);
extTextureDescriptor.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
wetd.at(0,0)=extTextureDescriptor;
// extTexture=wgpu_device_import_external_texture(wd.at(0,0),&wetd.at(0,0));
// wet.at(0,0)=extTexture;
xyz.x=0;
xyz.y=0;
xyz.z=0;

samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_FILTERING;
wsbl.at(1,1)=samplerBindingLayout;

colorTextureViewDescriptor.format=wtf.at(0,0);
colorTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
colorTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
colorTextureViewDescriptor.baseMipLevel=0; // default = 0
colorTextureViewDescriptor.mipLevelCount=1;
colorTextureViewDescriptor.baseArrayLayer=0; // default = 0
colorTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(1,1)=colorTextureViewDescriptor;

options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;

