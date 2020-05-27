#pragma once
#include "Common.h"
#include <spdlog/spdlog.h>
#include <memory>

namespace Teal
{
	class TL_API Logger
	{
	public:
		Logger(const char* name);
		~Logger();

		static Logger& GetCoreLogger() { return _CoreLogger; }

		static void Init();

		inline void Trace(const char* fmt...);
		inline void Debug(const char* fmt...);
		inline void Info(const char* fmt...);
		inline void Warn(const char* fmt...);
		inline void Error(const char* fmt...);
		inline void Critical(const char* fmt...);

	private:
		std::shared_ptr<spdlog::logger> p_Logger;
		static Logger _CoreLogger;
	};
}
