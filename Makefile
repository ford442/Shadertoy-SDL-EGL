BIN_NAME += a0-001.js

LDFLAGS += -Wl,-O3,--lto-O3,-lm

SIMD_FLAGS += -DSIMD=2 -msimd128 -mavx

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

COMMON_FLAGS += -fopenmp -sSUPPORT_LONGJMP=emscripten -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 -stdlib=libc++ \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fPIE -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffinite-math-only -funsafe-math-optimizations -fno-trapping-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -fno-math-errno  \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O2 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sFULL_ES3=1 -lSDL -lGL -lEGL -sUSE_GLFW=0 -sUSE_REGAL=0 -sUSE_SDL=2 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=0 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=0 \
	 -sOFFSCREENCANVAS_SUPPORT=1 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0

LINK_FLAGS += -DQUAD $(LDFLAGS) -sDEFAULT_TO_CXX=0 -sLEGALIZE_JS_FFI=1 -sOFFSCREENCANVAS_SUPPORT=0 \
	 -sTEXTDECODER=0 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=0 --typed-function-references --enable-reference-types \
	 --use-preload-plugins --closure 0 --closureFriendly \
	 -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2147483648 --output_eol linux -mllvm -mtune=wasm32 -march=native -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

WEBGPU_FLAGS += -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

b3_audio:
	em++ src/audio/main.cpp -c -std=c++20 -sUSE_BOOST_HEADERS=1 -DSIMD=AVX -fno-fast-math -fno-math-errno -mbulk-memory -fno-stack-protector \
	-O3 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -fmerge-all-constants \
	-mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off -mtail-call -mnontrapping-fptoint \
	-fwasm-exceptions -ffunction-sections -fdata-sections -fno-tree-vectorize -fvectorize -Rpass=loop-vectorize \
	-Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -Wall -Wextra -pedantic -BOOST_UBLAS_NDEBUG
	em++ src/audio/audio.cpp -c -std=c++17 -sUSE_BOOST_HEADERS=1 -DSIMD=AVX -fno-fast-math -fno-math-errno -mbulk-memory -fno-stack-protector \
	-O3 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -fmerge-all-constants \
	-mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off -mtail-call -mnontrapping-fptoint \
	-fwasm-exceptions -ffunction-sections -fdata-sections -fno-tree-vectorize -fvectorize -Rpass=loop-vectorize \
	-Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -sUSE_SDL=2 -Wall -Wextra -pedantic -BOOST_UBLAS_NDEBUG 
	emcc main.o audio.o -o a3020.js -mllvm -force-vector-width=4 -std=c++17 -ffp-contract=off -mtune=tigerlake -march=corei7-avx -fno-math-errno \
	-O3 --closure 0 --closureFriendly -sPRECISE_F32=1 -sWASM_BIGINT=1 -mcpu=bleeding-edge \
	-fwhole-program-vtables -polly -sUSE_GLFW=0 -DSIMD=AVX -DEMMALLOC_USE_64BIT_OPS=1 \
	-sMALLOC=emmalloc --memory-init-file 0 -rtlib=compiler-rt -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 \
	-fwasm-exceptions -ffunction-sections -fdata-sections -sFETCH_SUPPORT_INDEXEDDB=0 -sSUPPORT_LONGJMP=wasm \
	-wasm-enable-eh -exception-model=wasm -sPRECISE_I64_MATH=2 -sUSE_BOOST_HEADERS=1 -Wall -Wextra -pedantic \
	-fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize --enable-fma \
	-msimd128 -mavx -mpclmul -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -BOOST_UBLAS_NDEBUG -NDEBUG \
	-sGLOBAL_BASE=8388608 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavxifma -maes -mtail-call -mnontrapping-fptoint \
	-sPOLYFILL=0 -sFAST_UNROLLED_MEMCPY_AND_MEMSET=1 -sASSERTIONS=0 -sTOTAL_STACK=8MB \
	-sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=512mb \
	-Wl,--lto-O3,--stack-first -DNDEBUG=1 \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--pre-js rSlider.js --pre-js slideOut.js

b3_audio_mk:
	em++ $(STDS) -c src/audio/main.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	em++ $(STDS) -c src/audio/audio.cpp -O2 $(COMMON_FLAGS) -Wno-incompatible-function-pointer-types $(SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_MIXER=1 -lSDL_mixer -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 -sUSE_OGG=0 -sUSE_VORBIS=0
	em++ $(STDS) -o $(BIN_NAME) -O2 $(COMMON_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_MIXER=1 -lSDL_mixer -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 -sUSE_OGG=0 -sUSE_VORBIS=0 \
	-sFORCE_FILESYSTEM=1 -Wno-incompatible-function-pointer-types \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o audio.o 

b3_shader_webgpu:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) lib/lib_webgpu.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o glh.o -static
	 em++ $(STDS) include/shader/egl.cpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o eglh.o -static
	 em++ $(STDS) -c src/shader/shader_webgpu.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o s3029dev.js -DEGLH -DLIB_WEBGPU -DINTRINS -DLIB_WEBGPU_CPP20 \
	 $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js -sFORCE_FILESYSTEM=1 \
	 --extern-pre-js js/gpujsx.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o shader_webgpu.o

all: b3_audio_mk
	echo 'Built 1ink.us Audio.'
