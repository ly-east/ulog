#ifndef ULOG_H
#define ULOG_H

#include "DllExport.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>

namespace ulog {
DllExport bool setFileLogger(const std::string &filename = "log.txt");
DllExport spdlog::logger &Get();

#define ul ulog::Get()
} // namespace ulog

#endif // ULOG_H
