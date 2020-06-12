#include "Win32Time.h"
#include "teal/core/Logger.h"

namespace Teal
{
	Win32DeltaTime::Win32DeltaTime()
	{
		LARGE_INTEGER time;
		BOOL status = QueryPerformanceFrequency(&_Freq);
		TL_ASSERT(status, "Should have got the frequency of the performance counter");
		status = QueryPerformanceCounter(&time);
		TL_ASSERT(status, "Should have got the time stamp");
		_PrevTime = (double)time.QuadPart / _Freq.QuadPart;
	}

	void Win32DeltaTime::CalculateDelta()
	{
		LARGE_INTEGER time;
		BOOL status = QueryPerformanceCounter(&time);
		TL_ASSERT(status, "Should have got the time stamp");
		double ftime = (double)time.QuadPart / _Freq.QuadPart;
		_DeltaTime = ftime - _PrevTime;
		_PrevTime = ftime;
	}
}