LDFLAGS += -Wl,-O3,--lto-O3,--stack-first

SIMD_FLAGS += -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -DSIMD=AVX

STDS += -std=gnu17 -std=gnu++98 -std=gnu++03 -std=gnu++11 -std=gnu++14 -std=gnu++17 -std=gnu++20 -std=gnu++2a -std=gnu++2b

LINK_SIMD_FLAGS += -mcx16 -mavxifma -mbmi -mbmi2 -mlzcnt -mavxneconvert -msimd128 -msse -msse2 -msse3 -mssse3 \
-msse4 -msse4.1 -msse4.2 -mavx -mavx2 -mpclmul -msha -mfma -mbmi2 -mpopcnt -maes -enable-fma -mavxvnni -DSIMD=AVX

COMMON_FLAGS += -mno-tail-call -sDISABLE_EXCEPTION_CATCHING=1 -Og -fmerge-all-constants -ffast-math -ffp-contract=off \
-ftree-vectorize -fstrict-vtable-pointers -funsafe-math-optimizations -fno-math-errno -mcpu=bleeding-edge \
-ffunction-sections -fdata-sections -fno-optimize-sibling-calls -fasynchronous-unwind-tables \
-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -fno-stack-protector \
-mmutable-globals -mnontrapping-fptoint -msign-ext

BOOST_FLAGS += -sUSE_BOOST_HEADERS=1 -BOOST_UBLAS_NDEBUG=1

GL_FLAGS += -sFULL_ES3=1 -sFULL_ES2=1 -sGL_MAX_TEMP_BUFFER_SIZE=4gb -sUSE_GLFW=3 \
-sGL_POOL_TEMP_BUFFERS=0 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2

LINK_FLAGS += $(LDFLAGS) -DISABLE_EXCEPTION_CATCHING=1 --use-preload-plugins --closure 0 --closureFriendly \
	 -march=haswell -sTOTAL_STACK=16MB -sENVIRONMENT='web,webview,node,shell' -sDYNAMIC_EXECUTION=2 \
	 -sGLOBAL_BASE=16777216 -sSUPPORT_ERRNO=0 -DNDEBUG=1 -polly -polly-position=before-vectorizer \
	 -sALLOW_MEMORY_GROWTH=1 --output_eol linux -sMALLOC=emmalloc -mllvm -mtune=haswell \
	 --memory-init-file 0 -rtlib=compiler-rt -DEMMALLOC_USE_64BIT_OPS=1

WEBGPU_FLAGS += -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -lmath.js -lhtml5.js -lint53.js

video_resurection_jebus:
	 em++ resurection_jebus.cpp -o b3666.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1024mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 -sFULL_ES2=1 \
	 -std=gnu++20 -sPRECISE_F32=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js \
	 --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujsx.js

video_resurection_edit:
	 em++ $(STDS) include/shader/intrins.h $(COMMON_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.h $(COMMON_FLAGS) $(SIMD_FLAGS) -o gl.o -static
	 em++ $(STDS) -c video_edit.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -DDOUBLE
	 em++ $(STDS) video_edit.o -o b3668.js $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) \
	 $(GL_FLAGS) $(LINK_FLAGS) $(WEBGPU_FLAGS) $(BOOST_FLAGS) -DINTRINS -DGL \
	 -sFORCE_FILESYSTEM=1 -sINITIAL_MEMORY=1024mb -sMAXIMUM_MEMORY=4gb -sPRECISE_F32=1 \
	 -sALLOW_MEMORY_GROWTH=1 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' -sUSE_SDL=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js \
	 --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujsx.js

video_resurection_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc resurection_jebus_webgpu.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc resurection_jebus_webgpu.o -fPIC -fPIE -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -o b3667.js $(STDS) $(GL_FLAGS) $(BOOST_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) -I/content/RAMDRIVE2/b3/include/vanilla/ -o b3667.js -sFORCE_FILESYSTEM=1 \
	 -sINITIAL_MEMORY=512mb -sALLOW_MEMORY_GROWTH=0 \
	 -sUSE_SDL=2 -sPRECISE_F32=1 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU',"runWebGPU",'wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] \
	 -std=c++17 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_startWebGPU","_runWebGPU"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js -lmath.js -lhtml5.js -lint53.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --extern-post-js pagec_webgpu.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujsx.js --memory-init-file 0 --closure 0

b3_vanilla_webgpu:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 em++ /usr/include/CL/opencl.hpp $(STDS) -static

	 em++ src/vanilla/main_webgpu.cpp -O3 -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS) -BOOST_NO_EXCEPTIONS
	 em++ main_webgpu.o -O3 -fPIC -fPIE -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -LOPENCL -o w3001.js \
	 $(STDS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sDISABLE_EXCEPTION_THROWING=1 \
	 -sINITIAL_MEMORY=512mb -lmath.js -lhtml5.js -lint53.js \
	 -sSUPPORT_ERRNO=0 -jsDWEBGPU_NO_BW_COMPAT=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] -sPRECISE_F32=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --memory-init-file 0 --closure 0 --closure-args=--externs=lib/webgpu-closure-externs.js

