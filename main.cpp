#include <iostream>
#include <sndth/vivid.hpp>

using namespace sndth;

int
main()
{
  try {
    std::cout << vivid::format("Hello from red{vigreen{vid}} or green{vired{vid}}!");
  } catch (const std::exception& error) {
    std::cerr << error.what();
  }
}
