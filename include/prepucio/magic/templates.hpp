#include <tuple>
#include <string_view>

template <typename Func> struct function_traits
    : public function_traits<decltype(&Func::operator())> {};

template <typename Ret, typename... Args> struct function_traits<Ret(Args...)> {
  using return_type = Ret;
  using args_tuple = std::tuple<Args...>;
};

template <typename Ret, typename... Args> struct function_traits<Ret (*)(Args...)>
    : public function_traits<Ret(Args...)> {};

template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret (Class::*)(Args...)> : public function_traits<Ret(Args...)> {};

template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret (Class::*)(Args...) const> : public function_traits<Ret(Args...)> {};

template <typename Func> using function_args_tuple = decltype(std::tuple_cat(
    std::declval<std::tuple<>>(), std::declval<typename function_traits<Func>::args_tuple>()));

// https://bitwizeshift.github.io/posts/2021/03/09/getting-an-unmangled-type-name-at-compile-time/
template <std::size_t... Idxs>
constexpr auto substring_as_array(std::string_view str, std::index_sequence<Idxs...>) {
  return std::array{str[Idxs]..., '\n'};
}

template <typename T> constexpr auto type_name_array() {
#if defined(__clang__)
  constexpr auto prefix = std::string_view{"[T = "};
  constexpr auto suffix = std::string_view{"]"};
  constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(__GNUC__)
  constexpr auto prefix = std::string_view{"with T = "};
  constexpr auto suffix = std::string_view{"]"};
  constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(_MSC_VER)
  constexpr auto prefix = std::string_view{"type_name_array<"};
  constexpr auto suffix = std::string_view{">(void)"};
  constexpr auto function = std::string_view{__FUNCSIG__};
#else
#  error Unsupported compiler
#endif

  constexpr auto start = function.find(prefix) + prefix.size();
  constexpr auto end = function.rfind(suffix);

  static_assert(start < end);

  constexpr auto name = function.substr(start, (end - start));
  return substring_as_array(name, std::make_index_sequence<name.size()>{});
}

template <typename T> struct type_name_holder {
  static inline constexpr auto value = type_name_array<T>();
};

template <typename T> constexpr auto type_name() -> std::string_view {
  constexpr auto &value = type_name_holder<T>::value;
  return std::string_view{value.data(), value.size()};
}

