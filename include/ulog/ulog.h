#ifndef ULOG_H
#define ULOG_H

#include "DllExport/DllExport.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>

namespace ulog {
// set log filename and optional log folder name
// @return error if any error occurred
DllExport bool
setFileLogger(const std::string &filename = "log.txt",
              spdlog::level::level_enum level = spdlog::level::info,
              const std::string &folder = "log");

DllExport spdlog::logger &Get();

#define ulg ulog::Get()
} // namespace ulog

#endif // ULOG_H
