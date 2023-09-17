TIMESTAMP := $(shell date +%m%y)

LDFLAGS := -Wl,-O3,--lto-O3,-lc,-lc++,-lc++abi,-lm,-lrt,-ldl,-S

SIMD_FLAGS := -mrelaxed-simd -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -msimd128 

STDS := -std=gnu17 -std=c2x -std=c++11 -std=c++14 -std=c++17 -std=gnu++17 -std=c++20 -std=gnu++20 \
	 -std=c++23 -std=gnu++23 -std=c++26 -std=gnu++26

LINK_SIMD_FLAGS := -mcx16 -mavxifma -mbmi -mbmi2 -mlzcnt -mavxneconvert -msse -msse2 -msse3 -mssse3 \
	 -msse4 -msse4.1 -msse4.2 -mavx -mavx2 -mpclmul -msha -mfma -mbmi2 -mpopcnt -maes -enable-fma -mavxvnni -msimd128 

COMMON_FLAGS := -sSUPPORT_LONGJMP=emscripten -sDEFAULT_TO_CXX=0 -pipe -mextended-const -mbulk-memory -matomics \
	 -sWASM_WORKERS=0 -sSHARED_MEMORY=0 \
	 -sDISABLE_EXCEPTION_CATCHING=1 -fPIC -fpie -finline-functions -funroll-loops \
	 -m32 -fmerge-all-constants -ffast-math -ffp-contract=fast \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer -fno-vectorize

STATIC_LINK_FLAGS := -sDISABLE_EXCEPTION_CATCHING=1 -mno-tail-call -O3 -fmerge-all-constants -ffast-math -ffp-contract=fast \
	 -ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
	 -mmutable-globals -mnontrapping-fptoint -msign-ext -fno-omit-frame-pointer

BOOST_FLAGS := -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1

GL_FLAGS := -sFULL_ES3=1 -sUSE_GLFW=0 -Wl,-lGL,-lEGL,-lGLESv2 -sUSE_REGAL=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_TRACK_ERRORS=0 -sGL_MAX_TEMP_BUFFER_SIZE=1073741824

LINK_FLAGS := $(LDFLAGS) -sALLOW_TABLE_GROWTH=1 -sEMULATE_FUNCTION_POINTER_CASTS=0 -sSUPPORT_BIG_ENDIAN=1 \
	 -sTRUSTED_TYPES=1 -sALLOW_UNIMPLEMENTED_SYSCALLS=0 -sIGNORE_MISSING_MAIN=0 -sABORT_ON_WASM_EXCEPTIONS=0 \
	 -sDEMANGLE_SUPPORT=0 -sASSERTIONS=2 \
	 -sTEXTDECODER=1 --use-preload-plugins --closure 0 --closureFriendly \
	 -march=haswell -sWASM=1 -sTOTAL_STACK=65536 -sSTRICT_JS=1 \
	 -sGLOBAL_BASE=352321536 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=3221225472 --output_eol linux -mllvm -mtune=haswell -wasm-enable-eh \
	 --memory-init-file 0 -rtlib=compiler-rt -sAUTO_ARCHIVE_INDEXES=0

WEBGPU_FLAGS := -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js


b3_shader_webgpu:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) lib/lib_webgpu.cpp -static $(STATIC_LINK_FLAGS)
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o glh.o -static
	 em++ $(STDS) -c -DDOUBLE src/shader/shader_webgpu.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) \
	 -DDOUBLE -DINTRINS $(BOOST_FLAGS) -DLIB_WEBGPU \
	 -DLIB_WEBGPU_CPP20 -o s3028test.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js js/gpujsx.js --extern-post-js js/rSlider.js --extern-post-js js/slideOut.js main.o shader_webgpu.o

vanilla_test:
	 emcc src/vanilla/main.cpp -o v3001test.js \
	 --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js

NAMESTAMP := v3001test-DTE.js
NAMESTAMP := $(subst DTE,$(TIMESTAMP),$(NAMESTAMP))
vanilla_test_gpujs:
	 emcc src/vanilla/main_gpujs.cpp -o $(NAMESTAMP) \
	 --extern-pre-js js/gpujsx.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js

b3_cropcircle:
	 em++ $(STDS) include/shader/intrins.hpp $(STATIC_LINK_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) -c -DDOUBLE src/vanilla/cropcircle.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) $(COMMON_FLAGS) $(LINK_FLAGS) $(GL_FLAGS) -DDOUBLE $(BOOST_FLAGS) \
	 -o cc001.js $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_nano","_rotat"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js cropcircle.o

video_resurection_edit:
	 em++ $(STDS) -c src/combine/video_edit.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) video_edit.o -o b3670test.js $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) \
	 $(GL_FLAGS) $(LINK_FLAGS) $(WEBGPU_FLAGS) $(BOOST_FLAGS) -sUSE_SDL=2 \
	 -sFORCE_FILESYSTEM=1 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_str","_nano","_pl"]' \
	 --extern-pre-js js/fluid.js --extern-pre-js js/flui.js --extern-pre-js js/setUp.js --extern-pre-js js/startUp.js \
	 --extern-post-js js/pagec.js --extern-pre-js js/rSlider.js --extern-pre-js js/slideOut.js --extern-pre-js js/gpujsx.js

