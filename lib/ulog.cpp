#include "ulog/ulog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"
#include <cassert>
#include <filesystem>
#include <string>

namespace ulog {

// ---------------------------------------------------------------------------
// Level conversion helpers
// ---------------------------------------------------------------------------

static spdlog::level::level_enum toSpdlogLevel(Level level) {
	switch (level) {
	case Level::Trace:
		return spdlog::level::trace;
	case Level::Debug:
		return spdlog::level::debug;
	case Level::Info:
		return spdlog::level::info;
	case Level::Warn:
		return spdlog::level::warn;
	case Level::Error:
		return spdlog::level::err;
	case Level::Critical:
		return spdlog::level::critical;
	case Level::Off:
		return spdlog::level::off;
	}
	return spdlog::level::info;
}

static Level fromSpdlogLevel(spdlog::level::level_enum lvl) {
	switch (lvl) {
	case spdlog::level::trace:
		return Level::Trace;
	case spdlog::level::debug:
		return Level::Debug;
	case spdlog::level::info:
		return Level::Info;
	case spdlog::level::warn:
		return Level::Warn;
	case spdlog::level::err:
		return Level::Error;
	case spdlog::level::critical:
		return Level::Critical;
	case spdlog::level::off:
		return Level::Off;
	}
	return Level::Info;
}

// ---------------------------------------------------------------------------
// Logger PImpl
// ---------------------------------------------------------------------------

struct Logger::Impl {
	std::shared_ptr<spdlog::logger> spdlogger;
};

Logger::Logger() : impl_(std::make_unique<Impl>()) {}

Logger::~Logger() = default;

void Logger::log(Level level, std::string_view msg) {
	if (impl_->spdlogger) {
		impl_->spdlogger->log(toSpdlogLevel(level), std::string{msg});
	}
}

void Logger::trace(std::string_view msg) { log(Level::Trace, msg); }

void Logger::debug(std::string_view msg) { log(Level::Debug, msg); }

void Logger::info(std::string_view msg) { log(Level::Info, msg); }

void Logger::warn(std::string_view msg) { log(Level::Warn, msg); }

void Logger::error(std::string_view msg) { log(Level::Error, msg); }

void Logger::critical(std::string_view msg) { log(Level::Critical, msg); }

void Logger::setLevel(Level level) {
	if (impl_->spdlogger) {
		impl_->spdlogger->set_level(toSpdlogLevel(level));
	}
}

Level Logger::level() const {
	if (impl_->spdlogger) {
		return fromSpdlogLevel(impl_->spdlogger->level());
	}
	return Level::Info;
}

void Logger::flush() {
	if (impl_->spdlogger) {
		impl_->spdlogger->flush();
	}
}

// ---------------------------------------------------------------------------
// Global instance
// ---------------------------------------------------------------------------

static Logger gLogger;

Logger &Logger::Get() { return gLogger; }

bool Logger::setFileLogger(const std::string &filename, Level level,
                           const std::string &folder) {
	std::filesystem::path log_path{std::filesystem::current_path()};

	if (!folder.empty()) {
		log_path.append(folder);
		if (!std::filesystem::exists(log_path))
			std::filesystem::create_directories(log_path);
	}

	log_path.append(filename);

	try {
		// create a file rotating logger with 512KB size max and 3 rotated files
		auto logger = spdlog::rotating_logger_mt("logger", log_path.string(),
		                                         1024 * 512, 3);

		// [Y-M-D H-M-S.e][thread ID][log level]content
		logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%t][%l]%v");
		logger->set_level(toSpdlogLevel(level));
		logger->flush_on(spdlog::level::err);

		spdlog::set_default_logger(logger);

		// wire the global wrapper to the newly created spdlog logger
		gLogger.impl_->spdlogger = logger;
	} catch (const spdlog::spdlog_ex &ex) {
		spdlog::error("Log init failed: {}", ex.what());
		return false;
	}

	return true;
}

} // namespace ulog
