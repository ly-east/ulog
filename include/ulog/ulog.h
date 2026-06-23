#ifndef ULOG_H
#define ULOG_H

#include "DllExport/DllExport.h"
#include <memory>
#include <string>
#include <string_view>

namespace ulog {

enum class Level {
	Trace,
	Debug,
	Info,
	Warn,
	Error,
	Critical,
	Off,
};

class DllExport Logger {
public:
	void log(Level level, std::string_view msg);

	void trace(std::string_view msg);
	void debug(std::string_view msg);
	void info(std::string_view msg);
	void warn(std::string_view msg);
	void error(std::string_view msg);
	void critical(std::string_view msg);

	void setLevel(Level level);
	Level level() const;
	void flush();

	static Logger &Get();
	static bool setFileLogger(const std::string &filename = "log.txt",
	                          Level level = Level::Info,
	                          const std::string &folder = "log");

	Logger();
	~Logger();

	Logger(const Logger &) = delete;
	Logger &operator=(const Logger &) = delete;
	Logger(Logger &&) = delete;
	Logger &operator=(Logger &&) = delete;

private:
	struct Impl;
	std::unique_ptr<Impl> impl_;
};

} // namespace ulog

#define ulg ulog::Logger::Get()

#endif // ULOG_H
