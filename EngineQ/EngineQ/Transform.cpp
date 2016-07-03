#include "Transform.hpp"

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

	Transform::Transform(Scripting::ScriptEngine& scriptEngine, Entity& entity) :
		Component{ scriptEngine, scriptEngine.GetTransformClass(), entity },
		parent{ nullptr },
		children{},
		position{ Vector3::GetZero() },
		scale{ Vector3::GetOne() },
		rotation{ Quaternion::GetIdentity() },
		localMatrix{ Matrix4::GetIdentity() },
		globalMatrix{ Matrix4::GetIdentity() },
		globalMatrixChanged{ false },
		localMatrixChanged{ false }
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
		for (Transform* child : children)
			child->VoidGlobalMatrix();
	}

	void Transform::VoidLocalMatrix()
	{
		localMatrixChanged = true;
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
}