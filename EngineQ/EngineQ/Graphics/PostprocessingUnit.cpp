#include "PostprocessingUnit.hpp"
#include "PostprocessingExceptions.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		int GetFramebufferNumber(RendererConfiguration* configuration, std::string name)
		{
			for (int i = configuration->Framebuffers.size()-1; i >= 0;i--)
			{
				if (configuration->Framebuffers[i].Name == name)
					return i;
			}
			return -1;
		}
		bool RenderingUnit::ValidateConfiguration(RendererConfiguration* configuration)
		{
			//Check naming 

			//if empty
			for (int i = configuration->Framebuffers.size()-1; i >=0 ;i--)
			{
				if (configuration->Framebuffers[i].Name.size() < 1)
					throw RendererConfigurationValidationException("Framebuffer name is empty");
			}

			//if duplicated
			for (int i = configuration->Framebuffers.size() - 1; i >= 0; i--)
			{
				for (int j = i - 1; j >= 0;j--)
				{
					if (configuration->Framebuffers[i].Name == configuration->Framebuffers[j].Name)
						throw RendererConfigurationValidationException("More than one framebuffer have the same name");
				}
			}

			//check if there are empty framebuffers
			for (int i = configuration->Framebuffers.size() - 1; i >= 0;i--)
			{
				if (configuration->Framebuffers[i].Textures.size() < 1)
					throw RendererConfigurationValidationException("Framebuffer without textures");
			}

			//check if effects use existing textures as input
			int temp;
			for (int i = configuration->Effects.size() - 1; i >= 0;i--)
			{
				for (int j = configuration->Effects[i].Input.size(); j >= 0;j--)
				{
					if ((temp = GetFramebufferNumber(configuration, configuration->Effects[i].Input[j].Framebuffer)) < 0 || configuration->Framebuffers[temp].Textures.size() < configuration->Effects[i].Input[j].TextureNumber)
						throw RendererConfigurationValidationException("Effect tries to use nonexistent texture"+ configuration->Effects[i].ShaderName);
				}
			}

			//todo: powtarzaj¹ce siê location w inpucie

		}

		void RenderingUnit::CreateFramebuffers(RendererConfiguration* configuration)
		{

		}

		void RenderingUnit::CreateEffects(RendererConfiguration* configuration)
		{

		}

		void RenderingUnit::BindFramebuffers(RendererConfiguration* configuration)
		{

		}

		RenderingUnit::RenderingUnit(RendererConfiguration* configuration)
		{
			ValidateConfiguration(configuration);

		}
	}
}
