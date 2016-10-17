#include "ShaderPass.hpp"

#include "../Objects/Camera.hpp"
#include "../Objects/Entity.hpp"
#include "../Objects/Transform.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		// TODO
		GLenum ShaderPass::textureLocations[10] = {
			GL_TEXTURE0,
			GL_TEXTURE1,
			GL_TEXTURE2,
			GL_TEXTURE3,
			GL_TEXTURE4,
			GL_TEXTURE5,
			GL_TEXTURE6,
			GL_TEXTURE7,
			GL_TEXTURE8,
			GL_TEXTURE9
		};



		InputConfiguration::InputConfiguration(GLuint position, GLuint texture, std::string name) : 
			Position{ position }, Texture{ texture }, Name{ name }
		{
		}

		ShaderPass::ShaderPass(Resources::Resource<Shader> shader) : 
			shader{ shader }
		{
		}

		void ShaderPass::BindTextures()
		{
			Utilities::Nullable<UniformLocation> tmp;
			int j = 0;
			for(auto& inputTexture : inputTextures)
			{
				glActiveTexture(GL_TEXTURE0+inputTexture.Position);
				glBindTexture(GL_TEXTURE_2D, inputTexture.Texture);
				if(inputTexture.Name!="")
				{
					tmp = shader->TryGetUniformLocation(inputTexture.Name.c_str());
					if(tmp!=nullval)
					shader->Bind(*tmp, j);
				}
				j++;
			}
		}

		void ShaderPass::UnbindTextures()
		{
			for(auto& i : inputTextures)
			{
				glActiveTexture(GL_TEXTURE0+i.Position);
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

		void ShaderPass::Activate(Camera* cam,float time) const
		{
			shader->Activate();
			auto tmp = shader->TryGetUniformLocation("cameraPosition");
			if (tmp != nullval)
				shader->Bind(*tmp, cam->GetEntity().GetTransform().GetPosition());
			tmp = shader->TryGetUniformLocation("time");
			if (tmp != nullval)
				shader->Bind(*tmp, time);
		}
	}
}