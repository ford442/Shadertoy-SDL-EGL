#include "../../include/vanilla/webgpu_tex4.hpp"

// #include "../../src/vanilla/webgpu_compute_vars_2.cpp"

int rNd4(int randomMax){
entropySeed=(randomMax)*randomizer();
std::srand(entropySeed);
randomNumber=std::rand()%randomMax;
return randomNumber;
}

const char * rd_fl(const char * Fnm){
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
return result;
}
return nullptr;
}

EM_BOOL getCode(const char * Fnm){
wgsl.at(0,0)=frag_body;
return EM_TRUE;
}

boost::function<EM_BOOL()>render=[](){
u64_uni.at(3,3)++;
u_time.t3=u_time.t2;
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u64_uni.at(0,0)=u_time.time_spana.count()*100u;
u64_uni.at(1,1)=u_time.time_spanb.count()*1000u;
f32_uniform.at(0,0)=float(u_time.time_spana.count())*100.0f;
u64_uni.at(2,2)=u_time.time_spanb.count()/1.0f;
colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
colorAttachment.view=wtv.at(1,1);
colorAttachment.storeOp=WGPU_STORE_OP_STORE; // WGPU_STORE_OP_DISCARD; 
// colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
colorAttachment.clearValue=clearC.at(0,0);
wrpca.at(0,0)=colorAttachment;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
wtv.at(3,3)=INTextureView;
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
wtv.at(4,4)=OUTTextureView;
OUTTexture2View=wgpu_texture_create_view(WGPU_Texture.at(0,0,2),&WGPU_TextureViewDescriptor.at(0,0,2));
wtv.at(5,5)=OUTTexture2View;
videoAttachment.view=wtv.at(3,3);
videoAttachment.storeOp=WGPU_STORE_OP_STORE;
// videoAttachment.loadOp=WGPU_LOAD_OP_LOAD;
videoAttachment.loadOp=WGPU_LOAD_OP_CLEAR;
videoAttachment.clearValue=clearC.at(0,0);
wrpca.at(1,1)=videoAttachment;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
  /*
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0f;
depthAttachment.depthReadOnly=EM_TRUE;
depthAttachment.depthLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.depthStoreOp=WGPU_STORE_OP_DISCARD; // WGPU_STORE_OP_UNDEFINED;
depthAttachment.stencilClearValue=0u;
depthAttachment.stencilReadOnly=EM_TRUE;
depthAttachment.stencilLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment.stencilStoreOp=WGPU_STORE_OP_UNDEFINED;
wrpdsa.at(0,0)=depthAttachment;
depthTextureView2=wgpu_texture_create_view(wt.at(5,5),&wtvd.at(3,3));
wtv.at(5,5)=depthTextureView2;
depthAttachment2.view=wtv.at(5,5);
depthAttachment2.depthClearValue=1.0f;
depthAttachment2.depthReadOnly=EM_TRUE;
depthAttachment2.depthLoadOp=WGPU_LOAD_OP_LOAD;
// depthAttachment2.depthLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment2.depthStoreOp=WGPU_STORE_OP_DISCARD; // WGPU_STORE_OP_UNDEFINED;
depthAttachment2.stencilClearValue=0u;
depthAttachment2.stencilReadOnly=EM_TRUE;
// depthAttachment2.stencilLoadOp=WGPU_LOAD_OP_LOAD;
depthAttachment2.stencilLoadOp=WGPU_LOAD_OP_CLEAR;
depthAttachment2.stencilStoreOp=WGPU_STORE_OP_UNDEFINED;
wrpdsa.at(1,1)=depthAttachment2;
  */
passDesc.numColorAttachments=1;
passDesc.colorAttachments=&wrpca.at(1,1); // &wrpca.at(0,0); // 
// passDesc.depthStencilAttachment=wrpdsa.at(1,1);  //  wrpdsa.at(0,0); //
passDesc.occlusionQuerySet=0;
passDesc.maxDrawCount=6;
renderTimestampWrites.querySet=0;
renderTimestampWrites.beginningOfPassWriteIndex=-1;
renderTimestampWrites.endOfPassWriteIndex=-1;
passDesc.timestampWrites=renderTimestampWrites;
wrpd.at(0,0)=passDesc;
passDesc2.numColorAttachments=1;
passDesc2.colorAttachments=&wrpca.at(0,0); // &wrpca.at(1,1); //
// passDesc2.depthStencilAttachment=wrpdsa.at(0,0);
passDesc2.occlusionQuerySet=0;
passDesc2.maxDrawCount=6;
passDesc2.timestampWrites=renderTimestampWrites;
wrpd.at(1,1)=passDesc2;
/*       //  Frame Data
std::ifstream fram(Fnm2,std::ios::binary);
std::vector<uint8_t> data((std::istreambuf_iterator<char>(fram)),(std::istreambuf_iterator<char>()));
frame_tensor.at(0,0)=data;
  // wetd.at(0,0).source=texid.at(0,0);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&wict.at(2,2),&frame_tensor.at(0,0),sze.at(1,1)*4,sze.at(1,1),sze.at(1,1),sze.at(1,1),1);
*/ 
  //  Render Pass
wceA=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(0,0)=wceA;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
 // wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&u64_siz.at(3,3),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&f32_uniform.at(2,2),sizeof(float));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(1,1),0,&u64_uni.at(3,3),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&f32_uniform.at(0,0),sizeof(float));
  // wgpu_render_pass_encoder_set_index_buffer(wrpe.at(0,0),wb.at(4,4),WGPU_INDEX_FORMAT_UINT32,0,36*sizeof(uint32_t));
// wgpu_render_pass_encoder_set_vertex_buffer(wrpe.at(0,0),0,wb.at(3,3),0,sizeof(Ffvertices));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0f,0.0f,szef.at(1,1),szef.at(1,1),0.0f,1.0f);
wgpu_render_pass_encoder_set_scissor_rect(wrpe.at(0,0),0.0f,0.0f,sze.at(1,1),sze.at(1,1));
wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
// wgpu_render_pass_encoder_draw_indexed(wrpe.at(0,0),36,1,0,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
  //  Render Pass 2  (sampler)
wceA={};
wceB=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(1,1)=wceB;
wrpe.at(1,1)=wgpu_command_encoder_begin_render_pass(wce.at(1,1),&wrpd.at(1,1));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(1,1),wrp.at(1,1));
wgpu_encoder_set_bind_group(wrpe.at(1,1),0,wbg.at(1,1),0,0);
// wgpu_queue_write_buffer(wq.at(0,0),wb.at(5,5),0,&u64_siz.at(2,2),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(5,5),0,&f32_uniform.at(1,1),sizeof(float));
// wgpu_render_pass_encoder_set_index_buffer(wrpe.at(0,0),wb.at(4,4),WGPU_INDEX_FORMAT_UINT32,0,36*sizeof(uint32_t));
// wgpu_render_pass_encoder_set_vertex_buffer(wrpe.at(0,0),0,wb.at(3,3),0,sizeof(Ffvertices));
wgpu_render_pass_encoder_set_viewport(wrpe.at(1,1),0.0f,0.0f,szef.at(0,0),szef.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_set_scissor_rect(wrpe.at(1,1),0.0f,0.0f,sze.at(0,0),sze.at(0,0));
wgpu_render_pass_encoder_draw(wrpe.at(1,1),6,1,0,0);
//  wgpu_render_pass_encoder_draw_indexed(wrpe.at(0,0),36,1,0,0,0);
wgpu_render_pass_encoder_end(wrpe.at(1,1));
wcb.at(1,1)=wgpu_command_encoder_finish(wce.at(1,1));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(1,1));
 // Compute Pass
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(wd.at(0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&WGPU_ComputePassDescriptor.at(0,0,0));
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),32,8,1);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
// wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,&WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
  //  Move resized texture
  wgpu_command_encoder_copy_texture_to_texture(WGPU_CommandEncoder.at(0,0,0),&wict.at(1,1),&wict.at(3,3),sze.at(3,3),sze.at(3,3),1);
  //  Buffer Data View
wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
if(WGPU_BufferStatus.at(0,0,0)!=3&&on.at(1,1)==0){
on.at(1,1)=1;
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
// wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),WGPU_MapCallback.at(0,0,0),&WGPU_UserData.at(0,0,0),mode1,0,OutputBufferBytes);
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),WGPU_BufferRange.at(0,0,1),0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.querySelector('#outText').innerHTML='Buffer at [2]:'+$0.toFixed(2);
document.querySelector('#outText').innerHTML+='Buffer at [3]:'+$1.toFixed(2);
},WGPU_ResultBuffer.at(0,0,0)[2],WGPU_ResultBuffer.at(0,0,0)[3]);
}
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
on.at(1,1)=3;
}
// wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one_and_destroy(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
return EM_TRUE;
};

void raf(){
render();
return;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result,void *userData){
if(on.at(0,0)==0){wd.at(0,0)=result;}

wcc.at(0,0)=wgpu_canvas_get_webgpu_context("canvas");
canvasViewFormat[0]={wtf.at(0,0)};
config.device=wd.at(0,0);
config.format=wtf.at(0,0);
config.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
// config.numViewFormats=1;
config.viewFormats=&canvasViewFormat[0];
config.alphaMode=WGPU_CANVAS_ALPHA_MODE_PREMULTIPLIED;
// config.alphaMode=WGPU_CANVAS_ALPHA_MODE_OPAQUE;
config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_DISPLAY_P3;
// config.colorSpace=HTML_PREDEFINED_COLOR_SPACE_SRGB;
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
emscripten_get_canvas_element_size("canvas",&szwI,&szhI);
emscripten_get_element_css_size("canvas",&szw,&szh);
u64_siz.at(3,3)=sze.at(1,1);
sze.at(0,0)=int(szhI);
sze.at(3,3)=int(std::max(sze.at(0,0),sze.at(1,1))*1.25);
u64_siz.at(2,2)=int(szhI);
f32_uniform.at(1,1)=szhI;
f32_uniform.at(2,2)=float(sze.at(1,1));
szef.at(0,0)=float(szhI);
szef.at(1,1)=float(sze.at(1,1));
WGPU_UserData.at(0,0,0)=userData;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorIn.format=wtf.at(2,2);
// textureDescriptorIn.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_STORAGE_BINDING;
textureDescriptorIn.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT|WGPU_TEXTURE_USAGE_TEXTURE_BINDING;
textureDescriptorIn.width=sze.at(1,1);
textureDescriptorIn.height=sze.at(1,1); // default = 1;
textureDescriptorIn.depthOrArrayLayers=1;
textureDescriptorIn.mipLevelCount=1;
textureDescriptorIn.sampleCount=1;
textureDescriptorIn.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureAviewFormats[0]={wtf.at(2,2)};
textureDescriptorIn.numViewFormats=0;
textureDescriptorIn.viewFormats=nullptr; // &textureAviewFormats[0];
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.format=wtf.at(2,2);
textureDescriptorOut.usage=WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC;
textureDescriptorOut.width=sze.at(3,3);
textureDescriptorOut.height=sze.at(3,3); // default = 1;
textureDescriptorOut.depthOrArrayLayers=1;
textureDescriptorOut.mipLevelCount=1;
textureDescriptorOut.sampleCount=1;
textureDescriptorOut.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut.numViewFormats=0;
textureDescriptorOut.viewFormats=nullptr;
textureDescriptorOut2.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut2.format=wtf.at(2,2);
textureDescriptorOut2.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
textureDescriptorOut2.width=sze.at(3,3);
textureDescriptorOut2.height=sze.at(3,3); // default = 1;
textureDescriptorOut2.depthOrArrayLayers=1;
textureDescriptorOut2.mipLevelCount=1;
textureDescriptorOut2.sampleCount=1;
textureDescriptorOut2.dimension=WGPU_TEXTURE_DIMENSION_2D;
textureDescriptorOut2.numViewFormats=0;
textureDescriptorOut2.viewFormats=nullptr;
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorIn;
WGPU_TextureDescriptor.at(0,0,1)=textureDescriptorOut;
WGPU_TextureDescriptor.at(0,0,2)=textureDescriptorOut2;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
uni_iResolution_Buffer_2=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(5,5));
wb.at(5,5)=uni_iResolution_Buffer_2;
Input_Image_Buffer.buffer=WGPU_Buffers.at(1,1,1);
// wicb.at(2,2)=Input_Image_Buffer;
Output_Image_Buffer.buffer=WGPU_Buffers.at(0,0,0);
// wicb.at(1,1)=Output_Image_Buffer;
Mapped_Image_Buffer.buffer=WGPU_Buffers.at(2,0,2);
// wicb.at(0,0)=Mapped_Image_Buffer;
wb.at(3,3)=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(3,3));
wb.at(4,4)=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(4,4));
    //  vert / indice buffers
