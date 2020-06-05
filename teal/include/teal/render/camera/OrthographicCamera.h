#pragma once

#include "Camera.h"

namespace Teal
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float l, float r, float t, float b, float n, float f)
		{
			float d[4][4] = {
				{2 / (r - l), 0, 0, -(r + l) / (r - l)},
				{0, 2 / (t - b), 0, -(t + b) / (t - b)},
				{0, 0, -2 / (f - n), -(f + n) / (f - n)},
				{0, 0, 0, 1}
			};
			p_Projection = d;
		}
	};
}