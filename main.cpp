#include <print>
#include <iostream>
#include <sndth/vivid.hpp>

using namespace sndth;

int
main()
{
  std::println("Hello from {} or {},",
               vivid::format("red{vigreen{vid}}"),
               vivid::format("green{vired{vid}}"));

  std::cout << vivid::format(
    "did you know that magenta{2} + magenta{2} is cyan{4}?\n");
}
