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
class vivid final {
public:
  static std::string colorize(std::string message) {
    for (auto &[name, value] : colors_) {
      auto find = name + '{';
      auto replace = std::format("\033[{}m", std::to_string(value));
      auto open_position = message.find(find);

      while (open_position != std::string::npos) {
        message.replace(open_position, find.length(), replace);

        const auto close_position =
            message.find('}', open_position + replace.length());

        if (close_position == std::string::npos) {
          throw std::exception(
              std::format("Opened bracket but not closed at {}",
                          (open_position + name.length()))
                  .c_str());
        }

        message.replace(close_position, 1, "\033[0m");
        open_position = message.find(find, close_position + 1);
      }
    }

    return message;
  }

private:
  static inline std::unordered_map<std::string, std::uint8_t> colors_ = {
      {"red", 31},  {"green", 32},   {"yellow", 33},
      {"blue", 34}, {"magenta", 35}, {"white", 37}};
};
// ReSharper disable once CommentTypo
} // namespace sndth
#endif
