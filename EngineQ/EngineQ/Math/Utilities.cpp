#include "Utilities.hpp"

namespace EngineQ
{
	namespace Math
	{
		template<typename TType>
		constexpr TType PI = static_cast<TType>(3.1415926535897932384626433832795028841971);

		float DegToRad(float degrees)
		{
			return degrees / 180.0f * PI<float>;
		}

		double DegToRad(double degrees)
		{
			return degrees / 180.0 * PI<double>;
		}
	}
}