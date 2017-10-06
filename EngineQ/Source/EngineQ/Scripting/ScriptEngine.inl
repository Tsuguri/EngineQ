

namespace EngineQ
{
	namespace Scripting
	{
		template<typename TReturn, typename... TArgs>
		void ScriptEngine::API_Register(const char* name, TReturn(*function)(TArgs...))
		{
			this->API_Register(name, reinterpret_cast<const void*>(function));
		}

		template<typename TType>
		TType& ScriptEngine::GetValue(ScriptObject object) const
		{
			return *static_cast<TType*>(this->Unbox(object));
		}
	}
}