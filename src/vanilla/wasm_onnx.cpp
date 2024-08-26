#include <emscripten.h>
#include <emscripten/bind.h>
#include "../../include/vanilla/avx.hpp"
#include "../../include/vanilla/defs.hpp"
#include <emscripten/em_types.h>
#include <emscripten/val.h>
#include "../../onnxruntime/include/onnxruntime/core/session/onnxruntime_cxx_api.h"
#include <iostream>
#include <sstream>

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
