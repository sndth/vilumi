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
    colourize(message, arguments);
  }

  template<typename... Arguments>
  static std::string colourize(std::string message, Arguments&&... arguments)
  {
    std::vector<std::string> values{ to_own_string(
      std::forward<Arguments>(arguments))... };
    size_t pos = 0;
    size_t index = 0;

    while ((pos = message.find("{}", pos)) != std::string::npos &&
           index < values.size()) {
      message.replace(pos, 2, values[index++]);
      pos += values[index - 1].size();
    }

    for (auto& [name, value] : colors_) {
      auto find = name + '(';
      auto replace "\033[" + std::to_string(value) + "m";
      auto open_position = message.find(find);

      while (open_position != std::string::npos) {
        message.replace(open_position, find.length(), replace);

        auto const close_position =
          message.find(')', open_position + replace.length());

        if (close_position == std::string::npos) {
          throw std::exception(
            "Opened bracket but not closed at " + (open_position + name.length()))
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
    { "red", 31 },  { "green", 32 },   { "yellow", 33 },
    { "blue", 34 }, { "magenta", 35 }, { "white", 37 }
  };
};
#endif
