#pragma once


#include "teal/core/Common.h"
#include "teal/core/Window.h"
#include "teal/event/AppEvent.h"
#include <memory>

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
		virtual inline bool VsyncEnabled() const { return _Vsync; };
		virtual void MakeCurrentContext() = 0;		

	protected:
		Window* _Window;
		bool _Vsync;
	};
}
