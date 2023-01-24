b3hd:

	 em++ src/b3ogl.cpp -m64 -c -nostdlib -sMEMORY64=2 \
	 -std=c++2a -O0 \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -DSIMD=128 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=fast

	 em++ src/b3emjs.cpp -m64 -c -O0 -nostdlib -sMEMORY64=2 \
	 -std=c++2a \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msign-ext -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -fno-fast-math -ffp-contract=off

	 em++ src/b3sdl.cpp -c -O0 -nostdlib \
	 -sUSE_SDL=2 -std=c++11 -fslp-vectorize -ftree-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -ffast-math -ffp-contract=fast -freciprocal-math

	 em++ src/b3main.cpp -c -O3 -nostdlib \
         -std=c++11 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -msign-ext -ffast-math -ffp-contract=fast -freciprocal-math

	 emcc b3main.o b3sdl.o -m64 b3ogl.o  b3emjs.o -o g3020.js -O0 -DNDEBUG \
	 -sWASMFS=1 \
	 -sEMBIND_STD_STRING_IS_UTF8=0 -sTEXTDECODER=0 -sMALLOC="emmalloc" -sSUPPORT_LONGJMP=0 -sFETCH_SUPPORT_INDEXEDDB=0 \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=2 -sWASM_BIGINT=1 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=128 -fuse-ld=mold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
          --pre-js gpujs.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js

castle:
	 em++ src/b3main.cpp -c -O3 -nostdlib \
         -std=c++11 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -msign-ext -ffast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/b3ogl.cpp -c \
	 -std=c++2a -O0 \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -DSIMD=128 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	 
	 em++ src/b3sdl.cpp -c -O0 -nostdlib \
	 -sUSE_SDL=2 -std=c++11 -fslp-vectorize -ftree-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -fno-fast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/b3emjs_castle.cpp -c -O0 -nostdlib \
	 -std=c++2a -DCASTLE2 \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msign-ext -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffp-contract=on
	 
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs_castle.o -o g302c.js -O0 -DNDEBUG \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=1 -sWASM_BIGINT=1 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=128 -fuse-ld=mold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
          --pre-js gpujs.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js 
	  
b3php:
	 em++ src/b3main.cpp -c -O3 -nostdlib \
         -std=c++11 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -msign-ext -ffast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/b3ogl.cpp -c \
	 -std=c++2a -O0 \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -DSIMD=128 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	 
	 em++ src/b3sdl.cpp -c -O0 -nostdlib \
	 -sUSE_SDL=2 -std=c++11 -fslp-vectorize -ftree-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -fno-fast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/b3emjs.cpp -c -O0 -nostdlib \
	 -std=c++2a \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msign-ext -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffp-contract=on
	 
	 emcc b3main.o b3ogl.o b3sdl.o b3emjs.o -o g302p.js -O0 -DNDEBUG \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=1 -sWASM_BIGINT=1 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=128 -fuse-ld=mold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
          --pre-js gpujs.js --pre-js rSlider.js --pre-js slideOut.js --extern-post-js fluid.js --extern-post-js flui.js 

cloud:
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


g00:
	 em++ src/b3main_g00.cpp -c -O3 -nostdlib \
         -std=c++11 -mcpu=bleeding-edge -fwasm-exceptions -ftree-vectorize \
	 -mbulk-memory -msign-ext -ffast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/b3ogl.cpp -c \
	 -std=c++2a -O0 \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -mmutable-globals -mnontrapping-fptoint \
	 -msimd128 -mavx -DSIMD=128 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off \
	 -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffast-math -ffp-contract=on
	 
	 em++ src/b3sdl.cpp -c -O0 -nostdlib \
	 -sUSE_SDL=2 -std=c++11 -fslp-vectorize -ftree-vectorize \
         -mcpu=bleeding-edge -fwasm-exceptions \
	 -mbulk-memory -msign-ext -fno-fast-math -ffp-contract=fast -freciprocal-math
	 
	 em++ src/b3emjs_g00.cpp -c -O0 -nostdlib \
	 -std=c++2a \
         -mcpu=bleeding-edge -fwasm-exceptions -ffixed-point -fslp-vectorize -ftree-vectorize -mmutable-globals -mnontrapping-fptoint \
	 -fapprox-func -mbulk-memory -msign-ext -msimd128 -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -ffp-exception-behavior=maytrap -ffp-contract=on
	 
	 emcc b3main_g00.o b3ogl.o b3sdl.o b3emjs_g00.o -o g0025.js -O0 -DNDEBUG \
	 -sASSERTIONS=0 -USE_GLFW=0 -sPRECISE_F32=1 -sWASM_BIGINT=1 -std=c++2a -mcpu=bleeding-edge -fwasm-exceptions \
	 -DSIMD=128 -fuse-ld=mold -sUSE_SDL=2 -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_b3_egl","_nano","_clr","_frm"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
          --pre-js gpujs.js --pre-js rSlider.js --pre-js slideOut.js

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


