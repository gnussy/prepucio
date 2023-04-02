#include <fmt/core.h>

#include <prepucio/repl.hpp>

struct Counter {
  int value = 0;
  void increment() { ++value; }
  void decrement() { --value; }
  void increment_by(int amount) { value += amount; }
  void reset() { value = 0; }
  void display() { fmt::print("Value: {}\n", value); }
};

auto main() -> int {
  prepucio::REPL::Builder builder;
  Counter counter;

  // clang-format off
  builder
    .addCommand("check", "check the counter status", &Counter::display, &counter)
    .addCommand("increment", "increment the counter", &Counter::increment, &counter)
    .addCommand("decrement", "decrement the counter", &Counter::decrement, &counter)
    .addCommand("reset", "reset the counter", &Counter::reset, &counter)
    .addCommand("increment_by", "increment the counter by a given amount", &Counter::increment_by, &counter)
    .build()
    .run();
  // clang-format on
  return 0;
}
