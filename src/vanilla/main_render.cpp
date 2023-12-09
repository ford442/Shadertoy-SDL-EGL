#include "../../include/vanilla/main_render.hpp"

WGpuTextureView depthTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment;
WGpuRenderPassDepthStencilAttachment depthAttachment;
WGpuDepthStencilState depthState={};
WGpuTexture depthTexture;
WGpuTextureDescriptor depthTextureDescriptor={};
WGpuRenderPassDescriptor passDesc={};
WGpuCanvasConfiguration config;
WGpuShaderModuleDescriptor shaderModuleDescV={};
WGpuShaderModuleDescriptor shaderModuleDescF={};
WGpuShaderModule vs;
WGpuShaderModule fs;
WGpuVertexState vertState;
WGpuPrimitiveState priState;
WGpuFragmentState fragState;
WGpuBufferDescriptor bufferDescriptorU={};
// WGpuPipelineLayoutDescriptor renderPipelineLayoutDesc;  // unused by webgpu.h
// WGpuPipelineLayout pipeline_layout=0;
WGpuBindGroupLayout bindgroup_layout=0;
WGpuBindGroupLayoutEntry bindgroup_layout_entry={};
WGpuBindGroupEntry bindgroup_entry={};
WGpuBindGroup bindgroup=0;
// WGpuRenderPipelineDescriptor renderPipelineDesc;
WGpuRenderBundleEncoder renderBundleEncoder;
WGpuRenderBundleEncoderDescriptor renderBundleEncoderDescriptor={};

WGpuDeviceDescriptor deviceDesc={};
WGpuMultisampleState multiSamp;
WGpuBuffer uniBuffer;
WGpuBufferBindingLayout bufferBindingLayout1={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
double szh,szw;

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

static f_tensor sze=f_tensor{2,2};
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
static wb_tensor wb=wb_tensor{2,2};
static wbgle_tensor wbgle=wbgle_tensor{2,2};
static wbge_tensor wbge=wbge_tensor{2,2};
static wbgl_tensor wbgl=wbgl_tensor{2,2};
static wbg_tensor wbg=wbg_tensor{2,2};
static wrpd_tensor wrpd=wrpd_tensor{2,2};
static wrpca_tensor wrpca=wrpca_tensor{2,2};
static wbbl_tensor wbbl=wbbl_tensor{2,2};
static wbd_tensor wbd=wbd_tensor{2,2};
static wao_tensor wao=wao_tensor{2,2};
static wdd_tensor wdd=wdd_tensor{2,2};
static u64_tensor u64_uni=u64_tensor{4,4};
static tp_tensor tp=tp_tensor{2,2};
static wrbe_tensor wrbe=wrbe_tensor{2,2};
static wrbed_tensor wrbed=wrbed_tensor{2,2};
static wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};

const char *vertexShader =
"@vertex\n"
"fn main(@builtin(vertex_index) vertexIndex : u32) -> @builtin(position) vec4<f32> {\n"
"var pos = array<vec2<f32>, 4>(\n"
"vec2<f32>(-5.0, 0.5),\n"
"vec2<f32>(0.5, -0.5),\n"
"vec2<f32>(0.5, 0.5),\n"
"vec2<f32>(-0.5, 0.5)\n"
");\n"
"var posCCW = array<vec2<f32>, 4>(\n"
"vec2<f32>(-1.0, -1.0),\n"
"vec2<f32>(1.0, -1.0),\n"
"vec2<f32>(1.0, 1.0),\n"
"vec2<f32>(-1.0, 1.0)\n"
");\n"
"var posCW = array<vec2<f32>, 4>(\n"
"vec2<f32>(1.0, 1.0),\n"
"vec2<f32>(1.0, -1.0),\n"
"vec2<f32>(-1.0, -1.0),\n"
"vec2<f32>(-1.0, 1.0)\n"
");\n"
"return vec4<f32>(posCW[vertexIndex], 0.0, 1.0);\n"
"}\n";

const char *vertexShader2=
"var<private> gl_Position : vec4<f32>;\n"
"@vertex\n"
"fn main(@location(0) position : vec4<f32>) -> @builtin(position) vec4<f32> {\n"
"gl_Position = position;\n"
"return gl_Position;\n"
"}\n";
  
