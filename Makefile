tst1: main.cpp  Makefile
	em++ main.cpp  --closure 0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -flto -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -std=c++17 -o shader.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1

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

b3: b3.cpp  Makefile
	em++ b3.cpp -flto=thin --closure 1 -g2 -std=gnu++2b -O2 -ffast-math -sUSE_SDL=2 -sFULL_ES2=1 -sFULL_ES3=1 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sMALLOC="emmalloc" \
-o b3004.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js page.js

gpu: avg.cpp  Makefile
	em++ avg.cpp -flto=thin --closure 1 -g2 -std=gnu++2b -O2 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sMALLOC="emmalloc" \
-o g3003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js

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
         --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

fire:
	 em++ h3srgb.cpp -o g3013.js -sASYNCIFY -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 -sGL_UNSAFE_OPTS \
	 -std=c++20  \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js cl-gpu.js

texture:
	 em++ h3srgbtex.cpp -o t3001.js -sASYNCIFY -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=c++20 -s PTHREAD_POOL_SIZE=1 -sGL_POOL_TEMP_BUFFERS=0 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-pre-js fluid.js --extern-pre-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pageg.js --extern-pre-js cl-gpu.js


fire2:
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
	 em++ h3srgb.cpp -o s3001.js -DNDEBUG -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=gnu++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js fluid.js --post-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pages.js --extern-pre-js cl-gpu.js

paint:
	 em++ paint.cpp -o p3001.js -DNDEBUG -sFORCE_FILESYSTEM=1 \
	 -sMAXIMUM_MEMORY=4096mb -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=gnu++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano","_stp"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js fluid.js --post-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pageg.js --extern-pre-js cl-gpu.js


paint2:
	 em++ paint3.cpp -o p3002.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=2048mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 \
	 -std=gnu++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js fluid.js --post-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pagec.js --extern-pre-js cl-gpu.js

cloud:
	 em++ h3srgb.cpp -o c3001.js -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1536mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES2=0 -sFULL_ES3=1 \
	 -std=gnu++20 \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --extern-post-js tilt.js --extern-post-js fluid.js --extern-post-js flui.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js pagec.js --extern-pre-js cl-gpu.js


emloop:
	  em++ emloop.cpp -O3 -o g3011.js -DNDEBUG -sFORCE_FILESYSTEM=1 \
	 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1536mb -sTOTAL_STACK=64mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	 -sUSE_SDL=2 -sFULL_ES3=1 -sFULL_ES2=0 \
	 --closure 1 -g2 -ffast-math -flto=thin -std=gnu++2b -stdlib=libc++ \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js fluid.js --post-js flui.js --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

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


txt: txt.cpp  Makefile
	em++ txt.cpp -O3 -o t3001.js -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web  \
	-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
	 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
	-sUSE_SDL=2 -sFULL_ES3=1 \
	 -DNDEBUG -sSUPPORT_ERRNO=0 -sGL_DEBUG=0 -sGL_TRACK_ERRORS=0 \
	  -sGL_POOL_TEMP_BUFFERS=0 -sMEMORY64=0 -sLEGALIZE_JS_FFI=1 -sWASM_BIGINT=0 \
	 --closure 1 -g2 -std=gnu++2b -flto=thin \
         -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
         --post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --post-js pageg.js

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

heap-devel: h3.cpp  Makefile
	em++ h3.cpp -g -std=gnu++2b --closure 0 -O2 -sUSE_SDL=2 -sFULL_ES3=1 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb  \
-o g3004dev.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --extern-pre-js startUp.js --extern-post-js cl-gpu.js

glsl: glsl.cpp  Makefile
	emcc glsl.cpp -sFULL_ES3=1 --closure 0 -sUSE_SDL=2  \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMALLOC='emmalloc' -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O1 -o gui003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0 -sOFFSCREEN_FRAMEBUFFER=1

all: heap gpu
	echo 'Built 1ink.us Shaders.'
