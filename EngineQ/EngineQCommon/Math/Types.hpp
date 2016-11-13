#ifndef ENGINEQ_MATH_TYPES_HPP
#define ENGINEQ_MATH_TYPES_HPP

namespace EngineQ
{
	namespace Math
	{
		using Real = float;


		struct Matrix3;
		struct Matrix4;


		struct Quaternion;


		template<typename Type>
		struct Vector2_t;

		using Vector2i = Vector2_t<int>;
		using Vector2f = Vector2_t<float>;
		using Vector2d = Vector2_t<double>;

		using Vector2 = Vector2_t<Real>;


		template<typename Type>
		struct Vector3_t;

		typedef Vector3_t<int> Vector3i;
		typedef Vector3_t<float> Vector3f;
		typedef Vector3_t<double> Vector3d;

		typedef Vector3_t<Real> Vector3;


		template<typename Type>
		struct Vector4_t;

		using Vector4i = Vector4_t<int>;
		using Vector4f = Vector4_t<float>;
		using Vector4d = Vector4_t<double>;

		using Vector4 = Vector4_t<Real>;
	}
}

#endif // !ENGINEQ_MATH_TYPES_HPP
