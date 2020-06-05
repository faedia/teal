#pragma once

#include "teal/Math.h"

namespace Teal
{
	class Camera
	{
	public:
		void Translate(const Math::Vector<float, 3>& x);
		void Scale(const Math::Vector<float, 3>& x);
		void Rotate(float angle, const Math::Vector<float, 3>& axis);

		Math::Mat4f GetProjectionView() const;
	protected:
		Math::Mat4f p_Projection;
		Math::Mat4f p_Transform{1.0f};
	};
}
