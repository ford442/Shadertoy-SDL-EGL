
tst1: main.cpp  Makefile
	em++ main.cpp  --closure 0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -flto -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -std=c++17 -o shader.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1


tst2: main7.cpp  Makefile
	emcc main7.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl13.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=0

tst5: main9.cpp  Makefile
	emcc main9.cpp -sFULL_ES2=0 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sPRINTF_LONG_DOUBLE=0 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl16.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str","_read","_compile","_getShader"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=1

load: glsl_loader.cpp  Makefile
	emcc glsl_loader.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o glsl001.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0


droid: maind.cpp  Makefile
	emcc maind.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=128mb -sSINGLE_FILE=1 \
-O2 -o droid.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=1


tst6: main9func.cpp  Makefile
	emcc main9func.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl16func.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=0


tst7: main9file.cpp  Makefile
	emcc main9file.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl16file.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=0



tst+: main7.cpp  Makefile
	em++ main7.cpp -std=c++20 -sFULL_ES2=0 -sFULL_ES3=0 --closure 0 -sGL_TESTING=0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl15.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=0


bufa: main8.cpp  Makefile
	emcc main8.cpp -sFULL_ES2=0 -sFULL_ES3=0 --closure 0 -sGL_TESTING=0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl14.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=0

b3: b3.cpp  Makefile
	emcc b3.cpp -sFULL_ES2=0 -sFULL_ES3=0 --closure 0 -sGL_TESTING=0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o eb3001.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs.js -sSUPPORT_BIG_ENDIAN=0 --extern-post-js cl-gpu.js

glsl: glsl.cpp  Makefile
	emcc glsl.cpp -sFULL_ES2=1 -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o gui003.js -sEXPORTED_FUNCTIONS='["_main","_str","_pl","_read"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js --post-js fs-glsl.js -sSUPPORT_BIG_ENDIAN=0

tst3: main4.cpp  Makefile2
	emcc main4.cpp -sFULL_ES2=0 -g -sFULL_ES3=1 --closure 0 -sGL_TESTING=1 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl5.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1

tst3b: main5.cpp  Makefile
	em++ main5.cpp  -std=c++20 -sFULL_ES2=0 -sFULL_ES3=0 -g --closure 0 -sGL_TESTING=0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o egl5b.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1 --extern-post-js shader-web-background.min.js

tst4: js.c  Makefile
	emcc js.c -sFULL_ES2=0 -sFULL_ES3=0 --closure 0 -sGL_TESTING=0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -flto=thin -sENVIRONMENT=web -sMALLOC='emmalloc' -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -o js1.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1


all:  tst2 tst3 tst3b
	echo 'Built 1ink.us Shaders.'
