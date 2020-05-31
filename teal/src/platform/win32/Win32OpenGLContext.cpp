#include "Win32OpenGLContext.h"
#include "Win32Window.h"
#include <glad/glad_wgl.h>
#include <glad/glad.h>

namespace Teal
{
	HMODULE libGl;

	GLADloadproc getProcAddress(const char* name)
	{
		const GLADloadproc proc = (GLADloadproc)wglGetProcAddress(name);
		if (proc)
			return proc;

		return (GLADloadproc)GetProcAddress(libGl, name);
	}

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
			32,                   // Number of bits for the depthbuffer
			0,                    // Number of bits for the stencilbuffer
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

		if (!libGl)
			libGl = LoadLibraryA("opengl32.dll");

		int status = gladLoadWGLLoader((GLADloadproc)getProcAddress, windowP->GetHDC());

		status = wglMakeCurrent(NULL, NULL);
		status = wglDeleteContext(_OpenGLCtx);

		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_FLAGS_ARB, 0,
			0
		};

		_OpenGLCtx = wglCreateContextAttribsARB(windowP->GetHDC(), 0, attribs);
		status = wglMakeCurrent(windowP->GetHDC(), _OpenGLCtx);
		TL_ASSERT(status && _OpenGLCtx, "OpenGl Context should initialize successfuly")

		status = gladLoadGLLoader((GLADloadproc)getProcAddress);
		TL_ASSERT(status, "OpenGl functions should be loaded")

		TL_CORE_INFO((char*)glGetString(GL_VERSION));

		wglSwapIntervalEXT(_Vsync);

		glViewport(0, 0, 1280, 720);
	}

	Win32OpenGLContext::~Win32OpenGLContext()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_OpenGLCtx);
	}

	void Win32OpenGLContext::OnResize(WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
	}	
	
	void Win32OpenGLContext::SetVsync(bool enabled)
	{
		_Vsync = enabled;
		wglSwapIntervalEXT(_Vsync);
	}
}