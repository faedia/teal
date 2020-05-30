#include "teal/core/Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define GETLOGGER(l) (std::static_pointer_cast<spdlog::logger>(l))

namespace Teal
{
	Logger Logger::_CoreLogger ("Teal");

	Logger::Logger(const char* name) : _LoggerP(spdlog::stdout_color_mt(name)) {}

	Logger::~Logger()
	{
		spdlog::drop(GETLOGGER(_LoggerP)->name());
	}

	void Logger::Init() {
		spdlog::set_pattern("%^%L [%T:%f] %-8!n: %v%$");
		spdlog::set_level(spdlog::level::trace);
	}

	void Logger::Trace(const char* fmt...) { GETLOGGER(this->_LoggerP)->trace(fmt); }
	void Logger::Debug(const char* fmt...) { GETLOGGER(this->_LoggerP)->debug(fmt); }
	void Logger::Info(const char* fmt...) { GETLOGGER(this->_LoggerP)->info(fmt); }
	void Logger::Warn(const char* fmt...) { GETLOGGER(this->_LoggerP)->warn(fmt); }
	void Logger::Error(const char* fmt...) { GETLOGGER(this->_LoggerP)->error(fmt); }
	void Logger::Critical(const char* fmt...) { GETLOGGER(this->_LoggerP)->critical(fmt); }
}