#pragma once

#include <string>

namespace Teal
{
	class Shader
	{
	public:
		Shader(std::string vstr, std::string fstr) : _Vstr(vstr), _Fstr(fstr) {}
		virtual void Bind() = 0;
	protected:
		std::string _Vstr, _Fstr;
	};
}