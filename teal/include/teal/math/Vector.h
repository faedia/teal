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
		class Vector;

		template<typename T>
		class Vector<T, 4>
		{
		public:
			union
			{
				struct { T x, y, z, w; };
				struct { T r, g, b, a; };
				T data[4];
			};
		};

		template<typename T>
		class Vector<T, 3>
		{
		public:
			union
			{
				struct { T x, y, z; };
				struct { T r, g, b; };
				T data[3];
			};
		};
	}
}