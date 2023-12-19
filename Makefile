BIN_NAME += o0-001.js

LDFLAGS += -Wl,-O3,--lto-O3,-lc,-lc++,-lc++abi,-lm,-lpthread,-lrt,-ldl,-S

SIMD_FLAGS += -DSIMD=2 -msimd128 -mavx

STDS += -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

COMMON_FLAGS += -D__EMSCRIPTEN__ -fopenmp-simd -sSUPPORT_LONGJMP=emscripten -pthread -pipe -mextended-const \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 -stdlib=libc++ -mbulk-memory -matomics \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fpie -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS += -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O2 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sGL_ENABLE_GET_PROC_ADDRESS -sFULL_ES3=1 -sFULL_ES2=0 -sUSE_GLFW=0 \
	 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=1 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=1 -sGL_MAX_TEMP_BUFFER_SIZE=131072 \
	 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -lGL -lEGL \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=1

LINK_FLAGS += -DQUAD $(LDFLAGS) -sDEFAULT_TO_CXX=1 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sWASM_BIGINT=0 -sLEGALIZE_JS_FFI=0 -sOFFSCREENCANVAS_SUPPORT=0 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=0 --typed-function-references --enable-reference-types \
	 -sTEXTDECODER=0 --use-preload-plugins --closure 0 --closureFriendly \
	 -march=haswell -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=3221225472 --output_eol linux -mllvm -mtune=wasm32 -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

WEBGPU_FLAGS += -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

b3_cropcircle:
	 em++ $(STDS) -c src/vanilla/cropcircle.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o $(BIN_NAME) -O2 $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) \
	 -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_nano","_rotat","_emem"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js cropcircle.o

b3_cropcircle_3canvas:
	 em++ $(STDS) -c src/vanilla/cropcircle_3canvas.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o cc002.js -O2 $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) \
	 -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_nano","_rotat","_emem"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js cropcircle_3canvas.o

all: b3_cropcircle
	echo 'Built 1ink.us Cropcircle.'
