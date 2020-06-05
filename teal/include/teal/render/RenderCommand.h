#pragma once

#include "RenderAPI.h"
#include "VertexArray.h"
#include "Shader.h"

namespace Teal
{
	class RenderCommand
	{
	public:
		RenderCommand(const std::shared_ptr <RenderAPI>& rapi) : _RenderAPI(rapi) {}
		void inline DrawIndexed(const std::shared_ptr<VertexArray>& va)
		{
			_RenderAPI->DrawIndexed(va);
		}

	private:
		std::shared_ptr <RenderAPI> _RenderAPI;
	};
}