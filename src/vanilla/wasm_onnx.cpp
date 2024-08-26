#include <emscripten.h>
#include <emscripten/bind.h>
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include <emscripten/em_types.h>
#include <emscripten/val.h>
#include "../../onnxruntime/include/onnxruntime/core/session/onnxruntime_cxx_api.h"
#include <iostream>

template <typename T>
T vectorProduct(const std::vector<T>& v){
return accumulate(v.begin(),v.end(),1,std::multiplies<T>());
}

using namespace std;

std::vector<int64_t> to_int32(vector<string> tokens) {
std::vector<int64_t> ints;
for (string token : tokens) {
std::cout << token << std::endl;
}
return ints;
}

std::vector<float> to_floats(vector<string> tokens) {
std::vector<float> floats;
for (string token : tokens) {
std::cout << token << std::endl;
}
return floats;
}

std::vector<string> tokenize(string text) {
std::vector<string> tokens;
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
std::vector<string>tokens=tokenize(text);
std::vector<int64_t>ints=to_int32(tokens);
std::vector<float>floats=to_floats(tokens);

void cltest(){
std::vector<std::string>infos=Ort::GetAvailableProviders();
char* char_array=new char[infos.size()*infos[0].size()];
for (int i=0;i<infos.size();i++){
std::copy(infos[i].begin(),infos[i].end(),char_array+i*infos[0].size());
}
std::cout << char_array << std::endl;
Ort::Env ort_env;
std::cout << "got ORT env" << std::endl;
 std::string model_path="/model/model.onnx";
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
sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_BASIC);
std::cout << "got ORT session/options" << std::endl;
std::cout << "got ORT SessionOptions" << std::endl;

		// from ms
Ort::Session sesh{ort_env,"/model/model.onnx",sessionOptions};
std::cout << "got ORT Session" << std::endl;
Ort::AllocatorWithDefaultOptions allocator;
std::cout << "got ORT allocator" << std::endl;

size_t numInputNodes=sesh.GetInputCount();
size_t numOutputNodes=sesh.GetOutputCount();
std::cout << "got ORT nodes" << std::endl;
std::cout << "input ORT nodes" << numInputNodes << std::endl;
std::cout << "output ORT nodes" << numOutputNodes << std::endl;
auto inputName=sesh.GetInputNameAllocated(0,allocator);
// const char* inputName = session.Ort::detail::GetInputName(0, allocator);
std::cout << "got ORT input" << std::endl;
Ort::TypeInfo inputTypeInfo=sesh.GetInputTypeInfo(0);
auto inputTensorInfo=inputTypeInfo.GetTensorTypeAndShapeInfo();
ONNXTensorElementDataType inputType=inputTensorInfo.GetElementType();
std::vector<int64_t>inputDims=inputTensorInfo.GetShape();
if (inputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting input batch size to " << batchSize << "." << std::endl;
inputDims.at(0)=1;
inputDims.at(1)=3;
inputDims.at(2)=96;
}
auto outputName=sesh.GetOutputNameAllocated(0,allocator);
//   //   const char* outputName=sesh.Ort::detail::GetOutputName(0, allocator);
Ort::TypeInfo outputTypeInfo=sesh.GetOutputTypeInfo(0);
auto outputTensorInfo=outputTypeInfo.GetTensorTypeAndShapeInfo();
ONNXTensorElementDataType outputType=outputTensorInfo.GetElementType();
std::vector<int64_t>outputDims=outputTensorInfo.GetShape();
	std::cout << ".at(0)" << outputDims.at(0) << "." << std::endl;
	std::cout << ".at(1)" << outputDims.at(1) << "." << std::endl;
	std::cout << ".at(2)" << outputDims.at(2) << "." << std::endl;
/*
if (outputDims.at(0) == -1){
std::cout << "Got dynamic batch size. Setting output batch size to "
<< batchSize << "." << std::endl;
outputDims.at(0)=batchSize;
}

outputDims.at(0)=1;
outputDims.at(1)=3;
outputDims.at(2)=768;
outputDims.at(3)=768;

std::cout << "Input Name: " << inputName << std::endl;
std::cout << "Input Type: " << inputType << std::endl;
std::cout << "Input Dimensions 1: " <<  std::to_string(inputDims.at(0)) << std::endl;
std::cout << "Input Dimensions 2: " <<  std::to_string(inputDims.at(1)) << std::endl;
std::cout << "Input Dimensions 3: " <<  std::to_string(inputDims.at(2)) << std::endl;
std::cout << "Output Name: " << outputName << std::endl;
std::cout << "Output Type: " << outputType << std::endl;
std::cout << "Output Dimensions 1: " <<  std::to_string(outputDims.at(0)) << std::endl;
std::cout << "Output Dimensions 2: " <<  std::to_string(outputDims.at(1)) << std::endl;
std::cout << "Output Dimensions 3: " <<  std::to_string(outputDims.at(2)) << std::endl;
std::cout << "Output Dimensions 4: " <<  std::to_string(outputDims.at(3)) << std::endl;
std::cout << "Number of Input Nodes: " << numInputNodes << std::endl;
std::cout << "Number of Output Nodes: " << numOutputNodes << std::endl;

size_t inputTensorSize=vectorProduct(inputDims);
std::cout << "setting inputTensorSize:" << inputTensorSize << std::endl;
std::vector<float> inputTensorValues(inputTensorSize);
std::cout << "setting inputTensorValues " <<  std::endl;
for (int64_t i = 0; i < batchSize; ++i)
{
std::copy(floats.begin(),floats.end(),inputTensorValues.begin()+i*inputTensorSize);
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
	
std::vector<const char*> inputNames;
std::vector<const char*> outputNames;
inputNames.reserve(1);
std::cout << "Establishing text input" << std::endl;
inputNames.push_back(inputName.get());
outputNames.push_back(outputName.get());
std::cout << "Establishing tensor names" << std::endl;
Ort::MemoryInfo memoryInfo=Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator,OrtMemTypeCPU);
std::cout << "Establishing memoryInfo" << std::endl;
std::vector<Ort::Value>inputTensors;
std::vector<Ort::Value>outputTensors;
// Ort::Value outputTensors{nullptr};
	
inputTensors.push_back(Ort::Value::CreateTensor<float>(memoryInfo,inputTensorValues.data(),inputTensorSize,&inputDims.at(0),4));
outputTensors.push_back(Ort::Value::CreateTensor<float>(memoryInfo,outputTensorValues.data(),outputTensorSize,&outputDims.at(0),4));
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
/*
std::vector<Value> Run(const RunOptions& run_options, const char* const* input_names, const Value* input_values, size_t input_count,
                                   const char* const* output_names, size_t output_count);

void Run(const RunOptions& run_options, const char* const* input_names, const Value* input_values, size_t input_count,
                     const char* const* output_names, Value* output_values, size_t output_count);
		     


// std::vector<Ort::Value> output=sesh.Run(Ort::RunOptions{},inputNames.data(),inputTensors.data(),1,outputNames.data(),1);
// auto output=sesh.Run(Ort::RunOptions{nullptr},inputNames.data(),inputTensors.data(),1,outputNames.data(),1);

sesh.Run(Ort::RunOptions{},inputNames.data(),inputTensors.data(),inputNames.size(),outputNames.data(),outputTensors.data(),outputNames.size());
	std::cout << "Running inferrence." << std::endl;
// outputTensors[0]=std::move(output[0]);

auto outputDataPtr = outputTensors[0].GetTensorRawData();
	// Get the shape of the tensor.
std::vector<int64_t> shape = outputTensorInfo.GetShape();
  // Create a new image with the same shape as the tensor.
unsigned char* image_data = new unsigned char[shape.size()];
  // Copy the data from the tensor to the image.
// outputTensors.CopyTo(image_data);
  // Save the image to a file.
std::cout << "Got data. " << std::endl;

//  emscripten_image_data_type* data = emscripten_new_typed_array(image_data, shape.size(), EMSCRIPTEN_TYPED_ARRAY_U8);
//  emscripten_save_image(output_filename, data, shape[1], shape[0]);

  // Delete the image data.
delete[] image_data;

*/
	
// int width = 400; // emscripten_get_image_width("output.png");
// int height = 400; // emscripten_get_image_height("output.png");
// emscripten_image_data_type* data = emscripten_get_image_data("output.png", width, height);

// Display the image.
// emscripten_set_canvas_image_data(data, width, height);
//	std::cout << "Output tensors updated." << std::endl;


	return;
}


