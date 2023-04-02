#include <fmt/core.h>

#include <prepucio/repl.hpp>

auto main() -> int {
  prepucio::REPL::Builder builder;

  // clang-format off
  builder
    .addCommand("hello", "Prints hello world", 
      []() { fmt::print("Hello, World!\n"); })
    .build()
    .run();
  // clang-format on

  return 0;
}
