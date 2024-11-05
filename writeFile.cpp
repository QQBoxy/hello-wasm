// emcc writeFile.cpp -o writeFile.js -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_FUNCTIONS="['_modifyFile']" -s EXPORTED_RUNTIME_METHODS="['FS']" -s FORCE_FILESYSTEM=1

#include <iostream>
#include <fstream>
#include <emscripten.h>

// 定義一個函式，用來讀取檔案並修改其內容
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void modifyFile() {
        std::ifstream inputFile("/input");
        std::string content;

        // 讀取檔案內容
        if (inputFile) {
            std::getline(inputFile, content);
            inputFile.close();
        } else {
            std::cout << "Failed to open input file." << std::endl;
            return;
        }

        // 在檔案內容後加上 " world"
        content += " world";

        // 寫回檔案
        std::ofstream outputFile("/output");
        outputFile << content;
        outputFile.close();

        std::cout << "File modified: " << content << std::endl;
    }
}
