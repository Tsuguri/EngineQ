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
			static constexpr TType Eps = static_cast<TType>(0.00001);

			static constexpr inline float DegToRad(float degrees)
			{
				return degrees / 180.0f * PI<float>;
			}

			static constexpr inline double DegToRad(double degrees)
			{
				return degrees / 180.0 * PI<double>;
			}

			static constexpr inline float RadToDeg(float radians)
			{
				return radians / PI<float> * 180.0f;
			}

			static constexpr inline double RadToDeg(double radians)
			{
				return radians / PI<double> * 180.0;
			}
						
			static constexpr inline float Abs(float value)
			{
				return value <= 0.0f ? -value : value;
			}

			static constexpr inline double Abs(double value)
			{
				return value <= 0.0 ? -value : value;
			}

			template<typename TType>
			static constexpr inline bool EpsEqual(TType value1, TType value2)
			{
				return value1 == value2;
			}

			static constexpr inline bool EpsEqual(float value1, float value2)
			{
				return Abs(value1 - value2) < Eps<float>;
			}

			static constexpr inline bool EpsEqual(double value1, double value2)
			{
				return Abs(value1 - value2) < Eps<double>;
			}

			template<typename TType>
			static constexpr inline bool EpsNotEqual(TType value1, TType value2)
			{
				return value1 != value2;
			}

			static constexpr inline bool EpsNotEqual(float value1, float value2)
			{
				return Abs(value1 - value2) >= Eps<float>;
			}

			static constexpr inline bool EpsNotEqual(double value1, double value2)
			{
				return Abs(value1 - value2) >= Eps<double>;
			}
		};
	}
}

#endif // !ENGINEQ_MATH_UTILS_HPP
