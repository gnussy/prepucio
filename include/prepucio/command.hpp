#pragma once

#include <fmt/color.h>
#include <fmt/core.h>

#include <optional>
#include <penis/penis.hpp>
#include <prepucio/magic/templates.hpp>
#include <sstream>
#include <string>

namespace prepucio {
  class Command {
  public:
    using Callback = std::function<void(const std::vector<std::string> &args)>;

  private:
    std::string name;
    std::string description;
    std::string signature;
    Callback callback;

  public:
    template <typename Func, typename Object>
    Command(const std::string &name, const std::string &description, Func &&func, Object *object)
        : name(name), description(description) {
      this->callback = this->construct_callback<Func>([&func, object](auto &&args) {
        std::apply(func, std::tuple_cat(std::make_tuple(object), args));
      });
    }

    template <typename Func>
    Command(const std::string &name, const std::string &description, Func &&func)
        : name(name), description(description) {
      this->callback
          = this->construct_callback<Func>([&func](auto &&args) { std::apply(func, args); });
    }

    const std::string &get_name() const { return name; }
    const std::string &get_description() const { return description; }
    const std::string &get_signature() const { return signature; }

    void call(const std::vector<std::string> &args) { callback(args); }

  private:
    template <typename Func, typename ApplyFunction>
    Command::Callback construct_callback(ApplyFunction apply) {
      std::string_view signature = type_name<Func>();
      std::string_view arguments = signature.substr(signature.find_last_of('('));

      arguments.remove_suffix(1);
      signature = arguments;

      this->signature = std::string(signature);

      using FuncType = std::decay_t<Func>;
      using ArgsTuple = function_args_tuple<FuncType>;

      return [this, apply](const std::vector<std::string> &tokens) {
        if (tokens.size() != std::tuple_size<function_args_tuple<Func>>::value) {
          fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                     "[ERROR] Wrong number of arguments for command {}\n", tokens[0]);
          fmt::print(fg(fmt::color::red), "Expected {} arguments, got {}\n",
                     std::tuple_size<function_args_tuple<Func>>::value, tokens.size());
          return;
        }

        ArgsTuple args;
        parseTokensHelper(args, tokens,
                          std::make_index_sequence<std::tuple_size<ArgsTuple>::value>());
        apply(args);
      };
    }

    template <typename T> void parseToken(const std::string &token, T &value) {
      std::istringstream iss(token);
      iss >> value;
    }

    template <typename... Args>
    void parseTokens(std::tuple<Args...> &args, const std::vector<std::string> &tokens) {
      parseTokensHelper(args, tokens, std::make_index_sequence<sizeof...(Args)>());
    }

    template <typename Tuple, std::size_t... Is>
    void parseTokensHelper(Tuple &args, const std::vector<std::string> &tokens,
                           std::index_sequence<Is...>) {
      (parseToken(tokens[Is], std::get<Is>(args)), ...);
    }
  };
}  // namespace prepucio
