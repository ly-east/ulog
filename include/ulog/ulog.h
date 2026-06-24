#ifndef ULOG_H
#define ULOG_H

#include "DllExport/DllExport.h"
#include <spdlog/fmt/fmt.h>
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

	// non-template: pre-formatted messages
	void trace(std::string_view msg);
	void debug(std::string_view msg);
	void info(std::string_view msg);
	void warn(std::string_view msg);
	void error(std::string_view msg);
	void critical(std::string_view msg);

	// template: fmt-style format strings  (e.g. ulg.info("hello {}", name))
	template <typename... Args>
	void trace(fmt::format_string<Args...> fmt_str, Args &&...args) {
		log(Level::Trace, fmt::format(fmt_str, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void debug(fmt::format_string<Args...> fmt_str, Args &&...args) {
		log(Level::Debug, fmt::format(fmt_str, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void info(fmt::format_string<Args...> fmt_str, Args &&...args) {
		log(Level::Info, fmt::format(fmt_str, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void warn(fmt::format_string<Args...> fmt_str, Args &&...args) {
		log(Level::Warn, fmt::format(fmt_str, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void error(fmt::format_string<Args...> fmt_str, Args &&...args) {
		log(Level::Error, fmt::format(fmt_str, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void critical(fmt::format_string<Args...> fmt_str, Args &&...args) {
		log(Level::Critical, fmt::format(fmt_str, std::forward<Args>(args)...));
	}

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