int main(){

EM_ASM({

setTimeout(function(){
document.querySelector('#splash2').style.zIndex=3000;
document.querySelector('#splash2').style.display='none';
},4200);
  
setTimeout(function(){
document.querySelector('#splash1').style.zIndex=3000;
document.querySelector('#splash1').style.display='none';
},4500);
  
setTimeout(function(){
document.getElementById('vsiz').innerHTML=parseInt(window.innerHeight,10);
},500);
  
setTimeout(function(){
window.scrollTo({
top: 0,
left: 0,
behavior: "smooth",
});
},750);

function getModel(pth,fname){
const ff=new XMLHttpRequest();
ff.open('GET',pth,true);
ff.responseType='arraybuffer';
document.querySelector('#stat').innerHTML='Downloading ONNX Model';
document.querySelector('#stat').style.backgroundColor='yellow';
ff.addEventListener("load",function(){
let sarrayBuffer=ff.response;
if(sarrayBuffer){
let sfil=new Uint8ClampedArray(sarrayBuffer);
FS.writeFile('/model/'+fname,sfil);
document.querySelector('#stat').innerHTML='Downloaded ONNX Model';
document.querySelector('#stat').style.backgroundColor='blue';
}
});
ff.send(null);
}

document.querySelector('#startBtn2').addEventListener('click',function(){
var pth5=document.querySelector('#onnxPath').innerHTML;
getModel(pth5,'model.onnx');
console.log('Starting..');
});
  
});

cltest();

return 0;
}
