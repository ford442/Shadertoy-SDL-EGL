BIN_NAME += c0-004
AUDIO_BIN_NAME += c0-a001
LOADER_BIN_NAME += l0-001.js
WASM_BIN_NAME += c0-w001.wasm

LDFLAGS += -Wl,-O3,--lto-O3,-lc,-lc++,-lc++abi,-lm,-lpthread,-lrt,-ldl,-S

SIMD_FLAGS += -DSIMD=2 -msimd128 -mavx

STDS += -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

STDS_B += -std=gnu++20

COMMON_FLAGS += -fopenmp-simd -sSUPPORT_LONGJMP=emscripten -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sDISABLE_EXCEPTION_CATCHING=1 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 -stdlib=libc++ \
	 -fPIC -fPIE -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffinite-math-only -funsafe-math-optimizations -fno-trapping-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sGL_ENABLE_GET_PROC_ADDRESS -sFULL_ES3=1 -sFULL_ES2=0 -sLEGACY_GL_EMULATION=0 -sUSE_GLFW=0 -sUSE_REGAL=0 \
	 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=1 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=1 -sGL_MAX_TEMP_BUFFER_SIZE=33177600 \
	 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -lGL -lEGL \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0

LINK_FLAGS += --target=wasm32 -sMALLOC=emmalloc $(LDFLAGS) -sDEFAULT_TO_CXX=1 -sWASM_BIGINT=0 -sLEGALIZE_JS_FFI=0 -sOFFSCREENCANVAS_SUPPORT=0 \
	 -sTEXTDECODER=1 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=0 --typed-function-references --enable-reference-types \
	 --use-preload-plugins --closure 0 --closureFriendly -lpthread \
	 -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2147483648 --output_eol linux -mllvm -mtune=wasm32 -march=native -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt-mt -sAUTO_ARCHIVE_INDEXES=0

WEBGPU_FLAGS += -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

b3_shader_wasm:
	 em++ $(STDS) -c src/shader/shader_webgpu.cpp -O2 $(COMMON_FLAGS) $(GL_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 emcc $(STDS) -o $(WASM_BIN_NAME) -sSTANDALONE_WASM=1 -O2 $(COMMON_FLAGS) \
	 $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) -sUSE_SDL=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js -sFORCE_FILESYSTEM=1 \
	 --post-js js/rSlider.js --post-js js/slideOut.js main.o shader_webgpu.o

b3_shader:
	 em++ $(STDS) -c src/shader/shader_webgpu.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 emcc $(STDS) -O2 $(COMMON_FLAGS) \
	 $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) -sUSE_SDL=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js -sFORCE_FILESYSTEM=1 \
	 --post-js js/rSlider.js --post-js js/slideOut.js main.o shader_webgpu.o

b3_shader_webgpu:
	 b3_shader += -o $(BIN_NAME).js
b3_shader_webgpu_a:
	 b3_shader += -o $(BIN_NAME)a.js
b3_shader_webgpu_b:
	 b3_shader += -o $(BIN_NAME)b.js
b3_shader_webgpu_c:
	 b3_shader += -o $(BIN_NAME)c.js

b3_shader_au:
	 em++ $(STDS) -c src/shader/shader_audio.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main_audio.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 emcc $(STDS) -o $(AUDIO_BIN_NAME) -O2 $(COMMON_FLAGS) -sUSE_SDL=2 \
	 $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_pl","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js -sFORCE_FILESYSTEM=1 \
	 --post-js js/slideOut.js main_audio.o shader_audio.o
b3_shader_audio: b3_shader_au -o $(AUDIO_BIN_NAME).js
b3_shader_audio_a: b3_shader_au -o $(AUDIO_BIN_NAME)a.js
b3_shader_audio_b: b3_shader_au -o $(AUDIO_BIN_NAME)b.js
b3_shader_audio_c: b3_shader_au -o $(AUDIO_BIN_NAME)c.js

b3_loader:
	 em++ $(STDS) -c src/shader/loader.cpp -O3 $(COMMON_FLAGS)
	 emcc $(STDS) -o $(LOADER_BIN_NAME) -O3 $(COMMON_FLAGS) \
	 $(LINK_FLAGS) loader.o

all: b3_shader_webgpu
	echo 'Built 1ink.us Shaders.'
