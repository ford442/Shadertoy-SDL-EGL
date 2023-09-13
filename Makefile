LDFLAGS += -Wl,-O3,--lto-O3,-lc,-lc++,-lc++abi,-lm,-lpthread,-lrt,-ldl,-S

SIMD_FLAGS += -mrelaxed-simd -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -msimd128 

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

LINK_SIMD_FLAGS += -mcx16 -mavxifma -mbmi -mbmi2 -mlzcnt -mavxneconvert -msse -msse2 -msse3 -mssse3 \
	 -msse4 -msse4.1 -msse4.2 -mavx -mavx2 -mpclmul -msha -mfma -mbmi2 -mpopcnt -maes -enable-fma -mavxvnni -msimd128 

COMMON_FLAGS += -sSUPPORT_LONGJMP=emscripten -sDEFAULT_TO_CXX=0 -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fpie -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffp-contract=fast \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sFULL_ES3=1 -sUSE_GLFW=0 -Wl,-lGL,-lEGL,-lGLESv2 -sUSE_REGAL=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0 -sGL_MAX_TEMP_BUFFER_SIZE=1073741824

LINK_FLAGS += $(LDFLAGS) -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=2 \
	 -sTEXTDECODER=1 --use-preload-plugins --closure 0 --closureFriendly \
	 -march=haswell -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=3221225472 --output_eol linux -mllvm -mtune=haswell -wasm-enable-eh \
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
	 -DLIB_WEBGPU_CPP20 -o s3027.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js gpujsx.js --extern-post-js rSlider.js --extern-post-js slideOut.js main.o shader_webgpu.o

b3_video_google_llvm:
	 em++ src/video/main_google_street.cpp -c -std=c++20 -fno-math-errno -O0 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on -mcpu=bleeding-edge
	 em++ src/video/video_google_street.cpp -c -std=c++20 -fno-math-errno -O0 \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_google_street.o video_google_street.o -o g0004.js -mllvm -flto -std=c++20 -fno-math-errno -O0 -fno-rtti \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 \
	 -sTEXTDECODER=1 -sGL_MAX_TEMP_BUFFER_SIZE=4096mb \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sPRECISE_F32=1 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx -mavxifma \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1024mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES2=1 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_clr","_str","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js

b3_audio_mk:
	em++ $(STDS) -c src/audio/main.cpp $(COMMON_FLAGS) -O3 $(SIMD_FLAGS) $(BOOST_FLAGS)
	em++ $(STDS) -c src/audio/audio.cpp $(COMMON_FLAGS) -O2 $(SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 
	em++ $(STDS) -o a3020.js main.o audio.o $(COMMON_FLAGS) -O2 $(LINK_FLAGS) $(LINK_SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 \
	-sFORCE_FILESYSTEM=1 \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--extern-post-js rSlider.js --extern-post-js slideOut.js

all: b3hd
	echo 'Built 1ink.us Shaders.'