vertex_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(6,6));
wb.at(6,6)=vertex_Buffer;
indice_Buffer=wgpu_device_create_buffer(wd.at(0,0),&wbd.at(7,7));
wb.at(7,7)=indice_Buffer;
resizeSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(1,1));
wsmp.at(3,3)=resizeSampler;
shaderModuleDescriptor.code=comp_body; // wgl_cmp_src;
shaderModuleDescriptor.numHints=0;
shaderModuleDescriptor.hints=NULL;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(wd.at(0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
textureIn=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,0)=textureIn;
textureOut=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,1));
WGPU_Texture.at(0,0,1)=textureOut;
textureOut2=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,2));
WGPU_Texture.at(0,0,2)=textureOut2;
Input_Image_Texture.texture=WGPU_Texture.at(0,0,0);
Input_Image_Texture.origin=OriginXYZ;
Input_Image_Texture.aspect=WGPU_TEXTURE_ASPECT_ALL;
Output_Image_Texture.texture=WGPU_Texture.at(0,0,1);
Output_Image_Texture.origin=OriginXYZ;
Output_Image_Texture.aspect=WGPU_TEXTURE_ASPECT_ALL;
Output_Image_Texture2.texture=WGPU_Texture.at(0,0,2);
Output_Image_Texture2.origin=OriginXYZ;
Output_Image_Texture2.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(2,2)=Input_Image_Texture;
wict.at(1,1)=Output_Image_Texture;
wict.at(3,3)=Output_Image_Texture2;
INTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,0),&WGPU_TextureViewDescriptor.at(0,0,0));
OUTTextureView=wgpu_texture_create_view(WGPU_Texture.at(0,0,1),&WGPU_TextureViewDescriptor.at(0,0,1));
OUTTexture2View=wgpu_texture_create_view(WGPU_Texture.at(0,0,2),&WGPU_TextureViewDescriptor.at(0,0,2));
wtv.at(3,3)=INTextureView;
wtv.at(4,4)=OUTTextureView;
wtv.at(5,5)=OUTTexture2View;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoTextureDescriptor.format=wtf.at(2,2);
videoTextureDescriptor.usage=WGPU_TEXTURE_USAGE_TEXTURE_BINDING|WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_DST;
videoTextureDescriptor.width=sze.at(0,0);
videoTextureDescriptor.height=sze.at(0,0); // default = 1;
videoTextureDescriptor.depthOrArrayLayers=1;
videoTextureDescriptor.mipLevelCount=1;
videoTextureDescriptor.sampleCount=1;
videoTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
videoViewFormats[0]={wtf.at(0,0)};
videoTextureDescriptor.numViewFormats=0; // &videoViewFormats[0];
videoTextureDescriptor.viewFormats=nullptr; // &videoViewFormats[0];
wtd.at(2,2)=videoTextureDescriptor;
videoTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(2,2));
wt.at(2,2)=videoTexture;
videoTextureView=wgpu_texture_create_view(wt.at(2,2),&wtvd.at(2,2));
wtv.at(2,2)=videoTextureView;
  
      // Compute Input Buffer
