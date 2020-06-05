#pragma once

#include <memory>
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "teal/Math.h"
#include "RenderCommand.h"
#include "Camera.h"

namespace Teal
{
	class Renderer
	{
	public:
		Renderer(const RenderCommand& rc ) : p_RenderingCommand(rc) {};
		virtual ~Renderer() = default;

		virtual void ClearColor(Math::Vector<float, 4> c) = 0;
		virtual void Clear() = 0;
		virtual void Clear(Math::Vector<float, 4> c) = 0;

		virtual void Begin() {}
		virtual void End() {}

		virtual void Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<Shader>& shader, const Camera& camera);

		virtual std::shared_ptr<Shader> NewShader(const std::string& vstr, const std::string& fstr) = 0;
		virtual std::shared_ptr<Shader> NewShader(const std::string& file) = 0;
		virtual std::shared_ptr<Buffers::Vertex> NewVertexBuffer(float* vertices, const unsigned int& size, const Buffers::Layout& layout) = 0;
		virtual std::shared_ptr<Buffers::Index> NewIndexBuffer(unsigned int* indices, const unsigned int& count) = 0;
		virtual std::shared_ptr<VertexArray> NewVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib) = 0;

	protected:
		RenderCommand p_RenderingCommand;
	};
}
