#include "teal/core/Window.h"
#include "Win32Window.h"
#include "Win32OpenGLContext.h"

#include "teal/core/Logger.h"
#include <gl/GL.h>

namespace Teal
{
	Window::Window(const std::string& name)
	{
		_WindowData = new Win32Window(name);
		InitializeRenderingContext();

		Logger::GetCoreLogger().Info((char*)glGetString(GL_VERSION));
	}

	Window::~Window()
	{
		delete ((Win32OpenGLContext*)_RenderingContext);
		delete ((Win32Window*)_WindowData);
	}

	void Window::OnUpdate()
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		SwapBuffers(((Win32Window*)_WindowData)->GetHDC());
	}

	void Window::InitializeRenderingContext()
	{
		_RenderingContext = new Win32OpenGLContext(this);
	}
}
