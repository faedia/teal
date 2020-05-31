#include "teal/core/Window.h"
#include "Win32Window.h"
#include "Win32OpenGLContext.h"

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
			std::shared_ptr<Event> currentEventP = ((Win32Window*)_WindowData)->GetCurrentEvent();
			if (currentEventP && currentEventP->GetEventType() != EventType::None)
			{
				if (currentEventP->GetEventType() == EventType::WindowResize)
				{
					_RenderingContext->OnResize(*(std::static_pointer_cast<WindowResizeEvent>(currentEventP)));
				}

				_EventCallback(*currentEventP);
				((Win32Window*)_WindowData)->ResetEvent();
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

	bool Window::VsyncEnabled()
	{
		return _RenderingContext->VsyncEnabled();
	}
}
