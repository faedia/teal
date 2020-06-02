#pragma once

#include "teal/render/RenderingContext.h"
#include "teal/event/Event.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Teal
{
	class TL_API OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(Window* window) : RenderingContext(window) {}
		virtual void OnResize(WindowResizeEvent& event) override 
		{
			glViewport(0, 0, event.GetWidth(), event.GetHeight());
		}

		virtual std::shared_ptr<Shader> NewShader(std::string vstr, std::string fstr) override { return std::make_shared<OpenGLShader>(OpenGLShader(vstr, fstr)); }
	private:
	};
}