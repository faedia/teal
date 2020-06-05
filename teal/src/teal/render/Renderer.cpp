#include "teal/render/Renderer.h"

namespace Teal
{
	void Renderer::Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<Shader>& shader, const Camera& camera)
	{
		shader->Bind();
		shader->UploadUniformMat4("camera", camera.GetProjectionView());
		va->Bind();
		p_RenderingCommand.DrawIndexed(va);
	};

}