video_resurection_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc resurection_jebus_webgpu.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc resurection_jebus_webgpu.o -fPIC -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o b3667.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) -I/content/RAMDRIVE2/b3/include/vanilla/ -o b3667.js -sFORCE_FILESYSTEM=1 \
	 -sINITIAL_MEMORY=512mb -sALLOW_MEMORY_GROWTH=0 \
	 -sUSE_SDL=2 -sPRECISE_F32=1 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU',"runWebGPU",'wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -std=c++17 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_startWebGPU","_runWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-post-js pagec_webgpu.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujsx.js --memory-init-file 0 --closure 0

b3_vanilla_icc:
	# /opt/intel/oneapi/compiler/2023.2.0/linux/bin/icpx --target=wasm32 -o icc.o src/vanilla/icc.cpp
	# ar rcs icc.a icc.o
	 emcc src/vanilla/main_icc.cpp -O0 -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS) -BOOST_NO_EXCEPTIONS 
	 emcc main_icc.o -O0 -o w3003.js -fPIC -fPIE -Wl,-lm,-lrt,-L/content/RAMDRIVE2/b3/,-ltbb \
	 -std=c++17 $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sINITIAL_MEMORY=512mb \
	 -sSUPPORT_ERRNO=0 \
	 -sPRECISE_F32=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_icctest","_js_simd","_js_tuple_float_short","_js_tuple_float_long","_js_tuple_gl","_js_tuple_avx","_js_tuple_avx_gl","_js_Tensors","_js_double","_js_noblock"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js \
	 --memory-init-file 0 --closure 0

b3_vanilla_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 em++ -O0 -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS) src/vanilla/main_webgpu.cpp 
	 em++ -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 main_webgpu.o libonnxruntime_webassembly.a -O0 -g -o w3001.js \
	 -std=c++17 $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) -sFORCE_FILESYSTEM=1 \
	 -polly -sALLOW_MEMORY_GROWTH=1 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sINITIAL_MEMORY=1gb -lmath.js -lhtml5.js -lint53.js -sDISABLE_EXCEPTION_CATCHING=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-post-js src/vanilla/filesys.js --extern-post-js rSlider.js --extern-post-js slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --memory-init-file 0 --closure 0 --closure-args=--externs=lib/webgpu-closure-externs.js

