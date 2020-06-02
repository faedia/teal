#pragma once

#include "teal/render/Buffer.h"
#include <glad/glad.h>

namespace Teal
{
	namespace Buffers
	{
		class OpenGLVertex : public Vertex
		{
		public:
			OpenGLVertex(float* vertices, unsigned int size)
			{
				glCreateBuffers(1, &_BufferId);
				glBindBuffer(GL_ARRAY_BUFFER, _BufferId);
				glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			}

			virtual ~OpenGLVertex()
			{
				glDeleteBuffers(1, &_BufferId);
			}

			virtual void Bind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, _BufferId);
			}
		private:
			GLuint _BufferId;
		};

		class OpenGLIndex : public Index
		{
		public:			
			OpenGLIndex(unsigned int* indices, unsigned int count) : _Count(count)
			{
				glCreateBuffers(1, &_BufferId);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _BufferId);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
			}

			virtual ~OpenGLIndex()
			{
				glDeleteBuffers(1, &_BufferId);
			}

			virtual void Bind()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _BufferId);
			}

			virtual unsigned int GetCount() override { return _Count; };
		private:
			GLuint _BufferId;
			unsigned int _Count;
		};
	}
}
