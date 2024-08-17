// ReSharper disable All

#include <iostream>
#include <print>
#include <sndth/vivid.hpp>

int
main()
{
  std::string input = "Hello from red{vigreen{vid}} or green{vired{vid}}!";

  // Print raw string
  std::println("{}", input);

  // Print rich string
  std::println("{}", sndth::vivid::colorize(input));
}
