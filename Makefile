LDFLAGS += -Wl,-O3,--lto-O3,-lm

SIMD_FLAGS += -DSIMD=2 -msimd128 -mavx 

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

COMMON_FLAGS += -fopenmp -sSUPPORT_LONGJMP=emscripten -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 -stdlib=libc++ \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fPIE -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffinite-math-only -funsafe-math-optimizations -fno-trapping-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

COMMON_FLAGS_LINK += -sDEFAULT_TO_CXX=0 $(COMMON_FLAGS)

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sFULL_ES3=1 -sUSE_SDL=0 -sLEGACY_GL_EMULATION=0 -lGL -lGLESv2 -lEGL -sUSE_GLFW=0 -sUSE_REGAL=1 \
	 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=0 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=0 -sGL_MAX_TEMP_BUFFER_SIZE=33177600 \
	 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0

LINK_FLAGS += -DQUAD $(LDFLAGS) -sWASM_BIGINT=0 -sLEGALIZE_JS_FFI=0 -sOFFSCREENCANVAS_SUPPORT=1 \
	 -sTEXTDECODER=0 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=0 \
	 --use-preload-plugins --closure 0 --closureFriendly \
	 -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2147483648 --output_eol linux -mllvm -mtune=wasm32 -march=native -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

WEBGPU_FLAGS += -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

b3_shader_webgpu:
	 em++ $(STDS) -c src/shader/shader_webgpu.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o s3030.js -O2 \
	 $(COMMON_FLAGS_LINK) $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js -sFORCE_FILESYSTEM=1 \
	 --extern-pre-js js/gpujsx.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o shader_webgpu.o

all: b3_shader_webgpu
	echo 'Built 1ink.us Shaders.'