fire:
	 em++ h3srgb.cpp -o g3016.js \
	 -std=gnu++2b -fno-fast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb  \
         -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point -ffp-exception-behavior=strict -fslp-vectorize -mavx \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=off -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujs.js --post-js pagec.js

fire2:
	 em++ h3srgb.cpp -o g3016.js \
	 -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 \
	 -std=gnu++2b -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujs.js --post-js pagec.js --pre-js fluid.js --post-js flui.js


speed:
	 em++ h3speed.cpp -o gs001.js \
	 -std=gnu++2b -stdlib=libc++ -ffast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb  \
         -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point -fslp-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=fast -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujs.js --post-js pagec.js


cloudxx:
	 em++ h3srgb.cpp -o c3001.js \
	 -std=gnu++2b -stdlib=libc++ -ffast-math -ffp-contract=off -matomics -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb  \
         -mcpu=bleeding-edge -fwasm-exceptions -fexperimental-library -ffixed-point -fslp-vectorize \
	 -fapprox-func -mbulk-memory -msign-ext -m32 -msimd128 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mmutable-globals -mnontrapping-fptoint \
	 -mmultivalue -mextended-const -fno-signed-zeros -freciprocal-math -ffp-contract=fast -Xclang -menable-no-nans -Xclang -menable-no-infs \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sPRECISE_F32=2 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_b3","_nano","_clr"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js tilt.js --pre-js setUp.js --pre-js startUp.js --post-js rSlider.js --post-js slideOut.js --post-js gpujs.js --post-js pagec.js
	 
tst8c: glsl_loader2.cpp  Makefile
	em++ glsl_loader2.cpp -std=c++2b -O3 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sMALLOC="emmalloc" \
-o glsl_loader2.js -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js filesysNoSDL.js --extern-post-js ccall.js --post-js fs_loader.js --extern-pre-js setUp.js -sOFFSCREEN_FRAMEBUFFER=1

load: glsl_loader.cpp  Makefile
	emcc glsl_loader.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o glsl001.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0


heap: h3.cpp  Makefile
	 em++ h3.cpp -O2 -o g3007.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -ffast-math \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto=thin -std=gnu++2b \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

heapsrgb:
	  em++ h3srgb.cpp -O3 -o g3008.js -DNDEBUG -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto=thin -std=c++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --post-js fs.js --pre-js setUp.js --pre-js startUp.js --post-js pageg.js



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


fire22:
	 em++ 112222.cpp -o g3012.js -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=gnu++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_ldd"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagegs.js --extern-pre-js cl-gpu.js

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


tester:
	  em++ h3test.cpp -O3 -o g3009.js -DNDEBUG -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=700mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 -sFULL_ES2=0 \
	 --closure 1 -g2 -flto=thin -std=c++2b \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

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


g0:
	 em++ g00.cpp -o g0001.js -sFORCE_FILESYSTEM=1 \
	-sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	-std=gnu++20 \
        -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
        --extern-pre-js filesys.js --extern-pre-js ccall.js --extern-pre-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-pre-js pageg0.js  --extern-pre-js cl-gpu.js


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

img: img.cpp  Makefile
	em++ img.cpp -O1 -o i003.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web  \
	-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	 -DNDEBUG -sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	  -sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=0 -sWASM_BIGINT=0 \
	 --closure 1 -g2 -std=gnu++2b \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageImg.js


glsl: glsl.cpp  Makefile
	emcc glsl.cpp -sFULL_ES3=1 --closure 0 -sUSE_SDL=2  \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMALLOC='emmalloc' -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O1 -o gui003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0 -sOFFSCREEN_FRAMEBUFFER=1

all: b3hd
	echo 'Built 1ink.us Shaders.'
