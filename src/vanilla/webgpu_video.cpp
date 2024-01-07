#include "../../include/vanilla/main_render.hpp"
WGpuTextureView depthTextureView;
WGpuTextureView colorTextureView;
WGpuTextureView videoTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuTextureViewDescriptor videoTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment;
WGpuTexture depthTexture;
WGpuTexture colorTexture;
WGpuTexture videoTexture;
WGpuSampler videoSampler={};
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
WGpuBufferDescriptor bufferDescriptorSrc={};
WGpuBufferDescriptor bufferDescriptorDst={};
// WGpuPipelineLayoutDescriptor renderPipelineLayoutDesc;  // unused by webgpu.h
// WGpuPipelineLayout pipeline_layout=0;
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayoutEntry bindgroup_layout_entries[3]={};
WGpuBindGroupEntry bindgroup_entries[3]={};
WGpuBindGroup bindgroup=0;
// WGpuRenderPipelineDescriptor renderPipelineDesc;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};
WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuBuffer uniBuffer;
WGpuBuffer srcBuffer;
WGpuBuffer dstBuffer;
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayout1={};
WGpuSamplerBindingLayout samplerBindingLayout={};
WGpuImageCopyExternalImage videoFrm={};
WGPUImageCopyBuffer videoFrmBfrSrc={};
WGPUImageCopyBuffer videoFrmBfrDst={};
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

static i_tensor sze=i_tensor{2,2};
static wce_tensor wce=wce_tensor{2,2};
static wrpe_tensor wrpe=wrpe_tensor{2,2};
static wcb_tensor wcb=wcb_tensor{2,2};
static wd_tensor wd=wd_tensor{2,2};
static wq_tensor wq=wq_tensor{2,2};
static wa_tensor wa=wa_tensor{2,2};
static wcc_tensor wcc=wcc_tensor{2,2};
static wccf_tensor wccf=wccf_tensor{2,2};
static wrp_tensor wrp=wrp_tensor{2,2};
static wrpl_tensor wrpl=wrpl_tensor{2,2};
static wb_tensor wb=wb_tensor{5,5};
static wbgle_tensor wbgle=wbgle_tensor{2,2};
static wbge_tensor wbge=wbge_tensor{2,2};
static wbgl_tensor wbgl=wbgl_tensor{2,2};
static wbg_tensor wbg=wbg_tensor{2,2};
static wrpd_tensor wrpd=wrpd_tensor{2,2};
static wrpca_tensor wrpca=wrpca_tensor{2,2};
static wbbl_tensor wbbl=wbbl_tensor{2,2};
static wsbl_tensor wsbl=wsbl_tensor{2,2};
static wbd_tensor wbd=wbd_tensor{5,5};
static wao_tensor wao=wao_tensor{2,2};
static wdd_tensor wdd=wdd_tensor{2,2};
static u64_tensor u64_uni=u64_tensor{4,4};
static u64_tensor u64_siz=u64_tensor{4,4};
static wrbe_tensor wrbe=wrbe_tensor{2,2};
static wrbed_tensor wrbed=wrbed_tensor{2,2};
static wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
static wt_tensor wt=wt_tensor{2,2};
static wtd_tensor wtd=wtd_tensor{2,2};
static wtvd_tensor wtvd=wtvd_tensor{3,3};
static wtf_tensor wtf=wtf_tensor{5,5};
static wtv_tensor wtv=wtv_tensor{3,3};
static wicb_tensor wicb=wicb_tensor{3,3};
static wicei_tensor wicei=wicei_tensor{2,2};
static js_tensor js_data_pointer=js_tensor{2,2};
static u64_tensor u64_bfrSze=u64_tensor{4,4};
static wict_tensor wict=wict_tensor{4,4};
static wsd_tensor wsd=wsd_tensor{2,2};
static ws_tensor ws=ws_tensor{2,2};

/*
const char *vertexShader =
"@vertex\n"
"fn main(@builtin(vertex_index) vertexIndex : u32) -> @builtin(position) vec4<f32> {\n"
"var pos = array<vec2<f32>, 6>(\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(1.0f, -1.0f),\n"
"vec2<f32>(-1.0f, -1.0f),\n"
"vec2<f32>(-1.0f, 1.0f),\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, -1.0f)\n"
");\n"
"return vec4<f32>(pos[vertexIndex], 0.0f, 1.0f);\n"
"}\n";
*/


