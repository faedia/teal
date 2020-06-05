#pragma once

#include <memory>
#include "VertexArray.h"
#include "Shader.h"

namespace Teal
{
	class RenderAPI
	{
	public:
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va) = 0;
	};
}