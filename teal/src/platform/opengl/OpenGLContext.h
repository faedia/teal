#pragma once

#include "teal/render/RenderingContext.h"
#include "teal/event/Event.h"

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

		virtual std::shared_ptr<Shader> NewShader(const std::string& vstr, const std::string& fstr) override;
		virtual std::shared_ptr<Shader> NewShader(const std::string& file) override;
		virtual std::shared_ptr<Buffers::Vertex> NewVertexBuffer(float* vertices, unsigned int size) override;
		virtual std::shared_ptr<Buffers::Index> NewIndexBuffer(unsigned int* vertices, unsigned int count) override;
	private:
	};
}