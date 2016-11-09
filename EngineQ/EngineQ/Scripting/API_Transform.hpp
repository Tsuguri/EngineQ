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
			static void API_GetParent(const Object& transformBase, MonoObject*& parent);
			static void API_SetParent(Object& transformBase, MonoObject*& parent);

			static void API_GetPosition(const Object& transformBase, Math::Vector3& position);
			static void API_SetPosition(Object& transformBase, const Math::Vector3& position);

			static void API_GetGlobalPosition(Object& transformBase, Math::Vector3& position);
			static void API_SetGlobalPosition(Object& transformBase, const Math::Vector3& position);

			static void API_GetScale(const Object& transformBase, Math::Vector3& scale);
			static void API_SetScale(Object& transformBase, const Math::Vector3& scale);

			static void API_GetRotation(const Object& transformBase, Math::Quaternion& rotation);
			static void API_SetRotation(Object& transformBase, const Math::Quaternion& rotation);

			static void API_GetGlobalRotation(Object& transformBase, Math::Quaternion& rotation);
			static void API_SetGlobalRotation(Object& transformBase, const Math::Quaternion& rotation);

			static void API_GetLocalMatrix(Object& transformBase, Math::Matrix4& matrix);
			static void API_GetLocalMatrixInverse(Object& transformBase, Math::Matrix4& matrix);

			static void API_GetGlobalMatrix(Object& transformBase, Math::Matrix4& matrix);
			static void API_GetGlobalMatrixInverse(Object& transformBase, Math::Matrix4& matrix);

			static void API_GetChildCount(const Object& transformBase, std::int32_t& count);
			static void API_GetChild(const Object& transformBase, std::int32_t index, MonoObject*& child);

			static void API_Register(ScriptEngine& scriptEngine);
		};
	}
}

#endif // !ENGINEQ_SCRIPTING_API_TRANSFORM_HPP
