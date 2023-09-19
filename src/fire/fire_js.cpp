#include "../../include/fire/fire.hpp"

EM_JS(void,fl,(),{
});

EM_JS(void,fi,(),{
});

extern "C" {

void str(){
fl();
fi();
return;
}

}
