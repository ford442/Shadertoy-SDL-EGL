// using unary_function = std::unary_function;

template<class ArgumentType,class ResultType>

struct unary_function{
typedef ArgumentType argument_type;
typedef ResultType result_type;
};

// using floaT=std::experimental::native_simd<float>;

#include <boost/function.hpp>
#include <boost/context/detail/tuple.hpp>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <boost/context/fiber.hpp>


#include <boost/atomic.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