Compute_Bindgroup_Layout_Entries[0].binding=0;
Compute_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
        // Compute Output Buffer
Compute_Bindgroup_Layout_Entries[1].binding=1;
Compute_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
          // Compute Input Texture
Compute_Bindgroup_Layout_Entries[2].binding=2;
Compute_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
          // Compute Output Texture
Compute_Bindgroup_Layout_Entries[3].binding=3;
Compute_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[3].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
            //  Compute Sampler
Compute_Bindgroup_Layout_Entries[4].binding=4;
Compute_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Compute_Bindgroup_Layout_Entries[4].layout.sampler=wsbl.at(0,0);
            // Compute Time Uniform
Compute_Bindgroup_Layout_Entries[5].binding=5;
Compute_Bindgroup_Layout_Entries[5].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Compute_Bindgroup_Layout_Entries[5].layout.buffer=wbbl.at(2,2);
            // Compute Video Texture
Compute_Bindgroup_Layout_Entries[6].binding=6;
Compute_Bindgroup_Layout_Entries[6].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[6].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Compute_Bindgroup_Layout_Entries[6].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
            // Compute Resize Texture
Compute_Bindgroup_Layout_Entries[7].binding=7;
Compute_Bindgroup_Layout_Entries[7].visibility=WGPU_SHADER_STAGE_COMPUTE;
Compute_Bindgroup_Layout_Entries[7].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Compute_Bindgroup_Layout_Entries[7].layout.texture=wtbl.at(1,1);
            // Compute Color Attachment Texture
