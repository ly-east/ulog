# Ensure spdlog is installed alongside ulog so that
# find_dependency(spdlog) works from ulogConfig.cmake
set(SPDLOG_INSTALL ON CACHE BOOL "Generate the install target" FORCE)
add_subdirectory(spdlog)