const char *vertexShader3=
"var<private> iPosition : vec4<f32>;\n"
"var<private> gl_Position : vec4<f32>;\n"
"fn main_1() {\n"
"let x_15 : vec4<f32> = iPosition;\n"
"gl_Position = x_15;\n"
"return;\n"
"}\n"
"struct main_out {\n"
"@builtin(position)\n"
"gl_Position : vec4<f32>,\n"
"}\n"
"@vertex\n"
"fn main(@location(0) iPosition_param : vec4<f32>) -> main_out {\n"
"iPosition = iPosition_param;\n"
"main_1();\n"
"return main_out(gl_Position);\n"
"}\n";

const char *fragmentShader2 =
"@fragment\n"
"fn main() -> @location(0) vec4<f32> {\n"
"return vec4<f32>(1.0, 0.0, 0.73, 1.0);\n"
"}\n";
  
const char *fragmentShader =
"@group(0)@binding(0)var<uniform>iTime:u32;"
"var<private> fragColor_1 : vec4<f32>;\n"
"var<private> gl_FragCoord : vec4<f32>;\n"
"fn bas_vf3_(x : ptr<function, vec3<f32>>) -> vec3<f32> {\n"
"var i : vec3<f32>;\n"
"var f : vec3<f32>;\n"
"var s : vec3<f32>;\n"
"var k : vec3<f32>;\n"
"let x_32 : vec3<f32> = *(x);\n"
"i = floor(x_32);\n"
"let x_35 : vec3<f32> = *(x);\n"
"f = fract(x_35);\n"
"let x_38 : vec3<f32> = *(x);\n"
"s = sign((fract((x_38 / vec3<f32>(2.0f, 2.0f, 2.0f))) - vec3<f32>(0.5f, 0.5f, 0.5f)));\n"
"let x_52 : vec3<f32> = i;\n"
"let x_54 : vec3<f32> = i;\n"
"k = fract(((vec3<f32>(0.22062349319458007812f, 0.68507498502731323242f, 0.88257539272308349609f) * x_52) + vec3<f32>(x_54.y, x_54.z, x_54.x)));\n"
"let x_58 : vec3<f32> = s;\n"
"let x_59 : vec3<f32> = f;\n"
"let x_61 : vec3<f32> = f;\n"
"let x_67 : vec3<f32> = k;\n"
"let x_72 : vec3<f32> = f;\n"
"let x_74 : vec3<f32> = f;\n"
"return (((x_58 * x_59) * (x_61 - vec3<f32>(1.0f, 1.0f, 1.0f))) * (((((x_67 * 16.0f) - vec3<f32>(4.0f, 4.0f, 4.0f)) * x_72) * (x_74 - vec3<f32>(1.0f, 1.0f, 1.0f))) - vec3<f32>(1.0f, 1.0f, 1.0f)));\n"
"}\n"
"fn swayRandomized_vf3_vf3_(seed : ptr<function, vec3<f32>>, value : ptr<function, vec3<f32>>) -> vec3<f32> {\n"
"var param : vec3<f32>;\n"
"var param_1 : vec3<f32>;\n"
"var param_2 : vec3<f32>;\n"
"let x_83 : vec3<f32> = *(seed);\n"
"let x_84 : vec3<f32> = *(value);\n"
"let x_87 : vec3<f32> = *(seed);\n"
"let x_89 : vec3<f32> = *(value);\n"
"param = (vec3<f32>(x_87.z, x_87.x, x_87.y) + vec3<f32>(x_89.y, x_89.z, x_89.x));\n"
"let x_93 : vec3<f32> = bas_vf3_(&(param));\n"
"let x_95 : vec3<f32> = *(seed);\n"
"let x_97 : vec3<f32> = *(value);\n"
"param_1 = (vec3<f32>(x_95.y, x_95.z, x_95.x) + x_97);\n"
"let x_100 : vec3<f32> = bas_vf3_(&(param_1));\n"
"param_2 = (((x_83 + vec3<f32>(x_84.z, x_84.x, x_84.y)) - x_93) + x_100);\n"
"let x_103 : vec3<f32> = bas_vf3_(&(param_2));\n"
"return x_103;\n"
"}\n"
"fn cosmic_vf3_vf3_(c : ptr<function, vec3<f32>>, con : ptr<function, vec3<f32>>) -> vec3<f32> {\n"
"var param_3 : vec3<f32>;\n"
"var param_4 : vec3<f32>;\n"
"let x_106 : vec3<f32> = *(con);\n"
"let x_108 : vec3<f32> = *(c);\n"
"param_3 = x_108;\n"
"let x_110 : vec3<f32> = *(con);\n"
"param_4 = x_110;\n"
"let x_111 : vec3<f32> = swayRandomized_vf3_vf3_(&(param_3), &(param_4));\n"
"return ((x_106 + x_111) * 0.5f);\n"
"}\n"
"fn mainImage_vf4_vf2_(fragColor : ptr<function, vec4<f32>>, fragCoord : ptr<function, vec2<f32>>) {\n"
"var uv : vec2<f32>;\n"
"var param_5 : vec3<f32>;\n"
"var param_6 : vec3<f32>;\n"
"var aTime : f32;\n"
"var adj : vec3<f32>;\n"
"var s_1 : vec3<f32>;\n"
"var param_7 : vec3<f32>;\n"
"var param_8 : vec3<f32>;\n"
"var c_1 : vec3<f32>;\n"
"var param_9 : vec3<f32>;\n"
"var param_10 : vec3<f32>;\n"
"var con_1 : vec3<f32>;\n"
"var param_11 : vec3<f32>;\n"
"var param_12 : vec3<f32>;\n"
"var param_13 : vec3<f32>;\n"
"var param_14 : vec3<f32>;\n"
"let x_117 : vec2<f32> = *(fragCoord);\n"
"let x_128 : vec2<f32> = *(fragCoord);\n"
"param_5 = vec3<f32>(0.55436635017395019531f, 0.58203977346420288086f, 0.82431572675704956055f);\n"
"param_6 = (vec3<f32>(0.20092695951461791992f, 0.13512679934501647949f, 0.14187219738960266113f) - (vec3<f32>(x_128.y, x_128.x, x_128.y) * 0.00400000018998980522f));\n"
"let x_135 : vec3<f32> = swayRandomized_vf3_vf3_(&(param_5), &(param_6));\n"
"uv = ((x_117 * 0.10000000149011611938f) + (vec2<f32>(x_135.x, x_135.y) * 42.0f));\n"
"aTime = f32(iTime)/100000.0f;\n"
"adj = vec3<f32>(-1.11000001430511474609f, 1.40999996662139892578f, 1.61000001430511474609f);\n"
"let x_153 : f32 = aTime;\n"
"let x_154 : vec3<f32> = adj;\n"
"param_7 = vec3<f32>(34.0f, 76.0f, 59.0f);\n"
"param_8 = (vec3<f32>(x_153, x_153, x_153) + x_154);\n"
"let x_159 : vec3<f32> = swayRandomized_vf3_vf3_(&(param_7), &(param_8));\n"
"s_1 = (x_159 * 0.25f);\n"
"let x_167 : f32 = aTime;\n"
"let x_168 : vec3<f32> = adj;\n"
"param_9 = vec3<f32>(27.0f, 67.0f, 45.0f);\n"
"param_10 = (vec3<f32>(x_167, x_167, x_167) - vec3<f32>(x_168.y, x_168.z, x_168.x));\n"
"let x_174 : vec3<f32> = swayRandomized_vf3_vf3_(&(param_9), &(param_10));\n"
"c_1 = (x_174 * 0.25f);\n"
"let x_181 : f32 = aTime;\n"
"let x_183 : vec3<f32> = c_1;\n"
"let x_187 : f32 = uv.x;\n"
"let x_190 : vec3<f32> = s_1;\n"
"let x_193 : f32 = uv.y;\n"
"con_1 = (((vec3<f32>(0.00043750001350417733f, 0.00056249997578561306f, 0.00081250001676380634f) * x_181) + (x_183 * x_187)) + (x_190 * x_193));\n"
"param_11 = vec3<f32>(0.58203977346420288086f, 0.82431572675704956055f, 0.55436635017395019531f);\n"
"let x_199 : vec3<f32> = con_1;\n"
"param_12 = x_199;\n"
"let x_200 : vec3<f32> = cosmic_vf3_vf3_(&(param_11), &(param_12));\n"
"con_1 = x_200;\n"
"param_13 = vec3<f32>(2.20003986358642578125f, 2.44231581687927246094f, 2.17236638069152832031f);\n"
"let x_207 : vec3<f32> = con_1;\n"
"param_14 = x_207;\n"
"let x_208 : vec3<f32> = cosmic_vf3_vf3_(&(param_13), &(param_14));\n"
"con_1 = x_208;\n"
"let x_209 : vec3<f32> = con_1;\n"
"let x_215 : vec3<f32> = ((sin((x_209 * 3.14159989356994628906f)) * 0.5f) + vec3<f32>(0.5f, 0.5f, 0.5f));\n"
"*(fragColor) = vec4<f32>(x_215.x, x_215.y, x_215.z, 1.0f);\n"
"return;\n"
"}\n"
"fn main_1() {\n"
"var param_15 : vec4<f32>;\n"
"var param_16 : vec2<f32>;\n"
"let x_226 : vec4<f32> = gl_FragCoord;\n"
"param_16 = vec2<f32>(x_226.x, x_226.y);\n"
"mainImage_vf4_vf2_(&(param_15), &(param_16));\n"
"let x_229 : vec4<f32> = param_15;\n"
"fragColor_1 = x_229;\n"
"return;\n"
"}\n"
"struct main_out {\n"
"@location(0)\n"
"fragColor_1_1 : vec4<f32>,\n"
"}\n"
"@fragment\n"
"fn main(@builtin(position) gl_FragCoord_param : vec4<f32>) -> main_out {\n"
"gl_FragCoord = gl_FragCoord_param;\n"
"main_1();\n"
"return main_out(fragColor_1);\n"
"}\n\0";
  
