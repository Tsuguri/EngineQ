#include "Transform.hpp"

#include <algorithm>

#include "../Scripting/ScriptEngine.hpp"
#include "../Serialization/Serializer.hpp"
#include "../Serialization/Deserializer.hpp"
#include "../Serialization/SerializationRules.hpp"

namespace EngineQ
{
	Transform::const_iterator Transform::begin() const
	{
		return children.begin();
	}

	Transform::const_iterator Transform::end() const
	{
		return children.end();
	}

#pragma region Serialization

	Transform::Transform(Serialization::Deserializer& deserialzier) :
		Component{ deserialzier },
		parent{ deserialzier.GetReference<Transform>("parent") },
		children{ deserialzier.GetValue<std::vector<Transform*>>("children") },
		position{ deserialzier.GetValue<Math::Vector3>("position") },
		scale{ deserialzier.GetValue<Math::Vector3>("scale") },
		rotation{ deserialzier.GetValue<Math::Quaternion>("rotation") },
		localMatrix{ deserialzier.GetValue<Math::Matrix4>("localMatrix") },
		globalMatrix{ deserialzier.GetValue<Math::Matrix4>("globalMatrix") },
		localMatrixInverse{ deserialzier.GetValue<Math::Matrix4>("localMatrixInverse") },
		globalMatrixInverse{ deserialzier.GetValue<Math::Matrix4>("globalMatrixInverse") },
		localMatrixChanged{ deserialzier.GetValue<bool>("localMatrixChanged") },
		globalMatrixChanged{ deserialzier.GetValue<bool>("globalMatrixChanged") },
		localMatrixInverseChanged{ deserialzier.GetValue<bool>("localMatrixInverseChanged") },
		globalMatrixInverseChanged{ deserialzier.GetValue<bool>("globalMatrixInverseChanged") }
	{
	}

	void Transform::Serialize(Serialization::Serializer& serializer) const
	{
		Component::Serialize(serializer);
		serializer.StoreReference("parent", parent);
		serializer.StoreValue("children", &children);
		serializer.StoreValue("position", &position);
		serializer.StoreValue("scale", &scale);
		serializer.StoreValue("rotation", &rotation);
		serializer.StoreValue("localMatrix", &localMatrix);
		serializer.StoreValue("globalMatrix", &globalMatrix);
		serializer.StoreValue("localMatrixInverse", &localMatrixInverse);
		serializer.StoreValue("globalMatrixInverse", &globalMatrixInverse);
		serializer.StoreValue("localMatrixChanged", &localMatrixChanged);
		serializer.StoreValue("globalMatrixChanged", &globalMatrixChanged);
		serializer.StoreValue("localMatrixInverseChanged", &localMatrixInverseChanged);
		serializer.StoreValue("globalMatrixInverseChanged", &globalMatrixInverseChanged);
	}

#pragma endregion

	Transform::Transform(Scripting::ScriptEngine& scriptEngine, Entity& entity) :
		Component{ scriptEngine, scriptEngine.GetTransformClass(), entity },
		children{}
	{
		// TMP
		scriptEngine.InvokeConstructor(GetManagedObject());
	}

	Transform::~Transform()
	{
		for (auto child : this->children)
		{
			child->parent = nullptr;
			child->VoidGlobalMatrix();
		}
	}

	ComponentType Transform::GetType() const
	{
		return ComponentType::Transform;
	}

	void Transform::SetParent(Transform* parent)
	{
		if (this->parent == parent)
			return;

		if (this == parent)
			throw std::runtime_error("Cannot set parent to self");

		if (this->parent != nullptr)
		{
			std::vector<Transform*>& children = this->parent->children;
			children.erase(std::remove(children.begin(), children.end(), this), children.end());
		}

		this->parent = parent;

		if (this->parent != nullptr)
			this->parent->children.push_back(this);

		VoidGlobalMatrix();
	}

	void Transform::VoidGlobalMatrix()
	{
		if (globalMatrixChanged)
			return;

		globalMatrixChanged = true;
		globalMatrixInverseChanged = true;
		for (Transform* child : children)
			child->VoidGlobalMatrix();
	}

	void Transform::VoidLocalMatrix()
	{
		localMatrixChanged = true;
		localMatrixInverseChanged = true;
		VoidGlobalMatrix();
	}

	Transform* Transform::GetParent() const
	{
		return this->parent;
	}

	void Transform::SetPosition(const Math::Vector3& position)
	{
		this->position = position;
		VoidLocalMatrix();
	}

	Math::Vector3 Transform::GetPosition() const
	{
		return this->position;
	}

	void Transform::SetScale(const Math::Vector3& scale)
	{
		this->scale = scale;
		VoidLocalMatrix();
	}

	Math::Vector3 Transform::GetScale() const
	{
		return this->scale;
	}

	void Transform::SetRotation(const Math::Quaternion& rotation)
	{
		this->rotation = rotation;
		VoidLocalMatrix();
	}

	Math::Quaternion Transform::GetRotation() const
	{
		return this->rotation;
	}

	std::size_t Transform::GetChildCount() const
	{
		return children.size();
	}

	Transform* Transform::GetChild(std::size_t child) const
	{
		return children[child];
	}

	Math::Matrix4 Transform::GetGlobalMatrix()
	{
		if (globalMatrixChanged)
		{
			if (parent != nullptr)
				globalMatrix = parent->GetGlobalMatrix() * this->GetLocalMatrix();
			else
				globalMatrix = this->GetLocalMatrix();

			globalMatrixChanged = false;
		}

		return globalMatrix;
	}

	Math::Matrix4 Transform::GetLocalMatrix()
	{
		if (localMatrixChanged)
		{
			localMatrix = Math::Matrix4::CreateTranslation(position) * Math::Matrix4::CreateRotation(rotation) * Math::Matrix4::CreateScale(scale);

			localMatrixChanged = false;
		}

		return localMatrix;
	}

	Math::Matrix4 Transform::GetGlobalMatrixInverse()
	{
		if (globalMatrixInverseChanged)
		{
			globalMatrixInverse = GetGlobalMatrix().GetInversed();

			globalMatrixInverseChanged = false;
		}

		return globalMatrixInverse;
	}

	Math::Matrix4 Transform::GetLocalMatrixInverse()
	{
		if (localMatrixInverseChanged)
		{
			localMatrixInverse = GetLocalMatrix().GetInversed();

			localMatrixInverseChanged = false;
		}

		return localMatrixInverse;
	}
}