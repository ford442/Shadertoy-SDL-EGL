#include "../../include/vanilla/main_webgpu.hpp"

EmscriptenWebGLContextAttributes attr;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx=0;

double wi,hi;

void cltest(){
std::vector<std::string> infos=Ort::GetAvailableProviders();
char* char_array=new char[infos.size()*infos[0].size()];
for (int i=0;i<infos.size();i++){
std::copy(infos[i].begin(),infos[i].end(),char_array+i*infos[0].size());
}
std::cout << char_array << std::endl;
Ort::Env ort_env;
const char model_path[12]="/model.onnx";
const int64_t batchSize=2;
Ort::SessionOptions sessionOptions;
sessionOptions.SetIntraOpNumThreads(1);
	
		 // Sets graph optimization level
    // Available levels are
    // ORT_DISABLE_ALL -> To disable all optimizations
    // ORT_ENABLE_BASIC -> To enable basic optimizations (Such as redundant node
    // removals) ORT_ENABLE_EXTENDED -> To enable extended optimizations
    // (Includes level 1 + more complex optimizations like node fusions)
    // ORT_ENABLE_ALL -> To Enable All possible optimizations
	
sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
Ort::Session session(ort_env,model_path,sessionOptions);
Ort::AllocatorWithDefaultOptions allocator;

size_t numInputNodes=session.GetInputCount();
size_t numOutputNodes=session.GetOutputCount();

auto inputName=session.GetInputNameAllocated(0,allocator);

Ort::TypeInfo inputTypeInfo=session.GetInputTypeInfo(0);
auto inputTensorInfo=inputTypeInfo.GetTensorTypeAndShapeInfo();

ONNXTensorElementDataType inputType=inputTensorInfo.GetElementType();

std::vector<int64_t> inputDims=inputTensorInfo.GetShape();
if (inputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting input batch size to " << batchSize << "." << std::endl;
inputDims.at(0)=batchSize;
}

auto outputName=session.GetOutputNameAllocated(0,allocator);
auto outputName2=session.GetOutputNameAllocated(1,allocator);

Ort::TypeInfo outputTypeInfo=session.GetOutputTypeInfo(0);
auto outputTensorInfo=outputTypeInfo.GetTensorTypeAndShapeInfo();

ONNXTensorElementDataType outputType=outputTensorInfo.GetElementType();

std::vector<int64_t> outputDims=outputTensorInfo.GetShape();
if (outputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting output batch size to "
<< batchSize << "." << std::endl;
outputDims.at(0)=batchSize;
}

std::cout << "Number of Input Nodes: " << numInputNodes << std::endl;
std::cout << "Number of Output Nodes: " << numOutputNodes << std::endl;
std::cout << "Input Name: " << inputName << std::endl;
std::cout << "Input Type: " << inputType << std::endl;
std::cout << "Input Dimensions 1: " <<  std::to_string(inputDims.at(0)) << std::endl;
std::cout << "Input Dimensions 2: " <<  std::to_string(inputDims.at(1)) << std::endl;
// std::cout << "Input Dimensions 3: " <<  std::to_string(inputDims.at(2)) << std::endl;
std::cout << "Output Name: " << outputName << std::endl;
std::cout << "Output 2 Name: " << outputName2 << std::endl;
std::cout << "Output Type: " << outputType << std::endl;
std::cout << "Output Dimensions 1: " <<  std::to_string(outputDims.at(0)) << std::endl;
std::cout << "Output Dimensions 2: " <<  std::to_string(outputDims.at(1)) << std::endl;
std::cout << "Output Dimensions 3: " <<  std::to_string(outputDims.at(2)) << std::endl;
	
size_t inputTensorSize=2;// inputDims.at(0)*inputDims.at(1)*inputDims.at(2); // vectorProduct(inputDims);
std::cout << "setting inputTensorSize " <<  std::endl;

std::vector<float> inputTensorValues(inputTensorSize);
	std::cout << "setting inputTensorValues " <<  std::endl;

size_t outputTensorSize=1536; // vectorProduct(outputDims);
	std::cout << "setting outputTensorSize " <<  std::endl;

std::vector<float> outputTensorValues(outputTensorSize);
		std::cout << "setting outputTensorValues " <<  std::endl;

	std::string text_prompt="two birds";

  std::vector<float> text_prompt_vector;
  for (char c : text_prompt) {
    text_prompt_vector.push_back(c);
  }
	
std::cout << "Establishing text input" << std::endl;
	
std::vector<const char*>inputNames={"input_ids"};
std::vector<const char*>outputNames={"last_hidden_state","pooler_output"};

Ort::MemoryInfo memoryInfo=Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator,OrtMemType::OrtMemTypeDefault);
// std::cout << "Establishing memoryInfo" << std::endl;
	
