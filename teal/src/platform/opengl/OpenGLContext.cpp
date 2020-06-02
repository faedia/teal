#include "OpenGLContext.h"
#include "OpenGLShader.h"
#include "OpenGLBuffer.h"

namespace Teal
{
	std::shared_ptr<Shader> OpenGLContext::NewShader(const std::string& vstr, const std::string& fstr) 
	{
		return std::shared_ptr<OpenGLShader>(new OpenGLShader(vstr, fstr));
	}
	std::shared_ptr<Shader> OpenGLContext::NewShader(const std::string& file)
	{
		return std::shared_ptr<OpenGLShader>(nullptr);
	}


	std::shared_ptr<Buffers::Vertex> OpenGLContext::NewVertexBuffer(float* vertices, unsigned int size)
	{
		return std::shared_ptr<Buffers::OpenGLVertex>(new Buffers::OpenGLVertex(vertices, size));
	}
	std::shared_ptr<Buffers::Index> OpenGLContext::NewIndexBuffer(unsigned int* indices, unsigned int count)
	{
		return std::shared_ptr<Buffers::OpenGLIndex>(new Buffers::OpenGLIndex(indices, count));
	}

}