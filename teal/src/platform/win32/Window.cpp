#include "teal/Core.h"
#include "Win32Window.h"
#include "opengl/Win32OpenGLContext.h"
#include <dwmapi.h>
#include <queue>

namespace Teal
{
	Window::Window(const std::string& name)
	{
		_WindowData = new Win32Window(name, 1280, 720);
		InitializeRenderingContext();
	}

	Window::~Window()
	{
		delete ((Win32Window*)_WindowData);
	}

	void Window::OnUpdate()
	{
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			int status = TranslateMessage(&msg);

			DispatchMessage(&msg);
			std::queue<std::shared_ptr<Event>>& eventQueueP = ((Win32Window*)_WindowData)->GetEventQueue();
			while (!eventQueueP.empty())
			{
				std::shared_ptr<Event> e = eventQueueP.front();
				eventQueueP.pop();
				if (e->GetEventType() == EventType::WindowResize)
				{
					_RenderingContext->OnResize(*std::static_pointer_cast<WindowResizeEvent>(e));
				}
				_EventCallback(*e);
			}
		}
		SwapBuffers(((Win32Window*)_WindowData)->GetHDC());
	}

	void Window::InitializeRenderingContext()
	{
		_RenderingContext = std::unique_ptr<Win32OpenGLContext>(new Win32OpenGLContext(this));
	}


	void Window::SetVSync(bool enabled)
	{
		_RenderingContext->SetVsync(enabled);
	}

	bool Window::VsyncEnabled() const
	{
		return _RenderingContext->VsyncEnabled();
	}
}
