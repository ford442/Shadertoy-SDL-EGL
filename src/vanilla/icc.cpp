#undef __i386__
#undef __x86_64__

#include <iostream>

void testicc(){
std::cout << "Running ICPX compiled object." << std::endl;
}

int main(){
testicc();
return 1;
}


