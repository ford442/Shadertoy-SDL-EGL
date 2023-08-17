#include <iostream>

extern "C"{
void testicc(){
std::cout << "Running ICPX compiled object." << std::endl;
}
}

int main(){
testicc();
return 1;
}


