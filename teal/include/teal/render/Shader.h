#pragma once

#include <string>
#include "teal/core/Logger.h"
#include "teal/math/Matrix.h"

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

		virtual ~Shader() = default;
		virtual void Bind() = 0;
		virtual void UploadUniformMat4(const std::string& name, const Math::Mat4f& mat) = 0;

		static inline unsigned int TypeSize(Types type)
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
	};
}