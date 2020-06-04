#pragma once

#include "teal/render/VertexArray.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Teal
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib);
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() override;
	private:
		GLuint _VertexArrayId;
	};
}