const char * vertexShadera=
"struct VertexOutput {\n"
"@builtin(position) Position : vec4<f32>,\n"
"@location(0) fragUV : vec2<f32>\n"
"};\n"
"@vertex\n"
"fn main(@builtin(vertex_index) VertexIndex : u32) -> VertexOutput {\n"
"const pos = array<vec2<f32>, 6>(\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, -1.0f),\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(1.0f, -1.0f),\n"
"vec2<f32>(-1.0f, -1.0f)\n"
");\n"
"const uv = array<vec2<f32>, 6>(\n"
"vec2(1.0f, 0.0f),\n"
"vec2(1.0f, 1.0f),\n"
"vec2(0.0f, 1.0f),\n"
"vec2(1.0f, 0.0f),\n"
"vec2(0.0f, 1.0f),\n"
"vec2(0.0f, 0.0f)\n"
");\n"
"var output : VertexOutput;\n"
"output.Position = vec4(pos[VertexIndex], 0.0f, 1.0f);\n"
"output.fragUV = uv[VertexIndex];\n"
"return output;\n"
"}\n";


const char * vertexShaderb=
"struct VertexOutput {\n"
"@builtin(position) Position : vec4<f32>,\n"
"@location(0) fragUV : vec2<f32>\n"
"};\n"
"@vertex\n"
"fn main(@builtin(vertex_index) VertexIndex : u32) -> VertexOutput {\n"
"const pos = array<vec4<f32>, 36>(\n"
"vec4<f32>( 1.0f, -1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   -1.0f, -1.0f, 1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, -1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   1.0f, -1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   1.0f, -1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   -1.0f, -1.0f, -1.0f, 1.0f ),\n"

 "vec4<f32>(   1.0f, 1.0f, 1.0f, 1.0f    ),\n"
 "vec4<f32>(   1.0f, -1.0f, 1.0f, 1.0f  ),\n"
  "vec4<f32>(  1.0f, -1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   1.0f, 1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   1.0f, 1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   1.0f, -1.0f, -1.0f, 1.0f ),\n"

 "vec4<f32>(   -1.0f, 1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   1.0f, 1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   1.0f, 1.0f, -1.0f, 1.0f  ),\n"
 "vec4<f32>(   -1.0f, 1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, 1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   1.0f, 1.0f, -1.0f, 1.0f  ),\n"

 "vec4<f32>(   -1.0f, -1.0f, 1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, 1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   -1.0f, 1.0f, -1.0f, 1.0f ),\n"
  "vec4<f32>(  -1.0f, -1.0f, -1.0f, 1.0f ),\n"
"vec4<f32>(    -1.0f, -1.0f, 1.0f, 1.0f ),\n"
  "vec4<f32>(  -1.0f, 1.0f, -1.0f, 1.0f ),\n"

 "vec4<f32>(   1.0f, 1.0f, 1.0f, 1.0f   ),\n"
 "vec4<f32>(   -1.0f, 1.0f, 1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, -1.0f, 1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, -1.0f, 1.0f, 1.0f ),\n"
 "vec4<f32>(   1.0f, -1.0f, 1.0f, 1.0f  ),\n"
 "vec4<f32>(   1.0f, 1.0f, 1.0f, 1.0f  ),\n"

 "vec4<f32>(   1.0f, -1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, -1.0f, -1.0f, 1.0f),\n"
 "vec4<f32>(   -1.0f, 1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   1.0f, 1.0f, -1.0f, 1.0f   ),\n"
"vec4<f32>(    1.0f, -1.0f, -1.0f, 1.0f ),\n"
 "vec4<f32>(   -1.0f, 1.0f, -1.0f, 1.0f )\n"
");\n"
"const uv = array<vec2<f32>, 36>(\n"
"vec2( 1.0f, 1.0f),\n"
"vec2(     0.0f, 1.0f),\n"
"vec2(     0.0f, 0.0f),\n"
"vec2(   1.0f, 0.0f),\n"
"vec2(     1.0f, 1.0f),\n"
"vec2(    0.0f, 0.0f),\n"

 "vec2(  1.0f, 1.0f),\n"
 "vec2(    0.0f, 1.0f),\n"
 "vec2(    0.0f, 0.0f),\n"
 "vec2(    1.0f, 0.0f),\n"
 "vec2(    1.0f, 1.0f),\n"
