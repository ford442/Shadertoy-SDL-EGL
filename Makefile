
tst1: main.cpp  Makefile
	em++ main.cpp -sGL_TESTING=1 --closure 0 -sUSE_SDL=2 -sEXPORT_NAME='createModule' -sMODULARIZE=1 \
-sUSE_WEBGL2=1 -sPRINTF_LONG_DOUBLE=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -flto -sSUPPORT_LONGJMP=0 -DNDEBUG -sASSERTIONS=0 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -std=c++17 -o shader.js -sEXPORTED_FUNCTIONS='["_main","_pl","_str"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-post-js index.js --post-js filesys.js --post-js ccall.js -sSUPPORT_BIG_ENDIAN=1 \
--extern-post-js shader-web-background.min.js

all: tst1
	echo 'Built 1ink.us Shaders.'
