#include <prepucio/utils/string.hpp>
#include <sstream>

namespace prepucio::utils {
  std::vector<std::string> split(const std::string &str) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(str);
    while (iss >> token) {
      tokens.push_back(token);
    }
    return tokens;
  }
}  // namespace prepucio::utils
