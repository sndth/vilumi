//        _       _     _
// __   _(_)_   _(_) __| |
// \ \ / / \ \ / / |/ _` |
//  \ V /| |\ V /| | (_| |
//   \_/ |_| \_/ |_|\__,_|
// https://github.com/sndth/vivid
// A fast and simple text color parser

#pragma once

#ifndef VIVID_HPP
#define VIVID_HPP

#include <string>
#include <unordered_map>

// ReSharper disable once IdentifierTypo
namespace sndth {
class vivid
{
#if _HAS_CXX17 == 0
  using string = std::string;
#else
  using string = std::string_view;
#endif

  using unordered_color = std::unordered_map<std::string, std::uint8_t>;

public:
  static std::string colorize(const string message)
  {
    std::string output;

    for (auto& [name, value] : colors_) {
      if (output.empty())
        output = message.data();

      size_t position = 0;

      while (position != std::string::npos) {
        position = output.find(name + '{');

        if (position == string::npos)
          continue;

        output.replace(position,
                       name.size() + 1,
                       std::format("\033[{}m", std::to_string(value)));

        position = output.find('}');

        if (position == string::npos)
          continue;

        output.erase(position, 1);
        output.insert(position, "\033[0m");
      }
    }

    return output;
  }

private:
  static inline unordered_color colors_ = { { "reset", 0 },    { "black", 30 },
                                            { "red", 31 },     { "green", 32 },
                                            { "yellow", 33 },  { "blue", 34 },
                                            { "magenta", 35 }, { "cyan", 36 },
                                            { "white", 37 } };
};
}
#endif