b3_vanilla_render:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 emcc src/vanilla/main_render.cpp \
	 -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc main_render.o -fPIC -fPIE -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -DCOMPUTE -o w3001.js \
	 $(STDS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) $(GL_FLAGS) \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 \
	 -sINITIAL_MEMORY=512mb -lmath.js -lhtml5.js -lint53.js \
	 -sSUPPORT_ERRNO=0 -jsDWEBGPU_DEBUG=1 -jsDWEBGPU_NO_BW_COMPAT=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=1 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] -sPRECISE_F32=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --memory-init-file 0 --closure 0 

b3_vanilla_webgpu_debug:
	 em++ lib/lib_webgpu_cpp20.cpp $(STDS) -static
	 em++ lib/lib_webgpu.cpp $(STDS) -static
	 em++ src/vanilla/main_render.cpp -I/content/RAMDRIVE2/b3/include/vanilla/ -c -std=c++17 $(BOOST_FLAGS) $(SIMD_FLAGS)
	 emcc main_render.o -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 -DCOMPUTE -o w3001.js \
	 $(STDS) $(BOOST_FLAGS) $(LINK_SIMD_FLAGS) $(GL_FLAGS) \
	 -sALLOW_MEMORY_GROWTH=1 \
	 -sINITIAL_MEMORY=512mb -lmath.js -lhtml5.js -lint53.js \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sASYNCIFY=0 -sASYNCIFY_IMPORTS=['startWebGPU','runWebGPU','wgpu_buffer_map_sync','navigator_gpu_request_adapter_sync','wgpu_adapter_request_device_sync'] -sPRECISE_F32=1 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_GLFW=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_startWebGPU","_runWebGPU","_runWebGPU2"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js

b3_vanilla_llvm:
	 em++ src/vanilla/main.cpp -c -sUSE_BOOST_HEADERS=1 -std=gnu17 -std=c++17 -mbulk-memory -mnontrapping-fptoint -msimd128 \
	 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc src/vanilla/js.c -c -std=gnu17 -mbulk-memory -mnontrapping-fptoint -msimd128
	 emcc main.o js.o -o v3020.js -mllvm -std=gnu17 -std=c++17 -mbulk-memory -mnontrapping-fptoint -msimd128 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=1 -sUSE_BOOST_HEADERS=1 -sUSE_WEBGPU=1 -sINITIAL_MEMORY=2048mb \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha \
	 -rtlib=compiler-rt \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -DEMMALLOC_USE_64BIT_OPS=1 \
	 -sASYNCIFY=1 -sPRECISE_F32=1 -sWASM_BIGINT=1 -sUSE_GLFW=0 -sNO_DISABLE_EXCEPTION_CATCHING \
	 -sEXPORTED_FUNCTIONS='["_main","_wgpu_init1","_wgpu_init2","_wgpu_init3","_wgpu_init4","_js_simd","_js_hello","_js_tuple_float_short","_js_tuple_float_long","_js_tuple_gl","_js_tuple_avx","_js_tuple_avx_gl","_js_Tensors","_js_double","_js_noblock"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js 