std::vector<Ort::Value> inputTensors{nullptr};
Ort::Value outputTensors{nullptr};

	
// Ort::Value inputTensor=Ort::Value::CreateTensor<float>(
// memoryInfo,text_prompt_vector.data(),text_prompt_vector.size(),inputDims.data(),
// inputDims.size());
	
inputTensors.push_back(Ort::Value::CreateTensor<float>(
memoryInfo, inputTensorValues.data(), inputTensorSize, 2,
1));
	
std::cout << "Establishing Tensors" << std::endl;
	
std::cout << "Creating CPU link " << std::endl;


// Ort::RunOptions runOpts;
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
session.Run(Ort::RunOptions{},inputNames.data(),inputTensors.data(),1,outputNames.data(),&outputTensors,2);
	
//   void Run(const RunOptions& run_options, const char* const* input_names, const Value* input_values, size_t input_count,
//                     const char* const* output_names, Value* output_values, size_t output_count);
	
//   void Run(run_options,input_names,input_values,input_count,
//                     output_names,output_values,output_count);

std::cout << "Running inferrence." << std::endl;

auto outputDataPtr = outputTensors.GetTensorRawData();

 emscripten_webgl_init_context_attributes(&attr);
attr.alpha=EM_TRUE;
attr.stencil=EM_FALSE;
attr.depth=EM_FALSE;
attr.antialias=EM_TRUE;
attr.premultipliedAlpha=EM_TRUE;
attr.preserveDrawingBuffer=EM_FALSE;
attr.enableExtensionsByDefault=EM_FALSE;
attr.renderViaOffscreenBackBuffer=EM_FALSE;
attr.powerPreference=EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
attr.failIfMajorPerformanceCaveat=EM_FALSE;
attr.majorVersion=3;
attr.minorVersion=0;
ctx=emscripten_webgl_create_context("#scanvas",&attr);
emscripten_webgl_make_context_current(ctx);
emscripten_get_element_css_size("canvas",&wi,&hi);
	
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

}

extern"C"{

void testtr(){
    //     Ort::Env ort_env2;

      // Create an OpenVINO Runtime object.
// InferenceEngine::Core core;
 //   ov::Core core;
    /*
    unsigned char* img_data = NULL;
    ov_core_t* core = NULL;
    ov_model_t* model = NULL;
    ov_tensor_t* tensor = NULL;
    ov_preprocess_prepostprocessor_t* preprocess = NULL;
    ov_preprocess_input_info_t* input_info = NULL;
    ov_model_t* new_model = NULL;
    ov_preprocess_input_tensor_info_t* input_tensor_info = NULL;
    ov_preprocess_preprocess_steps_t* input_process = NULL;
    ov_preprocess_input_model_info_t* p_input_model = NULL;
    ov_compiled_model_t* compiled_model = NULL;
    ov_infer_request_t* infer_request = NULL;
    ov_tensor_t* output_tensor = NULL;
    struct infer_result* results = NULL;
    char* input_tensor_name = NULL;
    char* output_tensor_name = NULL;
    ov_output_const_port_t* input_port = NULL;
    ov_output_const_port_t* output_port = NULL;
    ov_layout_t* model_layout = NULL;
    ov_shape_t input_shape;

    CHECK_STATUS(ov_core_create(&core));
    */
}

}

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

