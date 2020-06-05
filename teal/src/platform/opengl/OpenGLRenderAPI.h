#pragma once

#include "teal/render/RenderAPI.h"
#include <glad/glad.h>

namespace Teal
{
	class OpenGLRenderAPI : public RenderAPI
	{
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va)
		{
			glDrawElements(GL_TRIANGLES, va->GetIB()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	};
}