#pragma once

#include <vector>
#include <memory>
#include "Buffer.h"

namespace Teal
{
	class VertexArray
	{
	public:
		VertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib) : p_VbVector(vbVector), p_Ib(ib) {}
		virtual ~VertexArray() = default;
		virtual void Bind() = 0;
		virtual std::shared_ptr<Buffers::Index> GetIB() const { return p_Ib; }
	protected:
		//std::vector<std::shared_ptr<Buffers::OpenGLVertex>> p_VbVector;
		std::vector<std::shared_ptr<Buffers::Vertex>> p_VbVector;
		std::shared_ptr<Buffers::Index> p_Ib;
	};
}