using mouse_tensor=boost::numeric::ublas::tensor<float>;
using shad_tensor=boost::numeric::ublas::tensor<boost::uint_t<32>::exact>;
using prg_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using sz_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using f_tensor=boost::numeric::ublas::tensor<float>;
using d_tensor=boost::numeric::ublas::tensor<double>;
using di_tensor=boost::numeric::ublas::tensor<boost::uint_t<64>::exact>;
using v_tensor=boost::numeric::ublas::tensor<v128_t>;
using i_tensor=boost::numeric::ublas::tensor<boost::int_t<64>::exact>;
using iptr_tensor=boost::numeric::ublas::tensor<int *>;
using fptr_tensor=boost::numeric::ublas::tensor<float *>;
using uiptr_tensor=boost::numeric::ublas::tensor<uint32_t *>;
using gi_tensor=boost::numeric::ublas::tensor<GLint>;
using li_tensor=boost::numeric::ublas::tensor<long>;
using void_tensor=boost::numeric::ublas::tensor<void *>;
using bgle_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayoutEntry *>;
using bge_tensor=boost::numeric::ublas::tensor<WGpuBindGroupEntry *>;
using bmc_tensor=boost::numeric::ublas::tensor<WGpuBufferMapCallback>;
using wdc_tensor=boost::numeric::ublas::tensor<WGpuOnSubmittedWorkDoneCallback>;
using oac_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterCallback>;
using odc_tensor=boost::numeric::ublas::tensor<WGpuRequestDeviceCallback>;
using bbl_tensor=boost::numeric::ublas::tensor<WGpuBufferBindingLayout>;
using bd_tensor=boost::numeric::ublas::tensor<WGpuBufferDescriptor>;
using md_tensor=boost::numeric::ublas::tensor<WGpuShaderModuleDescriptor>;
using dd_tensor=boost::numeric::ublas::tensor<WGpuDeviceDescriptor>;
using rao_tensor=boost::numeric::ublas::tensor<WGpuRequestAdapterOptions>;
using wa_tensor=boost::numeric::ublas::tensor<WGpuAdapter>;
using wq_tensor=boost::numeric::ublas::tensor<WGpuQueue>;
using cb_tensor=boost::numeric::ublas::tensor<WGpuCommandBuffer>;
using wb_tensor=boost::numeric::ublas::tensor<WGpuBuffer>;
using ce_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoder>;
using wd_tensor=boost::numeric::ublas::tensor<WGpuDevice>;
using cpe_tensor=boost::numeric::ublas::tensor<WGpuComputePassEncoder>;
using cp_tensor=boost::numeric::ublas::tensor<WGpuComputePipeline>;
using pl_tensor=boost::numeric::ublas::tensor<WGpuPipelineLayout>;
using cm_tensor=boost::numeric::ublas::tensor<WGpuShaderModule>;
using bg_tensor=boost::numeric::ublas::tensor<WGpuBindGroup>;
using bgl_tensor=boost::numeric::ublas::tensor<WGpuBindGroupLayout>;
using i53_tensor=boost::numeric::ublas::tensor<double_int53_t>;
using tex_tensor=boost::numeric::ublas::tensor<WGpuTexture>;
using td_tensor=boost::numeric::ublas::tensor<WGpuTextureDescriptor>;
using stbl_tensor=boost::numeric::ublas::tensor<WGpuStorageTextureBindingLayout>;
using tv_tensor=boost::numeric::ublas::tensor<WGpuTextureView>;
using tvd_tensor=boost::numeric::ublas::tensor<WGpuTextureViewDescriptor>;
using ced_tensor=boost::numeric::ublas::tensor<WGpuCommandEncoderDescriptor>;
using bms_tensor=boost::numeric::ublas::tensor<WGPU_BUFFER_MAP_STATE>;

