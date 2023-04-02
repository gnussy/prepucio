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

  builder.addCommand("hello", "Prints hello world", []() { fmt::print("Hello, {}!\n", "world"); })
      .addCommand("greet", "Greet the user back",
                  [](std::string greet) { fmt::print("Hello, {}!\n", greet); })
      .addCommand("add", "a", &Counter::increment, &counter)
      .addCommand("add_by", "a", &Counter::increment_by, &counter)
      .addCommand("display", "a", &Counter::display, &counter)
      .build()
      .run();
  return 0;
}
