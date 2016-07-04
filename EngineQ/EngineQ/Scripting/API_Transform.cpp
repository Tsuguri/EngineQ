#include "API_Transform.hpp"

#include "../Transform.hpp"
#include "../Entity.hpp"

namespace EngineQ
{
	namespace Scripting
	{
		void API_Transform::API_GetParent(const Transform& transform, MonoObject*& parent)
		{
			Transform* par = transform.GetParent();
			if (par == nullptr)
			{
				parent = nullptr;
				return;
			}

			parent = par->GetManagedObject();
		}

		void API_Transform::API_SetParent(Transform& transform, MonoObject*& parent)
		{
			Transform* par = static_cast<Transform*>(transform.GetNativeObject(parent));
			try
			{
				transform.SetParent(par);
			}
			catch (std::exception& e)
			{
				transform.GetScriptEngine().Throw_ArgumentException("Parent", e.what());
				return;
			}
		}

		void API_Transform::API_GetPosition(const Transform& transform, Vector3& position)
		{
			position = transform.GetPosition();
		}

		void API_Transform::API_SetPosition(Transform& transform, const Vector3& position)
		{
			transform.SetPosition(position);
		}

		void API_Transform::API_GetScale(const Transform& transform, Vector3& scale)
		{
			scale = transform.GetScale();
		}

		void API_Transform::API_SetScale(Transform& transform, const Vector3& scale)
		{
			transform.SetScale(scale);
		}

		void API_Transform::API_GetRotation(const Transform& transform, Quaternion& rotation)
		{
			rotation = transform.GetRotation();
		}

		void API_Transform::API_SetRotation(Transform& transform, const Quaternion& rotation)
		{
			transform.SetRotation(rotation);
		}

		void API_Transform::API_GetLocalMatrix(Transform& transform, Matrix4& matrix)
		{
			matrix = transform.GetLocalMatrix();
		}

		void API_Transform::API_GetGlobalMatrix(Transform& transform, Matrix4& matrix)
		{
			matrix = transform.GetGlobalMatrix();
		}

		void API_Transform::API_GetChildCount(Transform& transform, std::int32_t & count)
		{
			count = static_cast<std::int32_t>(transform.GetChildCount());
		}

		void API_Transform::API_GetChild(Transform& transform, std::int32_t index, MonoObject*& child)
		{
			if (index < 0 || index >= transform.GetChildCount())
			{
				transform.GetScriptEngine().Throw_IndexOutOfRangeException();
				return;
			}

			child = transform.GetChild(index)->GetManagedObject();
		}

		void API_Transform::API_Register(ScriptEngine& scriptEngine)
		{
			scriptEngine.API_Register("EngineQ.Transform::API_GetParent", API_GetParent);
			scriptEngine.API_Register("EngineQ.Transform::API_SetParent", API_SetParent);
			scriptEngine.API_Register("EngineQ.Transform::API_GetPosition", API_GetPosition);
			scriptEngine.API_Register("EngineQ.Transform::API_SetPosition", API_SetPosition);
			scriptEngine.API_Register("EngineQ.Transform::API_GetScale", API_GetScale);
			scriptEngine.API_Register("EngineQ.Transform::API_SetScale", API_SetScale);
			scriptEngine.API_Register("EngineQ.Transform::API_GetRotation", API_GetRotation);
			scriptEngine.API_Register("EngineQ.Transform::API_SetRotation", API_SetRotation);
			scriptEngine.API_Register("EngineQ.Transform::API_GetLocalMatrix", API_GetLocalMatrix);
			scriptEngine.API_Register("EngineQ.Transform::API_GetGlobalMatrix", API_GetGlobalMatrix);
			scriptEngine.API_Register("EngineQ.Transform::API_GetChildCount", API_GetChildCount);
			scriptEngine.API_Register("EngineQ.Transform::API_GetChild", API_GetChild);
		}
	}
}