static v_tensor sse=v_tensor{2,2};
static v_tensor sse2=v_tensor{2,2};
static v_tensor sse3=v_tensor{2,2};
static v_tensor sse4=v_tensor{1,1};
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
static cb_tensor WGPU_CommandBuffer=cb_tensor{1,1,3};
static wb_tensor WGPU_Buffers=wb_tensor{3,3,3};
static ce_tensor WGPU_CommandEncoder=ce_tensor{1,1,4};
static cpe_tensor WGPU_ComputePassCommandEncoder=cpe_tensor{1,1,3};
static cp_tensor WGPU_ComputePipeline=cp_tensor{1,1,1};
static pl_tensor WGPU_ComputePipelineLayout=pl_tensor{1,1,1};
static cm_tensor WGPU_ComputeModule=cm_tensor{1,1,1};
static bg_tensor WGPU_BindGroup=bg_tensor{1,1,2};
static bgl_tensor WGPU_BindGroupLayout=bgl_tensor{1,1,2};
static bgle_tensor WGPU_BindGroupLayoutEntries=bgle_tensor{1,1,2};
static bge_tensor WGPU_BindGroupEntries=bge_tensor{1,1,2};
static bmc_tensor WGPU_MapCallback=bmc_tensor{1,1,3};
static wdc_tensor WGPU_ComputeDoneCallback=wdc_tensor{1,1,3};
static oac_tensor WGPU_ObtainedAdapterCallback=oac_tensor{1,1,2};
static odc_tensor WGPU_ObtainedDeviceCallback=odc_tensor{1,1,2};
static bbl_tensor WGPU_BufferBindingLayout=bbl_tensor{1,1,4};
static bd_tensor WGPU_BufferDescriptor=bd_tensor{1,1,4};
static md_tensor WGPU_ShaderModuleDescriptor=md_tensor{1,1,3};
static di_tensor WGPU_BufferMappedRange=di_tensor{1,1,1};
static void_tensor WGPU_UserData=void_tensor{1,1,2};
static rao_tensor WGPU_RequestAdapterOptions=rao_tensor{1,1,1};
static dd_tensor WGPU_DeviceDescriptor=dd_tensor{1,1,1};
static uiptr_tensor WGPU_ResultBuffer=uiptr_tensor{1,1,1};
static uiptr_tensor WGPU_InputBuffer=uiptr_tensor{1,1,1};
static i53_tensor WGPU_BufferRange=i53_tensor{1,1,2};
static i53_tensor WGPU_BufferSize=i53_tensor{1,1,1};
static tex_tensor WGPU_Texture=tex_tensor{1,1,1};
static td_tensor WGPU_TextureDescriptor=td_tensor{1,1,1};
static stbl_tensor WGPU_StorageTextureBindingLayout=stbl_tensor{1,1,1};
static tvd_tensor WGPU_TextureViewDescriptor=tvd_tensor{1,1,1};
static tv_tensor WGPU_TextureView=tv_tensor{1,1,1};
static uiptr_tensor WGPU_ColorBuffer=uiptr_tensor{1,1,1};
static ced_tensor WGPU_CommandEncoderDescriptor=ced_tensor{1,1,1};
static bms_tensor WGPU_BufferStatus=bms_tensor{1,1,1};

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
GLsizei width=256;
GLsizei height=256;
GLuint wtexture[4];
WGpuTexture textureA;
  WGpuAdapter adapter=0;
  WGpuDevice device=0;
  WGpuQueue queue=0;
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
double_int53_t WGPU_Range_PointerB=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,1)=WGPU_Range_PointerB;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2), WGPU_BufferRange.at(0,0,1) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.getElementById('outText').innerHTML=$0;
},WGPU_ResultBuffer.at(0,0,0)[0]);
// std::cout << WGPU_ResultBuffer.at(0,0,0)[0] << std::endl;
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),mapCallbackStart,&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
// sleep(1);
// WGPU_Run();
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun=[](WGpuQueue queue,void *userData){
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
double_int53_t WGPU_Range_PointerC=wgpu_buffer_get_mapped_range(WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
WGPU_BufferRange.at(0,0,0)=WGPU_Range_PointerC;
wgpu_buffer_read_mapped_range(WGPU_Buffers.at(2,0,2),  WGPU_BufferRange.at(0,0,0) ,0,WGPU_ResultBuffer.at(0,0,0),OutputBufferBytes);
EM_ASM({
document.getElementById('outText').innerHTML=$0;
},WGPU_ResultBuffer.at(0,0,0)[0]);
}
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)==3){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
// wgpu_buffer_map_async(WGPU_Buffers.at(1,0,1),WGPU_MapCallback.at(0,0,1),&WGPU_UserData.at(0,0,0),mode1,0,WGPU_InputRangeSize);
usleep(250);
runWebGPU();
return;
};

WGpuOnSubmittedWorkDoneCallback onComputeDoneRun2=[](WGpuQueue queue,void *userData){
return;
};

