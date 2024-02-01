#include "../../include/vanilla/main_onnx.hpp"

template <typename T>
T vectorProduct(const std::vector<T>& v)
{
return accumulate(v.begin(),v.end(),1,std::multiplies<T>());
}

using namespace std;

vector<int32_t> to_int32(vector<string> tokens) {
vector<int32_t> ints;
for (string token : tokens) {
std::cout << token << std::endl;
}
return ints;
}

vector<string> tokenize(string text) {
vector<string> tokens;
  // Split the text into words.
stringstream ss(text);
string word;
while (getline(ss, word, ' ')) {
tokens.push_back(word);
}
  // Remove punctuation and stop words.
///  vector<string> stop_words = {"the", "of", "and", "to", "is", "was", "were", "be", "am", "are", "has", "have", "had", "that", "this", "it", "its", "with", "for", "by", "on", "at", "in", "to"};
///  for (int i = 0; i < tokens.size(); i++) {
///    if (ispunct(tokens[i][0]) || find(stop_words.begin(), stop_words.end(), tokens[i]) != stop_words.end()) {
///      tokens.erase(tokens.begin() + i);
///    }
///  }
  // Lowercase all words. 
	// remember to use all lowercase for now
//  for (int i = 0; i < tokens.size(); i++) {
//    tokens[i] = tolower(tokens[i]);
//  }
return tokens;
}

int max_wordlength=12;
string text="birds";
vector<string>tokens=tokenize(text);
vector<int32_t>ints=to_int32(tokens);

