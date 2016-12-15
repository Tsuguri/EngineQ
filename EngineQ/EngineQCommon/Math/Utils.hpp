#ifndef ENGINEQ_MATH_UTILS_HPP
#define ENGINEQ_MATH_UTILS_HPP

namespace EngineQ
{
	namespace Math
	{
		class Utils
		{
		public:
			template<typename TType>
			static constexpr TType PI = static_cast<TType>(3.1415926535897932384626433832795028841971);

			template<typename TType>
			static constexpr TType EPS = static_cast<TType>(0.00001);

			static float DegToRad(float degrees);
			static double DegToRad(double degrees);

			static float RadToDeg(float radians);
			static double RadToDeg(double radians);

			static bool EpsComp(float value1, float value2);
			static bool EpsComp(double value1, double value2);
		};
	}
}

#endif // !ENGINEQ_MATH_UTILS_HPP
