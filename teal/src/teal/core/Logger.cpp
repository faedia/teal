#include "teal/core/Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


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
}