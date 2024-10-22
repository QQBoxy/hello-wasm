// emcc add.c -o add.wasm -s STANDALONE_WASM -s --no-entry

#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int add(int a, int b)
{
    return a + b;
}