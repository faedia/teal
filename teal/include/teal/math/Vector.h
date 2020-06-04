#pragma once

#include <array>


/*******************************************************
*** NOTE: This is a temporary vector class, will be 
*** be optimised with simd later
*******************************************************/


namespace Teal
{
	namespace Math
	{
		template<typename T, unsigned int S>
		class Vector
		{
		public:
			std::array<T, S> data;
			Vector(const T d[S])
			{
				for (int i = 0; i < S; ++i)
					data[i] = d[i];
			}

			Vector(const std::array<T, S>& d)
			{
				data = d;
			}

			Vector(std::array<T, S>&& d)
			{
				data = std::move(d);
			}

			Vector<T, S> dot(Vector<T, S> const& a, Vector<T, S> const& b)
			{
				return a;
			}
		};
	}
}