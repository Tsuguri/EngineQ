#ifndef ENGINEQ_TRANSFORM_HPP
#define ENGINEQ_TRANSFORM_HPP

#include <vector>

#include "Types.hpp"

#include "Component.hpp"

#include "../Math/Vector3.hpp"
#include "../Math/Matrix4.hpp"
#include "../Math/Quaternion.hpp"

namespace EngineQ
{
	class Transform final : public Component
	{
		friend class Entity;

	public:
		typedef std::vector<Transform*>::const_iterator const_iterator;

		const_iterator begin() const;
		const_iterator end() const;


	private:
		Transform* parent = nullptr;
		std::vector<Transform*> children;

		Math::Vector3 position = Math::Vector3::GetZero();
		Math::Vector3 scale = Math::Vector3::GetOne();
		Math::Quaternion rotation = Math::Quaternion::GetIdentity();

		Math::Matrix4 localMatrix = Math::Matrix4::GetIdentity();
		Math::Matrix4 globalMatrix = Math::Matrix4::GetIdentity();

		Math::Matrix4 localMatrixInverse = Math::Matrix4::GetIdentity();
		Math::Matrix4 globalMatrixInverse = Math::Matrix4::GetIdentity();

		bool localMatrixChanged = false;
		bool globalMatrixChanged = false;
		bool localMatrixInverseChanged = false;
		bool globalMatrixInverseChanged = false;

		Transform(Scripting::ScriptEngine& scriptEngine, Entity& entity);

		void VoidLocalMatrix();
		void VoidGlobalMatrix();

	public:
	#pragma region Serialization

		Transform(Serialization::Deserializer& deserialzier);
		virtual void Serialize(Serialization::Serializer& serializer) const override;

	#pragma endregion

		virtual ~Transform();

		virtual ComponentType GetType() const override;

		void SetParent(Transform* parent);
		Transform* GetParent() const;

		std::size_t GetChildCount() const;
		Transform* GetChild(std::size_t child) const;

		void SetPosition(const Math::Vector3& position);
		Math::Vector3 GetPosition() const;

		void SetScale(const Math::Vector3& scale);
		Math::Vector3 GetScale() const;

		void SetRotation(const Math::Quaternion& rotation);
		Math::Quaternion GetRotation() const;

		Math::Matrix4 GetGlobalMatrix();
		Math::Matrix4 GetLocalMatrix();

		Math::Matrix4 GetGlobalMatrixInverse();
		Math::Matrix4 GetLocalMatrixInverse();
	};
}

#endif // !ENGINEQ_TRANSFORM_HPP