LDFLAGS += -Wl,-O3,--lto-O3,-lc,-lc++,-lc++abi,-lm,-lpthread,-lrt,-ldl,-S

SIMD_FLAGS += -DSIMD=2 -msimd128 -mavx 

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

COMMON_FLAGS += -sSUPPORT_LONGJMP=emscripten -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fpie -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sFULL_ES3=1 -sUSE_SDL=0 -sLEGACY_GL_EMULATION=0 -lGL -lEGL -sUSE_GLFW=0 -sUSE_REGAL=0 \
	 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=0 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=0 -sGL_MAX_TEMP_BUFFER_SIZE=262144 \
	 -sOFFSCREENCANVAS_SUPPORT=1 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0

LINK_FLAGS += -DQUAD $(LDFLAGS) -sWASM_BIGINT=0 -sDEFAULT_TO_CXX=1 -sLEGALIZE_JS_FFI=0 -sOFFSCREENCANVAS_SUPPORT=1 \
	 -sTEXTDECODER=0 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 --use-preload-plugins --closure 0 --closureFriendly --typed-function-references --enable-reference-types \
	 -march=native -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2147483648 --output_eol linux -mllvm -mtune=wasm32 -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

b3_video_google_mk:
	 em++ $(STDS) src/video/video_google_street.cpp -c $(COMMON_FLAGS) -O2 $(SIMD_FLAGS)
	 emcc $(STDS) -o g0004.js $(LINK_FLAGS) -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_clr","_str","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js main_google_street.o video_google_street.o

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
	 -DLIB_WEBGPU_CPP20 -o s3028.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js gpujsx.js --extern-post-js rSlider.js --extern-post-js slideOut.js main.o shader_webgpu.o

b3_audio_mk:
	em++ $(STDS) -c src/audio/main.cpp $(COMMON_FLAGS) -O3 $(SIMD_FLAGS) $(BOOST_FLAGS)
	em++ $(STDS) -c src/audio/audio.cpp $(COMMON_FLAGS) -O2 $(SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 
	em++ $(STDS) -o a3020.js main.o audio.o $(COMMON_FLAGS) -O2 $(LINK_FLAGS) $(LINK_SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 \
	-sFORCE_FILESYSTEM=1 \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--extern-post-js rSlider.js --extern-post-js slideOut.js

b3_video_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp -std=gnu17 -std=c++20 -static
	 em++ lib/lib_webgpu.cpp -std=gnu17 -std=c++20 -static
	 em++ src/video/main.cpp -c \
	 -fno-math-errno -std=c++20 -mcpu=bleeding-edge \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/video/video_webgpu.cpp -c -fno-math-errno -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge \
	 -fno-fast-math -ffunction-sections -fdata-sections
	 emcc main.o video_webgpu.o -o b3020w.js -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -mllvm -O3 -std=c++20 -fno-math-errno -flto \
	 -sASYNCIFY -sASSERTIONS=0 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mavxifma \
	 -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 \
	 -sPRECISE_F32=2 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections \
	 -fwhole-program-vtables -polly \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_b3_egl","_nano","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_googleStreetView_dev:
	 em++ src/video/main_google_street.cpp -c -O0 -std=c++20 -flto -fmerge-all-constants -mbulk-memory \
	 -ffast-math -fno-math-errno -mcpu=bleeding-edge -fstrict-vtable-pointers -fwhole-program-vtables-vtables \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -ffast-math \
	 -ffp-contract=on -fwasm-exceptions -ffunction-sections -fdata-sections -fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 em++ src/video/video_google_street.cpp -c -O0 -std=c++20 -flto -fmerge-all-constants -mbulk-memory -fno-math-errno -mcpu=bleeding-edge -fstrict-vtable-pointers -fwhole-program-vtables-vtables \
	 -ffp-contract=on \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -fwasm-exceptions -ffunction-sections -fdata-sections -fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 emcc main_google_street.o video_google_street.o -o g0003.js -mllvm -O0 -mbulk-memory -fmerge-all-constants -std=c++20 -sUSE_SDL=2 -flto \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-math-errno -mcpu=bleeding-edge -fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -msimd128 -mavx -mpclmul -msha -mavxifma -fstrict-vtable-pointers -fwhole-program-vtables-vtables \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -maes -sFETCH_SUPPORT_INDEXEDDB=0 -force-vector-width=4 \
	 -sPRECISE_F32=1 --closure 0 --closureFriendly -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sUSE_GLFW=3 -DEMMALLOC_USE_64BIT_OPS=1 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sENVIRONMENT=web -sPRECISE_I64_MATH=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_r4nd","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js --pre-js gpujsx.js --extern-post-js fluid.js --extern-post-js flui.js

all: b3_video_google_llvm
	echo 'Built 1ink.us Streetview.'