b3_shader_webgpu:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static
	 em++ $(STDS) lib/lib_webgpu.cpp -static
	 em++ $(STDS) include/shader/intrins.h $(COMMON_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.h $(COMMON_FLAGS) $(SIMD_FLAGS) -o gl.o -static
	 em++ $(STDS) -c src/shader/shader_webgpu.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -DDOUBLE
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 em++ $(STDS) -o s3026.js main.o shader_webgpu.o $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) \
	 $(GL_FLAGS) $(LINK_FLAGS) $(WEBGPU_FLAGS) $(BOOST_FLAGS) -DINTRINS -DGL \
	 -sFORCE_FILESYSTEM=1 -sINITIAL_MEMORY=1024mb -sMAXIMUM_MEMORY=4gb -sPRECISE_F32=1 -sDISABLE_EXCEPTION_THROWING=0 \
	 -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_wasmedge:
	 em++ $(STDS) lib/lib_webgpu_cpp20.cpp -static
	 em++ $(STDS) lib/lib_webgpu.cpp -static
	 em++ $(STDS) include/shader/intrins.h $(COMMON_FLAGS) $(SIMD_FLAGS) -o intrins.o -static
	 em++ $(STDS) include/shader/gl.h $(COMMON_FLAGS) $(SIMD_FLAGS) -o gl.o -static
	 em++ -std=c++14 -c src/shader/shader_webgpu.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -DDOUBLE
	 em++ $(STDS) -c src/shader/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	 emcc $(STDS) -o s3027.wasm main.o shader_webgpu.o $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) \
	 $(GL_FLAGS) $(LINK_FLAGS) $(WEBGPU_FLAGS) $(BOOST_FLAGS) -DINTRINS -DGL \
	 -sFORCE_FILESYSTEM=1 -sINITIAL_MEMORY=1024mb -sMAXIMUM_MEMORY=4gb -sPRECISE_F32=1 -sDISABLE_EXCEPTION_THROWING=0 \
	 -sASYNCIFY=1 -DLIB_WEBGPU -DLIB_WEBGPU_CPP20 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --js-library lib/lib_demo.js --js-library lib/library_miniprintf.js --js-library lib/lib_webgpu.js \
	 --closure-args=--externs=lib/webgpu-closure-externs.js \
	 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js

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
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_clr","_str","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_speed:
	 ###         Shader
	 @sh clang6.sh; \
	 em++ src/shader/shader_speed.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants -fno-stack-protector \
	 -mnontrapping-fptoint -Rpass=loop-vectorize -fasynchronous-unwind-tables \
	 -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 ###         Main
	 em++ src/shader/main.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants \
	 -mnontrapping-fptoint -fno-stack-protector \
	 -Rpass=loop-vectorize -fasynchronous-unwind-tables -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize
	 ###         Link
	 @sh clang12.sh; \
	 emcc main.o shader_speed.o -o s3024s.js $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) $(LDFLAGS) \
	 --use-preload-plugins --closure 0 --closureFriendly -mnontrapping-fptoint \
	 -force-vector-width=4 -mllvm -fno-stack-protector -fmerge-all-constants -wasm-enable-eh \
	 -exception-model=wasm -mtune=tigerlake -march=corei7-avx \
	 -fasynchronous-unwind-tables -Rpass=loop-vectorize -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize \
	 -sFETCH_SUPPORT_INDEXEDDB=0 -sALLOW_TABLE_GROWTH=1 -sGL_MAX_TEMP_BUFFER_SIZE=4096mb \
	 -sDYNAMIC_EXECUTION=0 -sPRECISE_F32=1 -sUSE_BOOST_HEADERS=1 -sTOTAL_STACK=8MB \
	 -sGL_ASSERTIONS=0 -sWASM_BIGINT=1 -DWORDS_BIGENDIAN=0 -DNDEBUG -BOOST_UBLAS_NDEBUG \
	 -sGLOBAL_BASE=8388608 -sPOLYFILL=0 -sFAST_UNROLLED_MEMCPY_AND_MEMSET=1 \
	 -sASSERTIONS=0 -sINITIAL_MEMORY=700mb -sMALLOC=emmalloc -DEMMALLOC_USE_64BIT_OPS=1 \
	 --memory-init-file 0 -rtlib=compiler-rt -sSUPPORT_LONGJMP=wasm \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 \
	 -sGL_UNSAFE_OPTS=1 -sGL_POOL_TEMP_BUFFERS=1 -sALLOW_TABLE_GROWTH=1 \
	 -sEVAL_CTORS=1 -sFULL_ES2=1 -sFULL_ES3=1 -sUSE_GLFW=3 -sTEXTDECODER=2 -sWASM=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sPRECISE_I64_MATH=2 --output_eol linux \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_compute:
	 ###         Shader
	 @sh clang6.sh; \
	 em++ src/shader/shader_compute.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants -fno-stack-protector \
	 -mnontrapping-fptoint -Rpass=loop-vectorize -fasynchronous-unwind-tables \
	 -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 ###         Main
	 em++ src/shader/main.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants \
	 -mnontrapping-fptoint -fno-stack-protector \
	 -Rpass=loop-vectorize -fasynchronous-unwind-tables -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize
	 ###         Link
	 @sh clang12.sh; \
	 emcc main.o shader_compute.o -o s3024c.js $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) $(LDFLAGS) \
	 --use-preload-plugins --closure 0 --closureFriendly -mnontrapping-fptoint \
	 -force-vector-width=4 -mllvm -fno-stack-protector -fmerge-all-constants -wasm-enable-eh \
	 -exception-model=wasm -mtune=tigerlake -march=corei7-avx \
	 -fasynchronous-unwind-tables -Rpass=loop-vectorize -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize \
	 -sFETCH_SUPPORT_INDEXEDDB=0 -sALLOW_TABLE_GROWTH=1 -sGL_MAX_TEMP_BUFFER_SIZE=4096mb \
	 -sDYNAMIC_EXECUTION=0 -sPRECISE_F32=1 -sUSE_BOOST_HEADERS=1 -sTOTAL_STACK=8MB \
	 -sGL_ASSERTIONS=1 -sLEGACY_GL_EMULATION=1 -sWASM_BIGINT=1 -DWORDS_BIGENDIAN=0 -NDEBUG -BOOST_UBLAS_NDEBUG \
	 -sGLOBAL_BASE=8388608 -sPOLYFILL=0 -sFAST_UNROLLED_MEMCPY_AND_MEMSET=1 \
	 -sASSERTIONS=0 -sINITIAL_MEMORY=2048mb \
	 -sMALLOC=emmalloc --memory-init-file 0 -rtlib=compiler-rt \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 \
	 -sGL_UNSAFE_OPTS=1 -sGL_POOL_TEMP_BUFFERS=0 -sALLOW_TABLE_GROWTH=1 \
	 -sEVAL_CTORS=1 -sFULL_ES2=0 -sFULL_ES3=0 -sUSE_GLFW=3 -sTEXTDECODER=2 -sWASM=1 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sPRECISE_I64_MATH=2 --output_eol linux \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_swp","_r4nd","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' \
	 -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js


