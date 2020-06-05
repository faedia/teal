#pragma once

#include "teal/render/Renderer.h"

namespace Teal
{
	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		virtual void ClearColor(Math::Vector<float, 4> c) override;
		virtual void Clear() override;
		virtual void Clear(Math::Vector<float, 4> c) override;

		virtual std::shared_ptr<Shader> NewShader(const std::string& vstr, const std::string& fstr) override;
		virtual std::shared_ptr<Shader> NewShader(const std::string& file) override;
		virtual std::shared_ptr<Buffers::Vertex> NewVertexBuffer(float* vertices, const unsigned int& size, const Buffers::Layout& layout) override;
		virtual std::shared_ptr<Buffers::Index> NewIndexBuffer(unsigned int* indices, const unsigned int& count) override;
		virtual std::shared_ptr<VertexArray> NewVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib) override;
	};
}