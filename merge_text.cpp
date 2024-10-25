// emcc merge_text.cpp -o merge_text.wasm -s STANDALONE_WASM --no-entry
#include <iostream>
#include <emscripten.h>

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    char *get_memory_for_char_array(int size)
    {
        return (new char[size]);
    }

    EMSCRIPTEN_KEEPALIVE
    char *merge_text(char *a, char *b, char *c)
    {
        strcpy(c, a);
        strcat(c, b);
        return c;
    }
}