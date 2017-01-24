namespace EngineQ
{
	template<typename Type>
	Type& Entity::AddComponent(bool enabled)
	{
		auto componentPtr = std::unique_ptr<Type>{ new Type{ this->scriptEngine, *this, enabled } };
		auto& component = *componentPtr;

		this->AddComponent(std::move(componentPtr));

		return component;
	}
}