b3_combine_dev:
	 em++ src/combine/main.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -flto -fno-stack-protector -fmerge-all-constants \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 em++ src/combine/video.cpp -c  $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -flto -fmerge-all-constants -fno-stack-protector \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 em++ src/combine/shader.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -flto -fmerge-all-constants -fno-stack-protector \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 em++ src/combine/audio.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) -flto -fno-stack-protector -fmerge-all-constants -sUSE_SDL=2 -sUSE_SDL_MIXER=2 -fno-fast-math \
	 -ffp-contract=off -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 emcc main.o audio.o video.o shader.o -o b3hd003.js $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) $(BOOST_FLAGS) $(LDFLAGS) -sALLOW_TABLE_GROWTH=1 -fno-stack-protector -mllvm -fmerge-all-constants -sUSE_SDL=2 \
	 -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -flto -DEMMALLOC_USE_64BIT_OPS=1 \
	 -sFETCH_SUPPORT_INDEXEDDB=0 -force-vector-width=4 -sGL_POOL_TEMP_BUFFERS=0 \
	 -sPRECISE_F32=1 -sWASM_BIGINT=1 -wasm-enable-eh -exception-model=wasm -sPOLYFILL=0 -sFAST_UNROLLED_MEMCPY_AND_MEMSET=1 -sUSE_GLFW=3 -mtune=tigerlake -march=corei7-avx \
	 -sASSERTIONS=0 -s DYLINK_DEBUG=0 -sWASM=1 -DNDEBUG=1 \
	 -sEVAL_CTORS=1 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 --closure 0 --closureFriendly -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sDYNAMIC_EXECUTION=0 -sGL_UNSAFE_OPTS=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sPRECISE_I64_MATH=2 -sGL_MAX_TEMP_BUFFER_SIZE=64mb -sGLOBAL_BASE=8388608 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_r4nd","_frm","_swp","_ud","_uu","_vd","_vu","_ml","_mr","_mu","_md"]' -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
	 --pre-js js/module.js --pre-js rSlider.js --pre-js slideOut.js --pre-js gpujsx.js --extern-post-js fluid.js --extern-post-js flui.js

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
	em++ $(STDS) -c src/audio/main.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS)
	em++ $(STDS) -c src/audio/audio.cpp $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 
	emcc $(STDS) -o a3020.js main.o audio.o $(COMMON_FLAGS) $(LINK_FLAGS) $(LINK_SIMD_FLAGS) $(BOOST_FLAGS) \
	-sUSE_SDL=2 -sUSE_SDL_IMAGE=0 -sUSE_SDL_TTF=0 -sUSE_SDL_NET=0 \
	-sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=256mb \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--pre-js rSlider.js --pre-js slideOut.js

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

b3_shader_glsl:
	 ###         Shader
	 @sh clang6.sh; \
	 em++ src/shader/shader_glsl.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants \
	 -mnontrapping-fptoint -Rpass=loop-vectorize -fasynchronous-unwind-tables \
	 -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 ###         Main
	 em++ src/shader/main.cpp -c $(COMMON_FLAGS) $(SIMD_FLAGS) $(BOOST_FLAGS) \
	 -fmerge-all-constants \
	 -mnontrapping-fptoint \
	 -Rpass=loop-vectorize -fasynchronous-unwind-tables -Rpass-missed=loop-vectorize \
	 -Rpass-analysis=loop-vectorize
	 ###         Link
	 @sh clang12.sh; \
	 emcc main.o shader_glsl.o -o gl001.js $(COMMON_FLAGS) $(LINK_SIMD_FLAGS) $(LDFLAGS) $(BOOST_FLAGS) \
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
	 
b3_video_shader_llvm:
	 em++ src/video/main_shader.cpp -c -std=c++2b -flto -fno-math-errno -O3 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on -mcpu=bleeding-edge
	 em++ src/video/video_shader.cpp -c -std=c++2b -flto -fno-math-errno -O3 \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_shader.o video_shader.o -o sh001.js -mllvm -flto -std=c++2b -fno-math-errno -O3 \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 \
	 -sTEXTDECODER=1 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sPRECISE_F32=1 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx -mavxifma \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections -sFORCE_FILESYSTEM=1 -sUSE_GLFW=0 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_llvm:
	 em++ src/shader/shader.cpp -c -O0 -m32 -fno-math-errno -mbulk-memory -fno-stack-protector -ffp-contract=off -fmerge-all-constants \
	 -std=c++2b -mcpu=bleeding-edge -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -flto -fstrict-vtable-pointers \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mtail-call -mnontrapping-fptoint \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ftree-vectorize -fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 em++ src/shader/main.cpp -c -O3 -m32 -ffast-math -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mbulk-memory -mavx -fmerge-all-constants -fno-stack-protector \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -flto -fstrict-vtable-pointers -mtail-call -mnontrapping-fptoint \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -ffp-contract=on \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ftree-vectorize -fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
	 emcc main.o shader.o -o s3022.js -m32 -static -flto -mllvm -ffp-contract=on -ftree-vectorize -mbulk-memory -fno-stack-protector -fmerge-all-constants -fwasm-exceptions -force-vector-width=4 -O0 -std=c++2b -fno-math-errno \
	 -mcpu=bleeding-edge -mtune=tigerlake -march=corei7-avx -ffunction-sections -fdata-sections -rtlib=compiler-rt -fvectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize \
	 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -mavxifma \
	 -msse -msse2 -msse3 -mssse3 -msse4 --closureFriendly -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 -fstrict-vtable-pointers -sALLOW_TABLE_GROWTH=1 -sGL_MAX_TEMP_BUFFER_SIZE=64mb -sGLOBAL_BASE=512 \
	 -sDYNAMIC_EXECUTION=0 -sPRECISE_F32=0 -sWASM_BIGINT=0 -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -mtail-call -mnontrapping-fptoint \
	 -sASSERTIONS=0 -s DYLINK_DEBUG=0 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -wasm-enable-eh -exception-model=wasm -sPOLYFILL=0 -sFAST_UNROLLED_MEMCPY_AND_MEMSET=1 -sUSE_GLFW=0 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sGL_UNSAFE_OPTS=0 \
	 -sGL_POOL_TEMP_BUFFERS=0 -sALLOW_TABLE_GROWTH=1 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sENVIRONMENT=web -sPRECISE_I64_MATH=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall","FS"]' \
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

