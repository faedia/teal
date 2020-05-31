#pragma once

#include "../core/Common.h"
#include "../core/Window.h"
#include "../Event.h"

namespace Teal
{
	class Window;
	class RenderingContext
	{
	public:
		RenderingContext(Window* window) : _Window(window), _Vsync(true) {}
		virtual ~RenderingContext() = default;
		virtual void OnResize(WindowResizeEvent& event) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual inline bool VsyncEnabled() { return _Vsync; };
	protected:
		Window* _Window;
		bool _Vsync;
	};
}

