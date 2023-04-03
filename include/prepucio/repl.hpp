#pragma once

#include <penis/penis.hpp>
#include <prepucio/command.hpp>
#include <prepucio/utils/string.hpp>
#include <string>
#include <tabulate/table.hpp>
#include <unordered_map>

namespace prepucio {
  class REPL {
  private:
    std::unordered_map<std::string, Command> commands;
    std::unordered_map<std::string, Command> events;
    penis::PromptBuilder builder;
    tabulate::Table signatures;

  public:
    class Builder {
    private:
      std::unordered_map<std::string, Command> commands;
      std::unordered_map<std::string, Command> events;

    public:
      template <typename Func>
      Builder &addCommand(const std::string &name, const std::string &description, Func &&func) {
        commands.emplace(name, Command{name, description, std::forward<Func>(func)});
        return *this;
      }

      template <typename Func, typename Object> Builder &addCommand(const std::string &name,
                                                                    const std::string &description,
                                                                    Func &&func, Object *object) {
        commands.emplace(name, Command{name, description, std::forward<Func>(func), object});
        return *this;
      }

      template <typename Func>
      Builder &addEvent(const std::string &name, const std::string &description, Func &&func) {
        events.emplace(name, Command{name, description, std::forward<Func>(func)});
        return *this;
      }

      template <typename Func, typename Object> Builder &addEvent(const std::string &name,
                                                                  const std::string &description,
                                                                  Func &&func, Object *object) {
        events.emplace(name, Command{name, description, std::forward<Func>(func), object});
        return *this;
      }

      REPL build() { return REPL(this->commands, this->events); }
      REPL *build_ptr() { return new REPL(this->commands, this->events); }
    };

    REPL(std::unordered_map<std::string, Command> commands,
         std::unordered_map<std::string, Command> events)
        : commands(std::move(commands)), events(std::move(events)) {
      signatures.add_row({"Command", "Description", "Arguments"});
      for (const auto &[name, command] : this->commands) {
        signatures.add_row({name, command.get_description(), command.get_signature()});
      }

      builder.prompt("❯ ");
      builder.subscribe_command([this](const std::string &input) { deal_with_command(input); });
      builder.subscribe_event([this](const std::string &input) { deal_with_event(input); });
    }

    void deal_with_command(const std::string &input) {
      std::vector<std::string> tokens = utils::split(input);
      if (tokens.empty()) return;

      std::string command = tokens[0];
      tokens.erase(tokens.begin());

      if (command == "quit") {
        exit(0);
      } else if (command == "help") {
        print_help();
      } else if (auto it = commands.find(command); it != commands.end()) {
        it->second.call(tokens);
      } else {
        std::cerr << "Error: unknown command '" << command << "'" << std::endl;
      }
    }

    void deal_with_event(const std::string &input) {
      std::vector<std::string> tokens = utils::split(input);
      if (tokens.empty()) return;

      std::string event_name = tokens[0];
      tokens.erase(tokens.begin());

      if (auto it = events.find(event_name); it != events.end()) {
        it->second.call(tokens);
      } else {
        std::cerr << "Error: unknown event '" << event_name << "'" << std::endl;
      }
    }

    void emit(const std::string &event_name, const std::string &args) {
      builder.emit_event(event_name, args);
    }

    void emit(const std::string &event_name) { builder.emit_event(event_name, ""); }

    void run() { builder.run(); }

    void prompt(const std::string &prompt) { builder.prompt(prompt); }

    void print_help() {
      std::cout << "Available commands:" << std::endl;
      std::cout << signatures << std::endl;
    }
  };
}  // namespace prepucio
