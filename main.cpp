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

  // Update input string
  input.replace(11, 3, "cyan");
  input.replace(41, 3, "cyan");

  // Try to print rich string
  std::println("{}", sndth::vivid::colorize(input));

  // This should throw exception, because in fact, we don't have cyan in our
  // color list. So let's try to add it!
  sndth::vivid::insert({ "cyan", 36 });

  // Try now, maybe this time will be work?
  std::println("{}", sndth::vivid::colorize(input));
}
