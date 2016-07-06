#ifndef ENGINEQ_SCRIPTING_API_TRANSFORM_H
#define ENGINEQ_SCRIPTING_API_TRANSFORM_H

#include "ScriptEngine.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Matrix4.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		using namespace EngineQ::Math;

		class API_Transform
		{
		public:
			static void API_GetParent(const Transform& transform, MonoObject*& parent);
			static void API_SetParent(Transform& transform, MonoObject*& parent);

			static void API_GetPosition(const Transform& transform, Vector3& position);
			static void API_SetPosition(Transform& transform, const Vector3& position);

			static void API_GetScale(const Transform& transform, Vector3& scale);
			static void API_SetScale(Transform& transform, const Vector3& scale);

			static void API_GetRotation(const Transform& transform, Quaternion& rotation);
			static void API_SetRotation(Transform& transform, const Quaternion& rotation);

			static void API_GetLocalMatrix(Transform& transform, Matrix4& matrix);
			static void API_GetGlobalMatrix(Transform& transform, Matrix4& matrix);

			static void API_GetChildCount(Transform& transform, std::int32_t & count);
			static void API_GetChild(Transform& transform, std::int32_t  index, MonoObject*& child);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_TRANSFORM_H