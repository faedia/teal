#pragma once

#include "teal/core/Time.h"
#include <Windows.h>

namespace Teal
{
	class Win32DeltaTime : public DeltaTime
	{
	public:
		Win32DeltaTime();
		virtual void CalculateDelta() override;
	private:
		LARGE_INTEGER _Freq;
	};
}