"vec2(    0.0f, 0.0f),\n"

"vec2(    1.0f, 1.0f),\n"
 "vec2(  0.0f, 1.0f),\n"
 "vec2(   0.0f, 0.0f),\n"
"vec2(   1.0f, 0.0f),\n"
"vec2(   1.0f, 1.0f),\n"
"vec2(    0.0f, 0.0f),\n"

 "vec2(    1.0f, 1.0f),\n"
"vec2(     0.0f, 1.0f),\n"
"vec2(     0.0f, 0.0f),\n"
"vec2(     1.0f, 0.0f),\n"
"vec2(    1.0f, 1.0f),\n"
"vec2(   0.0f, 0.0f),\n"

 "vec2(   1.0f, 1.0f),\n"
 "vec2(  0.0f, 1.0f),\n"
 "vec2( 0.0f, 0.0f),\n"
 "vec2(    0.0f, 0.0f),\n"
 "vec2(   1.0f, 0.0f),\n"
 "vec2(   1.0f, 1.0f),\n"

"vec2(     1.0f, 1.0f),\n"
"vec2(    0.0f, 1.0f),\n"
"vec2(    0.0f, 0.0f),\n"
"vec2(   1.0f, 0.0f),\n"
 "vec2(  1.0f, 1.0f),\n"
 "vec2(    0.0f, 0.0f)\n"
");\n"
"var output : VertexOutput;\n"
"output.Position = vec4(pos[VertexIndex]);\n"
"output.fragUV = uv[VertexIndex];\n"
"return output;\n"
"}\n";

const char * frag_body=
"@group(0) @binding(0) var <uniform> iTime : u32;\n"
"@group(0) @binding(1) var mySampler : sampler;\n"
"@group(0) @binding(2) var myTexture : texture_2d <f32>;\n"
"@fragment\n"
"fn main(@location(0) fragUV : vec2<f32>) -> @location(0) vec4<f32> {\n"
"return textureSample(myTexture, mySampler, fragUV);\n"
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

static uint8_t * result2=NULL;
static uint8_t * results2=NULL;
static long int length2=0;

