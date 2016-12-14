#include "ShaderPass.hpp"

#include "Camera.hpp"
#include "Framebuffer.hpp"

#include "ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		InputConfiguration::InputConfiguration(GLuint texture, std::string name) :
			Texture{ texture }, Name{ name }
		{
		}

		ShaderPass::ShaderPass(Resources::Resource<Shader> shader) :
			shader{ shader }
		{
		}

		void ShaderPass::BindTextures()
		{
			int i = 0;
			for (auto& inputTexture : inputTextures)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, inputTexture.Texture);
				if (inputTexture.Name != "")
				{
					Utilities::Nullable<UniformLocation> location = shader->TryGetUniformLocation(inputTexture.Name.c_str());
					if (location != nullval)
						shader->Bind(*location, i);
				}
				i++;
			}
		}

		void ShaderPass::UnbindTextures()
		{
			for (int j=0;j<inputTextures.size();j++)
			{
				glActiveTexture(GL_TEXTURE0 + j);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void ShaderPass::BindTargetBuffer() const
		{
			if (framebuffer == nullptr)
				Framebuffer::BindDefault();
			else
				framebuffer->Bind();
		}

		void ShaderPass::SetTargetBuffer(std::unique_ptr<Framebuffer>&&  buffer)
		{
			framebuffer = std::move(buffer);
		}

		void ShaderPass::AddInput(const InputConfiguration& input)
		{
			inputTextures.push_back(input);
		}

		void ShaderPass::Activate(Camera* cam, float time) const
		{
			shader->Activate();
			auto tmp = shader->TryGetUniformLocation("cameraPosition");
			if (tmp != nullval)
				shader->Bind(*tmp, cam->GetPosition());
			tmp = shader->TryGetUniformLocation("time");
			if (tmp != nullval)
				shader->Bind(*tmp, time);
		}
	}
}