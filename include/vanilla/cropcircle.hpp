#include <boost/cstdfloat.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgl.h>
// #include <webgl/webgl2.h>

#include <functional>
#include <chrono>
#include <ctime>
#include "../../include/vanilla/egl.hpp"

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

#include <boost/function.hpp>
