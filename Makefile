LDFLAGS += -Wl,-O3,--lto-O3,-lc++,-lc++abi,-lm,-lpthread,-lrt,-ldl,-S

SIMD_FLAGS += -mrelaxed-simd -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -msimd128 

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

LINK_SIMD_FLAGS += -DSIMD=1 -mcx16 -mavxifma -mbmi -mbmi2 -mlzcnt -mavxneconvert -msse -msse2 -msse3 -mssse3 \
	 -msse4 -msse4.1 -msse4.2 -mavx -mavx2 -mpclmul -msha -mfma -mbmi2 -mpopcnt -maes -enable-fma -mavxvnni -msimd128 

COMMON_FLAGS += -sSUPPORT_LONGJMP=emscripten -sDEFAULT_TO_CXX=0 -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 -stdlib=libc++ \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fpie -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffinite-math-only -funsafe-math-optimizations -fno-trapping-math -ffp-contract=fast \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=fast \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sFULL_ES2=1 -sFULL_ES3=1 -sUSE_GLFW=3 -Wl,-lGL,-lEGL,-lGLESv2 -sUSE_REGAL=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0 -sGL_MAX_TEMP_BUFFER_SIZE=1073741824

LINK_FLAGS += $(LDFLAGS) -sOFFSCREENCANVAS_SUPPORT=1 -sTEXTDECODER=0 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=2 -sSUPPORT_BIG_ENDIAN=1 \
	 --use-preload-plugins --closure 0 --closureFriendly \
	 -march=haswell -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=1 -sMAXIMUM_MEMORY=4294967296 -sINITIAL_MEMORY=3221225472 --output_eol linux -mllvm -mtune=intel -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

WEBGPU_FLAGS += -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

b3_shader_webgpu:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) lib/lib_webgpu.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o glh.o -static
	 em++ $(STDS) include/shader/egl.cpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o eglh.o -static
	 em++ $(STDS) -c -DDOUBLE src/shader/shader_webgpu.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) \
	 -DDOUBLE -DINTRINS $(BOOST_FLAGS) -DLIB_WEBGPU \
	 -DLIB_WEBGPU_CPP20 -o s3028dev.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js js/gpujsx.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o shader_webgpu.o

b3_shader_float:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) lib/lib_webgpu.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o glh.o -static
	 em++ $(STDS) include/shader/egl.cpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o eglh.o -static
	 em++ $(STDS) -c -DDOUBLE src/shader/shader_float.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) \
	 -DDOUBLE -DINTRINS $(BOOST_FLAGS) -DLIB_WEBGPU \
	 -DLIB_WEBGPU_CPP20 -o s3028dev.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js js/gpujsx.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o shader_webgpu.o

all: b3_shader_webgpu
	echo 'Built 1ink.us Shaders.'