static boost::function<void()>raf=[](){
// static void raf(){
WGPU_TextureDescriptor.at(0,0,0)=textureDescriptorA;
WGPU_CommandEncoderDescriptor.at(0,0,0)=commandEncoderDescriptor;
WGPU_Texture.at(0,0,0)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
WGPU_Texture.at(0,0,1)=wgpu_device_create_texture(WGPU_Device.at(0,0,0),&WGPU_TextureDescriptor.at(0,0,0));
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
WGPU_Buffers.at(1,1,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,0));
WGPU_Buffers.at(0,0,0)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,1));
WGPU_Buffers.at(1,0,1)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,2));
WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
// WGPU_BUFFER_MAP_STATE statebe=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
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
WGPU_ComputeModule.at(0,0,0)=wgpu_device_create_shader_module(WGPU_Device.at(0,0,0),&WGPU_ShaderModuleDescriptor.at(0,0,0));
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
WGPU_BindGroupLayout.at(0,0,0)=wgpu_device_create_bind_group_layout(WGPU_Device.at(0,0,0),WGPU_BindGroupLayoutEntries.at(0,0,0),2);
WGPU_ComputePipelineLayout.at(0,0,0)=wgpu_device_create_pipeline_layout(WGPU_Device.at(0,0,0),&WGPU_BindGroupLayout.at(0,0,0),1);
WGPU_ComputePipeline.at(0,0,0)=wgpu_device_create_compute_pipeline(WGPU_Device.at(0,0,0),WGPU_ComputeModule.at(0,0,0),Entry,WGPU_ComputePipelineLayout.at(0,0,0),NULL,0);
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
WGPU_BindGroup.at(0,0,0)=wgpu_device_create_bind_group(WGPU_Device.at(0,0,0),WGPU_BindGroupLayout.at(0,0,0),WGPU_BindGroupEntries.at(0,0,0),2);
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
// WGPU_Queue.at(0,0,1)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
// wgpu_queue_write_texture(WGPU_Queue.at(0,0,0),&WGPU_Input_Image,&WGPU_ColorBuffer.at(0,0,0),1024,0,1,1,1);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
 // wgpu_buffer_unmap(WGPU_Buffers.at(1,0,1));
//  WGPU_Buffers.at(2,0,2)=wgpu_device_create_buffer(WGPU_Device.at(0,0,0),&WGPU_BufferDescriptor.at(0,0,3));
// wgpu_object_destroy(WGPU_Buffers.at(2,0,2));
 // wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
    WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));

    WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));

if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,0),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
}
return;
};

static std::function<void()>WGPU_Run=[](){
//static void WGPU_Run(){
raN=rNd4(256);
input[0]=raN;
WGPU_InputBuffer.at(0,0,0)[0]=raN;
// std::cout << "Random input int:" << std::endl;
// std::cout << raN << std::endl;
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
WGPU_Queue.at(0,0,0)=wgpu_device_get_queue(WGPU_Device.at(0,0,0));
WGPU_CommandEncoder.at(0,0,0)=wgpu_device_create_command_encoder_simple(WGPU_Device.at(0,0,0));
WGPU_ComputePassCommandEncoder.at(0,0,0)=wgpu_command_encoder_begin_compute_pass(WGPU_CommandEncoder.at(0,0,0),&computePassDescriptor);
wgpu_compute_pass_encoder_set_pipeline(WGPU_ComputePassCommandEncoder.at(0,0,0),WGPU_ComputePipeline.at(0,0,0));
wgpu_encoder_set_bind_group(WGPU_ComputePassCommandEncoder.at(0,0,0),0,WGPU_BindGroup.at(0,0,0),0,0);
wgpu_queue_write_buffer(WGPU_Queue.at(0,0,0),WGPU_Buffers.at(1,1,1),0,WGPU_InputBuffer.at(0,0,0),InputBufferBytes);
wgpu_compute_pass_encoder_dispatch_workgroups(WGPU_ComputePassCommandEncoder.at(0,0,0),4,1,64);
wgpu_encoder_end(WGPU_ComputePassCommandEncoder.at(0,0,0));
wgpu_command_encoder_copy_buffer_to_texture(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Buffer,&WGPU_Output_Image,256,256,1);
// wgpu_command_encoder_copy_buffer_to_buffer(WGPU_CommandEncoder.at(0,0,0),WGPU_Buffers.at(0,0,0),0,WGPU_Buffers.at(2,0,2),0,OutputBufferBytes);
wgpu_command_encoder_copy_texture_to_buffer(WGPU_CommandEncoder.at(0,0,0),&WGPU_Output_Image,&WGPU_Mapped_Buffer,256,256,1);
    WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));

    WGPU_CommandBuffer.at(0,0,0)=wgpu_encoder_finish(WGPU_CommandEncoder.at(0,0,0));

