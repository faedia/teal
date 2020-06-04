#pragma once

#include <string>
#include "teal/core/Logger.h"

namespace Teal
{
	class Shader
	{
	public:

		enum class Types
		{
			None = 0,
			Float, Float2, Float3, Float4
		};

		Shader(const std::string& vstr, const std::string& fstr) : _Vstr(vstr), _Fstr(fstr) {}
		virtual ~Shader() = default;
		virtual void Bind() = 0;

		static unsigned int TypeSize(Types type)
		{
			switch (type)
			{
			case Types::None:   return 0;
			case Types::Float:  return 4;
			case Types::Float2: return 4 * 2;
			case Types::Float3: return 4 * 3;
			case Types::Float4: return 4 * 4;
			default:
				TL_ASSERT (false, "Expected Valid Shader Data Type");
			}
		}
	protected:
		std::string _Vstr, _Fstr;
	};
}