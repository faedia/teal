#include "teal/core/Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Teal
{
	Logger Logger::_CoreLogger ("Teal");

	Logger::Logger(const char* name)
	{
		p_Logger = spdlog::stdout_color_mt(name);
		p_Logger->set_level(spdlog::level::trace);
	}

	Logger::~Logger()
	{

	}

	void Logger::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		spdlog::set_level(spdlog::level::trace);
	}

	void Logger::Trace(const char* fmt...) { this->p_Logger->trace(fmt); }
	void Logger::Debug(const char* fmt...) { this->p_Logger->debug(fmt); }
	void Logger::Info(const char* fmt...) { this->p_Logger->info(fmt); }
	void Logger::Warn(const char* fmt...) { this->p_Logger->warn(fmt); }
	void Logger::Error(const char* fmt...) { this->p_Logger->error(fmt); }
	void Logger::Critical(const char* fmt...) { this->p_Logger->critical(fmt); }
}