void cltest(){
std::vector<std::string>infos=Ort::GetAvailableProviders();
char* char_array=new char[infos.size()*infos[0].size()];
for (int i=0;i<infos.size();i++){
std::copy(infos[i].begin(),infos[i].end(),char_array+i*infos[0].size());
}
std::cout << char_array << std::endl;
Ort::Env ort_env;
std::cout << "got ORT env" << std::endl;
 std::string model_path="/model.onnx";
const int64_t batchSize=2;
// Ort::SessionOptions sessionOptions;
// sessionOptions.SetIntraOpNumThreads(1);
		 // Sets graph optimization level
    // Available levels are
    // ORT_DISABLE_ALL -> To disable all optimizations
    // ORT_ENABLE_BASIC -> To enable basic optimizations (Such as redundant node
    // removals) ORT_ENABLE_EXTENDED -> To enable extended optimizations
    // (Includes level 1 + more complex optimizations like node fusions)
    // ORT_ENABLE_ALL -> To Enable All possible optimizations
// sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_DISABLE_ALL);
std::cout << "got ORT session/options" << std::endl;
std::cout << "got ORT SessionOptions" << std::endl;

		// from ms
  Ort::Session sesh{ort_env, "/model.onnx", Ort::SessionOptions{nullptr}};

std::cout << "got ORT Session" << std::endl;

Ort::AllocatorWithDefaultOptions allocator;
std::cout << "got ORT allocator" << std::endl;
/*
size_t numInputNodes=sesh.GetInputCount();
size_t numOutputNodes=sesh.GetOutputCount();
std::cout << "got ORT nodes" << std::endl;
auto inputName=sesh.GetInputNameAllocated(0,allocator);
// const char* inputName = session.Ort::detail::GetInputName(0, allocator);
std::cout << "got ORT input" << std::endl;
Ort::TypeInfo inputTypeInfo=sesh.GetInputTypeInfo(0);
auto inputTensorInfo=inputTypeInfo.GetTensorTypeAndShapeInfo();
ONNXTensorElementDataType inputType=inputTensorInfo.GetElementType();
std::vector<int64_t>inputDims=inputTensorInfo.GetShape();
if (inputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting input batch size to " << batchSize << "." << std::endl;
inputDims.at(0)=ints.size();
inputDims.at(1)=max_wordlength;
}
auto outputName=sesh.GetOutputNameAllocated(0,allocator);
//   //   const char* outputName=sesh.Ort::detail::GetOutputName(0, allocator);
Ort::TypeInfo outputTypeInfo=sesh.GetOutputTypeInfo(0);
auto outputTensorInfo=outputTypeInfo.GetTensorTypeAndShapeInfo();
ONNXTensorElementDataType outputType=outputTensorInfo.GetElementType();
std::vector<int64_t>outputDims=outputTensorInfo.GetShape();
if (outputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting output batch size to "
<< batchSize << "." << std::endl;
outputDims.at(0)=batchSize;
}

std::cout << "Input Name: " << inputName << std::endl;
std::cout << "Input Type: " << inputType << std::endl;
std::cout << "Input Dimensions 1: " <<  std::to_string(inputDims.at(0)) << std::endl;
std::cout << "Input Dimensions 2: " <<  std::to_string(inputDims.at(1)) << std::endl;
// std::cout << "Input Dimensions 3: " <<  std::to_string(inputDims.at(2)) << std::endl;
std::cout << "Output Name: " << outputName << std::endl;
std::cout << "Output Type: " << outputType << std::endl;
std::cout << "Output Dimensions 1: " <<  std::to_string(outputDims.at(0)) << std::endl;
std::cout << "Output Dimensions 2: " <<  std::to_string(outputDims.at(1)) << std::endl;
std::cout << "Output Dimensions 3: " <<  std::to_string(outputDims.at(2)) << std::endl;
std::cout << "Number of Input Nodes: " << numInputNodes << std::endl;
std::cout << "Number of Output Nodes: " << numOutputNodes << std::endl;

size_t inputTensorSize=vectorProduct(inputDims);
std::cout << "setting inputTensorSize:" << inputTensorSize << std::endl;
std::vector<int32_t> inputTensorValues(inputTensorSize);
std::cout << "setting inputTensorValues " <<  std::endl;
for (int64_t i = 0; i < batchSize; ++i)
{
std::copy(ints.begin(),ints.end(),inputTensorValues.begin()+i*inputTensorSize);
}
	
size_t outputTensorSize=vectorProduct(outputDims);
std::cout << "setting outputTensorSize " <<  std::endl;
  //  589824 ?
std::vector<float> outputTensorValues(outputTensorSize);
std::cout << "setting outputTensorValues " <<  std::endl;
std::string text_prompt="two birds";
std::vector<float>text_prompt_vector;
for(char c : text_prompt){
text_prompt_vector.push_back(c);
}
	
std::cout << "Establishing text input" << std::endl;
std::vector<const char*>inputNames={"input_ids"};
// std::vector<const char*>inputNames={inputName};
std::vector<const char*>outputNames={"last_hidden_state","pooler_output"};
// std::vector<const char*>outputNames={outputName};
std::cout << "Establishing tensor names" << std::endl;
Ort::MemoryInfo memoryInfo=Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator,OrtMemTypeCPU);
std::cout << "Establishing memoryInfo" << std::endl;
std::vector<Ort::Value>inputTensors;
Ort::Value outputTensors{nullptr};
inputTensors.push_back(Ort::Value::CreateTensor<int32_t>(memoryInfo,inputTensorValues.data(),inputTensorSize,&inputDims.at(0),6));
std::cout << "Establishing Tensors" << std::endl;
std::cout << "Creating CPU link " << std::endl;
Ort::RunOptions runOpts;
  // google colab
std::cout << "The Run function takes the text prompt and the desired output size as input.\n"
<< "The output size is the size of the desired image, in pixels.\n"
<< "The Run function returns an Ort::Value object. \n"
<< "The Ort::Value object contains the generated image. \n"
<< "You can use the GetTensor function to get the tensor data from the Ort::Value object. \n"
<< "The tensor data is a vector of floats that represents the image. \n"
<< "You can use the cv::Mat class to convert the tensor data to an image.\n"
<< std::endl;
// Run inference
// sesh.Run(Ort::RunOptions{},inputNames.data(),inputTensors.data(),1,outputNames.data(),&outputTensors,1);
//   void Run(const RunOptions& run_options, const char* const* input_names, const Value* input_values, size_t input_count,
//                     const char* const* output_names, Value* output_values, size_t output_count);
//   void Run(run_options,input_names,input_values,input_count,
//                     output_names,output_values,output_count);
// std::cout << "Running inferrence." << std::endl;
// auto outputDataPtr = outputTensors.GetTensorRawData();
	// Get the shape of the tensor.
//  std::vector<int64_t> shape = outputTensorInfo.GetShape();
  // Create a new image with the same shape as the tensor.
//  unsigned char* image_data = new unsigned char[shape.size()];
  // Copy the data from the tensor to the image.
//  outputTensors.CopyTo(image_data);
  // Save the image to a file.
std::cout << "Got data. " << std::endl;

//  emscripten_image_data_type* data = emscripten_new_typed_array(image_data, shape.size(), EMSCRIPTEN_TYPED_ARRAY_U8);
//  emscripten_save_image(output_filename, data, shape[1], shape[0]);

  // Delete the image data.
//  delete[] image_data;
	
// int width = 400; // emscripten_get_image_width("output.png");
// int height = 400; // emscripten_get_image_height("output.png");
// emscripten_image_data_type* data = emscripten_get_image_data("output.png", width, height);

// Display the image.
// emscripten_set_canvas_image_data(data, width, height);
//	std::cout << "Output tensors updated." << std::endl;
	return;
*/
}

