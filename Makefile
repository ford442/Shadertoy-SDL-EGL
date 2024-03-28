BIN_NAME += v0-003

TIMESTAMP := $(shell date +%m%y)

LDFLAGS += -Wl,-O3,--lto-O3,-lc,-lc++,-lc++abi,-lm,-lpthread,-lrt,-ldl,-S

SIMD_FLAGS := -DSIMD=2 -msimd128 -mavx 

STDS := -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

LINK_SIMD_FLAGS := -DSIMD=2 -msimd128 -mavx

COMMON_FLAGS += -sSUPPORT_LONGJMP=emscripten -pthread -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=1 -sSHARED_MEMORY=1 \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fPIE -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

COMMON_FLAGS_safe += -openmp-simd -pthread -pipe -mextended-const -matomics -sSUPPORT_LONGJMP=emscripten \
	 -fPIC -fPIE -finline-functions -funroll-loops -msign-ext -funsafe-math-optimizations \
	 -m32 -fmerge-all-constants -ffast-math -ffp-contract=off -fno-math-errno \
	 -ftree-vectorize -fstrict-vtable-pointers \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS := -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=off \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS := -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1 -DBOOST_HAS_THREADS

GL_FLAGS += -sFULL_ES3=1 -sFULL_ES2=1 -sLEGACY_GL_EMULATION=0 -lGL -lEGL -sUSE_GLFW=0 -sUSE_REGAL=0 \
	 -sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=1 -sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=1 -sGL_MAX_TEMP_BUFFER_SIZE=262144 \
	 -sOFFSCREENCANVAS_SUPPORT=1 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0

LINK_FLAGS += -DQUAD -DDOUBLE $(LDFLAGS) -sWASM_BIGINT=0 -sDEFAULT_TO_CXX=1 -sLEGALIZE_JS_FFI=1 -sOFFSCREENCANVAS_SUPPORT=1 \
	 -sTEXTDECODER=1 -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sASSERTIONS=1 -sPRECISE_F32=2 \
	 --use-preload-plugins --closure 0 --closureFriendly --typed-function-references --enable-reference-types \
	 -march=native -sWASM=1 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' -sSTRICT_JS=0 \
	 -sGLOBAL_BASE=352321536 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1984mb --output_eol linux -mllvm -mtune=wasm32 -wasm-enable-eh \
	 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

LINK_FLAGS_safe += $(LDFLAGS) \
	 --use-preload-plugins --closure 0 --closureFriendly \
	 -sTOTAL_STACK=65536 -sENVIRONMENT='web,worker' \
	 -sALLOW_MEMORY_GROWTH=0

WEBGPU_FLAGS := -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

NAMESTAMP := v3001test-DTE.js
NAMESTAMP := $(subst DTE,$(TIMESTAMP),$(NAMESTAMP))

vanilla_test_gpujs:
	 emcc src/vanilla/main_gpujs.cpp -o $(NAMESTAMP) \
	 --extern-pre-js js/gpujsx.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js

video_resurection_webgpua:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) $(STATIC_LINK_FLAGS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) $(STATIC_LINK_FLAGS) -static
	 emcc src/video/video_jebusa.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -o video_jebusa.o -c $(STDS) $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc video_jebusa.o -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o $(BIN_NAME)-resA.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 -sUSE_SDL=2 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/fluid.js --pre-js js/flui.js --pre-js js/setUp.js --pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --post-js js/pagec_webgpua.js --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js --closure 0

video_resurection_webgpua_safe:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) $(STATIC_LINK_FLAGS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) $(STATIC_LINK_FLAGS) -static
	 emcc src/video/video_jebusa.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -o video_jebusa.o -c $(STDS) $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc video_jebusa.o -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o $(BIN_NAME)-resA-safe.js $(STDS) $(LINK_FLAGS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 -sUSE_SDL=2 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/setUp.js --pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --post-js js/pagec_webgpua.js --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js --closure 0

video_resurection_webgpub:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/video/video_jebusb.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(STDS) $(BOOST_FLAGS) $(SIMD_FLAGS) $(COMMON_FLAGS)
	 emcc video_jebusb.o -fPIC -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 $(COMMON_FLAGS) -o $(BIN_NAME)-resB.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 -sUSE_SDL=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_nanoD"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/fluid.js --pre-js js/flui.js --pre-js js/setUp.js --pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --post-js js/pagec_webgpub.js --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js --closure 0

video_resurection_webgpuc:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/video/video_jebusc.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(STDS) $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc video_jebusc.o $(STDS) -fPIC -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o $(BIN_NAME)-resC.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 -sUSE_SDL=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_nanoD"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/fluid.js --pre-js js/flui.js --pre-js js/setUp.js --pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --post-js js/pagec_webgpuc.js --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js --closure 0

video_resurection_webgpuc_safe:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/video/video_jebusc.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c $(STDS) $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc video_jebusc.o $(STDS) -fPIC -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o $(BIN_NAME)-resCsafe.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS_safe) $(LINK_SIMD_FLAGS) \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 -sUSE_SDL=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_nanoD"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/fluid.js --pre-js js/flui.js --pre-js js/setUp.js --pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --post-js js/pagec_webgpuc.js --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js --closure 0

