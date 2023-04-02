#include <fmt/core.h>

#include <prepucio/repl.hpp>

auto main() -> int {
  prepucio::REPL::Builder builder;
  int counter = 0;

  // clang-format off
  builder
    .addCommand("check", "check the counter status",
      [&counter]() { fmt::print("The counter is at {}\n", counter); })
    .addCommand("increment", "increment the counter",
      [&counter]() { counter++; })
    .addCommand("decrement", "decrement the counter",
      [&counter]() { counter--; })
    .addCommand("reset", "reset the counter",
      [&counter]() { counter = 0; })
    .addCommand("increment_by", "increment the counter by a given amount",
      [&counter](int amount) { counter += amount; })
    .build()
    .run();
  // clang-format on
  return 0;
}
