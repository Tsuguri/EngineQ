#ifndef ENGINEQ_MATH_UTILS_HPP
#define ENGINEQ_MATH_UTILS_HPP
#include "Math/Types.hpp"

namespace EngineQ
{
	namespace Math
	{

		class Utils
		{
		public:
			static Real DegToRad(Real deg);
			static constexpr Real PI= 3.1415926536;
		};

	}
}
#endif