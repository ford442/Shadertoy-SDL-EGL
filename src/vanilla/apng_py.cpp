#include <emscripten.h>

#include <cstdio>

static char * result=NULL;

static long int length;

const char * rd_fl(const char * Fnm){
FILE * file=fopen(Fnm,"r");
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

int main(){
  
const char * Fnm=reinterpret_cast<const char *>("/depth.js");
const char * js_script=(char*)rd_fl(Fnm);
emscripten_async_run_script(js_script, 100); // 1 for async

return 0;
}
