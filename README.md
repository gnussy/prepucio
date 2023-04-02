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

...

# Installation

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
