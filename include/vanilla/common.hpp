
#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
using void_tensor=boost::numeric::ublas::tensor<void *>;
static void_tensor bin=void_tensor{1,1};

void gl_js();