b3_combine:
	 em++ src/combine/main.cpp -c -std=c++2a
	 em++ src/combine/audio.cpp -c -std=c++2a -sUSE_SDL=2
	 em++ src/combine/video.cpp -c -std=c++2a \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 em++ src/combine/shader.cpp -c -std=c++2a \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main.o audio.o video.o shader.o -o b3hd001.js -std=c++2a -sUSE_SDL=2 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --extern-pre-js gpujsx.js --extern-post-js fluid.js --extern-post-js flui.js

b3_combine_test:
	 em++ src/combine/main.cpp -c -O0 -std=c++20 \
	 -ffast-math -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/combine/audio.cpp -c -O0 -std=c++20 -sUSE_SDL=2 -fno-fast-math \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off -fno-math-errno -mcpu=bleeding-edge
	 em++ src/combine/video.cpp -c -O0 -std=c++20 -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-fast-math -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 em++ src/combine/shader.cpp -c -O0 -std=c++20 -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-fast-math -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sTEXTDECODER=2
	 emcc main.o audio.o video.o shader.o -o b3hd001.js -O0 -std=c++20 -sUSE_SDL=2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-math-errno -mcpu=bleeding-edge \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -sWASMFS=0 -mtune=tigerlake -march=corei7-avx -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_r4nd","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js

b3_combine_llvm:
	 em++ src/combine/main.cpp -c -O0 -std=c++2b \
	 -ffast-math -fno-math-errno -mcpu=bleeding-edge \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -ffp-contract=off -fwasm-exceptions -ffunction-sections -fdata-sections
	 em++ src/combine/audio.cpp -c -O0 -std=c++2b -sUSE_SDL=2 -fno-fast-math \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -ffp-contract=on -fno-math-errno -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections
	 em++ src/combine/video.cpp -c -O0 -std=c++2b -fno-math-errno -mcpu=bleeding-edge \
	 -fno-fast-math -ffp-contract=on \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -fwasm-exceptions -ffunction-sections -fdata-sections
	 em++ src/combine/shader.cpp -c -O0 -std=c++2b -fno-math-errno -mcpu=bleeding-edge \
	 -fno-fast-math -ffp-contract=on \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -fwasm-exceptions -ffunction-sections -fdata-sections
	 emcc main.o audio.o video.o shader.o -o b3hd002.js -static-pie -mllvm -O0 -std=c++2b -sUSE_SDL=2 -flto -sTOTAL_STACK=128MB \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-math-errno -mcpu=bleeding-edge -sTEXTDECODER=0 \
	 -msimd128 -mavx -mpclmul -msha -mavxifma \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sPRECISE_F32=1 -sWASM_BIGINT=0 -sWASMFS=0 -mtune=tigerlake -march=corei7-avx -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=3 \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_r4nd","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js --extern-pre-js fluid.js --extern-pre-js flui.js --post-js js/module.js

b3_combine_cloud:
	 em++ src/combine/main.cpp -c -O0 -std=c++2a \
	 -ffast-math -fno-math-errno -mcpu=bleeding-edge \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/combine/audio.cpp -c -O0 -std=c++2a -sUSE_SDL=2 -fno-fast-math \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off -fno-math-errno -mcpu=bleeding-edge
	 em++ src/combine/video.cpp -c -O0 -std=c++2a -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-fast-math -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 em++ src/combine/shader.cpp -c -O0 -std=c++2a -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-fast-math -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main.o audio.o video.o shader.o -o c002.js -mllvm -O0 -std=c++2a -sUSE_SDL=2 -flto \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -fno-math-errno -mcpu=bleeding-edge -sTEXTDECODER=1 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sPRECISE_F32=1 -sWASM_BIGINT=0 -sWASMFS=0 -mtune=tigerlake -march=corei7-avx -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_r4nd","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js setUp.js --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --extern-pre-js fluid.js --extern-pre-js flui.js --pre-js gpujsx.js --pre-js tilt.js

b3_shader:
	 em++ src/shader/main.cpp -c -std=c++2a
	 em++ src/shader/shader.cpp -c -std=c++2a
	 emcc main.o shader.o -o s3021.js -std=c++2a \
	 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_google:
	 em++ src/shader/main.cpp -c -std=c++2a
	 em++ src/shader/shader_google_street.cpp -c -std=c++2a \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main.o shader_google_street.o -o g0026.js -std=c++2a \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js

