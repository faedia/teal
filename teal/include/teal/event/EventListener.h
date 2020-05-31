#pragma once

#include "teal/core/Common.h"

namespace Teal
{
	class TL_API EventListener
	{
	public:
		virtual ~EventListener() {};
		virtual void onEvent(Event& event) = 0;
	};
}
