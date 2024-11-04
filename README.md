# About ulog
A wrapper of `spdlog` to address issue caused by static variable among DLLs/EXEs.

Target spdlog version is `v1.14.1`.

# Usage

## Introduce to Your Project

It is recommended to add this repository to your project as a submodule and place it into `third-party` folder.

Get repository by git:

``` sh
git submodule add https://github.com/ly-east/ulog.git third-party/ulog
git submodule update --init --recursive
```

...then add to your project as a dependency in CMakeLists.txt:

``` cmake
target_link_libraries(<YOUR-PROJECT-NAME> ulog)
```

...and include header file `ulog.h` where you should write log.

``` cpp
#include "ulog.h"

ul::error("hello, {}", "there");  // "hello, there"
```

Usage of log functions is just same to spdlog. Only thing you should notice is to replace `spdlog` by `ul`.

## Demo Program

A simple program `tester` demostrating the basic usage of ulog is shipped with ulog, though it won't be built by default.

You may flip the switch(set to `ON`) of cmake variable `ULOG_ENABLE_TESTER` in root CMake file to build it.
