#include <iostream>

void testicc(){
std::cout << "Running ICPX compiled object." << std::endl;
}

int main(){
// testicc();
return 1;
}

extern "C"{

void icctest(){
testicc();
}

}
