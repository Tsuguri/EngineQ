#ifndef ENGINEQ_TRANSFORM_HPP
#define ENGINEQ_TRANSFORM_HPP

#include <vector>
#include <algorithm>

#include "Component.hpp"

#include "Math/Vector3.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Matrix4.hpp"

#include "Scripting/ScriptEngine.hpp"

namespace EngineQ
{
	using namespace Math;

	class Entity;

	class Transform final : public Component
	{
		friend class Entity;

	public:
		typedef std::vector<Transform*>::const_iterator const_iterator;

		const_iterator begin() const;
		const_iterator end() const;


	private:
		Transform* parent;
		std::vector<Transform*> children;

		Vector3 position;
		Vector3 scale;
		Quaternion rotation;

		Matrix4 globalMatrix;
		Matrix4 localMatrix;

		Matrix4 globalMatrixInverse;
		Matrix4 localMatrixInverse;

		bool globalMatrixChanged;
		bool localMatrixChanged;
		bool globalMatrixInverseChanged;
		bool localMatrixInverseChanged;

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

		void SetPosition(const Vector3& position);
		Vector3 GetPosition() const;

		void SetScale(const Vector3& scale);
		Vector3 GetScale() const;

		void SetRotation(const Quaternion& rotation);
		Quaternion GetRotation() const;

		Matrix4 GetGlobalMatrix();
		Matrix4 GetLocalMatrix();

		Matrix4 GetGlobalMatrixInverse();
		Matrix4 GetLocalMatrixInverse();
	};
}

#endif // !ENGINEQ_TRANSFORM_HPP
