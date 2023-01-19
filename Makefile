b3hd:
	 em++ src/main.cpp -c \
	 -std=c++2a -stdlib=libc++ -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -msign-ext -ffast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/shader.cpp -c \
	 -std=c++2a -stdlib=libc++ \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -DSIMD=128 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=off 
	 
	 em++ src/sdl_audio.cpp -c \
	 -sUSE_SDL=2 -std=c++2a -stdlib=libc++ -fslp-vectorize -ftree-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -fno-fast-math -ffp-contract=on -freciprocal-math
	 
	 em++ src/emjs.cpp -c \
	 -std=c++2a -stdlib=libc++ \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msign-ext -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -DSIMD=128 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=off
	 
	 emcc main.o shader.o sdl_audio.o emjs.o -o g3021.js \
	 -DSIMD=128 -fuse-ld=mold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js rSlider.js --post-js slideOut.js --post-js fluid.js --post-js flui.js --pre-js gpujs.js 


cloud:
	 em++ src/b3main.cpp -c \
	 -fno-math-errno -std=gnu++2b -stdlib=libc++ -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -m32 -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3ogl.cpp -c \
	 -fno-math-errno -std=gnu++2b -stdlib=libc++ \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -mavx \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 em++ src/b3sdl.cpp -c \
	 -fno-math-errno -sUSE_SDL=2 -std=gnu++2b -stdlib=libc++ -fslp-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -m32 -fno-fast-math -ffp-contract=on -freciprocal-math
	 em++ src/b3emjs.cpp -c \
	 -fno-math-errno -std=gnu++2b -stdlib=libc++ -matomics \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs.o -o c3001.js \
	 -fuse-ld=gold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --pre-js fluid.js --pre-js flui.js --pre-js gpujs.js --pre-js tilt.js 


b3g00:
	 em++ src/main_g00.cpp -c \
	-fno-math-errno -std=gnu++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -m32 -matomics -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/shader.cpp -c \
	 -fno-math-errno -std=gnu++2a -matomics \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -mavx \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 em++ src/sdl_audio.cpp -c \
	 -fno-math-errno -sUSE_SDL=2 -std=gnu++2a -matomics -fslp-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -m32 -fno-fast-math -ffp-contract=on -freciprocal-math
	 em++ src/emjs_google.cpp -c \
	 -fno-math-errno -std=gnu++2a -matomics \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off
	 emcc main_google.o shader.o sdl_audio.o emjs_google.o -o g0001.js \
	 -fuse-ld=gold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --post-js  rSlider.js --post-js  slideOut.js --post-js gpujs.js 


txt:
	 em++ src/b3main.cpp -c \
	 -fno-math-errno -std=gnu++2b -stdlib=libc++ -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -m32 -matomics -ffast-math -ffp-contract=fast -freciprocal-math
	 em++ src/b3ogl.cpp -c \
	 -fno-math-errno -std=gnu++2b -stdlib=libc++ -matomics \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -mavx \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 em++ src/b3sdl.cpp -c \
	 -fno-math-errno -sUSE_SDL=2 -std=gnu++2b -stdlib=libc++ -matomics -fslp-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -m32 -fno-fast-math -ffp-contract=on -freciprocal-math
	 em++ src/b3emjs_txt.cpp -c \
	 -fno-math-errno -std=gnu++2b -stdlib=libc++ -matomics \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off 
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs_txt.o -o g3017.js \
	 -fuse-ld=gold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --pre-js rSlider.js --pre-js slideOut.js --pre-js fluid.js --pre-js flui.js --post-js gpujs.js 


speed:
	 em++ h3speed.cpp -o gs001.js \
	 -std=gnu++2b -stdlib=libc++ -ffast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb  \
         -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point -fslp-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=fast -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujs.js --post-js pagec.js


load: glsl_loader.cpp  Makefile
	emcc glsl_loader.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o glsl001.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0


t3st:
	 em++ h3test.cpp -o tx001.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 \
	 -std=c++20 -sASYNCIFY \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujs.js


texture:
	 em++ h3srgbtex.cpp -o t3001.js -sASYNCIFY -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=c++20 -s PTHREAD_POOL_SIZE=1 -sGL_POOL_TEMP_BUFFERS=0 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js cl-gpu.js


crp2:
	 em++ crp2.cpp -o c3002.js -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=1 -sFULL_ES3=1 \
	 -std=gnu++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUpCrp2.js --extern-post-js pagecrp2.js --extern-pre-js cl-gpu.js


shade:
	 em++ h3srgb.cpp -o s3001.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -fwasm-exceptions -fexperimental-library \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -mcpu=bleeding-edge \
	 -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -stdlib=libc++ -std=gnu++2a \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --post-js pages.js --pre-js rSlider.js --pre-js slideOut.js


paint:
	 em++ castle.cpp -o p3002.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sASSERTIONS=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=gnu++2b -sASYNCIFY -sPRECISE_F32=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_stp"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js fluid.js --post-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js gpujs.js


paint2:
	 em++ paint3.cpp -o p3002.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb -sASSERTIONS=0 \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 \
	 -std=gnu++2b -sASYNCIFY -sPRECISE_F32=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js rSlider.js --extern-pre-js slideOut.js --extern-pre-js gpujs.js


g3f: g3f.cpp  Makefile
	 em++ g3f.cpp -O0 -o g3f001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=0 \
	 -sUSE_SDL=2 -sFULL_ES3=0 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto=thin -std=gnu++2b \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --extern-pre-js setUp.js --post-js pagef.js


g3i: g3i.cpp  Makefile
	 em++ g3i.cpp -O3 -o g3i001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=0 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto=thin -std=gnu++2b \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]'  -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --extern-pre-js setUp.js --post-js pagei.js


dbl: dbl.cpp  Makefile
	em++ dbl.cpp -O1 -o d3001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web  \
	-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	 -DNDEBUG -sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	  -sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=1 -sWASM_BIGINT=0 \
	 --closure 1 -g2 -std=gnu++2b -flto=thin \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesysdbl.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js


crp:
	em++ crp.cpp -o c001.js -sFORCE_FILESYSTEM=1 -sMAXIMUM_MEMORY=4GB \
	-sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1400mb \
	-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	-sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	-sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=0 -sWASM_BIGINT=0 \
	--closure 1 -g2 -std=gnu++20 \
        -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
        --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUpCrp.js --post-js pagecrc.js


glsl: glsl.cpp  Makefile
	emcc glsl.cpp -sFULL_ES3=1 --closure 0 -sUSE_SDL=2  \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMALLOC='emmalloc' -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O1 -o gui003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0 -sOFFSCREEN_FRAMEBUFFER=1


all: b3hd
	echo 'Built 1ink.us Shaders.'