// Compute_Bindgroup_Layout_Entries[7].binding=7;
// Compute_Bindgroup_Layout_Entries[7].visibility=WGPU_SHADER_STAGE_COMPUTE;
// Compute_Bindgroup_Layout_Entries[7].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
// Compute_Bindgroup_Layout_Entries[7].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0)=Compute_Bindgroup_Layout_Entries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(wd.at(0,0),WGPU_Compute_Bindgroup_Layout_Entries.at(0,0,0),8);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(wd.at(0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(wd.at(0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
      // Compute Input Buffer
Compute_Bindgroup_Entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[0].binding=0;
Compute_Bindgroup_Entries[0].resource=WGPU_Buffers.at(1,1,1);
Compute_Bindgroup_Entries[0].bufferBindOffset=0;
Compute_Bindgroup_Entries[0].bufferBindSize=InputBufferBytes;
        // Compute Output Buffer
Compute_Bindgroup_Entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[1].binding=1;
Compute_Bindgroup_Entries[1].resource=WGPU_Buffers.at(0,0,0);
Compute_Bindgroup_Entries[1].bufferBindOffset=0;
Compute_Bindgroup_Entries[1].bufferBindSize=OutputBufferBytes;
          // Compute Input Texture
Compute_Bindgroup_Entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[2].binding=2;
Compute_Bindgroup_Entries[2].resource=wtv.at(3,3);
          // Compute Output Texture
Compute_Bindgroup_Entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[3].binding=3;
Compute_Bindgroup_Entries[3].resource=wtv.at(4,4);
            //  Compute Sampler
Compute_Bindgroup_Entries[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[4].binding=4;
Compute_Bindgroup_Entries[4].resource=wsmp.at(3,3);
            // Compute iTime Uniform
Compute_Bindgroup_Entries[5].binding=5;
Compute_Bindgroup_Entries[5].resource=wb.at(0,0);
Compute_Bindgroup_Entries[5].bufferBindOffset=0;
Compute_Bindgroup_Entries[5].bufferBindSize=sizeof(float);
            // Compute Video Texture
Compute_Bindgroup_Entries[6]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[6].binding=6;
Compute_Bindgroup_Entries[6].resource=wtv.at(2,2); 
            // Compute Resize Texture
Compute_Bindgroup_Entries[7]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Compute_Bindgroup_Entries[7].binding=7;
Compute_Bindgroup_Entries[7].resource=wtv.at(5,5);
            // Compute Color Attachment Texture
// Compute_Bindgroup_Entries[7]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
// Compute_Bindgroup_Entries[7].binding=7;
// Compute_Bindgroup_Entries[7].resource=wtv.at(1,1); 
WGPU_BindGroupEntries.at(0,0,0)=Compute_Bindgroup_Entries;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(wd.at(0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),8);
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(wd.at(0,0));
shaderModuleDescV.code=vertexShader;
vs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescV);
shaderModuleDescF.code=frag_body;
shaderModuleDescF2.code=frag_body2;
// shaderModuleDescF.code=fragmentShader;
fs=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF);
fs2=wgpu_device_create_shader_module(wd.at(0,0),&shaderModuleDescF2);
vertState.module=vs;
vertState.entryPoint="main";
vertState.numBuffers=1;
vertState.buffers=&wvbl.at(0,0);
vertState.numConstants=0;
vertState.constants=nullptr;
fragState.module=fs;
fragState.entryPoint="main";
fragState.numTargets=1;
fragState.targets=&colorTarget32;
fragState2.module=fs2;
fragState2.entryPoint="main";
fragState2.numTargets=1;
fragState2.targets=&colorTarget;
videoSampler=wgpu_device_create_sampler(wd.at(0,0),&wsd.at(0,0));
wsmp.at(0,0)=videoSampler;
videoTextureCopy.texture=wt.at(2,2);
videoTextureCopy.mipLevel=0;
videoTextureCopy.origin=xyz;
videoTextureCopy.aspect=WGPU_TEXTURE_ASPECT_ALL;
wict.at(0,0)=videoTextureCopy;

  //  Render Sampler
Render_Bindgroup_Layout_Entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[0].binding=0;
Render_Bindgroup_Layout_Entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Render_Bindgroup_Layout_Entries[0].layout.sampler=wsbl.at(1,1);
  //  Render iTime Buffer
Render_Bindgroup_Layout_Entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[1].binding=7;
Render_Bindgroup_Layout_Entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[1].layout.buffer=wbbl.at(2,2);
  //  Render TextureIN
Render_Bindgroup_Layout_Entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[2].binding=2;
Render_Bindgroup_Layout_Entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Render_Bindgroup_Layout_Entries[2].layout.texture=wtbl.at(1,1);
  //  Render iResolution Buffer
