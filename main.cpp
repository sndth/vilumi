#include <iostream>
#include <sndth/vivid.hpp>

int
main()
{
  std::cout << sndth::vivid::format(
    "Hello from red{vigreen{vid}} or green{vired{vid}}!");
}