b3_vanilla_render:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/vanilla/main_render.cpp \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc $(LDFLAGS) -fPIC -fPIE -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -DCOMPUTE -o w3001.js \
	 -sERROR_ON_UNDEFINED_SYMBOLS=0 $(STDS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=1024mb -lmath.js -lhtml5.js -lint53.js \
	 -O0 -sDISABLE_EXCEPTION_CATCHING=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU'] \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js rSlider.js --extern-pre-js slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-pre-js gpujsx.js --memory-init-file 0 --closure 0 main_render.o 

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

b3_shader_glsl:
	 ###         Shader
	 @sh clang6.sh; \
	 em++ src/shader/shader_glsl.cpp -c $(COMMON_FLAGS) -O2 $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants \
	 -mnontrapping-fptoint -Rpass=loop-vectorize -fasynchronous-unwind-tables \
	 -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 ###         Main
	 em++ src/shader/main.cpp -c $(COMMON_FLAGS) -O2 $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants \
	 -mnontrapping-fptoint \
	 -Rpass=loop-vectorize -fasynchronous-unwind-tables -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize
	 ###         Link
	 @sh clang12.sh; \
	 emcc main.o shader_glsl.o -o gl001.js $(COMMON_FLAGS) -O2  $(LINK_SIMD_FLAGS) $(LDFLAGS) $(BOOST_FLAGS) \
	 --use-preload-plugins --closureFriendly -mnontrapping-fptoint \
	 -mllvm -fmerge-all-constants -wasm-enable-eh \
	 -exception-model=wasm -rtlib=compiler-rt -mtune=tigerlake -march=corei7-avx \
	 -fasynchronous-unwind-tables -Rpass=loop-vectorize -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize \
	 -sFETCH_SUPPORT_INDEXEDDB=0 -sALLOW_TABLE_GROWTH=1 -sGL_MAX_TEMP_BUFFER_SIZE=2gb \
	 -sDYNAMIC_EXECUTION=0 -sPRECISE_F32=1 -sUSE_BOOST_HEADERS=1 -sTOTAL_STACK=8MB \
	 -sGL_ASSERTIONS=0 -sWASM_BIGINT=0 -DWORDS_BIGENDIAN=0 -sSUPPORT_LONGJMP=0 -NDEBUG \
	 -sPOLYFILL=0 -sFAST_UNROLLED_MEMCPY_AND_MEMSET=1 \
	 -BOOST_UBLAS_NDEBUG -sINITIAL_MEMORY=2048mb \
	 -sGLOBAL_BASE=8388608 -sASSERTIONS=2 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 \
	 -sGL_UNSAFE_OPTS=1 -sGL_POOL_TEMP_BUFFERS=2gb -sALLOW_TABLE_GROWTH=1 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_GLFW=3 -sUSE_WEBGPU=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sPRECISE_I64_MATH=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 -sTEXTDECODER=1 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js

b3hd:
	em++ src/b3ogl.cpp -c -fno-math-errno -fexperimental-library \
	-std=c++2a -O0 \
	-mcpu=bleeding-edge -fwasm-exceptions -fslp-vectorize -ftree-vectorize \
	-fapprox-func -mbulk-memory -mmutable-globals -mnontrapping-fptoint \
	-msimd128 -Dsimd=avx -mavx \
	-mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	\
	-ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	em++ src/b3emjs.cpp -c -O0 -std=c++2a \
	-Dsimd=sse42 \
	-mcpu=bleeding-edge -fwasm-exceptions -fslp-vectorize -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	-fapprox-func -mbulk-memory -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	-mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	-ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=on
	em++ src/b3sdl.cpp -c -O0 -std=c++11 -fno-math-errno -fexperimental-library \
	-sUSE_SDL=2 -fslp-vectorize -ftree-vectorize \
	-mcpu=bleeding-edge -fwasm-exceptions \
	-mbulk-memory -ffast-math -ffp-contract=fast -freciprocal-math
	em++ src/b3main.cpp -c -O3 -std=c++11 -fno-math-errno -fexperimental-library \
	-mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	-mbulk-memory -ffast-math -ffp-contract=fast -freciprocal-math
	emcc b3main.o b3sdl.o b3ogl.o b3emjs.o -o g3020.js -std=c++11 -fexperimental-library -O0 -fno-math-errno \
	-msimd128 -sPRECISE_F32=2 -sWASM_BIGINT=0 -mcpu=bleeding-edge -fwasm-exceptions \
	-DSIMD=AVX -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	-sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -polly \
	-sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_fire_egl","_b3_egl","_nano","_clr","_frm","_szz"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--pre-js startUp.js --post-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js

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

b3_fire:
	 em++ src/fire/main.cpp -c -std=c++2a
	 em++ src/fire/fire.cpp -c -std=c++2a
	 emcc main.o fire.o -o f3020.js -std=c++2a \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js

castle:
	 em++ src/b3main.cpp -c -O3 \
	 -std=c++11 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3ogl.cpp -c \
	 -std=c++2a -O0 \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -ftree-vectorize \
	 -fapprox-func -mbulk-memory -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -DSIMD=AVX \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	 em++ src/b3sdl.cpp -c -O0 \
	 -sUSE_SDL=2 -std=c++11 -ftree-vectorize \
	 -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -fno-fast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3emjs_castle.cpp -c -O0 \
	 -std=c++2a -DCASTLE2 \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -ffp-contract=on
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs_castle.o -o g302c.js -O0 -DNDEBUG=1 \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=1 -sWASM_BIGINT=0 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=AVX -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js

cloud:
	 em++ src/b3main.cpp -c \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -m32 -matomics -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3ogl.cpp -c \
	 -fno-math-errno -std=c++2b -matomics \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -mavx \
	 -fapprox-func -mbulk-memory -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 em++ src/b3sdl.cpp -c \
	 -fno-math-errno -sUSE_SDL=2 -std=c++2b -matomics \
	 -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -m32 -fno-fast-math -ffp-contract=on -freciprocal-math
	 em++ src/b3emjs.cpp -c \
	 -fno-math-errno -std=c++2b -matomics \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point \
	 -fapprox-func -mbulk-memory -m32 -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs.o -o c3001.js \
	 -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js setUp.js --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --pre-js fluid.js --pre-js flui.js --pre-js gpujsx.js --pre-js tilt.js

txt:
	 em++ src/b3main.cpp -c \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -m32 -matomics -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3ogl.cpp -c \
	 -fno-math-errno -std=c++2b -matomics \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -mavx \
	 -fapprox-func -mbulk-memory -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 em++ src/b3sdl.cpp -c \
	 -fno-math-errno -sUSE_SDL=2 -std=c++2b -matomics \
	 -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -m32 -fno-fast-math -ffp-contract=on -freciprocal-math
	 em++ src/b3emjs_txt.cpp -c \
	 -fno-math-errno -std=c++2b -matomics \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point \
	 -fapprox-func -mbulk-memory -m32 -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs_txt.o -o g3017.js \
	 -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js setUp.js --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --pre-js fluid.js --pre-js flui.js --post-js gpujsx.js

dbl: dbl.cpp Makefile
	em++ dbl.cpp -O1 -o d3001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	 -DNDEBUG=1=1 -sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	 -sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=1 -sWASM_BIGINT=0 \
	 --closure 1 -g2 -std=c++2b -flto \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js filesysdbl.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

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

all: b3_vanilla
	echo 'Built 1ink.us Testing.'
