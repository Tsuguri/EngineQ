#include "Transform.hpp"

#include "Serialization/SerializationRules.hpp"

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
		Component{deserialzier},
		parent{ deserialzier.GetReference<Transform>("parent") },
		children{ deserialzier.GetValue<std::vector<Transform*>>("children")},
		position{ deserialzier.GetValue<Vector3>("position") },
		scale{ deserialzier.GetValue<Vector3>("scale") },
		rotation{ deserialzier.GetValue<Quaternion>("rotation") },
		localMatrix{ deserialzier.GetValue<Matrix4>("localMatrix") },
		globalMatrix{ deserialzier.GetValue<Matrix4>("globalMatrix") },
		localMatrixInverse{ deserialzier.GetValue<Matrix4>("localMatrixInverse") },
		globalMatrixInverse{ deserialzier.GetValue<Matrix4>("globalMatrixInverse") },
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
		parent{ nullptr },
		children{},
		position{ Vector3::GetZero() },
		scale{ Vector3::GetOne() },
		rotation{ Quaternion::GetIdentity() },
		localMatrix{ Matrix4::GetIdentity() },
		globalMatrix{ Matrix4::GetIdentity() },
		localMatrixInverse{ Matrix4::GetIdentity() },
		globalMatrixInverse{ Matrix4::GetIdentity() },
		localMatrixChanged{ false },
		globalMatrixChanged{ false },
		localMatrixInverseChanged{ false },
		globalMatrixInverseChanged{ false }
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
			std::vector<Transform*>& v = this->parent->children;
			v.erase(std::remove(v.begin(), v.end(), this), v.end());
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

	void Transform::SetPosition(const Vector3& position)
	{
		this->position = position;
		VoidLocalMatrix();
	}

	Vector3 Transform::GetPosition() const
	{
		return this->position;
	}

	void Transform::SetScale(const Vector3& scale)
	{
		this->scale = scale;
		VoidLocalMatrix();
	}

	Vector3 Transform::GetScale() const
	{
		return this->scale;
	}

	void Transform::SetRotation(const Quaternion& rotation)
	{
		this->rotation = rotation;
		VoidLocalMatrix();
	}

	Quaternion Transform::GetRotation() const
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

	Matrix4 Transform::GetGlobalMatrix()
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

	Matrix4 Transform::GetLocalMatrix()
	{
		if (localMatrixChanged)
		{
			localMatrix = Matrix4::CreateTranslation(position) * Matrix4::CreateRotation(rotation) * Matrix4::CreateScale(scale);

			localMatrixChanged = false;
		}

		return localMatrix;
	}

	Matrix4 Transform::GetGlobalMatrixInverse()
	{
		if (globalMatrixInverseChanged)
		{
			globalMatrixInverse = GetGlobalMatrix().GetInversed();
			
			globalMatrixInverseChanged = false;
		}

		return globalMatrixInverse;
	}

	Matrix4 Transform::GetLocalMatrixInverse()
	{
		if (localMatrixInverseChanged)
		{
			localMatrixInverse = GetLocalMatrix().GetInversed();

			localMatrixInverseChanged = false;
		}

		return localMatrixInverse;
	}
}