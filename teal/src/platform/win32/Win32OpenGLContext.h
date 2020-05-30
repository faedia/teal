#pragma once

#include "teal/render/RenderingContext.h"
#include <Windows.h>

namespace Teal
{
	class TL_API Win32OpenGLContext : public RenderingContext
	{
	public:
		Win32OpenGLContext(Window* window);
		~Win32OpenGLContext();
	private:
		PIXELFORMATDESCRIPTOR _Pfd;
		HGLRC _OpenGLCtx;
	};
}