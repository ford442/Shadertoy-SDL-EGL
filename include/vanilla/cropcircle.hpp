#include <emscripten.h>
#include <webgl/webgl2.h>
#include <functional>

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/function.hpp>

float max;
float min;
float sum;
float avgSum;
float minSum;
float maxSum;
