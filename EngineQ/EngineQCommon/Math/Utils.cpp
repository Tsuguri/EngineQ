#include "Utils.hpp"

#include <cmath>

namespace EngineQ
{
	namespace Math
	{
		float Utils::DegToRad(float degrees)
		{
			return degrees / 180.0f * PI<float>;
		}

		double Utils::DegToRad(double degrees)
		{
			return degrees / 180.0 * PI<double>;
		}

		float Utils::RadToDeg(float radians)
		{
			return radians / PI<float> * 180.0f;
		}

		double Utils::RadToDeg(double radians)
		{
			return radians / PI<double> * 180.0;
		}

		bool Utils::EpsComp(float value1, float value2)
		{
			return std::abs(value1 - value2) < EPS<float>;
		}

		bool Utils::EpsComp(double value1, double value2)
		{
			return std::abs(value1 - value2) < EPS<double>;
		}
	}
}