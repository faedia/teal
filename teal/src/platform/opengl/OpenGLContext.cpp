#include "OpenGLContext.h"
#include "OpenGLShader.h"
#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"

namespace Teal
{
	void OpenGLContext::DebugMessage(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei length, const GLchar* msg, const void* window)
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
				//TL_CORE_TRACE(msg); 
				break;
			}
	}


	void OpenGLContext::EnableDbgMsg()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugMessage, _Window);
	}
}