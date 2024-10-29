// emcc base64.cpp -o base64.wasm -s STANDALONE_WASM -s --no-entry
#include <emscripten.h>

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    char *get_memory_for_char_array(int size)
    {
        return (new char[size]);
    }

    static const char MimeBase64[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'};

    static int DecodeMimeBase64[256] =
        {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
            -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    union Base64
    {
        struct
        {
            unsigned char c1;
            unsigned char c2;
            unsigned char c3;
        };

        struct
        {
            unsigned int e1 : 6;
            unsigned int e2 : 6;
            unsigned int e3 : 6;
            unsigned int e4 : 6;
        };
    };

    EMSCRIPTEN_KEEPALIVE
    bool base64_encode(const char *src, const int srcLength, char *result, int &resultLength)
    {
        if (src == NULL || srcLength <= 0)
        {
            return false;
        }

        int minResultLength = (srcLength % 3 == 0) ? srcLength / 3 * 4 : (srcLength / 3 + 1) * 4;
        if (result == NULL || resultLength < minResultLength)
        {
            return false;
        }
        resultLength = minResultLength;

        for (int i = 0, j = 0; i < srcLength; i += 3, j += 4)
        {
            union Base64 base;
            base.c3 = src[i];
            base.c2 = (i + 1 < srcLength) ? src[i + 1] : 0x00;
            base.c1 = (i + 2 < srcLength) ? src[i + 2] : 0x00;

            result[j + 0] = MimeBase64[base.e4];
            result[j + 1] = MimeBase64[base.e3];
            result[j + 2] = MimeBase64[base.e2];
            result[j + 3] = MimeBase64[base.e1];

            if (i + 1 >= srcLength)
                result[j + 2] = '=';
            if (i + 2 >= srcLength)
                result[j + 3] = '=';
        }

        return true;
    }

    EMSCRIPTEN_KEEPALIVE
    bool base64_decode(const char *src, const int srcLength, char *result, int &resultLength)
    {
        if (src == NULL || srcLength <= 0)
        {
            return false;
        }

        int minResultLength = srcLength / 4 * 3;
        if (src[srcLength - 1] == '=')
            minResultLength--;
        if (src[srcLength - 2] == '=')
            minResultLength--;
        if (result == NULL || resultLength < minResultLength)
        {
            return false;
        }
        resultLength = minResultLength;

        for (int i = 0, j = 0; i < srcLength; i += 4, j += 3)
        {
            Base64 base;
            base.e4 = DecodeMimeBase64[(int)src[i + 0]];
            base.e3 = DecodeMimeBase64[(int)src[i + 1]];
            base.e2 = (src[i + 2] != '=') ? DecodeMimeBase64[(int)src[i + 2]] : 0;
            base.e1 = (src[i + 3] != '=') ? DecodeMimeBase64[(int)src[i + 3]] : 0;

            result[j + 0] = base.c3;
            result[j + 1] = base.c2;
            result[j + 2] = base.c1;
        }

        return true;
    }
}
