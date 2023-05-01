#include "../../include/shader/shader_speed.hpp"

Run run;

// static inline GLuint(* cs)(GLenum,GLsizei,const GLchar **){&cmpl_shd};

// static inline void(*st)(){&run.strt};

extern "C" {

void str(){
run.strt();
return;
}

}
