#include <fmt/core.h>

#include <prepucio/repl.hpp>

auto main() -> int {
  prepucio::REPL::Builder builder;

  prepucio::REPL *repl
      = builder.addCommand("hello", "Prints hello world", [&repl]() { repl->emit("event"); })
            .addEvent("event", "Prints the event",
                      [&repl]() { repl->show_penis()->prompt("New prompt: "); })
            .build_ptr();

  repl->prompt("main> ");
  repl->run();

  return 0;
}
