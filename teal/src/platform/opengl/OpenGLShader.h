#pragma once

#include "teal/render/Shader.h"
#include <string>
#include <glad/glad.h>

namespace Teal
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string vstr, std::string fstr);

		virtual void Bind() override;
		
		void CompileShader(GLint shader, std::string str);
	private:
		GLuint _Program;
	};
}