#include "OpenGLShader.h"
#include "OpenGLContext.h"
#include "teal/core/Logger.h"

namespace Teal
{
	OpenGLShader::OpenGLShader(const std::string& vstr, const std::string& fstr) : Shader(vstr, fstr)
	{
		GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
		CompileShader(vshader, _Vstr);

		GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
		CompileShader(fshader, _Fstr);

		_Program = glCreateProgram();
		glAttachShader(_Program, vshader);
		glAttachShader(_Program, fshader);

		glLinkProgram(_Program);
		GLint link_status;
		glGetProgramiv(_Program, GL_LINK_STATUS, &link_status);
		if (link_status == GL_FALSE)
		{
			GLint log_length;
			glGetProgramiv(_Program, GL_INFO_LOG_LENGTH, &log_length);
			std::vector<GLchar> info_log_string(log_length);
			glGetProgramInfoLog(_Program, log_length, &log_length, &info_log_string[0]);
			TL_CORE_ERROR("{0}", info_log_string.data());
			TL_ASSERT(false, "Failed to link shader program!");

			glDeleteProgram(_Program);
			glDeleteShader(vshader);
			glDeleteShader(fshader);
			return;
		}

		glDetachShader(_Program, vshader);
		glDetachShader(_Program, fshader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_Program);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(_Program);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const Math::Mat4f& mat)
	{
		GLuint loc = glGetUniformLocation(_Program, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_TRUE, (GLfloat*)mat.data);
	}

	void OpenGLShader::CompileShader(GLint shader, std::string str)
	{
		const GLchar* src = (const GLchar*)str.c_str();

		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		GLint compile_status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
		{
			GLint log_length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
			std::vector<GLchar> info_log_string(log_length);
			glGetShaderInfoLog(shader, log_length, &log_length, &info_log_string[0]);
			TL_CORE_ERROR("{0}", info_log_string.data());
			TL_ASSERT(false, "Failed to compile shader!");
		}
	}

}