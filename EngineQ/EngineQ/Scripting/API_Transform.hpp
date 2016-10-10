#ifndef ENGINEQ_SCRIPTING_API_TRANSFORM_HPP
#define ENGINEQ_SCRIPTING_API_TRANSFORM_HPP

#include "Types.hpp"
#include "../Math/Types.hpp"
#include "../Objects/Types.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		class API_Transform
		{
		public:
			static void API_GetParent(const Transform& transform, MonoObject*& parent);
			static void API_SetParent(Transform& transform, MonoObject*& parent);

			static void API_GetPosition(const Transform& transform, Math::Vector3& position);
			static void API_SetPosition(Transform& transform, const Math::Vector3& position);

			static void API_GetScale(const Transform& transform, Math::Vector3& scale);
			static void API_SetScale(Transform& transform, const Math::Vector3& scale);

			static void API_GetRotation(const Transform& transform, Math::Quaternion& rotation);
			static void API_SetRotation(Transform& transform, const Math::Quaternion& rotation);

			static void API_GetLocalMatrix(Transform& transform, Math::Matrix4& matrix);
			static void API_GetGlobalMatrix(Transform& transform, Math::Matrix4& matrix);

			static void API_GetChildCount(Transform& transform, std::int32_t& count);
			static void API_GetChild(Transform& transform, std::int32_t index, MonoObject*& child);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_TRANSFORM_HPP