WGpuShaderModuleCompilationHint fragHint={};
WGpuTextureView depthTextureView;
WGpuTextureView colorTextureView;
WGpuTextureViewDescriptor depthTextureViewDescriptor={};
WGpuTextureViewDescriptor colorTextureViewDescriptor={};
WGpuRenderPassColorAttachment colorAttachment={};
WGpuRenderPassDepthStencilAttachment depthAttachment={};
WGpuTexture depthTexture;
WGpuTexture colorTexture;
WGpuTexture __128bit_Texture__;
WGpuTextureDescriptor depthTextureDescriptor={};
WGpuTextureDescriptor colorTextureDescriptor={};
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
WGpuBufferBindingLayout bufferBindingLayoutR={WGPU_BUFFER_BINDING_LAYOUT_DEFAULT_INITIALIZER};
WGpuTextureBindingLayout textureBindingLayout1={};
WGpuTextureBindingLayout textureBindingLayout2={};
WGpuTextureBindingLayout textureBindingLayout3={};
WGpuColorTargetState colorTarget={};
WGpuColorTargetState colorTarget2={};
WGpuCommandEncoder wceA={};
WGpuCommandEncoder wceB={};
WGpuSampler iChannel0Sampler={};
WGpuSamplerBindingLayout samplerBindingLayout={};
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

static i_tensor on=i_tensor{2,2};
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
static wpl_tensor wrpl=wpl_tensor{2,2};
static wb_tensor wb=wb_tensor{8,8};
static wbgle_tensor wbgle=wbgle_tensor{2,2};
static wbge_tensor wbge=wbge_tensor{2,2};
static wbgl_tensor wbgl=wbgl_tensor{2,2};
static wbg_tensor wbg=wbg_tensor{2,2};
static wrpd_tensor wrpd=wrpd_tensor{2,2};
static wrpca_tensor wrpca=wrpca_tensor{2,2};
static wbbl_tensor wbbl=wbbl_tensor{2,2};
static wbd_tensor wbd=wbd_tensor{8,8};
static wao_tensor wao=wao_tensor{2,2};
static wdd_tensor wdd=wdd_tensor{2,2};
static u64_tensor u64_uni=u64_tensor{8,8};
static u64_tensor u64_siz=u64_tensor{1,1};
static wrbe_tensor wrbe=wrbe_tensor{2,2};
static wrbed_tensor wrbed=wrbed_tensor{2,2};
static wrpdsa_tensor wrpdsa=wrpdsa_tensor{2,2};
static wt_tensor wt=wt_tensor{3,3};
static wtd_tensor wtd=wtd_tensor{3,3};
static wtvd_tensor wtvd=wtvd_tensor{2,2};
static wtf_tensor wtf=wtf_tensor{5,5};
static wtv_tensor wtv=wtv_tensor{2,2};
static wms_tensor wms=wms_tensor{2,2};
static wsm_tensor wsm=wsm_tensor{2,2};
static wsmd_tensor wsmd=wsmd_tensor{2,2};
static wcts_tensor wcts=wcts_tensor{2,2};
static wdss_tensor wdss=wdss_tensor{2,2};
static wvs_tensor wvs=wvs_tensor{2,2};
static wps_tensor wps=wps_tensor{2,2};
static wfs_tensor wfs=wfs_tensor{2,2};
static wrpid_tensor wrpid=wrpid_tensor{2,2};
static wtbl_tensor wtbl=wtbl_tensor{2,2};
static c_tensor wgsl=c_tensor{2,2};
static wsd_tensor wsd=wsd_tensor{2,2};
static ws_tensor wgpu_sampler=ws_tensor{2,2};
static wsbl_tensor wsbl=wsbl_tensor{2,2};

