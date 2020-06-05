#pragma once

#include "teal/render/RenderingContext.h"
#include "teal/event/Event.h"

#include <glad/glad.h>

#define TOSTRING(x) #x

namespace Teal
{
	class TL_API OpenGLContext : public RenderingContext
	{
	public:
		static void DebugMessage(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei length, const GLchar* msg, const void* window);

		OpenGLContext(Window* window) : RenderingContext(window) {}

		virtual void EnableDbgMsg();

		virtual void OnResize(WindowResizeEvent& event) override 
		{
			glViewport(0, 0, event.GetWidth(), event.GetHeight());
		}
	};
}