b3_shader_simd:
	 em++ src/shader/main.cpp -c -std=c++11
	 em++ src/shader/shader_simd.cpp -c -std=c++20 -msimd128 -mavx
	 emcc main.o shader_simd.o -o s3020.js -std=c++20 -msimd128 -mavx \
	 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_test:
	 em++ src/shader/main.cpp -c -O3 -ffast-math \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -mtune=tigerlake -march=corei7-avx \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=fast
	 em++ src/shader/shader.cpp -c -O0 -fno-math-errno -ffp-contract=on \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -mtune=tigerlake -march=corei7-avx -msimd128 -mavx \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections
	 emcc main.o shader.o -o s3021.js -O0 -std=c++2b -fno-math-errno -ffp-contract=fast \
	 -fwasm-exceptions -mcpu=bleeding-edge -mtune=tigerlake -march=corei7-avx -ffunction-sections -fdata-sections \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=1 \
	 -fwhole-program-vtables -polly -sWASMFS=0 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 -sTEXTDECODER=0 --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_js:
	 em++ src/shader/main.cpp -c -O3 -ffast-math \
	 -fno-math-errno -std=c++11 -mcpu=bleeding-edge \
	 -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/shader/shader.cpp -c -O0 -fno-math-errno -std=c++2b -fno-fast-math -ffp-contract=off \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -msimd128 -mavx \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -ffunction-sections -fdata-sections
	 emcc main.o shader.o -o s3021js.js -O0 -sWASM=0 -std=c++2b -fno-math-errno -ffp-contract=off \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sPRECISE_F32=2 -sWASMFS=0 -mtune=corei7-avx -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 -fwhole-program-vtables -polly -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js

b3_shader_texture:
	 em++ src/shader/main_texture.cpp -c -O0 -fpie -ffast-math \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/shader/shader_texture.cpp -c -O0 -fpie -fno-math-errno -fno-fast-math -ffp-contract=off \
	 -fno-math-errno -std=c++2b -mcpu=bleeding-edge -msimd128 -mavx \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections
	 emcc main_texture.o shader_texture.o -o t001.js -flto -mllvm -O0 -fpie -std=c++2b -fno-math-errno \
	 -fwasm-exceptions -mcpu=bleeding-edge -mtune=tigerlake -march=corei7-avx -ffunction-sections -fdata-sections \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 -fwhole-program-vtables -polly -sWASMFS=0 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=1 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 -sTEXTDECODER=0 --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js

b3_video_test:
	 em++ src/video/main.cpp -c -O3 -fpie \
	 -fno-math-errno -std=c++20 -mcpu=bleeding-edge \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/video/video.cpp -c -O0 -fpie -fno-math-errno -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -fno-fast-math -ffunction-sections -fdata-sections
	 emcc main.o video.o -o b3020.js -O0 -fpie -std=c++20 -fno-math-errno -flto \
	 -fwasm-exceptions \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_b3_egl","_nano","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_video_llvm:
	 em++ src/video/main.cpp -c -O0 -fpie \
	 -fno-math-errno -std=c++20 -mcpu=bleeding-edge \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on
	 em++ src/video/video.cpp -c -O0 -fpie -fno-math-errno -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge \
	 -fwasm-exceptions -fno-fast-math -ffunction-sections -fdata-sections
	 emcc main.o video.o -o b3020.js -mllvm -O0 -static-pie -std=c++20 -fno-math-errno -flto \
	 -fwasm-exceptions \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mavxifma \
	 -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sTEXTDECODER=0 \
	 -sPRECISE_F32=1 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sGL_UNSAFE_OPTS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_b3_egl","_nano","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_audio_test:
	em++ src/audio/main.cpp -c -std=c++2a -fno-math-errno -O0 -fpie \
	-mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on
	em++ src/audio/audio.cpp -c -std=c++2a -sUSE_SDL=2 -fno-math-errno -O0 -fpie \
	-msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	-mcpu=bleeding-edge -fwasm-exceptions -fno-fast-math -ffunction-sections -fdata-sections -ffp-contract=off
	emcc main.o audio.o -o a3020.js -std=c++2a -mtune=tigerlake -march=corei7-avx -fno-math-errno -O0 -fpie \
	-sPRECISE_F32=0 \
	-fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	-fwasm-exceptions -ffunction-sections -fdata-sections -sFETCH_SUPPORT_INDEXEDDB=0 \
	-msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	-sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sWASM_BIGINT=0 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--pre-js rSlider.js --pre-js slideOut.js

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

b3_video_google_test:
	 em++ src/video/main_google_street.cpp -c -std=c++20 -fno-math-errno -O0 -fpie \
	 -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=on -mcpu=bleeding-edge
	 em++ src/video/video_google_street.cpp -c -std=c++20 -fno-math-errno -O0 -fpie \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections -ffp-contract=off \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_google_street.o video_google_street.o -o g0003.js -std=c++20 -fno-math-errno -O0 -fpie \
	 -fwhole-program-vtables -polly -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 -sUSE_GLFW=0 \
	 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -ffunction-sections -fdata-sections -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sFETCH_SUPPORT_INDEXEDDB=0 -sGL_UNSAFE_OPTS=0 \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_clr","_str","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

