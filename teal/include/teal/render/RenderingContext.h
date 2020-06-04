#pragma once


#include "teal/core/Common.h"
#include "teal/core/Window.h"
#include "teal/event/AppEvent.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include <memory>

namespace Teal
{
	class Window;
	class RenderingContext
	{
	public:
		RenderingContext(Window* window) : _Window(window), _Vsync(true) {}
		virtual ~RenderingContext() = default;
		virtual void OnResize(WindowResizeEvent& event) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual inline bool VsyncEnabled() const { return _Vsync; };
		virtual void MakeCurrentContext() = 0;		
		virtual std::shared_ptr<Shader> NewShader(const std::string& vstr, const std::string& fstr) = 0;
		virtual std::shared_ptr<Shader> NewShader(const std::string& file) = 0;
		virtual std::shared_ptr<Buffers::Vertex> NewVertexBuffer(float* vertices, const unsigned int& size, const Buffers::Layout& layout) = 0;
		virtual std::shared_ptr<Buffers::Index> NewIndexBuffer(unsigned int* indices, const unsigned int& count) = 0;
		virtual std::shared_ptr<VertexArray> NewVertexArray(const std::vector<std::shared_ptr<Buffers::Vertex>>& vbVector, const std::shared_ptr<Buffers::Index>& ib) = 0;
	protected:
		Window* _Window;
		bool _Vsync;
	};
}

