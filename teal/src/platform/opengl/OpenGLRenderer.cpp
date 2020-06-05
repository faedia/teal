#include "OpenGLRenderer.h"
#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Teal
{

	OpenGLRenderer::OpenGLRenderer() 
		: Renderer(RenderCommand(std::shared_ptr<OpenGLRenderAPI>(new OpenGLRenderAPI())))
	{

	}

	void OpenGLRenderer::ClearColor(Math::Vector<float, 4> c)
	{
		glClearColor(c.r, c.g, c.b, c.a);
	}
	void OpenGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OpenGLRenderer::Clear(Math::Vector<float, 4> c)
	{
		ClearColor(c);
		Clear();
	}

	std::shared_ptr<Shader> OpenGLRenderer::NewShader(const std::string& vstr, const std::string& fstr)
	{
		return std::shared_ptr<OpenGLShader>(new OpenGLShader(vstr, fstr));
	}
	
	std::shared_ptr<Shader> OpenGLRenderer::NewShader(const std::string& file)
	{
		return std::shared_ptr<OpenGLShader>(nullptr);
	}

	std::shared_ptr<Buffers::Vertex> OpenGLRenderer::NewVertexBuffer(float* vertices, const unsigned int& size, const Buffers::Layout& layout)
	{
		return std::shared_ptr<Buffers::OpenGLVertex>(new Buffers::OpenGLVertex(vertices, size, layout));
	}
	
	std::shared_ptr<Buffers::Index> OpenGLRenderer::NewIndexBuffer(unsigned int* indices, const unsigned int& count)
	{
		return std::shared_ptr<Buffers::OpenGLIndex>(new Buffers::OpenGLIndex(indices, count));
	}
	
	std::shared_ptr<VertexArray> OpenGLRenderer::NewVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib)
	{
		return std::shared_ptr<OpenGLVertexArray>(new OpenGLVertexArray(vbVector, ib));
	}

}