// int raf(double time,void *userData){
void raf(){
u64_uni.at(3,3)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u64_uni.at(0,0)=u_time.time_spana.count()*1000;
u64_uni.at(1,1)=u_time.time_spanb.count()*1000;
// u64_uni.at(2,2)=u_time.time_spanb.count()/1.0f;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),&wbge.at(0,0),1);
wbg.at(0,0)=bindgroup;
wce.at(0,0)=wgpu_device_create_command_encoder(wd.at(0,0),0);
colorAttachment={WGPU_RENDER_PASS_COLOR_ATTACHMENT_DEFAULT_INITIALIZER};
colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(wcc.at(0,0)),0);
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.clearValue.r=1.0f;
colorAttachment.clearValue.g=0.0f;
colorAttachment.clearValue.b=1.0f;
colorAttachment.clearValue.a=1.0f;
depthTextureViewDescriptor.format=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
depthTextureViewDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL
depthTextureViewDescriptor.baseMipLevel=1; // default = 0
depthTextureViewDescriptor.mipLevelCount=1;
depthTextureViewDescriptor.baseArrayLayer=1; // default = 0
depthTextureViewDescriptor.arrayLayerCount=1;
  
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor.format=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers = 1;
depthTextureDescriptor.mipLevelCount= 1;
depthTextureDescriptor.sampleCount = 1;
depthTextureDescriptor.dimension= WGPU_TEXTURE_DIMENSION_2D;

  
depthTexture=wgpu_device_create_texture(wd.at(0,0),&depthTextureDescriptor);
depthAttachment.view=wgpu_texture_create_view(depthTexture,&depthTextureViewDescriptor);
depthAttachment.depthClearValue=1.0f;
depthAttachment.stencilClearValue=0;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.depthStoreOp=WGPU_STORE_OP_STORE;
depthAttachment.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.stencilStoreOp=WGPU_STORE_OP_STORE;
passDesc={};
wrpca.at(0,0)=colorAttachment;
wrpdsa.at(0,0)=depthAttachment;

passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(0,0);
wrpd.at(0,0)=passDesc;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
// fixed (mixin encoder)
// set bind ground needs WGPU Render Pass Encoder - not CommandEncoder
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
  wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,sze.at(0,0),sze.at(0,0),0.0,1.0);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),4,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
return;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result, void *userData){
wd.at(0,0)=result;
wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
config=WGPU_CANVAS_CONFIGURATION_DEFAULT_INITIALIZER;
config.device=wd.at(0,0);
config.format=navigator_gpu_get_preferred_canvas_format();
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
multiSamp={};
multiSamp.count=1;
multiSamp.mask=-1;
shaderModuleDescV={};
shaderModuleDescF={};
shaderModuleDescV.code=vertexShader;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=fragmentShader;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
WGpuColorTargetState colorTarget={};
colorTarget.format=WGPU_TEXTURE_FORMAT_BGRA8UNORM;
colorTarget.writeMask=15;
depthState.format=WGPU_TEXTURE_FORMAT_DEPTH32FLOAT_STENCIL8;
depthState.depthWriteEnabled=1;
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
bufferDescriptorU={sizeof(uint64_t),WGPU_BUFFER_USAGE_UNIFORM|WGPU_BUFFER_USAGE_COPY_DST,EM_FALSE};
wbd.at(0,0)=bufferDescriptorU;
uniBuffer=wgpu_device_create_buffer(wd.at(0,0),&bufferDescriptorU);
wb.at(0,0)=uniBuffer;
bufferBindingLayout1.type=WGPU_BUFFER_BINDING_TYPE_UNIFORM;
bufferBindingLayout1.hasDynamicOffset=0,
bufferBindingLayout1.minBindingSize=sizeof(uint64_t);
wbbl.at(0,0)=bufferBindingLayout1;
bindgroup_layout_entry={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entry.binding=0;
bindgroup_layout_entry.visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entry.type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entry.layout.buffer=wbbl.at(0,0);
wbgle.at(0,0)=bindgroup_layout_entry;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),&wbgle.at(0,0),1);
wbgl.at(0,0)=bindgroup_layout;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
WGpuRenderPipelineDescriptor renderPipelineDesc={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.primitive=priState;
renderPipelineDesc.fragment=fragState;
  
//  renderPipelineDesc.depthStencil=depthState;

// renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc.layout=wrpl.at(0,0);
renderPipelineDesc.multisample=multiSamp;
wrp.at(0,0)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc);
bindgroup_entry={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entry.binding=0;
bindgroup_entry.resource=wb.at(0,0);
bindgroup_entry.bufferBindOffset=0;
bindgroup_entry.bufferBindSize=sizeof(uint64_t);
wbge.at(0,0)=bindgroup_entry;
renderBundleEncoderDescriptor.sampleCount=4;
wrbed.at(0,0)=renderBundleEncoderDescriptor;
// renderBundleEncoder=wgpu_device_create_render_bundle_encoder(wd.at(0,0),&wrbed.at(0,0));
// wrbe.at(0,0)=renderBundleEncoder;
emscripten_get_element_css_size("canvas",&szw,&szh);
sze.at(0,0)=float(szh);
sze.at(0,1)=float(szw);
system_clock::time_point now=system_clock::now();
tp.at(0,0)=now;
u64_uni.at(0,0)=0;
u64_uni.at(3,3)=0;
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
emscripten_set_main_loop((void(*)())raf,0,0);
// emscripten_request_animation_frame_loop(raf,0);
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

void WGPU_Start(){
WGpuRequestAdapterOptions options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options={WGPU_REQUEST_ADAPTER_OPTIONS_DEFAULT_INITIALIZER};
options.powerPreference=WGPU_POWER_PREFERENCE_LOW_POWER;
options.forceFallbackAdapter=EM_FALSE;
wao.at(0,0)=options;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
}

EM_JS(void,js_main,(),{
function normalResStart(){
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
Module.ccall("startWebGPU");
},100);
document.getElementById('status').style.backgroundColor="green";
}
document.getElementById('pmhig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('ihig').innerHTML=parseInt(window.innerHeight,10);
document.getElementById('scanvas').height=parseInt(window.innerHeight,10);
document.getElementById('scanvas').width=parseInt(window.innerHeight,10);
document.getElementById('canvas').height=parseInt(window.innerHeight,10);
document.getElementById('canvas').width=parseInt(window.innerHeight,10);
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

}

int main(void){
js_main();
return 0;
}
