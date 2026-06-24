cmake_minimum_required(VERSION 3.15.0)

# ref: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
if (POLICY CMP0091)
cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

# ===================================================================
# start ulog project

project(ulog VERSION 0.5.0 LANGUAGES CXX)

# Version

configure_file(
  ${CMAKE_SOURCE_DIR}/resource/version/Version.h.in
  ${CMAKE_SOURCE_DIR}/resource/version/Version.h
  @ONLY
)

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

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_subdirectory(third-party)

# ===================================================================
# ulog dynamic link library

add_library(ulog SHARED lib/ulog.cpp)

target_compile_definitions(ulog PRIVATE ULOG_DLL=1)
target_include_directories(ulog PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/spdlog/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(ulog PRIVATE spdlog)

target_sources(ulog PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/resource/ulog.rc)

# Install public headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install bundled fmt headers (needed by ulog.h for inline template methods)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/third-party/spdlog/include/spdlog/fmt/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/spdlog/fmt)

# spdlog/fmt/fmt.h includes <spdlog/tweakme.h> — install just that header
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/third-party/spdlog/include/spdlog/tweakme.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/spdlog)

# Install ulog target with export
install(TARGETS ulog EXPORT ulogTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install the export targets file
install(EXPORT ulogTargets
  FILE ulogTargets.cmake
  NAMESPACE ulog::
  DESTINATION cmake/ulog
)

# Generate package version file
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/ulogConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

# Generate package config file from template
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ulogConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/ulogConfig.cmake
  INSTALL_DESTINATION cmake/ulog
)

# Install package config files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/ulogConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/ulogConfigVersion.cmake
  DESTINATION cmake/ulog
)

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
