/*
 * https://github.com/sndth/vilumi
 * Simple library for tweaking colors in strings
 * Software distributed only under the MIT License
 */

#pragma once

#ifndef VILUMI_HEADER
#define VILUMI_HEADER

#include <format>
#include <string>
#include <utility>
#include <unordered_map>

class vilumi final
{
  template<typename T>
  static std::string to_own_string(const T& value)
  {
    std::ostringstream res;
    res << value;
    return res.str();
  }

public:
  template<typename... Arguments>
  static std::string colorize(std::string message, Arguments&&... arguments)
  {
    return colourize(std::move(message), std::forward<Arguments>(arguments)...);
  }

  template<typename... Arguments>
  static std::string colourize(std::string message, Arguments&&... arguments)
  {
    std::size_t index = 0;
    std::size_t position = 0;
    std::vector<std::string> values{ to_own_string(
      std::forward<Arguments>(arguments))... };

    while ((position = message.find("{}", position)) != std::string::npos &&
           index < values.size()) {
      message.replace(position, 2, values[index++]);
      position += values[index - 1].size();
    }

    for (const auto& [name, code] : colors_) {
      std::size_t pos_open = 0;
      std::string tag_open = name + "(";
      std::string code_ansi = "\033[" + std::to_string(code) + "m";

      while ((pos_open = message.find(tag_open, pos_open)) !=
             std::string::npos) {
        message.replace(pos_open, tag_open.length(), code_ansi);

        std::size_t pos_close =
          message.find(')', pos_open + code_ansi.length());

        if (pos_close == std::string::npos) {
          throw std::runtime_error("Opened bracket for color '" + name +
                                   "' but not closed.");
        }

        message.replace(pos_close, 1, "\033[0m");
        pos_open = pos_close + 4;
      }
    }

    return message;
  }

private:
  static inline std::unordered_map<std::string, std::uint8_t> colors_ = {
    { "red", 31 },  { "green", 32 },   { "yellow", 33 },
    { "blue", 34 }, { "magenta", 35 }, { "white", 37 }
  };
};
#endif
