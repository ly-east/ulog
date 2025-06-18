cmake_minimum_required(VERSION 3.15.0)

# ref: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
if (POLICY CMP0091)
cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

# ===================================================================
# start ulog project

project(ulog VERSION 0.5.0 LANGUAGES CXX)

# ===================================================================
# compiler config

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif(MSVC)

# ===================================================================
# spdlog

add_subdirectory(third-party)

# ===================================================================
# ulog dynamic link library

add_library(ulog SHARED lib/ulog.cpp)

target_compile_definitions(ulog PUBLIC ULOG_DLL=1)
target_include_directories(ulog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ulog
  spdlog
)

install(TARGETS ulog)

# ===================================================================
# tester executable

set(ULOG_ENABLE_TESTER OFF)

if (ULOG_ENABLE_TESTER)
  add_executable(tester lib/tester.cpp)
  target_include_directories(tester PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

  target_link_libraries(tester
    ulog
  )

  install(TARGETS tester)
endif(ULOG_ENABLE_TESTER)
