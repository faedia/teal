#pragma once

#include "platform/opengl/OpenGLContext.h"
#include <Windows.h>

namespace Teal
{
	class TL_API Win32OpenGLContext : public OpenGLContext
	{
	public:
		Win32OpenGLContext(Window* window);
		~Win32OpenGLContext();

		virtual void SetVsync(bool enabled) override;

		virtual void MakeCurrentContext() override;
	private:
		PIXELFORMATDESCRIPTOR _Pfd;
		HGLRC _OpenGLCtx;
	};
}