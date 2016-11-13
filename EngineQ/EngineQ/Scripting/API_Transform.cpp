#include "API_Transform.hpp"

#include "ScriptEngine.hpp"

#include "../Objects/Transform.hpp"
#include <Math/Vector3.hpp>

namespace EngineQ
{
	namespace Scripting
	{
		void API_Transform::API_GetParent(const Object& transformBase, MonoObject*& parent)
		{
			auto& transform = static_cast<const Transform&>(transformBase);

			Transform* par = transform.GetParent();
			if (par == nullptr)
			{
				parent = nullptr;
				return;
			}

			parent = par->GetManagedObject();
		}

		void API_Transform::API_SetParent(Object& transformBase, MonoObject*& parent)
		{
			auto& transform = static_cast<Transform&>(transformBase);
			
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

		void API_Transform::API_GetPosition(const Object& transformBase, Math::Vector3& position)
		{
			auto& transform = static_cast<const Transform&>(transformBase);
			
			position = transform.GetPosition();
		}

		void API_Transform::API_SetPosition(Object& transformBase, const Math::Vector3& position)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			transform.SetPosition(position);
		}

		void API_Transform::API_GetGlobalPosition(Object& transformBase, Math::Vector3& position)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			position = transform.GetGlobalPosition();
		}

		void API_Transform::API_SetGlobalPosition(Object& transformBase, const Math::Vector3& position)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			transform.SetGlobalPosition(position);
		}

		void API_Transform::API_GetScale(const Object& transformBase, Math::Vector3& scale)
		{
			auto& transform = static_cast<const Transform&>(transformBase);

			scale = transform.GetScale();
		}

		void API_Transform::API_SetScale(Object& transformBase, const Math::Vector3& scale)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			transform.SetScale(scale);
		}

		void API_Transform::API_GetRotation(const Object& transformBase, Math::Quaternion& rotation)
		{
			auto& transform = static_cast<const Transform&>(transformBase);

			rotation = transform.GetRotation();
		}

		void API_Transform::API_SetRotation(Object& transformBase, const Math::Quaternion& rotation)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			transform.SetRotation(rotation);
		}

		void API_Transform::API_GetGlobalRotation(Object& transformBase, Math::Quaternion& rotation)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			rotation = transform.GetGlobalRotation();
		}

		void API_Transform::API_SetGlobalRotation(Object& transformBase, const Math::Quaternion& rotation)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			transform.SetGlobalRotation(rotation);
		}

		void API_Transform::API_GetLocalMatrix(Object& transformBase, Math::Matrix4& matrix)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			matrix = transform.GetLocalMatrix();
		}

		void API_Transform::API_GetLocalMatrixInverse(Object& transformBase, Math::Matrix4& matrix)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			matrix = transform.GetLocalMatrixInverse();
		}

		void API_Transform::API_GetGlobalMatrix(Object& transformBase, Math::Matrix4& matrix)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			matrix = transform.GetGlobalMatrix();
		}

		void API_Transform::API_GetGlobalMatrixInverse(Object& transformBase, Math::Matrix4& matrix)
		{
			auto& transform = static_cast<Transform&>(transformBase);

			matrix = transform.GetGlobalMatrixInverse();
		}

		void API_Transform::API_GetChildCount(const Object& transformBase, std::int32_t & count)
		{
			auto& transform = static_cast<const Transform&>(transformBase);

			count = static_cast<std::int32_t>(transform.GetChildCount());
		}

		void API_Transform::API_GetChild(const Object& transformBase, std::int32_t index, MonoObject*& child)
		{
			auto& transform = static_cast<const Transform&>(transformBase);

			if (index < 0 || static_cast<std::size_t>(index) >= transform.GetChildCount())
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
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetGlobalPosition", API_GetGlobalPosition);
			scriptEngine.API_Register("EngineQ.Transform::API_SetGlobalPosition", API_SetGlobalPosition);
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetScale", API_GetScale);
			scriptEngine.API_Register("EngineQ.Transform::API_SetScale", API_SetScale);
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetRotation", API_GetRotation);
			scriptEngine.API_Register("EngineQ.Transform::API_SetRotation", API_SetRotation);
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetGlobalRotation", API_GetGlobalRotation);
			scriptEngine.API_Register("EngineQ.Transform::API_SetGlobalRotation", API_SetGlobalRotation);
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetLocalMatrix", API_GetLocalMatrix);
			scriptEngine.API_Register("EngineQ.Transform::API_GetLocalMatrixInverse", API_GetLocalMatrixInverse);
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetGlobalMatrix", API_GetGlobalMatrix);
			scriptEngine.API_Register("EngineQ.Transform::API_GetGlobalMatrixInverse", API_GetGlobalMatrixInverse);
			
			scriptEngine.API_Register("EngineQ.Transform::API_GetChildCount", API_GetChildCount);
			scriptEngine.API_Register("EngineQ.Transform::API_GetChild", API_GetChild);
		}
	}
}