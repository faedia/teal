#pragma once
#include "Common.h"
#include <memory>
#include <spdlog/spdlog.h>
#define GETLOGGER(l) (std::static_pointer_cast<spdlog::logger>(l))

#define TL_CORE_TRACE(...) Teal::Logger::GetCoreLogger().Trace(__VA_ARGS__)
#define TL_CORE_DEBUG(...) Teal::Logger::GetCoreLogger().Debug(__VA_ARGS__)
#define TL_CORE_INFO(...) Teal::Logger::GetCoreLogger().Info(__VA_ARGS__)
#define TL_CORE_WARN(...) Teal::Logger::GetCoreLogger().Warn(__VA_ARGS__)
#define TL_CORE_ERROR(...) Teal::Logger::GetCoreLogger().Error(__VA_ARGS__)
#define TL_CORE_CRITICAL(...) Teal::Logger::GetCoreLogger().Critical(__VA_ARGS__)

namespace Teal
{
	class TL_API Logger
	{
	public:
		Logger(const char* name);
		~Logger();

		static Logger& GetCoreLogger() { return _CoreLogger; }

		static void Init();

		template<typename... Args>
		void Trace(const char* fmt, const Args&... args) { GETLOGGER(this->_LoggerP)->trace(fmt, args...); }
		template<typename... Args>
		void Debug(const char* fmt, const Args&... args) { GETLOGGER(this->_LoggerP)->debug(fmt, args...); }
		template<typename... Args>
		void Info(const char* fmt, const Args&... args) { GETLOGGER(this->_LoggerP)->info(fmt, args...); }
		template<typename... Args>
		void Warn(const char* fmt, const Args&... args) { GETLOGGER(this->_LoggerP)->warn(fmt, args...); }
		template<typename... Args>
		void Error(const char* fmt, const Args&... args) { GETLOGGER(this->_LoggerP)->error(fmt, args...); }
		template<typename... Args>
		inline void Critical(const char* fmt, const Args&... args) { GETLOGGER(this->_LoggerP)->critical(fmt, args...); }

		void Trace(const char* fmt) { GETLOGGER(this->_LoggerP)->trace(fmt); }
		void Debug(const char* fmt) { GETLOGGER(this->_LoggerP)->debug(fmt); }
		void Info(const char* fmt) { GETLOGGER(this->_LoggerP)->info(fmt); }
		void Warn(const char* fmt) { GETLOGGER(this->_LoggerP)->warn(fmt); }
		void Error(const char* fmt) { GETLOGGER(this->_LoggerP)->error(fmt); }
		void Critical(const char* fmt) { GETLOGGER(this->_LoggerP)->critical(fmt); }

	private:
		// This is a generic pointer to an internal class that has the implementation specific detail of the logger
		// This means that the users code should not be dependant on whatever logging library that is used and hides
		// all details from the end user.
		std::shared_ptr<void> _LoggerP;
		static Logger _CoreLogger;
	};
}
