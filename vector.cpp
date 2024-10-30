// emcc vector.cpp -o vector.js -lembind -s MODULARIZE -s EXPORT_ES6=1
#include <emscripten/bind.h>
#include <vector>

using namespace emscripten;

std::vector<int> returnVectorData(std::vector<int> &vec)
{
  for(int i = 0; i < vec.size(); i++)
  {
    vec[i] = vec[i] + 1;
  }
  return vec;
}

EMSCRIPTEN_BINDINGS(module)
{
  register_vector<int>("VectorInt");
  function("returnVectorData", &returnVectorData);
}