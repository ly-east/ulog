#ifndef ULOG_H
#define ULOG_H

#include "DllExport.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>

namespace ulog {
// set log filename and optional log folder name
// @return error if any error occurred
DllExport bool setFileLogger(const std::string &filename = "log.txt",
                             const std::string &folder = "log");
DllExport spdlog::logger &Get();

#define ul ulog::Get()
} // namespace ulog

#endif // ULOG_H
