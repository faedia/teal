#include "OpenGLShader.h"
#include "OpenGLContext.h"
#include "teal/core/Logger.h"

#include <fstream>
#include <streambuf>

namespace Teal
{
	static GLenum TypeStrToEnum(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "pixel")
			return GL_FRAGMENT_SHADER;

		TL_ASSERT(false, "Expected know shader type");
	}

	OpenGLShader::OpenGLShader(const std::string& vstr, const std::string& fstr)
	{
		GLuint vshader = CompileShader(GL_VERTEX_SHADER, vstr);
		GLuint fshader = CompileShader(GL_FRAGMENT_SHADER, fstr);
		_Program = LinkShader({ vshader, fshader });
	}

	OpenGLShader::OpenGLShader(const std::string& file)
	{
		std::ifstream f(file);
		std::string src;

		f.seekg(0, std::ios::end);
		src.reserve(f.tellg());
		f.seekg(0, std::ios::beg);
		src.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());

		auto map = Preprocess(src);
		std::vector<GLuint> shaders;
		for (auto item : map)
			shaders.push_back(CompileShader(item.first, item.second));

		_Program = LinkShader(shaders);
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

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& src)
	{
		std::unordered_map<GLenum, std::string> map;

		const std::string TokType = "#type";
		size_t pos = src.find(TokType, 0);
		while (pos != std::string::npos)
		{
			pos += TokType.length();
			pos = src.find_first_not_of(" ", pos);
			size_t end = src.find_first_not_of("abcdefghijklmnopqrstuvwxyz", pos);
			std::string type = src.substr(pos, end - pos);
			pos = src.find_first_not_of(" \r\n\t", end);
			end = src.find(TokType, pos);
			std::string subsrc = src.substr(pos, end - pos);
			map[TypeStrToEnum(type)] = subsrc;
			pos = end;
		}

		return map;
	}

	GLuint OpenGLShader::CompileShader(GLenum type, const std::string& str)
	{
		const GLchar* src = (const GLchar*)str.c_str();
		GLuint shader = glCreateShader(type);

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
			TL_ASSERT(false, "Expected successful compilation");
			return 0;
		}
		return shader;
	}

	GLuint OpenGLShader::LinkShader(const std::vector<GLuint>& shaders)
	{
		GLuint program = glCreateProgram();
		for (auto shader : shaders)
			glAttachShader(program, shader);

		glLinkProgram(program);
		GLint link_status;
		glGetProgramiv(program, GL_LINK_STATUS, &link_status);
		if (link_status == GL_FALSE)
		{
			GLint log_length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
			std::vector<GLchar> info_log_string(log_length);
			glGetProgramInfoLog(program, log_length, &log_length, &info_log_string[0]);
			TL_CORE_ERROR("{0}", info_log_string.data());
			TL_ASSERT(false, "Expected successful shader link");

			glDeleteProgram(program);
			for (auto shader : shaders)
				glDeleteShader(shader);
			return 0;
		}

		for (auto shader : shaders)
			glDetachShader(program, shader);

		return program;
	}

}