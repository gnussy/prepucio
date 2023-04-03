#include <fmt/core.h>

#include <prepucio/repl.hpp>

auto main() -> int {
  prepucio::REPL::Builder builder;

  // clang-format off
  prepucio::REPL repl = builder
    .addCommand("hello", "Prints hello world", 
      [&builder, &repl]() { repl.emit("event", "1 hello"); })
    .addEvent("event", "Prints the event", 
      [](int a, std::string b) { fmt::print("Event: {}, {}\n", a, b); }
    )
    .build();
  // clang-format off

  repl.run();

  return 0;
}
