#pragma once

#include "../core/Window.h"

namespace Teal
{
	class Window;
	class RenderingContext
	{
	public:
		RenderingContext(Window* window) : _Window(window) {}
		virtual ~RenderingContext() = default;
	protected:
		Window* _Window;
	};
}

