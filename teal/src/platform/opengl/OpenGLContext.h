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
		static void DebugMessage(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei length, const GLchar* msg, const void* window)
		{
			TL_ASSERT(sev != GL_DEBUG_SEVERITY_HIGH, msg)
			switch (sev)
			{
			case GL_DEBUG_SEVERITY_HIGH: 
				TL_CORE_ERROR(msg); break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				TL_CORE_WARN(msg); break;
			case GL_DEBUG_SEVERITY_LOW:
				TL_CORE_DEBUG(msg); break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				TL_CORE_TRACE(msg); break;
			}
		}

		OpenGLContext(Window* window) : RenderingContext(window) {}

		virtual void SetDbgMsg()
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(DebugMessage, _Window);
		}

		virtual void OnResize(WindowResizeEvent& event) override 
		{
			glViewport(0, 0, event.GetWidth(), event.GetHeight());
		}

		virtual std::shared_ptr<Shader> NewShader(const std::string& vstr, const std::string& fstr) override;
		virtual std::shared_ptr<Shader> NewShader(const std::string& file) override;
		virtual std::shared_ptr<Buffers::Vertex> NewVertexBuffer(float* vertices, const unsigned int& size, const Buffers::Layout& layout) override;
		virtual std::shared_ptr<Buffers::Index> NewIndexBuffer(unsigned int* vertices, const unsigned int& count) override;
		virtual std::shared_ptr<VertexArray> NewVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib) override;
	private:
	};
}