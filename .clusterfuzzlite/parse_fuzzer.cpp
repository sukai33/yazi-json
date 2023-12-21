#include <Json.h>
#include <string>

using namespace yazi::json;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string fuzz_input(reinterpret_cast<const char *>(data), size);

  Json json;
  try {
    json.parse(fuzz_input.c_str());
  } catch (...) {
  }
  json.clear();

  return 0;
}