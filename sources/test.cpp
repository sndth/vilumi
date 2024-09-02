#include <print>
#include <sndth/vivid.hpp>

using namespace sndth;

int main() {
  try {
    auto message = vivid::colorize(
        "red{red}, green{green}, blue{blue from yellow{vivid}!");
    std::println("{}", message);
  } catch (const std::exception &e) {
    std::println("{}", e.what());
  }
}
