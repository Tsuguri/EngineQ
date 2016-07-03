#ifndef ENGINEQ_TRANSFORM_H
#define ENGINEQ_TRANSFORM_H

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

	/*
	class Trigger
	{
	private:
		bool set;

		

		std::vector<Trigger*> dependencies;

		void Register(Trigger* trigger)
		{
			dependencies.push_back(trigger);
		}

	public:
		Trigger(std::initializer_list<Trigger&> triggers)
			: set(false)
		{
			for (Trigger& trigger : triggers)
				trigger.Register(this);
		}

		void Set()
		{
			set = true;

			for (Trigger* dep : dependencies)
				dep->Set();
		}

		void Reset()
		{
			set = false;
		}

		bool IsSet()
		{
			return set;
		}
	};
	*/

	class Transform : public Component
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

		bool globalMatrixChanged;
		bool localMatrixChanged;

		Transform(Scripting::ScriptEngine& scriptEngine, Entity& entity);

		void VoidLocalMatrix();
		void VoidGlobalMatrix();

	public:
		void SetParent(Transform* parent);
		Transform* GetParent() const;

		int GetChildCount() const;
		Transform* GetChild(int child) const;

		void SetPosition(const Vector3& position);
		Vector3 GetPosition() const;

		void SetScale(const Vector3& scale);
		Vector3 GetScale() const;

		void SetRotation(const Quaternion& rotation);
		Quaternion GetRotation() const;

		Matrix4 GetGlobalMatrix();
		Matrix4 GetLocalMatrix();
	};
}

#endif // !ENGINEQ_TRANSFORM_H