b3_video_google:
	 em++ src/video/main_google_street.cpp -c -std=c++20
	 em++ src/video/video_google_street.cpp -c -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2
	 emcc main_google_street.o video_google_street.o -o g0003.js -std=c++20 \
	 -msimd128 -mavx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sALLOW_MEMORY_GROWTH=1 -sFORCE_FILESYSTEM=1 -sINITIAL_MEMORY=4096mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_b3","_nano","_str","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js startUp.js --extern-pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

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

b3_audio_old:
	em++ src/audio/main.cpp -c -std=c++11 -fno-math-errno -O0
	em++ src/audio/audio.cpp -c -std=c++2b -sUSE_SDL=2 -O0
	emcc main.o audio.o -o a3020.js -std=c++2b -O0 \
	-sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	-sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sEXPORTED_FUNCTIONS='["_main","_pl","_r4nd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--pre-js rSlider.js --pre-js slideOut.js

b3_fire:
	 em++ src/fire/main.cpp -c -std=c++2a
	 em++ src/fire/fire.cpp -c -std=c++2a
	 emcc main.o fire.o -o f3020.js -std=c++2a \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js

b3_vanilla:
	 em++ src/vanilla/main.cpp -c -std=c++2a
	 emcc main.o -o v3020.js -std=c++2a \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 --pre-js rSlider.js --pre-js slideOut.js
	 
b3_vanilla_simd:
	 em++ src/vanilla/main_simd.cpp -c -O0 -fpie -std=c++2a \
	 -msimd128 -mavx \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge -fwasm-exceptions -ffunction-sections -fdata-sections
	 emcc main_simd.o -o v3020.js -O0 -std=c++2a -fpie \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mrdrnd \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -fno-math-errno -mcpu=bleeding-edge -fwasm-exceptions \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -ffunction-sections -fdata-sections \
	 -sPRECISE_F32=2 -sWASM_BIGINT=0 -mtune=corei7-avx \
	 -sEXPORTED_FUNCTIONS='["_main","_js_simd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js rSlider.js --pre-js slideOut.js

b3_vanilla_test:
	 em++ src/vanilla/main.cpp -c -O0 -fpie \
	 -fno-math-errno -std=c++20 -mcpu=bleeding-edge \
	 -fwasm-exceptions -ftree-vectorize -ffunction-sections -fdata-sections
	 emcc main.o -o v3020.js -O0 -fno-math-errno -std=c++20 \
	 -fwhole-program-vtables -polly -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -fwasm-exceptions -ftree-vectorize \
	 \
	 -msimd128 -mavx -mpclmul -maes -mavx2 -msha -mfma -mbmi2 -mpopcnt -mcx16 \
	 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -sPRECISE_F32=0 -sWASM_BIGINT=0 -mtune=tigerlake -march=corei7-avx \
	 -mcpu=bleeding-edge -fpie -flto -ffunction-sections -fdata-sections \
	 --pre-js rSlider.js --pre-js slideOut.js

b3hdm:
	 em++ src/b3ogl.cpp -c -std=c++2a -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 
	 em++ src/b3emjs.cpp -c -std=c++2a -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 
	 em++ src/b3sdl.cpp -c -std=c++2a -sUSE_SDL=2 -O3
	 em++ src/b3main.cpp -c -std=c++2a -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 
	 emcc b3main.o b3sdl.o b3ogl.o b3emjs.o -o g3020.js -std=c++2a \
	 -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_fire_egl","_nano","_clr","_frm","_szz"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js

sh4d3:
	 em++ src/b3ogl_sh4d3.cpp -c -fno-math-errno -fexperimental-library \
	 -std=c++2a -O0 \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -ftree-vectorize \
	 -fapprox-func -mbulk-memory -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -Dsimd=avx \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	 em++ src/b3main_sh4d3.cpp -c -O3 -std=c++11 -fno-math-errno -fexperimental-library \
	 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -ffast-math -ffp-contract=fast -freciprocal-math
	 emcc b3main_sh4d3.o b3ogl_sh4d3.o -o s3005.js -std=c++11 -fexperimental-library -O0 -mllvm -polly -static -DNDEBUG=1 -fno-math-errno -DWORDS_BIGENDIAN=0 -DCPU_IS_LITTLE_ENDIAN=1 \
	 -msimd128 -sWASMFS=1 -sPRECISE_F32=2 -mcpu=bleeding-edge -fwasm-exceptions \
	 -sTEXTDECODER=0 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -DSIMD=AVX -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sASSERTIONS=0 -USE_GLFW=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_b3_egl"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js

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

b3php:
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
	 em++ src/b3emjs.cpp -c -O0 \
	 -std=c++2a \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -ffp-contract=on
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs.o -o g302p.js -O0 -DNDEBUG=1 \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=1 -sWASM_BIGINT=0 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=128 -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
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

