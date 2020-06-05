#pragma once

#include "teal/render/Shader.h"
#include <string>
#include <glad/glad.h>

namespace Teal
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vstr, const std::string& fstr);
		virtual ~OpenGLShader() override;
		virtual void Bind() override;
		virtual void UploadUniformMat4(const std::string& name, const Math::Mat4f& mat) override;
		
		void CompileShader(GLint shader, std::string str);
	private:
		GLuint _Program;
	};
}