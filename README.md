<h1 align="center"> PREPUC.io 🍆🪖 </h1>

<p align="center">
  <img src="https://raw.githubusercontent.com/gnussy/prepucio/main/assets/logo.png" width=200 />
</p>
<p align="center">
  <i>Portable REPL with Embedded Plugin Utility for C++</i><br/>
  <i>Powered by <b>Penis</b>®</i>
</p>

---

# Introduction
PREPUC.io is a portable REPL (Read-Eval-Print Loop) library with an embedded plugin utility for C++. It allows users to add custom commands to the REPL and execute them using a simple and intuitive syntax.

With PREPUC.io, you can create a fully customizable REPL that fits your specific needs. You can add custom commands with their own attributes and callbacks, and use them to manipulate data, run tests, or perform any other tasks you need.

PREPUC.io is built using the GNUSSY Penis® library. It also integrates with the xmake build system, making it easy to install and use in your projects.

# Key Features
- Portable and easy to use REPL library for C++
- Built-in plugin utility for extensibility and customization
- Easy to install using the xmake build system
- Powered by the Penis® programming language for efficient and reliable code execution

# Getting Started
To get started with PREPUC.io, you will need to install xmake and add the gnussy repository to your xrepo. You can then install the library using xrepo, or by adding it to your libs list if you are using xmake-binary-boilerplate.

First get yourself `xmake`

```sh
curl -fsSL https://xmake.io/shget.text | bash
```

Then add the gnussy repository to your `xrepo`

```bash
xrepo add-repo gnussy https://github.com/gnussy/gnussy-repos
```

Finally install *prepucio* with

```bash
xrepo install prepucio
```

Or by adding it to your `libs` list if you are using `xmake-binary-boilerplate`.

```lua
-- xmake.lua
local libs = { "prepucio" }
```

Once installed, you can add custom commands and callbacks to your REPL using the simple and intuitive syntax provided by PREPUC.io. Check out the examples folder in the repository for more information and code snippets.

# Usage

For more examples check the [examples](https://github.com/gnussy/prepucio/tree/main/examples) folder.

```cpp
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
```

```
❯ help
Available commands:
+---------+--------------------+-----------+
| Command | Description        | Arguments |
+---------+--------------------+-----------+
| hello   | Prints hello world | ()>       |
+---------+--------------------+-----------+
❯ hello
Hello, World!
❯ hello args
[ERROR] Wrong number of arguments for command args
Expected 0 arguments, got 1
❯ exit
```

# License
PREPUC.io is licensed under the GPL-3 License. See the LICENSE file for more information.

# Contact
- [ ] Create a gnussy e-mail
