
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
using void_tensor=boost::numeric::ublas::tensor<void *>;
using wuint_tensor=boost::numeric::ublas::tensor<std::vector<GLchar>>;
using gli_tensor=boost::numeric::ublas::tensor<GLint>;

static void_tensor bin=void_tensor{1,1};
static wuint_tensor wbin=wuint_tensor{1,1};
static gli_tensor wbin_size=gli_tensor{1,1};

void gl_js();

