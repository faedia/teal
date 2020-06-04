#pragma once

#include "OpenGLVertexArray.h"

namespace Teal
{

	GLint ST2Count(Shader::Types type)
	{
		switch (type)
		{
		case Teal::Shader::Types::None:
			return 0;
		case Teal::Shader::Types::Float:
			return 1;
		case Teal::Shader::Types::Float2:
			return 2;
		case Teal::Shader::Types::Float3:
			return 3;
		case Teal::Shader::Types::Float4:
			return 4;
		}
	}

	GLenum ST2BaseType(Shader::Types type)
	{
		switch (type)
		{
		case Teal::Shader::Types::None:
			return 0;
		case Teal::Shader::Types::Float:
			return GL_FLOAT;
		case Teal::Shader::Types::Float2:
			return GL_FLOAT;
		case Teal::Shader::Types::Float3:
			return GL_FLOAT;
		case Teal::Shader::Types::Float4:
			return GL_FLOAT;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib)
		: VertexArray(vbVector, ib)
	{
		glGenVertexArrays(1, &_VertexArrayId);
		glBindVertexArray(_VertexArrayId);

		p_Ib->Bind();

		GLuint index = 0;
		for (auto& vb : vbVector)
		{
			const Buffers::Layout& layout = vb->GetLayout();
			vb->Bind();
			for (auto& elem : layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, ST2Count(elem.GetType()), ST2BaseType(elem.GetType()), GL_FALSE, layout.GetStride(), (const void*)elem.GetOffset());
				++index;
			}
		}
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_VertexArrayId);
	}

	void OpenGLVertexArray::Bind() 
	{
		glBindVertexArray(_VertexArrayId);
	}
}