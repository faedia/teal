#pragma once

#include "Vector.h"
#include <cmath>

#define M_PI 3.14159265358979323846

namespace Teal
{
	namespace Math
	{
		template<typename T, unsigned int X, unsigned int Y>
		class Matrix;

		typedef Matrix<float, 4, 4> Mat4f;

		template<typename T>
		class Matrix<T, 4, 4>
		{
		public:
			Matrix<T, 4, 4>() = default;
			Matrix<T, 4, 4>(T d[4][4])
			{
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						data[i][j] = d[i][j];
					}
				}
			}

			Matrix<T, 4, 4>(T n)
			{
				x11 = n;
				x22 = n;
				x33 = n;
				x44 = n;
			}

			union
			{
				struct { Vector<T, 4> x1, x2, x3, x4; };
				struct {
					T
						x11, x12, x13, x14,
						x21, x22, x23, x24,
						x31, x32, x33, x34,
						x41, x42, x43, x44;
				};
				T data[4][4] = {};
			};

			static Matrix<T, 4, 4> mul(const Matrix<T, 4, 4>& a, const Matrix<T, 4, 4>& b)
			{
				Matrix<T, 4, 4> x = {};
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						for (int r = 0; r < 4; ++r)
						{
							x.data[i][j] += a.data[i][r] * b.data[r][j];
						}
					}
				}
				return x;
			}

			static Matrix<T, 4, 4> mul(const T& c, const Matrix<T, 4, 4>& a)
			{
				Matrix<T, 4, 4> x;
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						x.data[i][j] = a.data[i][j] * c;
					}
				}
				return x;
			}

			static Matrix<T, 4, 4> translate(const Matrix<T, 4, 4>& a, const Math::Vector<float, 3>& t)
			{
				Matrix<T, 4, 4> x = a;
				x.x14 += t.data[0];
				x.x24 += t.data[1];
				x.x34 += t.data[2];
				return x;
			}

			static Matrix<T, 4, 4> scale(const Matrix<T, 4, 4>& a, const Math::Vector<float, 3>& s)
			{
				Matrix<T, 4, 4> x = a;
				x.x11 *= s.data[0];
				x.x22 *= s.data[1];
				x.x33 *= s.data[2];
				return x;
			}


			static Matrix<T, 4, 4> rotate(const Matrix<T, 4, 4>& m, const T& angle, const Math::Vector<float, 3>& axis)
			{
				float a = angle * static_cast<T>(M_PI) / static_cast<T>(180.0f);
				float c = std::cos(a);
				float s = std::sin(a);
				float x = axis.x;
				float y = axis.y;
				float z = axis.z;
				Math::Mat4f r{ 1.0f };
				r.x11 = c + x * x * (1 - c);
				r.x12 = x * y * (1 - c) - z * s;
				r.x13 = x * z * (1 - c) + y * s;
				r.x21 = y * x * (1 - c) + z * s;
				r.x22 = c + y * y * (1 - c);
				r.x23 = y * z * (1 - c) - x * s;
				r.x31 = z * x * (1 - c) - y * s;
				r.x32 = z * y * (1 - c) + x * s;
				r.x33 = c + z * z * (1 - c);
				return m * r;
			}

			static Matrix<T, 4, 4> transpose(const Matrix<T, 4, 4>& a)
			{
				Matrix<T, 4, 4> x;
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						x.data[i][j] = a.data[j][i];
					}
				}
				return x;
			}

			static T determinant(const Matrix<T, 4, 4>& a)
			{
				Matrix<T, 4, 4> c;
				c.x11 = +(a.x22 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x32 * (a.x23 * a.x44 - a.x24 * a.x43) + a.x42 * (a.x23 * a.x34 - a.x24 * a.x33));
				c.x21 = -(a.x12 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x32 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x42 * (a.x13 * a.x34 - a.x14 * a.x33));
				c.x31 = +(a.x12 * (a.x23 * a.x44 - a.x24 * a.x43) - a.x22 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x42 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x41 = -(a.x12 * (a.x23 * a.x34 - a.x24 * a.x33) - a.x22 * (a.x13 * a.x34 - a.x14 * a.x33) + a.x32 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x12 = -(a.x21 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x31 * (a.x23 * a.x44 - a.x24 * a.x43) + a.x41 * (a.x23 * a.x34 - a.x24 * a.x33));
				c.x22 = +(a.x11 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x31 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x41 * (a.x13 * a.x34 - a.x14 * a.x33));
				c.x32 = -(a.x11 * (a.x23 * a.x44 - a.x24 * a.x43) - a.x21 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x41 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x42 = +(a.x11 * (a.x23 * a.x34 - a.x24 * a.x33) - a.x21 * (a.x13 * a.x34 - a.x14 * a.x33) + a.x31 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x13 = +(a.x21 * (a.x32 * a.x44 - a.x34 * a.x42) - a.x31 * (a.x22 * a.x44 - a.x24 * a.x42) + a.x41 * (a.x22 * a.x34 - a.x24 * a.x32));
				c.x23 = -(a.x11 * (a.x32 * a.x44 - a.x34 * a.x42) - a.x31 * (a.x12 * a.x44 - a.x14 * a.x42) + a.x41 * (a.x12 * a.x34 - a.x14 * a.x32));
				c.x33 = +(a.x11 * (a.x22 * a.x44 - a.x24 * a.x42) - a.x21 * (a.x12 * a.x44 - a.x14 * a.x42) + a.x41 * (a.x12 * a.x24 - a.x14 * a.x22));
				c.x43 = -(a.x11 * (a.x22 * a.x34 - a.x24 * a.x32) - a.x21 * (a.x12 * a.x34 - a.x14 * a.x32) + a.x31 * (a.x12 * a.x24 - a.x14 * a.x22));
				c.x14 = -(a.x21 * (a.x32 * a.x43 - a.x33 * a.x42) - a.x31 * (a.x22 * a.x43 - a.x23 * a.x42) + a.x41 * (a.x22 * a.x33 - a.x23 * a.x32));
				c.x24 = +(a.x11 * (a.x32 * a.x43 - a.x33 * a.x42) - a.x31 * (a.x12 * a.x43 - a.x13 * a.x42) + a.x41 * (a.x12 * a.x33 - a.x13 * a.x32));
				c.x34 = -(a.x11 * (a.x22 * a.x43 - a.x23 * a.x42) - a.x21 * (a.x12 * a.x43 - a.x13 * a.x42) + a.x41 * (a.x12 * a.x23 - a.x13 * a.x22));
				c.x44 = +(a.x11 * (a.x22 * a.x33 - a.x23 * a.x32) - a.x21 * (a.x12 * a.x33 - a.x13 * a.x32) + a.x31 * (a.x12 * a.x23 - a.x13 * a.x22));
				return (a.x11 * c.x11) + (a.x12 * c.x12) + (a.x13 * c.x13) + (a.x14 * c.x14);
			}

			static Matrix<T, 4, 4> inverse(const Matrix<T, 4, 4>& a)
			{
				Matrix<T, 4, 4> c;
				c.x11 = +(a.x22 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x32 * (a.x23 * a.x44 - a.x24 * a.x43) + a.x42 * (a.x23 * a.x34 - a.x24 * a.x33));
				c.x21 = -(a.x12 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x32 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x42 * (a.x13 * a.x34 - a.x14 * a.x33));
				c.x31 = +(a.x12 * (a.x23 * a.x44 - a.x24 * a.x43) - a.x22 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x42 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x41 = -(a.x12 * (a.x23 * a.x34 - a.x24 * a.x33) - a.x22 * (a.x13 * a.x34 - a.x14 * a.x33) + a.x32 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x12 = -(a.x21 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x31 * (a.x23 * a.x44 - a.x24 * a.x43) + a.x41 * (a.x23 * a.x34 - a.x24 * a.x33));
				c.x22 = +(a.x11 * (a.x33 * a.x44 - a.x34 * a.x43) - a.x31 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x41 * (a.x13 * a.x34 - a.x14 * a.x33));
				c.x32 = -(a.x11 * (a.x23 * a.x44 - a.x24 * a.x43) - a.x21 * (a.x13 * a.x44 - a.x14 * a.x43) + a.x41 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x42 = +(a.x11 * (a.x23 * a.x34 - a.x24 * a.x33) - a.x21 * (a.x13 * a.x34 - a.x14 * a.x33) + a.x31 * (a.x13 * a.x24 - a.x14 * a.x23));
				c.x13 = +(a.x21 * (a.x32 * a.x44 - a.x34 * a.x42) - a.x31 * (a.x22 * a.x44 - a.x24 * a.x42) + a.x41 * (a.x22 * a.x34 - a.x24 * a.x32));
				c.x23 = -(a.x11 * (a.x32 * a.x44 - a.x34 * a.x42) - a.x31 * (a.x12 * a.x44 - a.x14 * a.x42) + a.x41 * (a.x12 * a.x34 - a.x14 * a.x32));
				c.x33 = +(a.x11 * (a.x22 * a.x44 - a.x24 * a.x42) - a.x21 * (a.x12 * a.x44 - a.x14 * a.x42) + a.x41 * (a.x12 * a.x24 - a.x14 * a.x22));
				c.x43 = -(a.x11 * (a.x22 * a.x34 - a.x24 * a.x32) - a.x21 * (a.x12 * a.x34 - a.x14 * a.x32) + a.x31 * (a.x12 * a.x24 - a.x14 * a.x22));
				c.x14 = -(a.x21 * (a.x32 * a.x43 - a.x33 * a.x42) - a.x31 * (a.x22 * a.x43 - a.x23 * a.x42) + a.x41 * (a.x22 * a.x33 - a.x23 * a.x32));
				c.x24 = +(a.x11 * (a.x32 * a.x43 - a.x33 * a.x42) - a.x31 * (a.x12 * a.x43 - a.x13 * a.x42) + a.x41 * (a.x12 * a.x33 - a.x13 * a.x32));
				c.x34 = -(a.x11 * (a.x22 * a.x43 - a.x23 * a.x42) - a.x21 * (a.x12 * a.x43 - a.x13 * a.x42) + a.x41 * (a.x12 * a.x23 - a.x13 * a.x22));
				c.x44 = +(a.x11 * (a.x22 * a.x33 - a.x23 * a.x32) - a.x21 * (a.x12 * a.x33 - a.x13 * a.x32) + a.x31 * (a.x12 * a.x23 - a.x13 * a.x22));
				T det = ((a.x11 * c.x11) + (a.x12 * c.x12) + (a.x13 * c.x13) + (a.x14 * c.x14));
				return mul((static_cast<T>(1) / det), transpose(c));
			}

			Matrix<T, 4, 4> mul(const Matrix<T, 4, 4>& a) const
			{
				return mul(*this, a);
			}

			Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4>& a) const
			{
				return this->mul(a);
			}
		};

		template <typename T>
		Matrix<T, 4, 4> operator*(const T& c, const Matrix<T, 4, 4>& a)
		{
			return Matrix<T, 4, 4>::mul(c, a);
		}
	}
}