Render_Bindgroup_Layout_Entries[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[3].binding=5;
Render_Bindgroup_Layout_Entries[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[3].layout.buffer=wbbl.at(2,2);
  //  Render iFrame Buffer
Render_Bindgroup_Layout_Entries[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[4].binding=6;
Render_Bindgroup_Layout_Entries[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries[4].layout.buffer=wbbl.at(0,0);
  //  Render TextureOUT
Render_Bindgroup_Layout_Entries[5]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries[5].binding=1;
Render_Bindgroup_Layout_Entries[5].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Render_Bindgroup_Layout_Entries[5].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
wbgle.at(0,0)=Render_Bindgroup_Layout_Entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),5);
wbgl.at(0,0)=bindgroup_layout;
  
  //  Render_2 Sampler
Render_Bindgroup_Layout_Entries_2[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[0].binding=0;
Render_Bindgroup_Layout_Entries_2[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_SAMPLER;
Render_Bindgroup_Layout_Entries_2[0].layout.sampler=wsbl.at(1,1);
  //  Render_2 iTime Buffer
Render_Bindgroup_Layout_Entries_2[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[1].binding=7;
Render_Bindgroup_Layout_Entries_2[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[1].layout.buffer=wbbl.at(2,2);
  //  Render_2 TextureIN
Render_Bindgroup_Layout_Entries_2[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[2].binding=2;
Render_Bindgroup_Layout_Entries_2[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_TEXTURE;
Render_Bindgroup_Layout_Entries_2[2].layout.texture=wtbl.at(1,1);
  //  Render_2 iResolution Buffer
Render_Bindgroup_Layout_Entries_2[3]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[3].binding=5;
Render_Bindgroup_Layout_Entries_2[3].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[3].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[3].layout.buffer=wbbl.at(2,2);
  //  Render_2 iFrame Buffer
Render_Bindgroup_Layout_Entries_2[4]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[4].binding=6;
Render_Bindgroup_Layout_Entries_2[4].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[4].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
Render_Bindgroup_Layout_Entries_2[4].layout.buffer=wbbl.at(0,0);
  //  Render_2 TextureOUT
Render_Bindgroup_Layout_Entries_2[5]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Layout_Entries_2[5].binding=1;
Render_Bindgroup_Layout_Entries_2[5].visibility=WGPU_SHADER_STAGE_FRAGMENT;
Render_Bindgroup_Layout_Entries_2[5].type=WGPU_BIND_GROUP_LAYOUT_TYPE_STORAGE_TEXTURE;
Render_Bindgroup_Layout_Entries_2[5].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(1,1,1);
wbgle.at(1,1)=Render_Bindgroup_Layout_Entries_2;
bindgroup_layout_2=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(1,1),5);
wbgl.at(1,1)=bindgroup_layout_2;
WGpuPipelineLayout pipeline_layout=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(0,0),1);
wrpl.at(0,0)=pipeline_layout;
renderPipelineDesc.vertex.module=vs;
renderPipelineDesc.vertex.entryPoint="main";
renderPipelineDesc.primitive=priState;
renderPipelineDesc.fragment=fragState;
renderPipelineDesc.depthStencil=depthState;
renderPipelineDesc.layout=wrpl.at(0,0);
// renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc.multisample=multiSamp;
wrp.at(0,0)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc);
WGpuPipelineLayout pipeline_layout_2=wgpu_device_create_pipeline_layout(wd.at(0,0),&wbgl.at(1,1),1);
wrpl.at(1,1)=pipeline_layout_2;
WGpuRenderPipelineDescriptor renderPipelineDesc2={WGPU_RENDER_PIPELINE_DESCRIPTOR_DEFAULT_INITIALIZER};
renderPipelineDesc2.vertex.module=vs;
renderPipelineDesc2.vertex.entryPoint="main";
renderPipelineDesc2.primitive=priState;
renderPipelineDesc2.fragment=fragState2;
renderPipelineDesc2.depthStencil=depthState;
renderPipelineDesc2.layout=wrpl.at(1,1);
// renderPipelineDesc.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc2.multisample=multiSamp;
wrp.at(1,1)=wgpu_device_create_render_pipeline(wd.at(0,0),&renderPipelineDesc2);

  //  Render Sampler
Render_Bindgroup_Entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[0].binding=0;
Render_Bindgroup_Entries[0].resource=wsmp.at(0,0);
    //  Render iTime Buffer
Render_Bindgroup_Entries[1].binding=7;
Render_Bindgroup_Entries[1].resource=wb.at(0,0);
Render_Bindgroup_Entries[1].bufferBindOffset=0;
Render_Bindgroup_Entries[1].bufferBindSize=sizeof(float);
  //  Render TextureIN
Render_Bindgroup_Entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[2].binding=2;
Render_Bindgroup_Entries[2].resource=wtv.at(2,2);
  //  Render iResolution Buffer
Render_Bindgroup_Entries[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[3].binding=5;
Render_Bindgroup_Entries[3].resource=wb.at(2,2);
Render_Bindgroup_Entries[3].bufferBindOffset=0;
Render_Bindgroup_Entries[3].bufferBindSize=sizeof(float);
  //  Render iFrame Buffer
Render_Bindgroup_Entries[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[4].binding=6;
Render_Bindgroup_Entries[4].resource=wb.at(1,1);
Render_Bindgroup_Entries[4].bufferBindOffset=0;
Render_Bindgroup_Entries[4].bufferBindSize=sizeof(uint64_t);
  //  Render TextureOUT
Render_Bindgroup_Entries[5]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries[5].binding=1;
Render_Bindgroup_Entries[5].resource=wtv.at(3,3);
wbge.at(0,0)=Render_Bindgroup_Entries;
    //  Render_2 Sampler
Render_Bindgroup_Entries_2[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[0].binding=0;
Render_Bindgroup_Entries_2[0].resource=wsmp.at(0,0);
    //  Render_2 iTime Buffer
Render_Bindgroup_Entries_2[1].binding=7;
Render_Bindgroup_Entries_2[1].resource=wb.at(0,0);
Render_Bindgroup_Entries_2[1].bufferBindOffset=0;
Render_Bindgroup_Entries_2[1].bufferBindSize=sizeof(float);
  //  Render_2 TextureIN
Render_Bindgroup_Entries_2[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[2].binding=2;
Render_Bindgroup_Entries_2[2].resource=wtv.at(2,2);
  //  Render_2 iResolution Buffer
Render_Bindgroup_Entries_2[3]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[3].binding=5;
Render_Bindgroup_Entries_2[3].resource=wb.at(5,5);
Render_Bindgroup_Entries_2[3].bufferBindOffset=0;
Render_Bindgroup_Entries_2[3].bufferBindSize=sizeof(float);
  //  Render_2 iFrame Buffer
Render_Bindgroup_Entries_2[4]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[4].binding=6;
Render_Bindgroup_Entries_2[4].resource=wb.at(1,1);
Render_Bindgroup_Entries_2[4].bufferBindOffset=0;
Render_Bindgroup_Entries_2[4].bufferBindSize=sizeof(uint64_t);
  //  Render_2 TextureOUT
Render_Bindgroup_Entries_2[5]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
Render_Bindgroup_Entries_2[5].binding=1;
Render_Bindgroup_Entries_2[5].resource=wtv.at(3,3);
wbge.at(1,1)=Render_Bindgroup_Entries_2;

  /*
depthTextureViewDescriptor.format=wtf.at(5,5);
depthTextureViewDescriptor.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
depthTextureViewDescriptor.aspect=WGPU_TEXTURE_ASPECT_ALL;
depthTextureViewDescriptor.baseMipLevel=0; // default = 0
depthTextureViewDescriptor.mipLevelCount=1;
depthTextureViewDescriptor.baseArrayLayer=0; // default = 0
depthTextureViewDescriptor.arrayLayerCount=1;
wtvd.at(0,0)=depthTextureViewDescriptor;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor.format=wtf.at(5,5);
depthTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor.width=sze.at(0,0);
depthTextureDescriptor.height=sze.at(0,0); // default = 1;
depthTextureDescriptor.depthOrArrayLayers=1;
depthTextureDescriptor.mipLevelCount=1;
depthTextureDescriptor.sampleCount=1;
depthTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthViewFormats[0]={wtf.at(5,5)};
depthTextureDescriptor.viewFormats=&depthViewFormats[0];
wtd.at(0,0)=depthTextureDescriptor;
depthTexture=wgpu_device_create_texture(wd.at(0,0),&wtd.at(0,0));
wt.at(0,0)=depthTexture;
depthTextureDescriptor2.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthTextureDescriptor2.format=wtf.at(5,5);
depthTextureDescriptor2.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
depthTextureDescriptor2.width=sze.at(1,1);
depthTextureDescriptor2.height=sze.at(1,1); // default = 1;
depthTextureDescriptor2.depthOrArrayLayers=1;
depthTextureDescriptor2.mipLevelCount=1;
depthTextureDescriptor2.sampleCount=1;
depthTextureDescriptor2.dimension=WGPU_TEXTURE_DIMENSION_2D;
depthViewFormats2[0]={wtf.at(5,5)};
depthTextureDescriptor2.viewFormats=&depthViewFormats2[0];
wtd.at(3,3)=depthTextureDescriptor2;
depthTexture2=wgpu_device_create_texture(wd.at(0,0),&wtd.at(3,3));
wt.at(5,5)=depthTexture2;
depthTextureViewDescriptor2.format=wtf.at(5,5);
depthTextureViewDescriptor2.dimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
depthTextureViewDescriptor2.aspect=WGPU_TEXTURE_ASPECT_ALL;
depthTextureViewDescriptor2.baseMipLevel=0; // default = 0
depthTextureViewDescriptor2.mipLevelCount=1;
depthTextureViewDescriptor2.baseArrayLayer=0; // default = 0
depthTextureViewDescriptor2.arrayLayerCount=1;
wtvd.at(3,3)=depthTextureViewDescriptor2;
  */
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
colorTextureDescriptor.format=wtf.at(0,0);
colorTextureDescriptor.usage=WGPU_TEXTURE_USAGE_RENDER_ATTACHMENT;
colorTextureDescriptor.width=sze.at(0,0);
colorTextureDescriptor.height=sze.at(0,0); // default = 1;
colorTextureDescriptor.depthOrArrayLayers=1;
colorTextureDescriptor.mipLevelCount=1;
colorTextureDescriptor.sampleCount=1;
colorTextureDescriptor.dimension=WGPU_TEXTURE_DIMENSION_2D;
wtd.at(1,1)=colorTextureDescriptor;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(6,6),0,Ffvertices,sizeof(Ffvertices));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(7,7),0,indices,36*sizeof(uint32_t));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),5);
wbg.at(0,0)=bindgroup;
bindgroup_2=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(1,1),wbge.at(1,1),5);
wbg.at(1,1)=bindgroup_2;
u64_uni.at(0,0)=0;
u64_uni.at(3,3)=0;
f32_uniform.at(0,0)=0.0f;
d64_uniform.at(0,0)=0.0;
u_time.t1=boost::chrono::high_resolution_clock::now();
u_time.t2=boost::chrono::high_resolution_clock::now();
u_time.t3=boost::chrono::high_resolution_clock::now();
u_time.time_spanb=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t3);
u_time.time_spana=boost::chrono::duration<boost::compute::double_,boost::chrono::seconds::period>(u_time.t2-u_time.t1);
if(on.at(0,0)==1){
emscripten_cancel_main_loop();
}
emscripten_set_main_loop((void(*)())raf,0,0);
on.at(0,0)=1;
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8;
deviceDesc.requiredFeatures=WGPU_FEATURE_FLOAT32_FILTERABLE;
  /*
WGPU_FEATURES_BITFIELD ftr=wgpu_adapter_or_device_get_features(wa.at(0,0));
// deviceDesc.requiredFeatures=ftr;
WGpuSupportedLimits lmts;
lmts.maxUniformBufferBindingSize=sizeof(uint64_t);
lmts.maxStorageBufferBindingSize=1*1024*1024;
lmts.maxBufferSize=1*1024*1024;
lmts.maxColorAttachmentBytesPerSample=64;
wgpu_adapter_or_device_get_limits(wa.at(0,0),&lmts);
  */
// deviceDesc.requiredLimits=lmts;
wdd.at(0,0)=deviceDesc;
wgpu_adapter_request_device_async(wa.at(0,0),&wdd.at(0,0),ObtainedWebGpuDeviceStart,0);
}

EM_BOOL WGPU_Start(int sz){
sze.at(1,1)=sz;
navigator_gpu_request_adapter_async(&wao.at(0,0),ObtainedWebGpuAdapterStart,0);
return EM_TRUE;
}

// #include "../../src/vanilla/webgpu_compute_js_tex.cpp"

extern"C"{

void startWebGPUi(int sz){
WGPU_Start(sz);
return;
}

void startWebGPUbi(int sz){
WGPU_Start(sz);
return;
}

}

int main(){
on.at(0,0)=0;
js_main();
return 0;
}
