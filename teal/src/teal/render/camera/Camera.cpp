#include "teal/render/camera/Camera.h"

namespace Teal
{
	void Camera::Translate(const Math::Vector<float, 3>& x)
	{
		p_Transform = Math::Mat4f::translate(p_Transform, x);
	}

	void Camera::Scale(const Math::Vector<float, 3>& x)
	{
		p_Transform = Math::Mat4f::scale(p_Transform, x);
	}

	void Camera::Rotate(float angle, const Math::Vector<float, 3>& axis)
	{
		p_Transform = Math::Mat4f::rotate(p_Transform, angle, axis);
	}

	Math::Mat4f Camera::GetProjectionView() const
	{
		return p_Projection * Math::Mat4f::inverse(p_Transform);
	}
}