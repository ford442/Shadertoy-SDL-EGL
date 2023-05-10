#pragma once

// #include <wasm_simd128.h>

// #include <tmmintrin.h> // ssse 3
// #include <smmintrin.h>  // sse 4.1
// #include <mmintrin.h>  //  experimental
#include <mm3dnow.h>  //  experimental

#define VLEAVE _mm256_zeroupper

// #include <xmmintrin.h>
// #include <immintrin.h> 
// #include <nmmintrin.h>  //  sse 4.2
// #include <unistd.h>
// #include <avxintrin.h>  // AVX
