#pragma once
#include "Common.h"
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
		// This is a generic pointer to an interal class that has the implementation specific detail of the logger
		// This means that the users code should not be dependant on whatever logging library that is used and hides
		// all details from the end user.
		std::shared_ptr<void> _LoggerP;
		static Logger _CoreLogger;
	};
}
