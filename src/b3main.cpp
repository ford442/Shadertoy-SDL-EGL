#include <'../include/b3main.hpp'>
int main(){
EM_ASM({
FS.mkdir("/snd");
FS.mkdir("/shader");
});
return 0;
};