video_test:
	 em++ $(STDS) -c src/video/main.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/video/video_test.cpp -O2 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o $(BIN_NAME).js $(COMMON_FLAGS) -O2 $(LINK_SIMD_FLAGS) \
	 $(GL_FLAGS) $(LINK_FLAGS) $(BOOST_FLAGS) -sUSE_SDL=0 \
	 -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_str","_nano","_r4nd"]' \
	 --extern-pre-js js/fluid.js --extern-pre-js js/flui.js --extern-pre-js js/setUp.js --extern-pre-js js/startUp.js \
	 --extern-post-js js/pagec.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js --extern-pre-js js/gpujsx.js video_test.o main.o

video_test2:
	 em++ -std=c++20 -c src/video/main.cpp -O2 $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ -std=c++20 -c src/video/video_test.cpp -O2 $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ -std=c++20 -o $(BIN_NAME).js -O2 $(SIMD_FLAGS) \
	 $(GL_FLAGS) $(WEBGPU_FLAGS) -sALLOW_MEMORY_GROWTH=0 $(BOOST_FLAGS) -sUSE_SDL=0 \
	 -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_str","_nano","_r4nd"]' \
	 --extern-pre-js js/fluid.js --extern-pre-js js/flui.js --extern-pre-js js/setUp.js --extern-pre-js js/startUp.js \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js --extern-pre-js js/gpujsx.js video_test.o main.o

video_test3:
	 em++ $(STDS) -c src/video/main.cpp -O0 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/video/video_test.cpp -O0 $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o $(BIN_NAME).js $(COMMON_FLAGS) $(LINK_FLAGS) -O0 $(SIMD_FLAGS) \
	 $(GL_FLAGS) $(WEBGPU_FLAGS) -sALLOW_MEMORY_GROWTH=0 $(BOOST_FLAGS) -sUSE_SDL=0 \
	 -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_str","_nano","_r4nd"]' \
	 --pre-js js/setUp.js --pre-js js/startUp.js \
	 --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js video_test.o main.o

video_new:
	 emcc src/video/video_new.cpp -o v0-test.js --pre-js js/gpujsx.js

video_resurection_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/video/video_jebus.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++20 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc video_jebus.o -fPIC -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o $(BIN_NAME)-res.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 \
	 -sINITIAL_MEMORY=2048mb -sALLOW_MEMORY_GROWTH=0 -sUSE_SDL=2 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -std=c++20 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js js/fluid.js --extern-pre-js js/flui.js --extern-pre-js js/setUp.js --extern-pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-post-js js/pagec_webgpu.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js --extern-pre-js js/gpujsx.js --closure 0

video_resurection_webgpu2:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/video/video_jebus2.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++20 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc video_jebus2.o -fPIC -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o $(BIN_NAME)-res.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -sFORCE_FILESYSTEM=1 \
	 -sINITIAL_MEMORY=1024mb -sALLOW_MEMORY_GROWTH=0 -sUSE_SDL=2 -std=c++20 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js js/fluid.js --pre-js js/flui.js --pre-js js/setUp.js --pre-js js/startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --post-js js/pagec_webgpu.js --pre-js js/rSlider.js --pre-js js/slideOut.js --pre-js js/gpujsx.js --closure 0

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

b3_video_youtube_llvm:
	 em++ src/video/main_google_street.cpp -c -std=c++20 -fno-math-errno -O0 -fpie \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on -mcpu=bleeding-edge
	 em++ src/video/video_youtube.cpp -c -std=c++20 -fno-math-errno -O0 -fpie \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_google_street.o video_youtube.o -o y001.js -mllvm -flto -std=c++20 -fno-math-errno -O0 -fpie \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 -sTEXTDECODER=0 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sEVAL_CTORS -sPRECISE_F32=0 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 -sGL_UNSAFE_OPTS=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_clr","_str","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_video_web_llvm:
	 em++ src/video/main_google_street.cpp -c -std=c++20 -fno-math-errno \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on -mcpu=bleeding-edge
	 em++ src/video/video_web.cpp -c -std=c++20 -fno-math-errno \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_google_street.o video_web.o -o w001.js -mllvm -flto -std=c++20 -fno-math-errno \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=3 \
	 -sTEXTDECODER=1 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sEVAL_CTORS -sPRECISE_F32=1 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx -mavxifma \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 -sGL_UNSAFE_OPTS=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_clr","_str","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_video_youtube:
	 em++ src/video/main_google_street.cpp -c -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 em++ src/video/video_youtube.cpp -c -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_google_street.o video_youtube.o -o g0003.js -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sALLOW_MEMORY_GROWTH=1 -sFORCE_FILESYSTEM=1 -sINITIAL_MEMORY=4096mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_nano","_str","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js startUp.js --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

img: img.cpp Makefile
	em++ img.cpp -O1 -o i003.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	-DNDEBUG=1 -sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	-sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=0 -sWASM_BIGINT=0 \
	--closure 1 -g2 -std=c++2b \
	-sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageImg.js

all: video_test
	echo 'Built 1ink.us Video.'
