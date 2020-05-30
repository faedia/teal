#include "Win32OpenGLContext.h"
#include "Win32Window.h"
#include <gl/GL.h>
#include "teal/core/Logger.h"

namespace Teal
{
	Win32OpenGLContext::Win32OpenGLContext(Window* window) : RenderingContext(window)
	{
		Win32Window* windowP = (Win32Window*)(_Window->GetWindowData());
		_Pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		int pixelFormat = ChoosePixelFormat(windowP->GetHDC(), &_Pfd);
		SetPixelFormat(windowP->GetHDC(), pixelFormat, &_Pfd);

		if (!(_OpenGLCtx = wglCreateContext(windowP->GetHDC())))
		{
			Logger::GetCoreLogger().Error("Unable create context");
		}
		if (!wglMakeCurrent(windowP->GetHDC(), _OpenGLCtx))
		{
			Logger::GetCoreLogger().Error("Unable to make current");
		}

		glViewport(0, 0, 1280, 720);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Win32OpenGLContext::~Win32OpenGLContext()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_OpenGLCtx);
	}
}