/*
static mouse_tensor mms=mouse_tensor{2,2};
static mouse_tensor mms2=mouse_tensor{2,2};

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
"@group(0)@binding(0)var<storage,read>inputBuffer:array<u32,262144>;"
"@group(0)@binding(1)var<storage,read_write>outputBuffer:array<u32,262144>;"
"@group(0)@binding(2)var textureA:texture_storage_2d<rgba32uint,write>;"
"@compute@workgroup_size(4,1,64)"
"fn computeStuff(@builtin(global_invocation_id)global_id:vec3<u32>){"
"let f:u32=global_id.z;"
"let g:u32=global_id.x;"
// "let coord:vec2<u32>=vec2<u32>(0,0);"
// "let flo:vec4<u32>=vec4<u32>(24,24,24,255);"
// "let u0:u32=0;"
// "let clr:f32=textureLoad(textureA:texture_storage_2d<u32>,coord,u0);"
// "textureStore(textureA,coord,vec4<u32>(24,24,24,255));"
// "let h:u32=f*g;"
// "var i:u32;"
// "loop{"
"outputBuffer[global_id.x]=inputBuffer[global_id.x];"
// "outputBuffer[(f*g)+1]=inputBuffer[0];"
// "outputBuffer[(f*g)+2]=inputBuffer[0];"
// "outputBuffer[(f*g)+3]=inputBuffer[0];"
// "i+=4;"
// "if i==256{break;}"
// "}"
"}";

const char * vertexShader =
"@vertex\n"
"fn main(@builtin(vertex_index) vertexIndex : u32) -> @builtin(position) vec4<f32> {\n"
// "out.iChannel0Texture = iChannel0;\n"
// "out.iChannel0Sampler = iChannel0Sampler;\n"
"var pos = array<vec2<f32>, 6>(\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, 1.0f),\n"
"vec2<f32>(-1.0f, -1.0f),\n"
"vec2<f32>(1.0f, 1.0f),\n"
"vec2<f32>(1.0f, -1.0f),\n"
"vec2<f32>(-1.0f, -1.0f)\n"
");\n"
"return vec4<f32>(pos[vertexIndex], 0.0f, 1.0f);"
"}\n";

const char * fragHeader="";

const char * fragEntry="main_1";

const char * Fnm=reinterpret_cast<const char *>("/shader/shader.wgsl");
const char * FnmB=reinterpret_cast<const char *>("/shader/shader.wgsl");

static char8_t * result=NULL;
static char * results=NULL;
static long int length=0;

static wq_tensor WGPU_Queue=wq_tensor{1,1,2};
static wcb_tensor WGPU_CommandBuffer=wcb_tensor{1,1,3};
static wb_tensor WGPU_Buffers=wb_tensor{3,3,3};
static wce_tensor WGPU_CommandEncoder=wce_tensor{1,1,4};
static wcpe_tensor WGPU_ComputePassCommandEncoder=wcpe_tensor{1,1,3};
static wcpd_tensor WGPU_ComputePassDescriptor=wcpd_tensor{1,1,3};
static wcp_tensor WGPU_ComputePipeline=wcp_tensor{1,1,1};
static wpl_tensor WGPU_ComputePipelineLayout=wpl_tensor{1,1,1};
static wsm_tensor WGPU_ComputeModule=wsm_tensor{1,1,1};
static wbg_tensor WGPU_BindGroup=wbg_tensor{1,1,2};
static wbgl_tensor WGPU_BindGroupLayout=wbgl_tensor{1,1,2};
static wbgle_tensor WGPU_BindGroupLayoutEntries=wbgle_tensor{1,1,2};
static wbge_tensor WGPU_BindGroupEntries=wbge_tensor{1,1,2};
static wbmc_tensor WGPU_MapCallback=wbmc_tensor{1,1,3};
static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
static wbbl_tensor WGPU_BufferBindingLayout=wbbl_tensor{1,1,4};
static wbd_tensor WGPU_BufferDescriptor=wbd_tensor{1,1,4};
static wsmd_tensor WGPU_ShaderModuleDescriptor=wsmd_tensor{1,1,3};
static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
static void_tensor WGPU_UserData=void_tensor{1,1,2};
static uiptr_tensor WGPU_ResultBuffer=uiptr_tensor{1,1,1};
static uiptr_tensor WGPU_InputBuffer=uiptr_tensor{1,1,1};
static i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
static i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
static wt_tensor WGPU_Texture=wt_tensor{1,1,1};
static wtd_tensor WGPU_TextureDescriptor=wtd_tensor{1,1,1};
static wstbl_tensor WGPU_StorageTextureBindingLayout=wstbl_tensor{1,1,1};
static wtvd_tensor WGPU_TextureViewDescriptor=wtvd_tensor{1,1,1};
static wtv_tensor WGPU_TextureView=wtv_tensor{1,1,1};
static uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
static wced_tensor WGPU_CommandEncoderDescriptor=wced_tensor{1,1,1};
static wbms_tensor WGPU_BufferStatus=wbms_tensor{1,1,1};

uint32_t workgroupSize=64;
uint32_t OutputBufferUnits=262144;
uint32_t OutputBufferBytes=262144*4;
uint32_t InputBufferUnits=262144;
uint32_t InputBufferBytes=262144*4;
uint64_t WGPU_InputRangeSize=OutputBufferBytes;

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
WGpuBindGroupLayoutEntry bindGroupLayoutEntries[3]={};
WGpuBindGroupLayoutEntry bindGroupLayoutEntriesB[2]={};
WGpuBindGroupEntry bindGroupEntry[3]={};
WGpuBindGroupEntry bindGroupEntryB[2]={};
WGpuBufferBindingLayout bufferBindingLayout1={3};
WGpuBufferBindingLayout bufferBindingLayout2={2};
WGpuBufferBindingLayout bufferBindingLayout3={2};
WGpuBufferBindingLayout bufferBindingLayout4={2};
WGpuStorageTextureBindingLayout storageTextureBindingLayout1={1,34,2};
WGpuRequestAdapterOptions options={WGPU_POWER_PREFERENCE_HIGH_PERFORMANCE,false};
std::vector<float>color_input(InputBufferUnits);
std::vector<uint8_t>input(InputBufferBytes);
std::vector<uint8_t>outputd(OutputBufferBytes);
std::vector<uint8_t>outpute(OutputBufferBytes);
WGpuBufferDescriptor bufferDescriptorI={InputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorO={OutputBufferBytes,WGPU_BUFFER_USAGE_STORAGE|WGPU_BUFFER_USAGE_COPY_SRC,false};
WGpuBufferDescriptor bufferDescriptorM={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
WGpuBufferDescriptor bufferDescriptorC={OutputBufferBytes,WGPU_BUFFER_USAGE_MAP_READ|WGPU_BUFFER_USAGE_COPY_DST,false};
// 14 = R32FLOAT   34 = RGBA32UINT
WGpuTextureDescriptor textureDescriptorA={256,256,1,1,1,2,34,WGPU_TEXTURE_USAGE_STORAGE_BINDING|WGPU_TEXTURE_USAGE_COPY_SRC|WGPU_TEXTURE_USAGE_COPY_DST};
WGpuTextureViewDescriptor textureViewDescriptorA={34,WGPU_TEXTURE_VIEW_DIMENSION_2D};
char * cmp_bdy=wgl_cmp_src;
WGpuShaderModuleDescriptor shaderModuleDescriptor={cmp_bdy,0,NULL};
int randomNumber=0,entropySeed=0;
std::random_device randomizer;
int raN=0;
int raND=0;
uint32_t * WGPU_Result_Array=new uint32_t[OutputBufferBytes];
uint32_t * WGPU_Input_Array=new uint32_t[InputBufferBytes];
uint32_t * WGPU_Color_Input_Array=new uint32_t[InputBufferBytes];
WGpuImageCopyTexture WGPU_Input_Image={};
WGpuImageCopyTexture WGPU_Output_Image={};
WGpuImageCopyBuffer WGPU_Input_Buffer={};
WGpuImageCopyBuffer WGPU_Output_Buffer={};
WGpuImageCopyBuffer WGPU_Mapped_Buffer={};
uint32_t outP;
double_int53_t WGPU_Range_PointerB;
double_int53_t WGPU_Range_PointerC;


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
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), WGPU_BufferRange.at(0,0,1) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.getElementById('outText').innerHTML=$0;
},WGPU_ResultBuffer.at(0,0,0)[0]);
// std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
// if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// }
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
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
result=static_cast<char8_t *>(malloc((length+1)*sizeof(char8_t)));
if(result){
size_t actual_length=fread(result,sizeof(char8_t),length,file);
result[actual_length++]={'\0'};
}
fclose(file);
results=reinterpret_cast<char *>(result);
return results;
}
return nullptr;
}

void getCode(const char * Fnm){
const char * frag_body=(char *)rd_fl(Fnm);
wgsl.at(0,0)=frag_body;
return;
}

void raf(){
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
colorTexture=wgpu_canvas_context_get_current_texture(wcc.at(0,0));
wt.at(1,1)=colorTexture;
colorTextureView=wgpu_texture_create_view(wt.at(1,1),&wtvd.at(1,1));
wtv.at(1,1)=colorTextureView;
// colorAttachment.view=wgpu_texture_create_view(wgpu_canvas_context_get_current_texture(wcc.at(0,0)),0);
colorAttachment.view=wtv.at(1,1);
colorAttachment.storeOp=WGPU_STORE_OP_STORE;
colorAttachment.loadOp=WGPU_LOAD_OP_LOAD;
colorAttachment.clearValue.r=1.0f;
colorAttachment.clearValue.g=1.0f;
colorAttachment.clearValue.b=1.0f;
colorAttachment.clearValue.a=1.0f;
wrpca.at(0,0)=colorAttachment;
// depthAttachment={};
depthTextureView=wgpu_texture_create_view(wt.at(0,0),&wtvd.at(0,0));
wtv.at(0,0)=depthTextureView;
depthAttachment.view=wtv.at(0,0);
depthAttachment.depthClearValue=1.0f;
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
      // Compute Pass
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(wd.at(0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&WGPU_ComputePassDescriptor.at(0,0,0));
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
raN=rNd4(256);
WGPU_InputBuffer.at(0,0,0)[0]=raN;
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&WGPU_Input_Image,&WGPU_ColorBuffer.at(0,0,0),1024,0,1,1,1);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
 // wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
//  WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
// wgpu_object_destroy(WGPU_Buffers.at(2,0,2));
 // wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
      wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
      wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));
// if(WGPU_BufferStatus.at(0,0,0)!=1){
// wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// }
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one_and_destroy(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
    // wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
wgpu_buffer_map_async(WGPU_Buffers.at(2,0,2),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,OutputBufferBytes);
}
  // Render pass A (color)
wceA=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(0,0)=wceA;
wrpe.at(0,0)=wgpu_command_encoder_begin_render_pass(wce.at(0,0),&wrpd.at(0,0));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(0,0),wrp.at(0,0));
wgpu_encoder_set_bind_group(wrpe.at(0,0),0,wbg.at(0,0),0,0);
wgpu_queue_write_buffer(wq.at(0,0),wb.at(0,0),0,&u64_uni.at(0,0),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(1,1),0,&u64_uni.at(1,1),sizeof(uint64_t));
wgpu_queue_write_buffer(wq.at(0,0),wb.at(2,2),0,&u64_uni.at(2,2),sizeof(uint64_t));
wgpu_render_pass_encoder_set_viewport(wrpe.at(0,0),0.0,0.0,sze.at(0,0),sze.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_draw(wrpe.at(0,0),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(0,0));
wcb.at(0,0)=wgpu_command_encoder_finish(wce.at(0,0));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(0,0));
wceA={};
  // Render pass B (depth)
wceB=wgpu_device_create_command_encoder(wd.at(0,0),0);
wce.at(1,1)=wceB;
wrpe.at(1,1)=wgpu_command_encoder_begin_render_pass(wce.at(1,1),&wrpd.at(1,1));
wgpu_render_pass_encoder_set_pipeline(wrpe.at(1,1),wrp.at(1,1));
wgpu_encoder_set_bind_group(wrpe.at(1,1),0,wbg.at(0,0),0,0);
wgpu_render_pass_encoder_set_viewport(wrpe.at(1,1),0.0,0.0,sze.at(0,0),sze.at(0,0),0.0f,1.0f);
wgpu_render_pass_encoder_draw(wrpe.at(1,1),6,1,0,0);
wgpu_render_pass_encoder_end(wrpe.at(1,1));
wcb.at(1,1)=wgpu_command_encoder_finish(wce.at(1,1));
wgpu_queue_submit_one_and_destroy(wq.at(0,0),wcb.at(1,1));
wceB={};
return;
}

void ObtainedWebGpuDeviceStart(WGpuDevice result, void *userData){
wd.at(0,0)=result;
WGPU_UserData.at(0,0,0)=userData;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(wd.at(0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Input_Image.texture=WGPU_Texture.at(0,0,0);
WGPU_Output_Image.texture=WGPU_Texture.at(0,0,1);
WGPU_TextureViewDescriptor.at(0,0,0)=textureViewDescriptorA;
WGPU_ResultBuffer.at(0,0,0)=WGPU_Result_Array;
WGPU_InputBuffer.at(0,0,0)=WGPU_Input_Array;
WGPU_ColorBuffer.at(0,0,0)=WGPU_Color_Input_Array;
WGPU_BufferDescriptor.at(0,0,0)=bufferDescriptorI;
WGPU_BufferDescriptor.at(0,0,1)=bufferDescriptorO;
WGPU_BufferDescriptor.at(0,0,2)=bufferDescriptorM;
WGPU_BufferDescriptor.at(0,0,3)=bufferDescriptorC;
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(wd.at(0,0),&WGPU_BufferDescriptor.at(0,0,3));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
// if(WGPU_BufferStatus.at(0,0,0)!=1){
// wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
// }
WGPU_Output_Buffer.buffer=WGPU_Buffers.at(0,0,0);
WGPU_Output_Buffer.bytesPerRow=4096;
WGPU_Output_Buffer.rowsPerImage=256;
WGPU_Mapped_Buffer.buffer=WGPU_Buffers.at(2,0,2);
WGPU_Mapped_Buffer.bytesPerRow=4096;
WGPU_Mapped_Buffer.rowsPerImage=256;
raN=rNd4(256);
input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
// std::cout << "Random input:" << std::endl;
// std::cout << raN << std::endl;
WGPU_ShaderModuleDescriptor.at(0,0,0)=shaderModuleDescriptor;
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(wd.at(0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
WGPU_BufferBindingLayout.at(0,0,1)=bufferBindingLayout1;
WGPU_BufferBindingLayout.at(0,0,2)=bufferBindingLayout2;
WGPU_BufferBindingLayout.at(0,0,3)=bufferBindingLayout3;
WGPU_BufferBindingLayout.at(0,0,4)=bufferBindingLayout4;
WGPU_StorageTextureBindingLayout.at(0,0,0)=storageTextureBindingLayout1;
bindGroupLayoutEntries[0].binding=0;
bindGroupLayoutEntries[0].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[0].type=1;
bindGroupLayoutEntries[0].layout.buffer=WGPU_BufferBindingLayout.at(0,0,1);
bindGroupLayoutEntries[1].binding=1;
bindGroupLayoutEntries[1].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[1].type=1;
bindGroupLayoutEntries[1].layout.buffer=WGPU_BufferBindingLayout.at(0,0,2);
bindGroupLayoutEntries[2].binding=2;
bindGroupLayoutEntries[2].visibility=WGPU_SHADER_STAGE_COMPUTE;
bindGroupLayoutEntries[2].type=4;
bindGroupLayoutEntries[2].layout.storageTexture=WGPU_StorageTextureBindingLayout.at(0,0,0);
WGPU_BindGroupLayoutEntries.at(0,0,0)=bindGroupLayoutEntries;
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(wd.at(0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(wd.at(0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(wd.at(0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
bindGroupEntry[0].binding=0;
bindGroupEntry[0].resource=WGPU_Buffers.at(1,1,1);
bindGroupEntry[0].bufferBindOffset=0;
bindGroupEntry[0].bufferBindSize=InputBufferBytes;
bindGroupEntry[1].binding=1;
bindGroupEntry[1].resource=WGPU_Buffers.at(0,0,0);
bindGroupEntry[1].bufferBindOffset=0;
bindGroupEntry[1].bufferBindSize=OutputBufferBytes;
bindGroupEntry[2].binding=2;
bindGroupEntry[2].resource=WGPU_Texture.at(0,0,0);
WGPU_BindGroupEntries.at(0,0,0)=bindGroupEntry;
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(wd.at(0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_ComputePassDescriptor.at(0,0,0)=computePassDescriptor;
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(wd.at(0,0));
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
wtf.at(0,0)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
wtf.at(3,3)=WGPU_TEXTURE_FORMAT_RGBA16FLOAT;
wtf.at(4,4)=WGPU_TEXTURE_FORMAT_RGBA32FLOAT;
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
wccf.at(0,0)=config;
wgpu_canvas_context_configure(wcc.at(0,0),&wccf.at(0,0));
// emscripten_get_element_css_size("canvas",&szh,&szw);
emscripten_get_canvas_element_size("canvas",&szhI,&szwI);
u64_siz.at(0,0)=szhI;
sze.at(0,0)=szhI;
sze.at(0,1)=szhI;
multiSamp={};
multiSamp.count=1;
multiSamp.mask=-1;
multiSamp2={};
multiSamp2.count=1; // 4;
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
depthState={};
depthState.format=WGPU_TEXTURE_FORMAT_INVALID;
depthState.depthWriteEnabled=0;
depthState.depthCompare=WGPU_COMPARE_FUNCTION_INVALID;
wdss.at(0,0)=depthState;
depthState2={};
depthState2.format=wtf.at(2,2);
depthState2.depthWriteEnabled=1;
depthState2.depthCompare=WGPU_COMPARE_FUNCTION_LESS_EQUAL;
// depthState2.depthCompare=WGPU_COMPARE_FUNCTION_ALWAYS;
wdss.at(1,1)=depthState2;
vertState={};
vertState.module=wsm.at(0,0);
vertState.entryPoint="main";
vertState.numBuffers=0;
vertState.buffers=nullptr;
vertState.numConstants=0;
vertState.constants=nullptr;
wvs.at(0,0)=vertState;
priState={};
priState.topology=WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Defaults to WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ('triangle-list')
// priState.stripIndexFormat=WGPU_INDEX_FORMAT_UINT32; // Defaults to undefined, must be explicitly specified if WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP ('line-strip') or WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ('triangle-strip') is used.
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
iChannel0SamplerDescriptor.addressModeU=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
iChannel0SamplerDescriptor.addressModeV=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
iChannel0SamplerDescriptor.addressModeW=WGPU_ADDRESS_MODE_CLAMP_TO_EDGE;
iChannel0SamplerDescriptor.magFilter=WGPU_FILTER_MODE_LINEAR;
iChannel0SamplerDescriptor.minFilter=WGPU_FILTER_MODE_LINEAR;
iChannel0SamplerDescriptor.mipmapFilter=WGPU_MIPMAP_FILTER_MODE_LINEAR;
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
textureBindingLayout1.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_UINT;
textureBindingLayout1.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout1.multisampled=1;
wtbl.at(0,0)=textureBindingLayout1;
textureBindingLayout2.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_FLOAT;
textureBindingLayout2.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout2.multisampled=1;
wtbl.at(1,1)=textureBindingLayout2;
textureBindingLayout3.sampleType=WGPU_TEXTURE_SAMPLE_TYPE_DEPTH;
textureBindingLayout3.viewDimension=WGPU_TEXTURE_VIEW_DIMENSION_2D;
textureBindingLayout3.multisampled=1;
wtbl.at(2,2)=textureBindingLayout3;
bindgroup_layout_entries[0]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[0].binding=0;
bindgroup_layout_entries[0].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[0].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[0].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[1]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[1].binding=1;
bindgroup_layout_entries[1].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[1].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[1].layout.buffer=wbbl.at(0,0);
bindgroup_layout_entries[2]={WGPU_BUFFER_BINDING_LAYOUT_ENTRY_DEFAULT_INITIALIZER};
bindgroup_layout_entries[2].binding=2;
bindgroup_layout_entries[2].visibility=WGPU_SHADER_STAGE_FRAGMENT;
bindgroup_layout_entries[2].type=WGPU_BIND_GROUP_LAYOUT_TYPE_BUFFER;
bindgroup_layout_entries[2].layout.buffer=wbbl.at(0,0);
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
wbgle.at(0,0)=bindgroup_layout_entries;
bindgroup_layout=wgpu_device_create_bind_group_layout(wd.at(0,0),wbgle.at(0,0),3);
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
renderPipelineDesc2.layout=wrpl.at(0,0);
// renderPipelineDesc2.layout=WGPU_AUTO_LAYOUT_MODE_AUTO;
renderPipelineDesc2.multisample=wms.at(1,1);
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
__128bit_Texture__=wgpu_device_create_texture(wd.at(0,0),&wtd.at(2,2));
wt.at(2,2)=__128bit_Texture__;
bindgroup_entries[0]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[0].binding=0;
bindgroup_entries[0].resource=wb.at(0,0);
bindgroup_entries[0].bufferBindOffset=0;
bindgroup_entries[0].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[1]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[1].binding=1;
bindgroup_entries[1].resource=wb.at(1,1);
bindgroup_entries[1].bufferBindOffset=0;
bindgroup_entries[1].bufferBindSize=sizeof(uint64_t);
bindgroup_entries[2]={WGPU_BIND_GROUP_ENTRY_DEFAULT_INITIALIZER};
bindgroup_entries[2].binding=2;
bindgroup_entries[2].resource=wb.at(2,2);
bindgroup_entries[2].bufferBindOffset=0;
bindgroup_entries[2].bufferBindSize=sizeof(uint64_t);
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
wbge.at(0,0)=bindgroup_entries;
// renderBundleEncoderDescriptor.sampleCount=1;
// renderBundleEncoderDescriptor.depthStencilFormat=wtf.at(2,2);
// wrbed.at(0,0)=renderBundleEncoderDescriptor;
// renderBundleEncoder=wgpu_device_create_render_bundle_encoder(wd.at(0,0),&wrbed.at(0,0));
// wrbe.at(0,0)=renderBundleEncoder;
wq.at(0,0)=wgpu_device_get_queue(wd.at(0,0));
// tme=get_current_time_in_milliseconds();
// wTime.iTime=get_current_time_in_milliseconds();
bindgroup=wgpu_device_create_bind_group(wd.at(0,0),wbgl.at(0,0),wbge.at(0,0),3);
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
// emscripten_set_main_loop_timing(2,1);
emscripten_set_main_loop((void(*)())raf,0,0);
// emscripten_request_animation_frame_loop(raf,0);
on.at(0,0)=1;
}

void ObtainedWebGpuAdapterStart(WGpuAdapter result, void *userData){
wa.at(0,0)=result;
deviceDesc={WGPU_DEVICE_DESCRIPTOR_DEFAULT_INITIALIZER};
// deviceDesc.requiredFeatures=WGPU_FEATURE_DEPTH32FLOAT_STENCIL8|WGPU_FEATURE_FLOAT32_FILTERABLE|WGPU_FEATURE_RG11B10UFLOAT_RENDERABLE;
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

EM_JS(void,js_main,(),{
FS.mkdir('/shader');
window.scroll(0,0);
function highResStart(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#scanvas').width=window.innerWidth*4;
document.querySelector('#scanvas').height=window.innerHeight*4;
document.querySelector('#di').click();
setTimeout(function(){
document.querySelector('#stat').innerHTML='Sending Start';
document.querySelector('#stat').style.backgroundColor='green';
Module.ccall('str',{async:true});
},50);
setTimeout(function(){
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#scanvas').width=window.innerHeight;
document.querySelector('#scanvas').height=window.innerHeight;
document.querySelector('#di').click();
},150);
}
function normalResStart(){
setTimeout(function(){
document.querySelector('#shut').innerHTML=2;
document.querySelector('#circle').width=window.innerWidth;
document.querySelector('#circle').height=window.innerHeight;
document.querySelector('#di').click();
Module.ccall("startWebGPU",{async:true});
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
scanShaders();

document.querySelector('#pmhig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#ihig').innerHTML=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').height=parseInt(window.innerHeight,10);
document.querySelector('#scanvas').width=parseInt(window.innerHeight,10);
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
let shdMenu=document.querySelector('#sh1');
let highRes=document.querySelector('#resMode').value;
                       //  get onnx model  //
document.querySelector('#path').innerHTML='https://1ink.us/files/OverNet.onnx';
var pth=document.querySelector('#path').innerHTML;
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading Shader';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/shader/model.onnx',sfil);
document.querySelector('#stat').innerHTML='Downloaded Model';
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
cltest();
// WGPU_Start();
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