inline uint8_t * rd_frm(const char * Fnm2){
FILE * file2=fopen(Fnm,"r");
::boost::tuples::tie(result2,results2,file2);
if(file2){
int32_t stat=fseek(file2,(int32_t)0,SEEK_END);
if(stat!=0){
fclose(file2);
return nullptr;
}
length=ftell(file2);
stat=fseek(file2,(int32_t)0,SEEK_SET);
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


void raf(){
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
wtv.at(2,2)=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
passDesc={};
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(0,0);
passDesc.depthStencilAttachment=wrpdsa.at(0,0);
wrpd.at(0,0)=passDesc;
 uint8_t * fram=(uint8_t*)rd_frm(Fnm2);
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,sze.at(0,0),sze.at(0,0),0.0f,1.0f);
wgpu_queue_write_texture(wq.at(0,0),&wict.at(0,0),fram,sze.at(0,0)*8,sze.at(0,0),sze.at(0,0),sze.at(0,0),1);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),36,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
return;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result,void *userData){
wd.at(0,0)=result;
js_data_pointer.at(0,0)=0;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
// const char * frag_body=(char*)rd_fl(Fnm);
WGPU_TEXTURE_FORMAT canvasFormat=navigator_gpu_get_preferred_canvas_format();
// wtf.at(0,0)=canvasFormat;
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
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_canvas_element_size("canvas",&szhI,&szwI);
sze.at(0,0)=szhI;
sze.at(0,1)=szhI;
multiSamp={};
multiSamp.count=0;
multiSamp.mask=-1;
shaderModuleDescV={};
shaderModuleDescF={};
shaderModuleDescV.code=vertexShadera;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=frag_body;
// shaderModuleDescF.code=fragmentShader;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
WGpuColorTargetState colorTarget={};
colorTarget.format=wtf.at(0,0);
colorTarget.writeMask=15;
depthState={};
depthState.format=WGPU_TEXTURE_FORMAT_DEPTH24PLUS;
depthState.depthWriteEnabled=1;
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
  /*
u64_bfrSze.at(0,0)=sze.at(0,0)*sze.at(0,0)*4;
WGpuBufferDescriptor bufferDescriptorIn={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorOut={u64_bfrSze.at(0,0),WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
wbd.at(3,3)=bufferDescriptorIn;
wbd.at(4,4)=bufferDescriptorOut;
srcBuffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(3,3));
dstBuffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(4,4));
wb.at(3,3)=srcBuffer;
wb.at(4,4)=dstBuffer;
wicb.at(1,1)=videoFrmBfrDst;
WGpuOrigin2D xy={};
xy.x=0;
xy.y=0;
// videoFrm.source; // must point to a WGpuImageBitmap (could also point to a HTMLVideoElement, HTMLCanvasElement or OffscreenCanvas, but those are currently unimplemented)
videoFrm.origin=xy;
videoFrm.flipY=EM_FALSE;
  */
videoSamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_REPEAT;
videoSamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_REPEAT;
videoSamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_REPEAT;
videoSamplerDescriptor.magFilter=WGPU_FILTER_MODE_NEAREST;
videoSamplerDescriptor.minFilter=WGPU_FILTER_MODE_NEAREST;
videoSamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_NEAREST;
videoSamplerDescriptor.lodMinClamp=0;
videoSamplerDescriptor.lodMaxClamp=32;
// videoSamplerDescriptor.compare;  // default = WGPU_COMPARE_FUNCTION_INVALID (not used)
videoSamplerDescriptor.maxAnisotropy=1;
wsd.at(0,0)=videoSamplerDescriptor;
videoSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
ws.at(0,0)=videoSampler;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoTextureDescriptor.format=wtf.at(0,0);
videoTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
videoTextureDescriptor.width=sze.at(0,0);
videoTextureDescriptor.height=sze.at(0,0); // default = 1;
videoTextureDescriptor.depthOrArrayLayers=2;
videoTextureDescriptor.mipLevelCount=1;
videoTextureDescriptor.sampleCount=1;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
WGPU_TEXTURE_FORMAT videoViewFormats[1]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0; // &videoViewFormats[0];
videoTextureDescriptor.viewFormats=nullptr;// &videoViewFormats[0];
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
WGpuOrigin3D xyz={};
xyz.x=0;
xyz.y=0;
xyz.z=0;
WGpuImageCopyTexture videoTextureCopy;
videoTextureCopy.texture=wt.at(2,2);
videoTextureCopy.mipLevel=0;
videoTextureCopy.origin=xyz;
videoTextureCopy.aspect=WGPU_TEXTURE_ASPECT_ALL;
// videoTextureCopy.colorSpace
// videoTextureCopy.premultipliedAlpha
wict.at(0,0)=videoTextureCopy;
bufferDescriptorUni={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptorUni;
uniBuffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptorUni);
wb.at(0,0)=uniBuffer;
bufferBindingLayout1.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayout1.hasDynamicOffset=0,
bufferBindingLayout1.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayout1;
textureBindingLayout1.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
// textureBindingLayout1.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UNFILTERABLE_FLOAT;
// textureBindingLayout1.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UINT;
textureBindingLayout1.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout1.multisampled=0;
samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_FILTERING;
// samplerBindingLayout.type=WGPU_SAMPLER_BINDING_TYPE_NON_FILTERING;
wsbl.at(1,1)=samplerBindingLayout;
bindgroup_layout_entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[0].binding=0;
bindgroup_layout_entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[0].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[1].binding=1;
bindgroup_layout_entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
bindgroup_layout_entries[1].layout.sampler=wsbl.at(1,1);
bindgroup_layout_entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[2].binding=2;
bindgroup_layout_entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
bindgroup_layout_entries[2].layout.texture=textureBindingLayout1;
wbgle.at(0,0)=bindgroup_layout_entries;
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
renderPipelineDesc.multisample=multiSamp;
wrp.at(0,0)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc);
bindgroup_entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[0].binding=0;
bindgroup_entries[0].resource=wb.at(0,0);
bindgroup_entries[0].bufferBindOffset=0;
bindgroup_entries[0].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[1].binding=1;
bindgroup_entries[1].resource=ws.at(0,0);
bindgroup_entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[2].binding=2;
bindgroup_entries[2].resource=wtv.at(2,2);
wbge.at(0,0)=bindgroup_entries;
// renderBundleEncoderDescriptor.sampleCount=1;
// renderBundleEncoderDescriptor.depthStencilFormat=WGPU_TEXTURE_FORMAT_DEPTH24PLUS_STENCIL8;
// wrbed.at(0,0)=renderBundleEncoderDescriptor;
// renderBundleEncoder=wgpu_device_create_render_bundle_encoder(wd.at(0,0),&wrbed.at(0,0));
// wrbe.at(0,0)=renderBundleEncoder;
emscripten_get_element_css_size("canvas",&szh,&szw);
emscripten_get_canvas_element_size("canvas",&szhI,&szwI);
u64_siz.at(0,0)=szhI;
sze.at(0,0)=szh;
// sze.at(1,1)=szhI;
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
emscripten_set_main_loop_timing(2,1);
emscripten_set_main_loop((void(*)())raf,0,0);
// emscripten_request_animation_frame_loop(raf,0);
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
WGPU_FEATURES_BITFIELD ftr=wgpu_adapter_or_device_get_features(wa.at(0,0));
deviceDesc.requiredFeatures=ftr;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(){
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options.powerPreference=WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
}