g00:
	 em++ src/b3main_g00.cpp -c -O3 \
	 -std=c++11 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3ogl.cpp -c \
	 -std=c++2a -O0 \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -ftree-vectorize \
	 -fapprox-func -mbulk-memory -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -DSIMD=128 \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	 em++ src/b3sdl.cpp -c -O0 \
	 -sUSE_SDL=2 -std=c++11 -ftree-vectorize \
	 -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -fno-fast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3emjs_g00.cpp -c -O0 \
	 -std=c++2a \
	 -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -ffp-exception-behavior=maytrap -ffp-contract=on
	 emcc b3main_g00.o b3ogl.o b3sdl.o b3emjs_g00.o -o g0025.js -O0 -DNDEBUG=1 \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=1 -sWASM_BIGINT=0 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=128 -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js gpujsx.js --pre-js rSlider.js --pre-js slideOut.js

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

fire:
	 em++ h3srgb.cpp -o g3016.js \
	 -std=c++2b -fno-fast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point -ffp-exception-behavior=strict -fslp-vectorize -mavx \
	 -fapprox-func -mbulk-memory -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujsx.js --post-js pagec.js

fire2:
	 em++ h3srgb.cpp -o g3016.js \
	 -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 \
	 -std=c++2b -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujsx.js --post-js pagec.js --pre-js fluid.js --post-js flui.js

speed:
	 em++ h3speed.cpp -o gs001.js \
	 -std=c++2b -ffast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point \
	 -fapprox-func -mbulk-memory -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=fast \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \

cloudxx:
	 em++ h3srgb.cpp -o c3001.js \
	 -std=c++2b -ffast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point \
	 -fapprox-func -mbulk-memory -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mmutable-globals -mnontrapping-fptoint \
	 -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=fast \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js tilt.js --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujsx.js --post-js pagec.js

tst8c: glsl_loader2.cpp Makefile
	em++ glsl_loader2.cpp -std=c++2b -O3 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-DNDEBUG=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sMALLOC="emmalloc" \
-o glsl_loader2.js -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js filesysNoSDL.js --extern-post-js ccall.js --post-js fs_loader.js --extern-pre-js setUp.js -sOFFSCREEN_FRAMEBUFFER=1

load: glsl_loader.cpp Makefile
	emcc glsl_loader.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o glsl001.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0

t3st:
	 em++ h3test.cpp -o tx001.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 \
	 -std=c++20 -sASYNCIFY \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujsx.js

texture:
	 em++ h3srgbtex.cpp -o t3001.js -sASYNCIFY -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=c++20 -s PTHREAD_POOL_SIZE=1 -sGL_POOL_TEMP_BUFFERS=0 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js cl-gpu.js

fire22:
	 em++ 112222.cpp -o g3012.js -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=c++20 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_ldd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagegs.js --extern-pre-js cl-gpu.js

crp2:
	 em++ crp2.cpp -o c3002.js -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=1 -sFULL_ES3=1 \
	 -std=c++20 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUpCrp2.js --extern-post-js pagecrp2.js --extern-pre-js cl-gpu.js

shade:
	 em++ h3srgb.cpp -o s3001.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -fwasm-exceptions -fexperimental-library \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -mcpu=bleeding-edge \
	 -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -std=c++2a \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --pre-js setUp.js --pre-js startUp.js --post-js pages.js --pre-js rSlider.js --pre-js slideOut.js

paint:
	 em++ castle.cpp -o p3002.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sASSERTIONS=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=c++2b -sASYNCIFY -sPRECISE_F32=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_stp"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js fluid.js --post-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js gpujsx.js

paint2:
	 em++ paint3.cpp -o p3002.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sASSERTIONS=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 \
	 -std=c++2b -sASYNCIFY -sPRECISE_F32=2 \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujsx.js

tester:
	 em++ h3test.cpp -O3 -o g3009.js -DNDEBUG=1 -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=700mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto -std=c++2b \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

g3f: g3f.cpp Makefile
	 em++ g3f.cpp -O0 -o g3f001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=0 \
	 -sUSE_SDL=2 -sFULL_ES3=0 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto -std=c++2b \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js filesys.js --post-js ccall.js --extern-pre-js setUp.js --post-js pagef.js

g3i: g3i.cpp Makefile
	 em++ g3i.cpp -O3 -o g3i001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=0 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto -std=c++2b \
	 -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	 --post-js filesys.js --post-js ccall.js --extern-pre-js setUp.js --post-js pagei.js

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

g0:
	em++ g00.cpp -o g0001.js -sFORCE_FILESYSTEM=1 \
	-sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	-std=c++20 \
	-sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--extern-pre-js filesys.js --extern-pre-js ccall.js --extern-pre-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-pre-js pageg0.js --extern-pre-js cl-gpu.js

crp:
	em++ crp.cpp -o c001.js -sFORCE_FILESYSTEM=1 -sMAXIMUM_MEMORY=4GB \
	-sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1400mb \
	-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	-sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	-sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=0 -sWASM_BIGINT=0 \
	--closure 1 -g2 -std=c++20 \
	-sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
	--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUpCrp.js --post-js pagecrc.js

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

glsl: glsl.cpp Makefile
	emcc glsl.cpp -sFULL_ES3=1 --closure 0 -sUSE_SDL=2 \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMALLOC='emmalloc' -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -DNDEBUG=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O1 -o gui003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0 -sOFFSCREEN_FRAMEBUFFER=1

all: b3hd
	echo 'Built 1ink.us Shaders.'