if(WGPU_BufferStatus.at(0,0,0)!=1){
wgpu_buffer_unmap(WGPU_Buffers.at(2,0,2));
}
wgpu_queue_set_on_submitted_work_done_callback(WGPU_Queue.at(0,0,0),WGPU_ComputeDoneCallback.at(0,0,1),0);
wgpu_queue_submit_one(WGPU_Queue.at(0,0,0),WGPU_CommandBuffer.at(0,0,0));
WGPU_BufferStatus.at(0,0,0)=wgpu_buffer_map_state(WGPU_Buffers.at(2,0,2));
if(WGPU_BufferStatus.at(0,0,0)!=3){
wgpu_buffer_map_sync(WGPU_Buffers.at(2,0,2),mode1,0,OutputBufferBytes);  
}
return;
};

static void WGPU_Run2(){
return;
}

static void ObtainedWebGpuDeviceStart2(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
raf();
return;
}

static void ObtainedWebGpuDeviceStart(WGpuDevice result,void * userData){
device=result;
WGPU_Device.at(0,0,0)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,1),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

static void ObtainedWebGpuAdapterStart2(WGpuAdapter result,void * userData){
WGPU_Adapter.at(0,0,1)=result;
wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
}

static void ObtainedWebGpuAdapterStart(WGpuAdapter result,void * userData){
adapter=result;
WGPU_Adapter.at(0,0,0)=result;
    wgpu_adapter_request_device_async(WGPU_Adapter.at(0,0,0),&WGPU_DeviceDescriptor.at(0,0,0),WGPU_ObtainedDeviceCallback.at(0,0,1),&WGPU_UserData.at(0,0,0));
// navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,1),&WGPU_UserData.at(0,0,1));
return;
}

std::function<void()>WGPU_Start=[](){
// void WGPU_Start(){
WGPU_UserData.at(0,0,0)=userDataA;
WGPU_UserData.at(0,0,1)=userDataB;
WGPU_ObtainedDeviceCallback.at(0,0,0)=ObtainedWebGpuDeviceStart;
WGPU_ObtainedDeviceCallback.at(0,0,1)=ObtainedWebGpuDeviceStart2;
WGPU_DeviceDescriptor.at(0,0,0)=deviceDescriptor;
WGPU_RequestAdapterOptions.at(0,0,0)=options;
WGPU_ObtainedAdapterCallback.at(0,0,0)=ObtainedWebGpuAdapterStart;
WGPU_ObtainedAdapterCallback.at(0,0,1)=ObtainedWebGpuAdapterStart2;
WGPU_ComputeDoneCallback.at(0,0,0)=onComputeDoneStart;
WGPU_ComputeDoneCallback.at(0,0,1)=onComputeDoneRun;
WGPU_ComputeDoneCallback.at(0,0,2)=onComputeDoneRun2;
WGPU_MapCallback.at(0,0,0)=mapCallbackStart;
WGPU_MapCallback.at(0,0,1)=mapCallbackRun;
WGPU_MapCallback.at(0,0,2)=mapCallbackRun2;
 navigator_gpu_request_adapter_async(&WGPU_RequestAdapterOptions.at(0,0,0),WGPU_ObtainedAdapterCallback.at(0,0,0),&WGPU_UserData.at(0,0,0));
return;
};

EM_JS(void,js_main,(),{

function strr(){
Module.ccall("runWebGPU");
}

function normalResStart(){
// Module.ccall("startWebGPU");
Module.ccall("runWebGPU2");
setTimeout(function(){
document.getElementById('shut').innerHTML=2;
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
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

document.getElementById('startBtn2').addEventListener('click',function(){
// myStopFunction();
Module.ccall("runWebGPU");
// Module.ccall("runWebGPU2");
// const myInterval=setInterval(strr,16.6);
});

document.getElementById('startBtn4').addEventListener('click',function(){
Module.ccall("startWebGPU");
});
	
setTimeout(function(){
document.getElementById('circle').width=window.innerWidth;
document.getElementById('circle').height=window.innerHeight;
document.getElementById('di').click();
},500);

});

extern"C"{

void startWebGPU(){
// WGPU_Start();
// sleep(1);
cltest();
}

void runWebGPU(){
WGPU_Run();
}

void runWebGPU2(){
WGPU_Start();
}

}

int main(void){
// testtr();
js_main();
// sleep(1);
// WGPU_Start();
return 0;
}
