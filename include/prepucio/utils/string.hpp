#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace prepucio::utils {
  inline std::vector<std::string> split(const std::string &str) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(str);
    while (iss >> token) {
      tokens.push_back(token);
    }
    return tokens;
  }
}  // namespace prepucio::utils
