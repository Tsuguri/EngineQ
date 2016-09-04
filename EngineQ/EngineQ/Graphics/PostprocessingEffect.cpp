#include "PostprocessingEffect.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		PostprocessingEffect::PostprocessingEffect(std::shared_ptr<Shader> shader) : shader(shader)
		{

		}

		void PostprocessingEffect::Activate()
		{
			shader->Activate();
		}
	}
}