EM_BOOL framm(uint8_t * em){
js_data_pointer.at(0,0)=em;
return EM_TRUE;
}

extern "C"{

void frm(uint8_t * h){
framm(h);
return;
}

}

/*
const context = cnvb.getContext("webgpu");
const gpu = navigator.gpu;
const format = gpu.getPreferredCanvasFormat();
const adapter = await gpu.requestAdapter();
const device = await adapter.requestDevice();
context.configure({ device, format, alphaMode: "opaque" });
let texture = device.createTexture({
format: "rgba8unorm",
size: [SiZ, SiZ, 2],
usage:
GPUTextureUsage.COPY_DST |
GPUTextureUsage.RENDER_ATTACHMENT |
GPUTextureUsage.TEXTURE_BINDING,
}); 
device.queue.writeTexture({texture,bytesPerRow: 4 * cnv.height,rowsPerImage: cnv.height,}, pixelData.buffer, pixelData.byteOffset,[texture.size[0], texture.size[1], 2]);
const textureData = new Uint8Array(cnv.height * cnv.height * 4); // Assuming RGBA format
device.queue.readTexture({texture,bytesPerRow: 4 * cnv.width,rowsPerImage: cnv.height,}, textureData.buffer, textureData.byteOffset, [texture.size[0],texture.size[1], 2]);
*/

EM_JS(void,js_main,(),{
FS.mkdir('/shader');
FS.mkdir('/video');

async function videoFrames(){
let SiZ=parseInt(window.innerHeight);
let dSiz=SiZ*SiZ*4;
let vv=document.getElementById('mv');
let cnv=document.getElementById('bcanvas');
let cnvb=document.getElementById('canvas');
// const H=Module.HEAPU8.buffer;
const gl2=cnv.getContext('2d',{willReadFrequently:true});
gl2.drawImage(vv,0,0);
let imageData=gl2.getImageData(0,0,cnv.width,cnv.height);
setInterval(function(){
gl2.drawImage(vv,0,0);
imageData=gl2.getImageData(0,0,cnv.height,cnv.height);
var pixelData=new Uint8Array(imageData.data.buffer);
var heapArray=new Uint8Array(H);
FS.writeFile('/video/frame.gl',pixelData);

// heapArray.set(pixelData);
// Module.ccall("frm",null,["Number"],[0]);
},50);
}
  
function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('canvas').height=parseInt(window.innerHeight,10);
document.getElementById('bcanvas').height=parseInt(window.innerHeight,10);
document.getElementById('canvas').width=parseInt(window.innerHeight,10);
document.getElementById('bcanvas').width=parseInt(window.innerHeight,10);
document.getElementById('di').click();
videoFrames();
Module.ccall("startWebGPU");
},500);
document.getElementById('status').style.backgroundColor="green";
}
document.getElementById('status').height=20;
document.getElementById('status').width=parseInt(window.innerHeight,10);
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
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);
});

extern"C"{

void startWebGPU(){
WGPU_Start();
}

}

int main(){
js_main();
return 0;
}
