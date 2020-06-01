#pragma once

#include "teal/Render.h"
#include <Windows.h>

namespace Teal
{
	class TL_API Win32OpenGLContext : public RenderingContext
	{
	public:
		Win32OpenGLContext(Window* window);
		~Win32OpenGLContext();

		void OnResize(WindowResizeEvent& event) override;
		void SetVsync(bool enabled) override;

		virtual void MakeCurrentContext() override;
	private:
		PIXELFORMATDESCRIPTOR _Pfd;
		HGLRC _OpenGLCtx;
	};
}