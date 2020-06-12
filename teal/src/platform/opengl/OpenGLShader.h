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
		OpenGLShader(const std::string& name);
		virtual ~OpenGLShader() override;
		virtual void Bind() override;
		virtual void UploadUniformMat4(const std::string& name, const Math::Mat4f& mat) override;
		
		static std::unordered_map<GLenum, std::string> Preprocess(const std::string& src);
		static GLuint CompileShader(GLenum type, const std::string& str);
		static GLuint LinkShader(const std::vector<GLuint>& shaders);
	private:
		GLuint _Program;
	};
}