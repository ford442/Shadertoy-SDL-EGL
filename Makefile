
tst1: main.cpp  Makefile
	em++ main.cpp  --closure 0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -flto -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -std=c++17 -o shader.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1

tst8b: egl4b.cpp  Makefile
	em++ egl4b.cpp -std=c++2b -O2 -sFULL_ES2=1 -sFULL_ES3=1 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-o sh1t.js -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--extern-post-js filesysNoSDL.js --extern-post-js ccall.js --post-js fs.js --extern-pre-js setUp.js

tst9: egl5.cpp  Makefile
	em++ egl5.cpp -std=c++2b -O2 -sFULL_ES2=1 -sFULL_ES3=1 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-DNDEBUG -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=1400mb -sMALLOC="emmalloc" \
-o sh9.js -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--extern-post-js filesysNoSDL.js --extern-post-js ccall.js --post-js fs.js --extern-pre-js setUp.js

sdl: sdl.cpp  Makefile
	em++ sdl.cpp -std=gnu++2b --closure 0 -O2 -sUSE_SDL=2 -sFULL_ES2=1 -sFULL_ES3=1 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=256mb -sMALLOC="emmalloc" \
-o sdl.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js


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
	em++ b3.cpp -DNDEBUG -flto=thin --closure 1 -g2 -std=gnu++2b -O2 -sUSE_SDL=2 -sFULL_ES2=1 -sFULL_ES3=1 -sGL_TESTING=1 \
-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 -sENVIRONMENT=web \
-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sMALLOC="emmalloc" \
-o b3003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_b3","_nano"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' \
--post-js filesys.js --post-js ccall.js --post-js fs.js --extern-pre-js setUp.js --post-js startUp.js --post-js page.js

glsl: glsl.cpp  Makefile
	emcc glsl.cpp -sFULL_ES2=0 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2  \
-sUSE_WEBGL2=1 -sENVIRONMENT=web -sMALLOC='emmalloc' -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o gui003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0 -sOFFSCREEN_FRAMEBUFFER=1

all: b3
	echo 'Built 1ink.us Shaders.'
